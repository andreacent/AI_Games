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
		/*
		else {
			cout<<"Collision position "<<collision->position.x<<","<<collision->position.z<<endl;
			cout<<"Collision normal "<<collision->normal.x<<","<<collision->normal.z<<endl;
		}
		*/

		// Otherwise create a target
		target.position = collision->position + collision->normal * avoidDistance;

		// 2. Delegate to seek
		return Seek::getSteering();

	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
    	character.update(getSteering(),maxSpeed,deltaTime);
		//cout<<"character velocity "<<character.velocity.x<<","<<character.velocity.z<<endl<<endl;
	}
};