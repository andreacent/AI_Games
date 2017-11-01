#ifndef BEHAVIORS_CPP
#define BEHAVIORS_CPP

#include "Behaviors.h"
#include <map>
#include <list>

GLfloat getNewOrientation(GLfloat currentOrientation, glm::vec3 velocity){
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

GLfloat randomBinomial(){ return rand() - rand(); }

glm::vec3 getVectorOrientation(GLfloat orientation){
	glm::vec3 vecOrientation = {-sin(orientation),0.0,cos(orientation)};//{-sin(orientation),cos(orientation)};
	return vecOrientation;
};

GLfloat mapToRange(GLfloat orientation){
	if (orientation > M_PI) orientation -= 2*M_PI;
	else if (orientation < -M_PI) orientation += 2*M_PI;
	return orientation;
}

glm::vec3 rotateVectorZ(glm::vec3 v, GLfloat ang){
	return glm::vec3(v.x * cos(ang) + v.z * sin(ang), v.y, v.z * cos(ang) - v.x * sin(ang) );
}

GLfloat maxSpeed = 6;
GLfloat maxAcceleration = 10;
GLfloat maxPrediction = 0.1;

void createMapBaseBehaviors(
		Kinematic &character,
		Kinematic &target, 
		std::list<Kinematic*> &targets,
		CollisionDetector &collisionDetector,
		std::map<string,Behavior*> &behaviors ){

	//(character,target, targetRadius,slowRadius, maxAcceleration,maxSpeed) 
	behaviors["arrive"] = new Arrive(character,target,2,4,maxAcceleration,maxSpeed);
	//(character,targets,threshold,decayCoefficient,maxAcceleration) 
    behaviors["separation"] = new Separation(character,targets,6,10,30);
	//(character,target,maxAcceleration, maxPrediction)
    behaviors["pursue"] = new Pursue(character,target,maxAcceleration,maxPrediction);
    //(character,target, maxAngularAcceleration,maxRotation,slowRadius,targetRadius)
	behaviors["lwyg"] = new LookWhereYoureGoing(character,target,10,30,5,2); 
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,4.5,3);
}

void createMapAllBehaviors(
		Kinematic &character,
		Kinematic &target, 
		CollisionDetector &collisionDetector,
		std::list<Kinematic*> &targets,
		std::map<string,Behavior*> &behaviors ){
	
	GLfloat maxRotation = 30;
	//GLfloat maxAngularAcceleration = 20;

    behaviors["seek"] = new Seek(character,target,maxAcceleration);
    behaviors["flee"] = new Flee(character,target,maxAcceleration); 
	//(character,target, targetRadius,slowRadius, maxAcceleration,maxSpeed) 
	behaviors["arrive"] = new Arrive(character,target,2,4,maxAcceleration,maxSpeed);
    //(character,target, maxAngularAcceleration,maxRotation,slowRadius,targetRadius)
    behaviors["align"] = new Align(character,target,20,maxRotation,5,2);
    //(character,target,maxAcceleration)
    behaviors["velocityMatch"] = new VelocityMatch(character,target,16); 
	//(character,target,maxAcceleration, maxPrediction)
    behaviors["pursue"] = new Pursue(character,target,maxAcceleration,maxPrediction); 
	//(character,target,maxAcceleration, maxPrediction)
    behaviors["evade"] = new Evade(character,target,maxAcceleration,maxPrediction); 
    //(character,target, maxAngularAcceleration,maxRotation,slowRadius,targetRadius)
    behaviors["face"] = new Face(character,target,10,30,5,2);
    //(character,target, maxAngularAcceleration,maxRotation,slowRadius,targetRadius)
	behaviors["lwyg"] = new LookWhereYoureGoing(character,target,10,30,5,2); 
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
    behaviors["wander"] = new Wander(character,20,maxRotation,5,2, 0,4,2,50,maxAcceleration);
	//(character,targets,threshold,decayCoefficient,maxAcceleration) 
    behaviors["separation"] = new Separation(character,targets,3,6,maxAcceleration);  
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,4.5,3);
}

#endif