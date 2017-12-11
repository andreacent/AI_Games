/* 
    Andrea Centeno
    sep-dic 2017
*/
#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <GL/gl.h>
#include <glm/glm.hpp>
#include "../mesh/Mesh.cpp"

#include <list>

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

	/*
	cambia la posicion del personaje si es valida, es decir,
	no sale del mapa
	*/
	bool setNewPosition(glm::vec3 newPos){
		if( newPos.z > 1.5 && newPos.z < 39) position.z = newPos.z;	
		if (newPos.x > 1 && newPos.x < 53 ) position.x = newPos.x; 
		position.y = newPos.y;
	}

	void updatePosition(GLfloat deltaTime, std::list<Mesh*> meshs){	 //
		glm::vec3 nesPos = position + (velocity * deltaTime);
		for (std::list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m){
			if ((*m)->insideMesh(nesPos)) return;
		}	
		setNewPosition(nesPos);
	}

	void reset(glm::vec3 position){	 //
		this->position = position;
		this->orientation = 0;
		this->velocity = {0,0,0};
		this->rotation = 0;
	}

	void updateOrientation(GLfloat deltaTime){
		orientation += rotation * deltaTime;
	}

	void update(SteeringOutput steering,GLfloat maxSpeed,GLfloat deltaTime){
		// Update the position and orientation
		setNewPosition(position + (velocity * deltaTime));
		//updatePosition(deltaTime, meshs);
		orientation += rotation * deltaTime;

		// and the velocity and rotation
		velocity += steering.linear * deltaTime;
		orientation += steering.angular * deltaTime;

		// Check for speeding and clip
		if (glm::length(velocity) > maxSpeed){
			velocity = glm::normalize(velocity) * maxSpeed;
		}
	}

	void update(GLfloat angular,GLfloat maxSpeed,GLfloat deltaTime){
		// Update the position and orientation
		orientation += rotation * deltaTime;
		// and the velocity and rotation
		orientation += angular * deltaTime;
	}

	void update(glm::vec3 linear,GLfloat maxSpeed,GLfloat deltaTime){
		// Update the position and orientation
		setNewPosition(position + (velocity * deltaTime));

		// and the velocity and rotation
		velocity += linear * deltaTime;

		// Check for speeding and clip
		if (glm::length(velocity) > maxSpeed){
			velocity = glm::normalize(velocity) * maxSpeed;
		}
	}
};

#endif