class LookWhereYoureGoing: public Align{
public:
	LookWhereYoureGoing(Kinematic &c, Kinematic &t, GLfloat sr, GLfloat tr, GLfloat maa, GLfloat mr) 
		: Align(c, t, sr, tr, maa, mr) {}

	SteeringOutput getSteering(){
		// 1. Calculate the target to delegate to align

		GLfloat lastOrientation;
		SteeringOutput steering;

		// Check for a zero direction, and make no change if so
		if (length(character.velocity) == 0){
			steering.angular = 0.0;
			return steering;
		}

		lastOrientation = target.orientation;
		// Otherwise set the target based on the velocity
		target.orientation = atan2(-character.velocity.x, character.velocity.z);

		// 2. Delegate to align
		steering = Align::getSteering();

		target.orientation = lastOrientation;

		return steering;
	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	SteeringOutput so = getSteering();
    	if(so.angular != 0.0) character.update(so,maxSpeed,deltaTime);
	}
};