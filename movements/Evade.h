class Evade: public Flee{
private:
	// Holds the maximum prediction time
	GLfloat maxPrediction;

public:
	Evade(Kinematic &c, Kinematic &t, GLfloat ma, GLfloat mp) : Flee(c,t,ma), maxPrediction(mp) {}

	SteeringOutput getSteering(){
		vec3 direction,lastPosition;
		GLfloat distance,speed,prediction;

		//1. Calculate the target to delegate to Flee
		// Work out the distance to target
		direction = target.position - character.position;
		distance = length(direction);

		// Work out our current speed
		speed = length(character.velocity);

		// Check if speed is too small to give a reasonable
		// prediction time
		if(speed <= distance / maxPrediction){
			prediction = maxPrediction;
		}
		else{//Otherwise calculate the prediction time
			prediction = distance / speed;
		}

		lastPosition = target.position;

		target.position += target.velocity * prediction;
		SteeringOutput steering = Flee::getSteering(); //2. Delegate to Flee
		
		target.position = lastPosition;

		return steering;
	}
};