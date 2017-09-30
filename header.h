/* 
    Andrea Centeno
    sep-dic 2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <list>

#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

GLfloat getNewOrientation(GLfloat currentOrientation, vec2 velocity);
GLfloat randomBinomial();
vec2 getVectorOrientation(GLfloat orientation);
GLfloat mapToRange(GLfloat orientation);

struct Static {
	vec2 position;
	GLfloat orientation;

	void update(vec2 velocity,GLfloat rotation) { 
		position += velocity;
		orientation += rotation;
	}

	void update(vec2 velocity,GLfloat rotation,GLfloat deltaTime) { 
		position += velocity * deltaTime;
		orientation += rotation * deltaTime;
	}
};

struct SteeringOutput {
	vec2 linear;
	GLfloat angular;

	SteeringOutput(vec2 l={0.0,0.0}, GLfloat a=0.0) : linear(l), angular(a) {}
};

struct Kinematic{
	vec2 position;
	GLfloat orientation; //radian
	vec2 velocity;
	GLfloat rotation;//radian

	Kinematic(vec2 p={0.0,0.0}, GLfloat o=0.0, vec2 v={0.0,0.0}, GLfloat r=0.0) 
		: position(p), orientation(o), velocity(v), rotation(r) {}

	void updatePosition(GLfloat deltaTime){
		position += velocity * deltaTime;
	}

	void updateOrientation(GLfloat deltaTime){
		orientation += rotation * deltaTime;
	}

	void update (SteeringOutput steering,GLfloat deltaTime) { 
		// Update the position and orientation
		position += velocity * deltaTime;
		orientation += rotation * deltaTime;
		// and the velocity and rotation
		velocity += steering.linear * deltaTime;
		orientation += steering.angular * deltaTime;
	}

	void update(SteeringOutput steering,GLfloat maxSpeed,GLfloat deltaTime){
		// Update the position and orientation
		position += velocity * deltaTime;
		orientation += rotation * deltaTime;

		// and the velocity and rotation
		velocity += steering.linear * deltaTime;
		orientation += steering.angular * deltaTime;

		// Check for speeding and clip
		if (distance(velocity,{0,0}) > maxSpeed){
			velocity = normalize(velocity) * maxSpeed;
		}
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
		return atan2(velocity.x, velocity.y);
	}	
	else{ //Otherwise use the current orientation
		return currentOrientation;
	}
};

GLfloat randomBinomial(){
	return rand() - rand();
}

vec2 getVectorOrientation(GLfloat orientation){
	vec2 vecOrientation = {-sin(orientation),cos(orientation)};//{-sin(orientation),cos(orientation)};
	return vecOrientation;
};

GLfloat mapToRange(GLfloat orientation){
	if (orientation > M_PI) orientation -= 2*M_PI;
	else if (orientation < -M_PI) orientation += 2*M_PI;
	return orientation;
}