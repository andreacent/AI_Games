/* 
    Andrea Centeno
    carnet USB: 10-10138
    sep-dic 2017
*/
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

	left v1 - v2 
	top v2 - v4 
	rifht v4 - v3
	bottom v1 - v3
	*/
	void draw(){			
		glColor3f(color.x,color.y,color.z);
		glBegin(GL_TRIANGLE_STRIP);
			for (glm::vec3 v : vectices) {
				glVertex3f(v.x, v.y, v.z); 
			}	
		glEnd();
	}

	bool insideMesh(glm::vec3 point){
		int j = 3;
		float offset = 0.4;
		
		if( point.x + offset  >= vectices[0].x && point.x - offset <= vectices[3].x
			&& point.z + offset >= vectices[0].z && point.z - offset <= vectices[1].z ) 
			return true;

		return false;
	}

	void createTriangles(bool top, bool right,bool bottom, bool left){
		GLfloat iY,fY;
		iY = -1;
		fY = 1;

		glm::vec3 a = {vectices[0].x, fY, vectices[0].z};
		glm::vec3 b = {vectices[0].x, iY, vectices[0].z};
		glm::vec3 c = {vectices[2].x, fY, vectices[2].z};
		glm::vec3 d = {vectices[2].x, iY, vectices[2].z};
		glm::vec3 e = {vectices[3].x, iY, vectices[3].z};
		glm::vec3 f = {vectices[1].x, iY, vectices[1].z};
		glm::vec3 g = {vectices[1].x, fY, vectices[1].z};
		glm::vec3 h = {vectices[3].x, fY, vectices[3].z};

		if(left){
			triangles.push_back(std::vector<glm::vec3> {f, b, g});
			triangles.push_back(std::vector<glm::vec3> {a, g, b});
		}
		if(right){
			triangles.push_back(std::vector<glm::vec3> {e, h, c});
			triangles.push_back(std::vector<glm::vec3> {c, d, e});
		}
		if(bottom){
			triangles.push_back(std::vector<glm::vec3> {a, b, c});
			triangles.push_back(std::vector<glm::vec3> {c, b, d});
		}
		if(top){
			triangles.push_back(std::vector<glm::vec3> {f, g, e});
			triangles.push_back(std::vector<glm::vec3> {e, g, h});
		}
	}
};

#endif