#ifndef SEEK_H
#define SEEK_H

class Seek: public Behavior{
protected:
	// Holds the Kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;
	// Holds the maximum acceleration of the character
	GLfloat maxAcceleration;

public:
	Seek(Kinematic &c, Kinematic &t, GLfloat ma) : character(c), target(t), maxAcceleration(ma){}

	bool getSteering(SteeringOutput &steering){
		// Get the direction to the target
		steering.linear = target.position - character.position;

		// Give full acceleration along this direction
		steering.linear = glm::normalize(steering.linear) * maxAcceleration;

		// Output the steering
		steering.angular = 0;

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput steering;
		getSteering(steering);
    	character.update(steering,maxSpeed,deltaTime);
	}
};

#endif