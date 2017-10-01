class Face: public Align{
public:
	Face(Kinematic &c, Kinematic &t, GLfloat sr, GLfloat tr, GLfloat maa, GLfloat mr) : Align(c, t, sr, tr, maa, mr) {}

	SteeringOutput getSteering(){
		vec3 direction;
		GLfloat lastOrientation;

		SteeringOutput steering;

		// 1. Calculate the target to delegate to align
		// Work out the direction to target
		direction = target.position - character.position;

		// Check for a zero direction, and make no change if so
		if (length(direction) == 0.0){
			steering.angular = 0.0;
			return steering;
		};

		lastOrientation = target.orientation;

		// Put the target together
		target.orientation = atan2(-direction.x, direction.z);//atan2(-direction.x, direction.y);

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