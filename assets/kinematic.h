#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <GL/gl.h>
#include <glm/glm.hpp>

struct SteeringOutput {
	glm::vec3 linear;
	GLfloat angular;

	SteeringOutput(glm::vec3 l={0.0,0.0,0.0}, GLfloat a=0.0) : linear(l), angular(a) {}
};

struct Kinematic{
	glm::vec3 position;
	GLfloat orientation; //radian
	glm::vec3 velocity;
	GLfloat rotation;//radian

	Kinematic(glm::vec3 p={0.0,0.0,0.0}, GLfloat o=0.0, glm::vec3 v={0.0,0.0,0.0}, GLfloat r=0.0) 
		: position(p), orientation(o), velocity(v), rotation(r) {}

	void updatePosition(GLfloat deltaTime){
		position += velocity * deltaTime;
	}

	void updateOrientation(GLfloat deltaTime){
		orientation += rotation * deltaTime;
	}

	void update(SteeringOutput steering,GLfloat maxSpeed,GLfloat deltaTime){
		// Update the position and orientation
		position += velocity * deltaTime;
		orientation += rotation * deltaTime;

		// and the velocity and rotation
		velocity += steering.linear * deltaTime;
		orientation += steering.angular * deltaTime;

		// Check for speeding and clip
		if (glm::length(velocity) > maxSpeed){
			velocity = glm::normalize(velocity) * maxSpeed;
		}
	}
};

#endif