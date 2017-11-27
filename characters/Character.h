/* 
	Sergio Teran
	11-11020
	sep-dic 2017
*/
#include "../assets/StateMachine.h"
using namespace glm;

class Character{
protected:
	StateMachine *stateMachine = NULL;

	char rol;
	char orientation = 'd';


public:
	Kinematic &character;

	float px = 0.125/2;

	Character(Kinematic &c,char rl,StateMachine *sm)  : character(c),rol(rl),stateMachine(sm) {}
	Character(Kinematic &c,char rl)  : character(c),rol(rl) {}

	void setStateMachine(StateMachine *s){ stateMachine = s; }
	void checkStateMachine(){ stateMachine->check(); }

	/**************** GUIDES ****************/
	void drawOrigin(){
		//origin
		glColor3f(0,0,1);
		glBegin(GL_LINES);
			glVertex3f(   1, 0, 0);
			glVertex3f(  -1, 0, 0);

			glVertex3f(  0, 0, 1);
			glVertex3f(  0, 0, -1);
		glEnd();
	}

	void drawLineV(float x){
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex3f( x, 0,  9);
			glVertex3f( x, 0, -9);
		glEnd();  
	}

	void drawLineH(float z){
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex3f( -7, 0, z);
			glVertex3f(  7, 0, z);
		glEnd();  
	}

	void drawGuide(int x, int z){
			
		for(int i = 0; i <= x; i++){
			drawLineV(-i*1.0);
			drawLineV(i*1.0);
		}
		
		for(int j = 0; j <= z; j++){
			drawLineH(-j*1.0);
			drawLineH(j*1.0);
		}

		drawOrigin();
	}

	/**************** SQUARE ****************/
	void drawSquare(vec3 position,vec3 colorSqr,float timesX,float timesZ){
		float x = position.x;
		float z = position.z;
		float pxX = px*timesX;
		float pxZ = px*timesZ;

		glPushMatrix();
			glPointSize(px);

			glTranslatef(x,0.0,z);
			
			glColor3f(colorSqr.x,colorSqr.y,colorSqr.z);

			glBegin(GL_POLYGON);
				glVertex3f(   0, 0.0,  pxZ); //a
				glVertex3f( pxX, 0.0,  pxZ); //b
				glVertex3f( pxX, 0.0,  0); //c
				glVertex3f(   0, 0.0,  0); //d
			glEnd();
			
		glPopMatrix();
	}

	void drawMirrorX(vec3 position,float transX,float transZ,vec3 colorSqr,float timesX,float timesZ){
		float x = position.x+transX*px;
		float z = position.z+transZ*px;

		drawSquare({  2*x,position.y,2*z },colorSqr, 2*timesX, 2*timesZ);
		drawSquare({ -2*x,position.y,2*z },colorSqr,-2*timesX, 2*timesZ);
	}

	/**************** HEAD ****************/
	void drawSideHead(vec3 positionH,vec3 colorLine,vec3 colorSkin,vec3 colorSkinS,char dir){

		float x = positionH.x;
		float y = positionH.y;
		float z = positionH.z-1*px;

		float w = 1;
		float t = 0;
		float tc = 0;

		if( dir == 'l'){x -=1*px;}
		if( dir == 'r'){w = -1;t = -2;tc=2;}

		//piel
		drawSquare({   w*2*(x+-(-2+t+tc)*px),y,2*(z+ -3*px) },colorSkin, 2*1, 2* 1);
		drawSquare({   w*2*(x+-(3+t-tc)*px),y,2*(z+ 0*px) },colorSkin, 2*5, 2* -5);

		//head
		drawSquare({   2*(x+-(4+t)*px),y,2*(z+ 0*px) },colorLine, 2*7, 2* 1);
		drawSquare({ w*2*(x+- 4   *px),y,2*(z+ 0*px) },colorLine, 2*1, 2*-4);
		drawSquare({ w*2*(x+- 3   *px),y,2*(z+-5*px) },colorLine, 2*1, 2* 1);
		drawSquare({ w*2*(x+-(2+(t+(t/2)))*px),y,2*(z+-6*px) },colorLine, 2*4, 2* 1);
		drawSquare({ w*2*(x+  1   *px),y,2*(z+-5*px) },colorLine, 2*1, 2* 1);
		drawSquare({ w*2*(x+  2   *px),y,2*(z+-4*px) },colorLine, 2*1, 2* 1);
		drawSquare({ w*2*(x+  3   *px),y,2*(z+-2*px) },colorLine, 2*1, 2*-2);
		drawSquare({ w*2*(x+  2   *px),y,2*(z+ 0*px) },colorLine, 2*1, 2*-2);
		
		drawSquare({ w*2*(x+ -1*px),y,2*(z+ -2*px) },colorLine, 2*1, 2*-2);
	}

