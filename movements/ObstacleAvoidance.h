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
		: Seek(c,*new Kinematic(),ma), collisionDetector(cd), avoidDistance(ad), lookahead(l){}

	bool getSteering(SteeringOutput &steering){
		vec3 rayVector,rayVectorL,rayVectorR;
		GLfloat raySize = lookahead * 0.7;

		Collision collision;

		// 1. Calculate the target to delegate to seek

		// Calculate the collision ray vector
		rayVector = glm::normalize(character.velocity) * lookahead;
		rayVectorL = glm::normalize(rotateVectorZ(character.velocity, glm::radians(-35.0))) * raySize;
		rayVectorR = glm::normalize(rotateVectorZ(character.velocity, glm::radians(35.0))) * raySize;

		//cout<<"-- distance(charPos, ray) "<<glm::distance(collision.position,rayVector)<<endl;

		drawRay(character.position, rayVector);
		drawRay(character.position, rayVectorR);
		drawRay(character.position, rayVectorL);

		// Find the collision
		if(!collisionDetector.getCollision(character.position, rayVector, collision, lookahead)){
			if(!collisionDetector.getCollision(character.position, rayVectorR, collision, raySize)){
				if(!collisionDetector.getCollision(character.position, rayVectorL, collision, raySize))
					return false;
			}
		}

		// Otherwise create a target
		target.position = collision.position + collision.normal * avoidDistance;

		//cout<<"-- Collision position "<<collision.position.x<<","<<collision.position.z<<endl;
		//cout<<"Collision normal "<<collision.normal.x<<","<<collision.normal.z<<endl;
		//cout<<"target position "<<target.position.x<<","<<target.position.z<<endl;

		// 2. Delegate to seek
		steering = Seek::getSteering();

		//cout<<"steering.linear "<<steering.linear.x<<","<<steering.linear.z<<endl;
		return true;

	}

	void update(GLfloat maxSpeed,GLfloat deltaTime){
		SteeringOutput steering;
		if(ObstacleAvoidance::getSteering(steering)) character.update(steering,maxSpeed,deltaTime);
	}
};