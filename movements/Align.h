/* 
    Andrea Centeno
    carnet USB: 10-10138
    sep-dic 2017
*/ 
#ifndef ALIGN_H
#define ALIGN_H

class Align: public Behavior{
protected:
	// Holds the Kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;
	// Holds the max angular acceleration and rotation
	// of the character
	GLfloat maxAngularAcceleration;
	GLfloat maxRotation; 

	// Holds the radius for beginning to slow down
	GLfloat slowRadius;

	// Holds the radius for arriving at the target
	GLfloat targetRadius;

	// Holds the time over which to achieve target speed
	GLfloat timeToTarget = 0.1;

public:
	//maxRotation, slowRadius, targetRadius to radians
	Align(Kinematic &c, Kinematic &t, GLfloat maa, GLfloat mr, GLfloat sr, GLfloat tr) : 
		character(c), target(t)
		,slowRadius(glm::radians(sr)), targetRadius(glm::radians(tr))
		,maxAngularAcceleration(maa), maxRotation(glm::radians(mr)){}

	bool getSteering(SteeringOutput &steering){
		GLfloat rotation,rotationSize,targetRotation,angularAcceleration;

		// Get the naive direction to the target
		rotation = target.orientation - character.orientation;

		// Map the result to the (-pi, pi) interval
		rotation = mapToRange(rotation);
		rotationSize = abs(rotation);

		// Check if we are there, return no steering
		if (rotationSize < targetRadius) return false;

		// If we are outside the slowRadius, then use
		// maximum rotation
		if (rotationSize > slowRadius){
			targetRotation = maxRotation;
		}
		else{ // Otherwise calculate a scaled rotation
			targetRotation = maxRotation * rotationSize / slowRadius;
		}

		// The final target rotation combines
		// speed (already in the variable) and direction
		targetRotation *= rotation / rotationSize;

		// Acceleration tries to get to the target rotation
		steering.angular = targetRotation - character.rotation;
		steering.angular /= timeToTarget;

		// Check if the acceleration is too great
		angularAcceleration = abs(steering.angular);
		if (angularAcceleration > maxAngularAcceleration){
			steering.angular /= angularAcceleration;
			steering.angular *= maxAngularAcceleration;
		}

		// Output the steering
		steering.linear = {0.0,0.0,0.0};

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput so;
    	if(getSteering(so)) character.update(so.angular,maxSpeed,deltaTime);
	}
};

#endif