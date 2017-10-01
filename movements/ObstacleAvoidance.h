// #include "Collision.h"

class ObstacleAvoidance: public Seek{
protected:
	// Holds a collision detector
	CollisionDetector &collisionDetector;

	// Holds the minimum distance to a wall (i.e., how far
	// to avoid collision) should be greater than the
	// radius of the character.
	GLfloat avoidDistance;

	// Holds the distance to look ahead for a collision
	// (i.e., the length of the collision ray)
	GLfloat lookahead;

public:
	ObstacleAvoidance(Kinematic &c, GLfloat ma, CollisionDetector &cd, GLfloat ad, GLfloat l) 
		: Seek(c,*new Kinematic(),ma), collisionDetector(cd), avoidDistance(ad), lookahead(l) {}

	SteeringOutput getSteering(){
		vec3 rayVector;

		SteeringOutput steering;
		Collision *collision;

		// 1. Calculate the target to delegate to seek

		// Calculate the collision ray vector
		rayVector = normalize(character.velocity) * lookahead;

		drawRay(character.position, rayVector);

		// Find the collision
		collision = collisionDetector.getCollision(character.position, rayVector);

		// If have no collision, do nothing
		if (!collision) return steering;

			// Otherwise create a target
		target.position = collision->position + collision->normal * avoidDistance;
		//cout<<"target.position "<<target.position.x<<","<<target.position.z<<endl;

		// 2. Delegate to seek
		return Seek::getSteering();

	}
};