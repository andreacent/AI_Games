struct Collision{
	vec3 position;
	vec3 normal;
};

class CollisionDetector{
protected:
	list<Mesh*> &meshs;

public:
	CollisionDetector(list<Mesh*> &ms) : meshs(ms) {}

	Collision *getCollision(vec3 position, vec3 moveAmount){
		Collision *collision;

		for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m){
			vector<vec3> vertexes = (*m)->getTriangles();
			vec3 intersect;
			vec3 p1,p2,p3;
			for(int i=0;i<12;i++){
				p1 = vertexes.at(i);
				p2 = vertexes.at(i+1);
				p3 = vertexes.at(i+2);

				if(glm::intersectRayTriangle(position,moveAmount,p1,p2,p3,intersect)){
					float z = 1.0 - intersect.x - intersect.y;
					collision->position = p1 * z + p2 * intersect.x + p3 * intersect.y;
					collision->normal = glm::normalize(glm::cross(p3 - p1, p2 - p1)); 
					cout<< "collision->normal"<<collision->normal.x<<","<<collision->normal.y<<endl;
					return collision;
				}
			}
		}

		return NULL;
	}
};


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

		// Find the collision
		collision = collisionDetector.getCollision(character.position, rayVector);

		// If have no collision, do nothing
		if (!collision) return steering;

			// Otherwise create a target
		target.position = collision->position + collision->normal * avoidDistance;
		cout<<"target.position "<<target.position.x<<","<<target.position.y<<endl;

		// 2. Delegate to seek
		return Seek::getSteering();

	}
};