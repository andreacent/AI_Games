/* 
    Andrea Centeno
    10-10138
    Sergio Teran
    11-11020
    sep-dic 2017
*/

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

	// Holds a list of BehaviorAndWeight instances.
	list<BehaviorAndWeight*> &behaviors;

public:

	BlendedSteering(Kinematic &c, GLfloat mr,GLfloat ma,GLfloat ms,list<BehaviorAndWeight*> &b) 
		: character(c),maxRotation(glm::radians(mr)),maxAcceleration(ma),behaviors(b) {}
	

	// Returns the acceleration required.
	SteeringOutput getSteering(){

		// Create the steering structure for accumulation
		SteeringOutput steering;

		// Accumulate all accelerations
		for (list<BehaviorAndWeight*>::iterator behaviorI = behaviors.begin(); behaviorI != behaviors.end(); ++behaviorI ){
			
			GLfloat w = (*behaviorI)->weight;			
			SteeringOutput so = (*behaviorI)->behavior->getSteering();

			steering.linear  += w * so.linear;
			steering.angular += w * so.angular;
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
