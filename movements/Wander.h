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
	Wander(Kinematic &c, GLfloat sr, GLfloat tr, GLfloat maa, GLfloat mr
		,GLfloat woff,GLfloat wr,GLfloat wrate,GLfloat wo,GLfloat ma) 
		: Face(c, *new Kinematic(), sr, tr, maa, mr),wanderOffset(woff)
			,wanderRadius(glm::radians(wr)),wanderRate(glm::radians(wrate))
			,wanderOrientation(glm::radians(wo)),maxAcceleration(ma){}

	SteeringOutput getSteering(){
		GLfloat targetOrientation;

		SteeringOutput steering;
		
		// Update the wander orientation
		wanderOrientation += randomBinomial() * wanderRate;

		// Calculate the combined target orientation
		targetOrientation = wanderOrientation +	character.orientation;

		// Calculate the center of the wander circle
		target.position = character.position + wanderOffset * getVectorOrientation(character.orientation);

		// Calculate the target location
		target.position += wanderRadius * getVectorOrientation(targetOrientation);

		// 2. Delegate to face
		steering = Face::getSteering();

		// 3. Now set the linear acceleration to be at full
		// acceleration in the direction of the orientation
		steering.linear = maxAcceleration * getVectorOrientation(character.orientation);


		return steering;
	}
};