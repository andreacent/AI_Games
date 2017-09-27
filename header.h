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

GLfloat getNewOrientation(GLfloat currentOrientation, vec2 velocity);

struct Static {
	vec2 position;
	GLfloat orientation;

	void update(vec2 velocity,GLfloat rotation) { 
		position.x += velocity.x;
		position.y += velocity.y;
		orientation += rotation;
	}

	void update(vec2 velocity,GLfloat rotation,GLfloat deltaTime) { 
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
		orientation += rotation * deltaTime;
	}
};

struct SteeringOutput {
	vec2 linear;
	GLfloat angular;
};

struct Kinematic{
	vec2 position;
	GLfloat orientation; 
	vec2 velocity;
	GLfloat rotation;

	void update (SteeringOutput steering,GLfloat deltaTime) { 
		// Update the position and orientation
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
		orientation += rotation * deltaTime;
		// and the velocity and rotation
		velocity.x += steering.linear.x * deltaTime;
		velocity.y += steering.linear.y * deltaTime;
		orientation += steering.angular * deltaTime;
	}
};

struct KinematicSteeringOutput{
	vec2 velocity;
	GLfloat rotation;
};

GLfloat getNewOrientation(GLfloat currentOrientation, vec2 velocity){
	//Make sure we have a velocity
	if (distance(velocity,{0,0}) > 0){
		//Calculate orientation using an arc tangent of
		//the velocity components.
		return atan2(-velocity.x, velocity.y);
	}	
	else{ //Otherwise use the current orientation
		return currentOrientation;
	}
};