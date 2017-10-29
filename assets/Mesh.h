#ifndef MESH_H
#define MESH_H

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>

class Mesh{
protected:
	GLfloat height;
	glm::vec3 color;
	glm::vec3 position;
	char type; //W:wall, O:obstacle1, H:hole, R:Roof
	
public:	GLfloat width;

	Mesh(glm::vec3 p, GLfloat h, GLfloat w, glm::vec3 c,char t) 
		: position(p),height(h),width(w),color(c),type(t) {}

	/*
		Vertex  Triangle    Face
		------+-----------+-----
		0 0 0
		0 1 0
		1 0 0  000 010 100  **0
		1 1 0  100 010 110  **0
		1 1 1  100 110 111  1**
		0 1 0  111 110 010  *1*
		0 1 1  111 010 011  *1*
		0 0 1  011 010 001  0**
		1 1 1  011 001 111  **1
		1 0 1  111 001 101  **1
		1 0 0  111 101 100  1**
		0 0 1  100 101 001  *0*
		0 0 0  100 001 000  *0*
	
		0 1 0  000 001 010  0**
	*/

	void draw(){	
		GLfloat iX,iY,iZ,fX,fY,fZ;
		
		iX = position.x-(width/2);
		fX = position.x+(width/2);

		iZ = position.z-(height/2);
		fZ = position.z+(height/2);

		iY = 0;
		fY = 0.25;
		
		switch (type){       	
	        case 'W':
	        case 'R': 
	        case 'H':
	        case 'O':

		
	    		glColor3f(color.x,color.y,color.z);
				glBegin(GL_TRIANGLE_STRIP);
				// a,b,c,d,e,b,f,g,e,h,c,g,a,b
				glVertex3f(iX, iY, iZ); //1
				glVertex3f(iX, fY, iZ); //2
				glVertex3f(fX, iY, iZ); //3
				glVertex3f(fX, fY, iZ); //4
				glVertex3f(fX, fY, fZ); //5
				glVertex3f(iX, fY, iZ); //6

				glVertex3f(iX, fY, fZ); //7
				glVertex3f(iX, iY, fZ); //8
				glVertex3f(fX, fY, fZ); //9
				glVertex3f(fX, iY, fZ); //10
				glVertex3f(fX, iY, iZ); //11
				glVertex3f(iX, iY, fZ); //12
				glVertex3f(iX, iY, iZ); //13
				glVertex3f(iX, fY, iZ); //14
					
				glEnd();
	        break;	
	        default: break;
	    } 
	}	

	std::list<std::vector<glm::vec3>> getTriangles(){
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

		/* TRIANGLES */
		return std::list<std::vector<glm::vec3>> { 
			  vector<glm::vec3> {a, b, c}
			, vector<glm::vec3> {c, b, d}
			, vector<glm::vec3> {c, d, e}
			, vector<glm::vec3> {e, d, b}
			, vector<glm::vec3> {e, b, f}
			, vector<glm::vec3> {f, b, g}
			, vector<glm::vec3> {f, g, e}
			, vector<glm::vec3> {e, g, h}
			, vector<glm::vec3> {e, h, c}
			, vector<glm::vec3> {c, h, g}
			, vector<glm::vec3> {c, g, a}
			, vector<glm::vec3> {a, g, b} };
	}
};
#endif