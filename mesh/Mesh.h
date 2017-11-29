#ifndef MESH_H
#define MESH_H

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>
#include <iostream>

class Mesh{
protected:
	glm::vec3 color;
	std::list<std::vector<glm::vec3>> &triangles;
	
public:	

	Mesh(glm::vec3 c) : color(c),triangles(*new std::list<std::vector<glm::vec3>>{}) {}

	void setTriangles(std::list<std::vector<glm::vec3>> &t){ triangles = t; }

	std::list<std::vector<glm::vec3>> getTriangles(){ return triangles;}

	virtual void draw() = 0;
	virtual void createTriangles(bool top, bool right,bool bottom, bool left) = 0;
	virtual bool insideMesh(glm::vec3 point) = 0;

	void printPoint(glm::vec3 p, char c){
		std::cout<<c<<" "<<p.x<<","<<p.y<<","<<p.z<<std::endl;
	}


	/*
	CUBO
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
	

	void drawCube(){	
		GLfloat iX,iY,iZ,fX,fY,fZ;
		
		iX = position.x-(width/2);
		fX = position.x+(width/2);

		iZ = position.z-(height/2);
		fZ = position.z+(height/2);

		iY = 0;
		fY = 0.25;
				
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
	}	

	//Obtiene triangulos de un cubo (type = C)
	std::list<std::vector<glm::vec3>> getTrianglesCube(){
		GLfloat iX,iY,iZ,fX,fY,fZ;
		iX = position.x-(width/2);
		iZ = position.z-(height/2);
		fX = position.x+(width/2);
		fZ = position.z+(height/2);
		iY = -1;
		fY = 1;

		// POINTS 
		glm::vec3 a = {iX, fY, iZ};
		glm::vec3 b = {iX, iY, iZ};
		glm::vec3 c = {fX, fY, iZ};
		glm::vec3 d = {fX, iY, iZ};
		glm::vec3 e = {fX, iY, fZ};
		glm::vec3 f = {iX, iY, fZ};
		glm::vec3 g = {iX, fY, fZ};
		glm::vec3 h = {fX, fY, fZ};

		// TRIANGLES 
		return std::list<std::vector<glm::vec3>> { 
				  std::vector<glm::vec3> {a, b, c}
				, std::vector<glm::vec3> {c, b, d}
				, std::vector<glm::vec3> {c, d, e}
				, std::vector<glm::vec3> {e, d, b}//piso (y)
				, std::vector<glm::vec3> {e, b, f}//piso (y)
				, std::vector<glm::vec3> {f, b, g}
				, std::vector<glm::vec3> {f, g, e}
				, std::vector<glm::vec3> {e, g, h}
				, std::vector<glm::vec3> {e, h, c}				
				, std::vector<glm::vec3> {c, h, g}//techo (y)
				, std::vector<glm::vec3> {c, g, a}//techo (y)
				, std::vector<glm::vec3> {a, g, b} };
	}
	*/
};
#endif