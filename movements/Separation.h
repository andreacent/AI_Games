class Separation{
protected:
	// Holds the kinematic data for the character
	Kinematic &character;
	// Holds a list of potential targets
	list<Kinematic*> &targets;

	// Holds the threshold to take action
	GLfloat threshold;

	// Holds the constant coefficient of decay for the
	// inverse square law force
	GLfloat  decayCoefficient;

	// Holds the maximum acceleration of the character
	GLfloat  maxAcceleration;

public:
	Separation(Kinematic &c, list<Kinematic*> &ts,GLfloat t,GLfloat d,GLfloat ma) 
		: character(c), targets(ts), threshold(t), decayCoefficient(d), maxAcceleration(ma) {}

	SteeringOutput getSteering(){
		vec3 direction;
		GLfloat distance,strength;

		// The steering variable holds the output
		SteeringOutput steering;

		// Loop through each target
		for (list<Kinematic*>::iterator target=targets.begin(); target != targets.end(); ++target){
			// Check if the target is close
			direction = (*target)->position - character.position;
			distance = glm::length(direction);

			if (distance < threshold){
				// Calculate the strength of repulsion
				strength = std::min(decayCoefficient / (distance * distance), maxAcceleration);

				// Add the acceleration				
				steering.linear += strength * glm::normalize(-direction);
			}
		}			

		// We’ve gone through all targets, return the result
		return steering;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	SteeringOutput so = getSteering();
    	if(length(so.linear) != 0) character.update(so,maxSpeed,deltaTime);
	}
};