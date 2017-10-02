/* 
    Andrea Centeno
    sep-dic 2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

using namespace glm;
using namespace std;

#include "Mesh.h"
#include "Collision.h"

GLfloat getNewOrientation(GLfloat currentOrientation, vec3 velocity);
GLfloat randomBinomial();
vec3 getVectorOrientation(GLfloat orientation);
GLfloat mapToRange(GLfloat orientation);

struct SteeringOutput {
	vec3 linear;
	GLfloat angular;

	SteeringOutput(vec3 l={0.0,0.0,0.0}, GLfloat a=0.0) : linear(l), angular(a) {}
};

struct Kinematic{
	vec3 position;
	GLfloat orientation; //radian
	vec3 velocity;
	GLfloat rotation;//radian

	Kinematic(vec3 p={0.0,0.0,0.0}, GLfloat o=0.0, vec3 v={0.0,0.0,0.0}, GLfloat r=0.0) 
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

class Behavior{};

GLfloat getNewOrientation(GLfloat currentOrientation, vec3 velocity){
	//Make sure we have a velocity
	if (glm::length(velocity) > 0){
		//Calculate orientation using an arc tangent of
		//the velocity components.
		return atan2(velocity.x, velocity.z);
	}	
	else{ //Otherwise use the current orientation
		return currentOrientation;
	}
};

GLfloat randomBinomial(){
	return rand() - rand();
}

vec3 getVectorOrientation(GLfloat orientation){
	vec3 vecOrientation = {-sin(orientation),0.0,cos(orientation)};//{-sin(orientation),cos(orientation)};
	return vecOrientation;
};

GLfloat mapToRange(GLfloat orientation){
	if (orientation > M_PI) orientation -= 2*M_PI;
	else if (orientation < -M_PI) orientation += 2*M_PI;
	return orientation;
}

vec3 rotateVectorZ(vec3 v, GLfloat ang){
	return vec3(v.x * cos(ang) + v.z * sin(ang), v.y, v.z * cos(ang) - v.x * sin(ang) );
}