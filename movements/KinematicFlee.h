class KinematicFlee{
private:
	// Holds the maximum speed the character can travel
	GLfloat maxSpeed;
	// Holds the static data for the character and target
	Static &character;
	Static &target;

public:
	
	KinematicFlee(Static &c, Static &t, GLfloat ms = 0.01) : character(c), target(t), maxSpeed(ms){}

	KinematicSteeringOutput getSteering(){
		// Create the structure for output
		KinematicSteeringOutput steering;
		// Get the direction to the target
		steering.velocity = character.position - target.position;
		// The velocity is along this direction, at full speed
		steering.velocity = normalize(steering.velocity) * maxSpeed;
		// Face in the direction we want to move
		character.orientation = getNewOrientation(character.orientation,
													steering.velocity);

		steering.rotation = 0;

		return steering;
	}
};