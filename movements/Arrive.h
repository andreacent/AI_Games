#ifndef ARRIVE_H
#define ARRIVE_H

class Arrive: public Behavior{
protected:
	// Holds the Kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;
	// Holds the maximum acceleration of the character
	GLfloat maxAcceleration;
	GLfloat maxSpeed;

	// Holds the radius for arriving at the target
	GLfloat targetRadius;

	// Holds the radius for beginning to slow down
	GLfloat slowRadius;

	// Holds the time over which to achieve target speed
	GLfloat timeToTarget = 0.1;

public:
	Arrive(Kinematic &c, Kinematic &t, GLfloat tr, GLfloat sr, GLfloat ma, GLfloat ms) : 
		character(c), target(t), targetRadius(tr), slowRadius(sr), maxAcceleration(ma), maxSpeed(ms){}

	bool getSteering(SteeringOutput &steering){
		glm::vec3 direction,targetVelocity;
		GLfloat targetSpeed,targetDistance;

		// Get the direction to the target
		direction = target.position - character.position;
		targetDistance =glm::length(direction);

		// Check if we are there, return no steering
		if (targetDistance - targetRadius < -1E-9) return false;

		// If we are outside the slowRadius, then go max speed
		if (targetDistance - slowRadius > 1E-9){
			targetSpeed = maxSpeed;
		}
		else{// Otherwise calculate a scaled speed
			targetSpeed = maxSpeed * targetDistance / slowRadius;
		}

		// The target velocity combines speed and direction
		targetVelocity = glm::normalize(direction) * targetSpeed;

		// Acceleration tries to get to the target velocity
		steering.linear = targetVelocity - character.velocity;
		steering.linear /= timeToTarget;

		// Check if the acceleration is too fast
		if(glm::length(steering.linear) > maxAcceleration){
			steering.linear = glm::normalize(steering.linear) * maxAcceleration;
		}
		
		// Output the steering
		steering.angular = 0;

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	SteeringOutput so ;
    	if(getSteering(so)) character.update(so,maxSpeed,deltaTime);
	}
};

#endif