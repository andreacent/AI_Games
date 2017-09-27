class KinematicArrive{
private:
	// Holds the static data for the character and target
	Static &character;
	Static &target;

	// Holds the satisfaction radius
	GLfloat radius;
	// Holds the maximum speed the character can travel
	GLfloat maxSpeed;
	// Holds the time to target constant
	GLfloat timeToTarget = 0.25;

public:

	KinematicArrive(Static &c, Static &t, GLfloat r=2.5, GLfloat ms = 0.01) : character(c), target(t), maxSpeed(ms), radius(r){}

	KinematicSteeringOutput getSteering(){
		// Create the structure for output
		KinematicSteeringOutput steering;
		// Get the direction to the target
		steering.velocity = target.position - character.position;

		GLfloat length = distance(steering.velocity,{0,0});
		// Check if we’re within radius
		if(length < radius){ // We can return no steering request
			steering.velocity = {0.0,0.0};
			return steering;
		}

		// We need to move to our target, we’d like to
		// get there in timeToTarget seconds
		steering.velocity /= timeToTarget;

		// If this is too fast, clip it to the max speed
		if (length > maxSpeed){	
			steering.velocity = normalize(steering.velocity) * maxSpeed;
		}

		// Face in the direction we want to move
		character.orientation = getNewOrientation(character.orientation,
													steering.velocity);

		steering.rotation = 0;

		return steering;
	}
};