struct JumpPoint{
	// The position of the jump point
	vec3 jumpLocation;
	// The position of the landing pad
	vec3 landingLocation;
	// The change in position from jump to landing
	// This is calculated from the other values
	vec3 deltaPosition;
};

class Jump : public VelocityMatch{
protected:
	// Holds the jump point to use
	JumpPoint &jumpPoint;

	// Keeps track of whether the jump is achievable
	bool canAchieve = false;

	// Holds the maximum speed of the character
	GLfloat maxSpeed;

	// Holds the maximum vertical jump velocity
	GLfloat maxYVelocity;

public:
	Jump(Kinematic &c, GLfloat ma, JumpPoint &jp, GLfloat ms, GLfloat mvY) 
		: VelocityMatch(c, *new Kinematic(), ma), jumpPoint(jp), maxSpeed(ms), maxYVelocity(mvY) {}

	SteeringOutput getSteering(){
		// Check if we have a trajectory, and create
		// one if not.
		if (!target) calculateTarget();

		// Check if the trajectory is zero
		// If not, we have no acceleration
		if (!canAchieve) return new SteeringOutput();

		// Check if we’ve hit the jump point (character
		// is inherited from the VelocityMatch base class)
		if (character.position.near(target.position) && character.velocity.near(target.velocity)){
			// Perform the jump, and return no steering (we’re airborne, no need to steer).
			scheduleJumpAction()
			return new SteeringOutput();
		}

		// Delegate the steering
		return VelocityMatch::getSteering();

	}

	// Works out the trajectory calculation
	void calculateTarget(){
		target = *new Kinematic();
		target.position = jumpPoint.jumpLocation;

		// Calculate the first jump time
		GLfloat sqrtTerm = sqrt(2*gravity.y*jumpPoint.deltaPosition.y +	maxYVelocity*maxVelocity);
		GLfloat jumpTime = (maxYVelocity - sqrtTerm) / gravity.y;

		// Check if we can use it
		if (!checkJumpTime(jumpTime)){
			// Otherwise try the other time
			jumpTime = (maxYVelocity + sqrtTerm) / gravity.y;
			checkJumpTime(jumpTime);
		}
	}

	// Private helper method for the calculateTarget function
	bool checkJumpTime(GLfloat jumpTime){
		// Calculate the planar speed
		GLfloat vx = jumpPoint.deltaPosition.x / jumpTime;
		GLfloat vz = jumpPoint.deltaPosition.z / jumpTime;
		GLfloat speedSq = vx*vx + vz*vz;

		// Check it
		if (speedSq < maxSpeed*maxSpeed){
			// We have a valid solution, so store it
			target.velocity.x = vx;
			target.velocity.z = vz;
			canAchieve = true;
		}

		return canAchieve;
	}

};