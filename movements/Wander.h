//NO FUNCIONA

class Wander: public Face{
	// Holds the radius and forward offset of the wander
	// circle.
	GLfloat wanderOffset;
	GLfloat wanderRadius;

	// Holds the maximum rate at which the wander orientation
	// can change
	GLfloat wanderRate;

	// Holds the current orientation of the wander target
	GLfloat wanderOrientation;

	// Holds the maximum acceleration of the character
	GLfloat maxAcceleration;

public:
	Wander(Kinematic &c, Kinematic &t, GLfloat sr, GLfloat tr, GLfloat maa, GLfloat mr
		,GLfloat woff,GLfloat wr,GLfloat wrate,GLfloat wo,GLfloat ma) 
		: Face(c, t, sr, tr, maa, mr),wanderOffset(woff)
			,wanderRadius(wr),wanderRate(wrate)
			,wanderOrientation(wo),maxAcceleration(ma){}

	SteeringOutput getSteering(){
		GLfloat targetOrientation;
		vec2 targetPosition;

		SteeringOutput steering;
		
		// Update the wander orientation
		wanderOrientation += randomBinomial() * wanderRate;

		// Calculate the combined target orientation
		targetOrientation = wanderOrientation +	character.orientation;

		targetPosition = target.position;

		// Calculate the center of the wander circle
		cout<<"-- character.position "<<character.position.x<<","<<character.position.y<<endl;
		cout<<"   wanderOffset "<<wanderOffset<<endl;
		cout<<"   getVectorOrientation(character.orientation) "<<getVectorOrientation(character.orientation).x<<","<<getVectorOrientation(character.orientation).y<<endl;
		cout<<"   wanderRadius "<<wanderRadius<<endl;
		cout<<"   getVectorOrientation(targetOrientation) "<<getVectorOrientation(targetOrientation).x<<","<<getVectorOrientation(targetOrientation).y<<endl;

		target.position = character.position + wanderOffset * getVectorOrientation(character.orientation);

		// Calculate the target location
		target.position += wanderRadius * getVectorOrientation(targetOrientation);

		cout<<"   real target position "<<targetPosition.x<<","<<targetPosition.y<<endl;
		cout<<"        target position "<<target.position.x<<","<<target.position.y<<endl;

		// 2. Delegate to face
		steering = Face::getSteering();

		target.position = targetPosition;


		// 3. Now set the linear acceleration to be at full
		// acceleration in the direction of the orientation
		steering.linear = maxAcceleration * getVectorOrientation(character.orientation);
		cout<<"   steering.linear "<<steering.linear.x<<","<<steering.linear.y<<endl;
		cout<<"   steering.angular "<<steering.angular<<endl;


		return steering;
	}
};