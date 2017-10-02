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

	// Holds a list of BehaviorAndWeight instances.
	list<BehaviorAndWeight*> &behaviors;

	// Holds the maximum acceleration and rotation
	GLfloat maxRotation;
	GLfloat maxAcceleration;

public:
	// Returns the acceleration required.
	SteeringOutput getSteering(){
		// Create the steering structure for accumulation
		SteeringOutput steering;

		// Accumulate all accelerations
		for (list<BehaviorAndWeight*>::iterator behaviorI = behaviors.begin(); behaviorI != behaviors.end(); ++behaviorI ){
			steering.linear  += (*behaviorI)->weight * (*behaviorI)->behavior->getSteering().linear;
			steering.angular += (*behaviorI)->weight * (*behaviorI)->behavior->getSteering().angular;
		};

		// Crop the result and return
		if( steering.linear > maxAcceleration ){
			steering.linear  = maxAcceleration;
		}
		if( steering.angular > maxRotation ){
			steering.angular  = maxRotation;
		}

		return steering;
	};
};
