/* 
    Andrea Centeno
    carnet USB: 10-10138
    Sergio Teran
    carnet USB: 11-11020
    sep-dic 2017
*/ 
#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

GLfloat getNewOrientation(GLfloat currentOrientation, vec3 velocity);
GLfloat randomBinomial();
vec3 getVectorOrientation(GLfloat orientation);
GLfloat mapToRange(GLfloat orientation);
vec3 rotateVectorZ(vec3 v, GLfloat ang);

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

class Behavior{
public:
	virtual bool getSteering(SteeringOutput &steering) = 0;
	virtual void update(GLfloat maxSpeed,GLfloat deltaTime) = 0;
};

#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "Align.h"
#include "VelocityMatch.h"
#include "Pursue.h"
#include "Evade.h"
#include "Face.h"
#include "LookWhereYoureGoing.h"
#include "Wander.h"
#include "Separation.h"
#include "ObstacleAvoidance.h"
#include "BlendedSteering.h"