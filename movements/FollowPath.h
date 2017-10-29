#ifndef FOLLOWPATH_H
#define FOLLOWPATH_H

#include "../assets/bezier.h"

#include <list>
#include <glm/glm.hpp>

class FollowPath: public Seek{
protected:
	//Holds the path to follow
	Bezier path;

	//Holds the distance along the path to generate the
	//target. Can be negative if the character is to move
	//along the reverse direction.
	GLfloat pathOffset;

	//Holds the current position on the path
	GLfloat currentParam;

public:
	FollowPath(Kinematic &c, GLfloat ma, GLfloat po=0.1) : Seek(c,*new Kinematic(),ma), pathOffset(po) {}

	void setPath(std::list<glm::vec3> points){ path = {points}; }

	Bezier getPath(){ return path; }

	bool getSteering(SteeringOutput &steering){
		//Find the current position on the path
		currentParam = path.getParam(character.position);

		//Get the target position
		target.position = path.getPoint(currentParam + pathOffset);

		Seek::getSteering(steering);

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput steering;
	    getSteering(steering);
	    character.update(steering,maxSpeed,deltaTime);
	}
};

#endif