// NO ESTA IMPLEMENTADO

class FollowPath: public Seek{
private:
	// Holds the path to follow
	path

	//Holds the distance along the path to generate the
	// target. Can be negative if the character is to move
	// along the reverse direction.
	pathOffset

	// Holds the current position on the path
	currentParam

public:
	FollowPath(Kinematic &c, Kinematic &t, GLfloat ma, GLfloat mp) : Seek(c,t,ma), maxPrediction(mp) {}

	SteeringOutput getSteering(){
		// 1. Calculate the target to delegate to face

		// Find the current position on the path
		currentParam = path.getParam(character.position, currentPos)

		// Offset it
		targetParam = currentParam + pathOffset

		// Get the target position
		target.position = path.getPosition(targetParam)

		// 2. Delegate to seek
		return Seek.getSteering()
	}
};