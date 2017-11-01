/* 
    Sergio Teran
    11-11020
    sep-dic 2017
*/
#include "../assets/StateMachine.h"
using namespace glm;

class Character{
protected:
	Kinematic &character;
	//StateMachine &stateMachine;

	char rol;


public:

    float px = 0.125/2;

	//Character(Kinematic &c,char rl,StateMachine &sm)  : character(c),rol(rl),stateMachine(sm) {}
	Character(Kinematic &c,char rl)  : character(c),rol(rl) {}


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
		vec3 facing = character.velocity;

		if(facing.x < 0 && abs(facing.x) > abs(facing.z)){
			
	    	drawSideHead(positionH,colorLine,colorSkin,colorSkinS,'l');
		
		}else if(facing.x > 0 && abs(facing.x) > abs(facing.z)){
			
	    	drawSideHead(positionH,colorLine,colorSkin,colorSkinS,'r');
		
		}else if(facing.z > 0 && abs(facing.x) < abs(facing.z)){
		
	    	drawFullHead(positionH,colorLine,colorSkin,colorSkinS,'u');
		
		}else{
		
	    	//drawSideHead(positionH,colorLine,colorSkin,colorSkinS,'r');
	    	drawFullHead(positionH,colorLine,colorSkin,colorSkinS,'d');
		
		}
	}

};