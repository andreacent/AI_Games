class Align{
private:
	// Holds the Kinematic data for the character and target
	Kinematic &character;
	Kinematic &target;
	// Holds the max angular acceleration and rotation
	// of the character
	GLfloat maxAngularAcceleration;
	GLfloat maxRotation;

	// Holds the radius for beginning to slow down
	GLfloat slowRadius;

	// Holds the radius for arriving at the target
	GLfloat targetRadius;

	// Holds the time over which to achieve target speed
	GLfloat timeToTarget = 0.1;

public:
	Align(Kinematic &c, Kinematic &t, GLfloat sr=5, GLfloat tr=2, GLfloat maa=0.01, GLfloat mr=0.02) : 
		character(c), target(t),slowRadius(sr), targetRadius(tr), maxAngularAcceleration(maa), maxRotation(mr){}

	SteeringOutput getSteering(){
		GLfloat rotation,rotationSize,targetRotation,angularAcceleration;

		SteeringOutput steering;

		// Get the naive direction to the target
		rotation = target.orientation - character.orientation;

		// Map the result to the (-pi, pi) interval
		rotation = mapToRange(rotation);
		rotationSize = abs(rotationDirection);

		// Check if we are there, return no steering
		if (rotationSize < targetRadius){
			return steering;
		}

		// If we are outside the slowRadius, then use
		// maximum rotation
		if (rotationSize > slowRadius){
			targetRotation = maxRotation;
		}
		else{ // Otherwise calculate a scaled rotation
			targetRotation = maxRotation * rotationSize / slowRadius;
		}

		// The final target rotation combines
		// speed (already in the variable) and direction
		targetRotation *= rotation / rotationSize;

		// Acceleration tries to get to the target rotation
		steering.angular = targetRotation - character.rotation;
		steering.angular /= timeToTarget;


		// Check if the acceleration is too great
		angularAcceleration = abs(steering.angular);
		if (angularAcceleration > maxAngularAcceleration){
			steering.angular /= angularAcceleration;
			steering.angular *= maxAngularAcceleration;
		}

		// Output the steering
		steering.linear = {0.0,0.0};

		return steering;
	}
};