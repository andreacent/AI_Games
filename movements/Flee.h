class Flee{
protected:
	// Holds the Kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;
	// Holds the maximum acceleration of the character
	GLfloat maxAcceleration;

public:
	Flee(Kinematic &c, Kinematic &t, GLfloat ma = 0.001) : character(c), target(t), maxAcceleration(ma){}

	SteeringOutput getSteering(){

		SteeringOutput steering;
		// Get the direction to the target
		steering.linear = character.position - target.position;

		// Give full acceleration along this direction
		steering.linear = normalize(steering.linear) * maxAcceleration;

		// Output the steering
		steering.angular = 0;

		return steering;
	}
};