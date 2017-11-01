#ifndef M_RECTANGLE_P_H
#define M_RECTANGLE_P_H

#include "Mesh.h"

class RectanglePoints: public Mesh{
protected:
	std::list<glm::vec3> &vectices;
public:	
	RectanglePoints(glm::vec3 c,std::list<glm::vec3> &v) 
		: Mesh(c), vectices(v) {}

	/*
			v2	v4
			
	v1	v3
	*/
	void draw(){			
		glColor3f(color.x,color.y,color.z);
		glBegin(GL_TRIANGLE_STRIP);
			for (glm::vec3 v : vectices) {
				glVertex3f(v.x, v.y, v.z); 
			}	
		glEnd();
	}	

	void createTriangles(bool top, bool right,bool bottom, bool left){
	}
};

#endif