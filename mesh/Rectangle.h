#ifndef M_RECTANGLE_H
#define M_RECTANGLE_H

#include "Mesh.h"

class Rectangle: public Mesh{
protected:
	GLfloat height;
	GLfloat width;
	glm::vec3 position;
public:	
	Rectangle(glm::vec3 c, glm::vec3 p, GLfloat h, GLfloat w) 
		: Mesh(c), position(p),height(h),width(w) {}

	Rectangle(glm::vec3 c, glm::vec3 p, GLfloat h, GLfloat w,
				bool top, bool right,bool bottom, bool left) 
				: Mesh(c), position(p),height(h),width(w) {
			createTriangles(top, right,bottom, left);
		}

	void draw(){		
		GLfloat iX,iY,iZ,fX,fY,fZ;
		
		iX = position.x-(width/2);
		fX = position.x+(width/2);

		iZ = position.z-(height/2);
		fZ = position.z+(height/2);

		iY = 0;
		
    	glColor3f(color.x,color.y,color.z);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(fX, iY, iZ); 
		glVertex3f(fX, iY, fZ); 
		glVertex3f(iX, iY, iZ); 
		glVertex3f(iX, iY, fZ); 		
		glEnd();
	}	

	void createTriangles(bool top, bool right,bool bottom, bool left){
		GLfloat iX,iY,iZ,fX,fY,fZ;
		iX = position.x-(width/2);
		iZ = position.z-(height/2);
		fX = position.x+(width/2);
		fZ = position.z+(height/2);
		iY = -1;
		fY = 1;

		/* POINTS */
		glm::vec3 a = {iX, fY, iZ};
		glm::vec3 b = {iX, iY, iZ};
		glm::vec3 c = {fX, fY, iZ};
		glm::vec3 d = {fX, iY, iZ};
		glm::vec3 e = {fX, iY, fZ};
		glm::vec3 f = {iX, iY, fZ};
		glm::vec3 g = {iX, fY, fZ};
		glm::vec3 h = {fX, fY, fZ};

		triangles.clear();
		
		if(right){
			triangles.push_back(std::vector<glm::vec3> {e, h, c});
			triangles.push_back(std::vector<glm::vec3> {c, d, e});
		}
		if(left){
			triangles.push_back(std::vector<glm::vec3> {f, b, g});
			triangles.push_back(std::vector<glm::vec3> {a, g, b});
		}
		if(top){
			triangles.push_back(std::vector<glm::vec3> {f, g, e});
			triangles.push_back(std::vector<glm::vec3> {e, g, h});
		}
		if(bottom){
			triangles.push_back(std::vector<glm::vec3> {a, b, c});
			triangles.push_back(std::vector<glm::vec3> {c, b, d});
		}
	}

	bool insideMesh(glm::vec3 point){ return false; }
};

#endif