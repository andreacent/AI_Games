#ifndef BLENDED_H
#define BLENDED_H

/* 
    Andrea Centeno
    10-10138
    Sergio Teran
    11-11020
    sep-dic 2017
*/

#include <list>

struct BehaviorAndWeight{
	Behavior *behavior;
	GLfloat weight;

	BehaviorAndWeight(Behavior *b, GLfloat w) : behavior(b), weight(w) {}
};

class BlendedSteering{
protected:

	//Holds the character in action
	Kinematic &character;


	// Holds the maximum acceleration and rotation
	GLfloat maxRotation;
	GLfloat maxAcceleration;
	GLfloat maxSpeed;

	// Holds a list of BehaviorAndWeight instances.
	std::list<BehaviorAndWeight*> &behaviors;

public:

	BlendedSteering(Kinematic &c, GLfloat mr,GLfloat ma,GLfloat ms,std::list<BehaviorAndWeight*> &b) 
		: character(c),maxRotation(glm::radians(mr)),maxAcceleration(ma),maxSpeed(ms),behaviors(b) {}
	
	void setBehaviors(std::list<BehaviorAndWeight*> &b){ behaviors = b; }

	void addBehavior(BehaviorAndWeight* b){ behaviors.push_back(b); }

	// Returns the acceleration required.
	SteeringOutput getSteering(){

		// Create the steering structure for accumulation
		SteeringOutput steering;

		// Accumulate all accelerations
		for (std::list<BehaviorAndWeight*>::iterator behaviorI = behaviors.begin(); behaviorI != behaviors.end(); ++behaviorI ){

			GLfloat w = (*behaviorI)->weight;			
			SteeringOutput so;
			if((*behaviorI)->behavior->getSteering(so)){
				steering.linear  += w * so.linear;
				steering.angular += w * so.angular;
			}
		};

		// Crop the result and return
		if(glm::length(steering.linear) > maxAcceleration) steering.linear = glm::normalize(steering.linear) * maxAcceleration;
		if( steering.angular > maxRotation ) steering.angular  = maxRotation;

		return steering;
	};

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput so = getSteering();
    	character.update(so,maxSpeed,deltaTime);
	}
};

#endif