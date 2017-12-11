/* 
    Andrea Centeno
    carnet USB: 10-10138
    sep-dic 2017
*/
#ifndef OBSAVOIDANCE_H
#define OBSAVOIDANCE_H

#include <glm/gtx/intersect.hpp>
#include "../assets/Collision.h"
#include <iostream>

void drawRay(glm::vec3 position, glm::vec3 direction) {
    glPushMatrix();
        glTranslatef(position.x,position.y,position.z);
        glBegin(GL_LINES);
            glVertex3f(0.0,0.0, 0.0);
            glVertex3f(direction.x,direction.y, direction.z);
        glEnd();
    glPopMatrix();
}

class ObstacleAvoidance: public Seek{
protected:
	// Holds a collision detector
	CollisionDetector &collisionDetector;

	// Holds the minimum distance to a wall (i.e., how far
	// to avoid collision) should be greater than the
	// radius of the character.
	GLfloat avoidDistance;

	// Holds the distance to look ahead for a collision
	// (i.e., the length of the collision ray)
	GLfloat lookahead;

public:
	ObstacleAvoidance(Kinematic &c, GLfloat ma, CollisionDetector &cd, GLfloat ad, GLfloat l) 
		: Seek(c,*new Kinematic(),ma), collisionDetector(cd), avoidDistance(ad), lookahead(l){}

	bool getSteering(SteeringOutput &steering){
		glm::vec3 rayVector,rayVectorL,rayVectorR;
		Collision collision;

		//cout<<"evadir"<<endl;
		// 1. Calculate the target to delegate to seek

		// Calculate the collision ray vector
		rayVector = glm::normalize(character.velocity) * lookahead;

		GLfloat raySize = lookahead * 0.6;
		rayVectorL = glm::normalize(rotateVectorZ(character.velocity, glm::radians(-35.0))) * raySize;
		rayVectorR = glm::normalize(rotateVectorZ(character.velocity, glm::radians(35.0))) * raySize;
		
		// Find the collision
		if(!collisionDetector.getCollision(character.position,collision
											,rayVector, lookahead
											,rayVectorR, raySize
											,rayVectorL, raySize)){
			return false;
		}

		// Otherwise create a target
		target.position = collision.position + collision.normal * avoidDistance;

		//drawRay(character.position, rayVectorR);
		//drawRay(character.position, rayVectorL);
		//drawRay(character.position, rayVector);
		//cout<<"-- Collision position "<<collision.position.x<<","<<collision.position.z<<endl;
		//cout<<"Collision normal "<<collision.normal.x<<","<<collision.normal.z<<endl;
		//cout<<"target position "<<target.position.x<<","<<target.position.z<<endl;
		

		// 2. Delegate to seek
		Seek::getSteering(steering);

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput steering;
		if(ObstacleAvoidance::getSteering(steering)) character.update(steering.linear,maxSpeed,deltaTime);
	}
};

#endif