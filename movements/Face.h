#ifndef FACE_H
#define FACE_H

class Face: public Align{
public:
	Face(Kinematic &c, Kinematic &t, GLfloat sr, GLfloat tr, GLfloat maa, GLfloat mr) : Align(c, t, sr, tr, maa, mr) {}

	bool getSteering(SteeringOutput &steering){
		glm::vec3 direction;
		GLfloat lastOrientation;

		// 1. Calculate the target to delegate to align
		// Work out the direction to target
		direction = target.position - character.position;

		// Check for a zero direction, and make no change if so
		if (glm::length(direction) == 0.0) return false;

		lastOrientation = target.orientation;

		// Put the target together
		target.orientation = atan2(-direction.x, direction.z);//atan2(-direction.x, direction.y);

		// 2. Delegate to align
		Align::getSteering(steering);

		target.orientation = lastOrientation;

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput so;
	    if(getSteering(so)) character.update(so,maxSpeed,deltaTime);
	}
};

#endif