	void drawFullHead(vec3 positionH,vec3 colorLine,vec3 colorSkin,vec3 colorSkinS, char dir){
		
		//piel
		drawMirrorX(positionH,0, 0,colorSkin,5,-4);
		drawMirrorX(positionH,0,-5,colorSkin,3, 1);
	   
		//eyes
		if( dir == 'd'){
			drawMirrorX(positionH,1,-4,colorLine,1,2);
			drawMirrorX(positionH,0,-5,colorSkinS,1,1);
		}

		//head
		drawMirrorX({positionH.x,positionH.y,positionH.z},0,0,colorLine,5,1);
		drawMirrorX(positionH,4, 0,colorLine,1,-2);
		drawMirrorX(positionH,5,-2,colorLine,1,-2);
		drawMirrorX(positionH,4,-4,colorLine,1, 1);
		drawMirrorX(positionH,3,-4,colorLine,1,-2);
		drawMirrorX(positionH,0,-6,colorLine,4, 1);
	}

	void drawHead(vec3 positionH,vec3 colorLine,vec3 colorSkin,vec3 colorSkinS){
		switch(orientation) 
		{
			case 'l':  
			case 'r':     
				drawSideHead(positionH,colorLine,colorSkin,colorSkinS,orientation);
			break;
			case 'u':  
			case 'd':
				drawFullHead(positionH,colorLine,colorSkin,colorSkinS,orientation);
			break;
			default: break;
		}
	}

	double setOrientation(){
		glm::vec3 facing = character.velocity;
		double deg;

		if(rol !='t' && glm::length(facing) > 0){				
			if(facing.x < 0 && abs(facing.x) > abs(facing.z)) orientation = 'l';		
			else if(facing.x > 0 && abs(facing.x) > abs(facing.z)) orientation = 'r';		
			else if(facing.z > 0 ) orientation = 'u';		
			else orientation = 'd';
			return 0.0;	
		}

		if(character.orientation != 0 && glm::length(facing) == 0) { //no tiene velocidad
			deg = glm::degrees(character.orientation);
		}
		else if (glm::length(facing) > 0) { //tiene velocidad			
			deg = glm::degrees(atan2(facing.x, facing.z)) + 180;
		}
		else { //orientacion = 0 y no tiene velocidad 	
			orientation='d';
			return 0.0;	
		}

		if ( deg > 360 || deg < -360 ) deg = (int)deg % 360;
		if ( deg < 0 ) deg = 360 + deg;

		switch((int)deg) 
		{
			case 360: 
			case 0:    
				orientation = 'd';
				return 0.0;
			case 90:     
				orientation = 'l';
				return 0.0;
			case 180: 
				orientation = 'u';
				return 0.0; 
			case 270:
				orientation = 'r';
				return 0.0; 
			default: break;
		}

		double deg90 = (int)deg % 90;

		if ( deg > 135 && deg < 225 ){//espalda
			orientation = 'u';
			return deg90;
		}
		else if( deg >= 225 && deg <= 270 ){//derecha + arriba
			orientation = 'r';
			return -deg90;
		}
		else if( deg > 270 && deg <= 315 ){//derecha + abajo
			orientation = 'r';
			return deg90;
		}
		else if( deg > 315 && deg < 360 ){//frente derecha
			orientation = 'd';
			return deg;
		}
		else if( deg > 0 && deg < 45 ){//frente izquierda
			orientation = 'd';
			return deg90;
		}
		else if( deg >= 45 && deg < 90 ){//izquierda + abajo
			orientation = 'l';
			return -deg90;
		}
		else if( deg > 90 && deg <= 135 ){//izquierda + arriba
			orientation = 'l';
			return deg90;
		}

		return 0.0;
	}

};