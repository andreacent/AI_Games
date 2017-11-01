#ifndef M_RECTANGLE_P_H
#define M_RECTANGLE_P_H

#include "Mesh.h"

class RectanglePoints: public Mesh{
protected:
	glm::vec3 vectices[4];
public:	
	RectanglePoints(glm::vec3 c,glm::vec3 v[]) : Mesh(c) {
		for(int i =0; i<4; i++){ vectices[i] = v[i]; }
	}

	RectanglePoints(glm::vec3 c,glm::vec3 v[],
				bool top, bool right,bool bottom, bool left) 
				: Mesh(c) {
			for(int i =0; i<4; i++){ vectices[i] = v[i]; }
			createTriangles(top, right,bottom, left);
		}
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
		GLfloat iY,fY;
		iY = -1;
		fY = 1;
	}
};

#endif