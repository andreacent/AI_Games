class LookWhereYoureGoing: public Align{
public:
	LookWhereYoureGoing(Kinematic &c, Kinematic &t, GLfloat sr, GLfloat tr, GLfloat maa, GLfloat mr) 
		: Align(c, t, sr, tr, maa, mr) {}

	bool getSteering(SteeringOutput &steering){
		// 1. Calculate the target to delegate to align

		GLfloat lastOrientation;

		// Check for a zero direction, and make no change if so
		if (length(character.velocity) == 0) return false;

		lastOrientation = target.orientation;
		// Otherwise set the target based on the velocity
		target.orientation = atan2(-character.velocity.x, character.velocity.z);

		// 2. Delegate to align
		Align::getSteering(steering);

		target.orientation = lastOrientation;

		return true;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	SteeringOutput so;
    	if(getSteering(so)) character.update(so,maxSpeed,deltaTime);
	}
};