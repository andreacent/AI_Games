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
		Collision *collision = new Collision();
		vec3 colPosition, colNormal;

		for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m){
			list<vector<vec3>> triangles = (*m)->getTriangles();
			vec3 intersect;
			vec3 p1,p2,p3;

			for (list<vector<vec3>>::iterator t=triangles.begin(); t != triangles.end(); ++t){
				p1 = (*t).at(0);
				p2 = (*t).at(1);
				p3 = (*t).at(2);

				if(glm::intersectRayTriangle(position,moveAmount,p1,p2,p3,intersect)){
					float z = 1.0 - intersect.x - intersect.y;
					collision->position = p1 * z + p2 * intersect.x + p3 * intersect.y;
					collision->normal = glm::normalize(glm::cross(p2 - p1,p3 - p1));
					//collision->normal = glm::normalize(glm::cross(p3 - p1, p2 - p1));
					//N = ( (V2 – V1) x (V3 – V1) ) / | (V2 – V1) x (V3 – V1) |
					return collision;
				}
			}
		}

		return NULL;
	}
};