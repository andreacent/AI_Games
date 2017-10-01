/* 
    Andrea Centeno
    sep-dic 2017
*/
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

GLfloat getNewOrientation(GLfloat currentOrientation, vec3 velocity);
vec3 getVectorOrientation(GLfloat orientation);

struct Static {
	vec3 position;
	GLfloat orientation;

	void update(vec3 velocity,GLfloat rotation) { 
		position += velocity;
		orientation += rotation;
	}

	void update(vec3 velocity,GLfloat rotation,GLfloat deltaTime) { 
		position += velocity * deltaTime;
		orientation += rotation * deltaTime;
	}
};

struct KinematicSteeringOutput{
	vec3 velocity;
	GLfloat rotation;
};

GLfloat getNewOrientation(GLfloat currentOrientation, vec3 velocity){
	//Make sure we have a velocity
	if (glm::length(velocity) > 0){
		//Calculate orientation using an arc tangent of
		//the velocity components.
		return atan2(-velocity.x, velocity.z);
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