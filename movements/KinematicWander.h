class KinematicWander{
private:
	// Holds the static data for the character and target
	Static &character;

	// Holds the maximum speed the character can travel
	GLfloat maxSpeed;

	// Holds the maximum rotation speed we’d like, probably
	// should be smaller than the maximum possible, to allow
	// a leisurely change in direction
	GLfloat maxRotation;

public:

	KinematicWander(Static &c, GLfloat mr=0.05, GLfloat ms = 0.01) : character(c), maxSpeed(ms), maxRotation(mr){}

	KinematicSteeringOutput getSteering(){
		// Create the structure for output
		KinematicSteeringOutput steering;

		// Get velocity from the vector form of the orientation
		steering.velocity = maxSpeed * getVectorOrientation(character.orientation);

		// Change our orientation randomly
		steering.rotation = randomBinomial() * maxRotation;

		return steering;
	}
};