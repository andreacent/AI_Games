class CollisionAvoidance: public Behavior{
protected:
	// Holds the kinematic data for the character
	Kinematic &character;
	// Holds a list of potential targets
	list<Kinematic*> &targets;

	// Holds the maximum acceleration
	GLfloat maxAcceleration;

	// Holds the collision radius of a character (we assume
	// all characters have the same radius here)
	GLfloat radius;

public:
	CollisionAvoidance(Kinematic &c, list<Kinematic*> &ts, GLfloat ma, GLfloat r) 
		: character(c), targets(ts), maxAcceleration(ma), radius(r) {}

	bool getSteering(SteeringOutput &steering){
		GLfloat distance, relativeSpeed, timeToCollision, minSeparation;
		vec3 relativePos,relativeVel;

		//1. Find the target that’s closest to collision

		//Store the first collision time
		GLfloat shortestTime = FLT_MAX;

		// Store the target that collides then, and other data
		// that we will need and can avoid recalculating
		Kinematic *firstTarget;
		GLfloat firstMinSeparation, firstDistance;
		vec3 firstRelativePos, firstRelativeVel;

		// Loop through each target
		for (list<Kinematic*>::iterator target=targets.begin(); target != targets.end(); ++target){
			// Calculate the time to collision
			relativePos = (*target)->position - character.position;
			relativeVel = (*target)->velocity - character.velocity;
			relativeSpeed = glm::length(relativeVel);
			timeToCollision = glm::dot(relativePos,relativeVel) / (relativeSpeed * relativeSpeed);

			// Check if it is going to be a collision at all
			distance = glm::length(relativePos);
			minSeparation = distance-relativeSpeed*shortestTime;
			if (minSeparation > 2*radius) {
				continue;
			}

			// Check if it is the shortest
			if (timeToCollision > 0 && timeToCollision < shortestTime){
				// Store the time, target and other data
				shortestTime = timeToCollision;
				firstTarget = (*target);
				firstMinSeparation = minSeparation;
				firstDistance = distance;
				firstRelativePos = relativePos;
				firstRelativeVel = relativeVel;
			}
		}
		//2. Calculate the steering

		// If we have no target, then exit
		if (!firstTarget) return false;
		
		// If we’re going to hit exactly, or if we’re already
		// colliding, then do the steering based on current
		// position.
		if (firstMinSeparation <= 0 || distance < 2*radius){
			relativePos = firstTarget->position - character.position;
		}		
		else{// Otherwise calculate the future relative position
			relativePos = firstRelativePos + firstRelativeVel * shortestTime;
		}

		// Avoid the target
		steering.linear = glm::normalize(relativePos) * maxAcceleration;

		// Return the steering
		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	SteeringOutput so;
    	if(getSteering(so)) character.update(so,maxSpeed,deltaTime);
	}
};