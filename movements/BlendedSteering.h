/* 
    Andrea Centeno
    10-10138
    Sergio Teran
    11-11020
    sep-dic 2017
*/
class BlendedSteering{
protected:

	struct BehaviorAndWeight{
		Behavior *behavior;
		GLfloat weight;
	};

	//Holds the character and the target in action
	Kinematic target;
	Kinematic character;


	// Holds the maximum acceleration and rotation
	GLfloat maxRotation;
	GLfloat maxAcceleration;
	GLfloat maxSpeed;

	// Holds a list of BehaviorAndWeight instances.
	list<BehaviorAndWeight*> behaviors;

public:

	BlendedSteering(Kinematic &c, Kinematic &t, GLfloat ma,GLfloat mr,GLfloat ms,char type) : 
		character(c), target(t), 
		maxAcceleration(ma),maxSpeed(ms),maxRotation(glm::radians(mr)){
			// Types of blended movements:
			// 	p - Pursue Enemy
			// 	r - Run Away Enemy
			// 	f - Follow Friend

			if( type == 'p'){
				Face* face = new Face(character,target,10,30,5,2); // Align() 

				BehaviorAndWeight faceW ={face,19};
    			behaviors.push_back(&faceW);
			};


		}
	

	// Returns the acceleration required.
	SteeringOutput getSteering(){

		// Create the steering structure for accumulation
		SteeringOutput steering;

		// Accumulate all accelerations
		for (list<BehaviorAndWeight*>::iterator behaviorI = behaviors.begin(); behaviorI != behaviors.end(); ++behaviorI ){
			
			GLfloat w = (*behaviorI)->weight;
			
			//SteeringOutput so = (*behaviorI)->behavior->getSteering();
			SteeringOutput so = {{1,1,1},1};

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
