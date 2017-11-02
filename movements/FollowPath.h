#ifndef FOLLOWPATH_H
#define FOLLOWPATH_H

#include "../assets/bezier.h"

#include <list>
#include <glm/glm.hpp>

class FollowPath: public Seek{
protected:
	//Holds the path to follow
	Bezier &path;

	//Holds the distance along the path to generate the
	//target. Can be negative if the character is to move
	//along the reverse direction.
	GLfloat pathOffset;

	//Holds the current position on the path
	GLfloat currentParam;

public:
	FollowPath(Kinematic &c, GLfloat ma, GLfloat po=0.1) 
		: Seek(c,*new Kinematic(),ma), pathOffset(po), path(*new Bezier()) {}
	FollowPath(Kinematic &c, Bezier &p, GLfloat ma, GLfloat po=0.1) 
		: Seek(c,*new Kinematic(),ma), pathOffset(po), path(p) {}

	glm::vec3 getCharacterPos(){ return character.position; }

	void setPath(std::list<glm::vec3> points){ path = {points}; }

	Bezier getPath(){ return path; }

	bool getSteering(SteeringOutput &steering){
		if (path.size < 1) return false;

		//Find the current position on the path
		currentParam = path.getParam(character.position);

		if (currentParam > 0.99) {
			path.size = 0;
			return false;
		}
		//Get the target position
		target.position = path.getPoint(currentParam + pathOffset);

		Seek::getSteering(steering);


		path.draw();
		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput steering;
	    if (getSteering(steering)) character.update(steering.linear,maxSpeed,deltaTime);
	    else character.velocity = {0.0,0.0,0.0}; //puede que no se deba hacer
	}
};

#endif