#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "../assets/kinematic.h"

#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace std;

class Behavior{
public:
	virtual bool getSteering(SteeringOutput &steering) = 0;
	virtual void update(GLfloat maxSpeed,GLfloat deltaTime) = 0;
};

GLfloat getNewOrientation(GLfloat currentOrientation, glm::vec3 velocity);
GLfloat randomBinomial();
glm::vec3 getVectorOrientation(GLfloat orientation);
GLfloat mapToRange(GLfloat orientation);
glm::vec3 rotateVectorZ(glm::vec3 v, GLfloat ang);

#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "Align.h"
#include "VelocityMatch.h"
/****Delegated Behaviors****/
#include "Pursue.h"
#include "Evade.h"
#include "Face.h"
#include "LookWhereYoureGoing.h"
#include "Wander.h"
#include "Separation.h"
#include "ObstacleAvoidance.h"
#include "FollowPath.h"
/****Combining****/
#include "BlendedSteering.h"

#endif