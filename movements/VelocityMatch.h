class VelocityMatch: public Behavior{
private:
	// Holds the Kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;
	// Holds the max angular acceleration and rotation
	// of the character
	GLfloat maxAcceleration;

	// Holds the time over which to achieve target speed
	GLfloat timeToTarget = 0.1;

public:
	VelocityMatch(Kinematic &c, Kinematic &t, GLfloat ma) : character(c), target(t),maxAcceleration(ma){}

	SteeringOutput getSteering(){
		SteeringOutput steering;

		// Acceleration tries to get to the target velocity
		steering.linear = target.velocity - character.velocity;
		steering.linear /= timeToTarget;

		// Check if the acceleration is too fast
		if (glm::length(steering.linear) > maxAcceleration){
			steering.linear = glm::normalize(steering.linear) * maxAcceleration;
		}

		// Output the steering
		steering.angular = 0;
		return steering;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	character.update(getSteering(),maxSpeed,deltaTime);
	}
};