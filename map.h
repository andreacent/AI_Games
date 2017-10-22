
    float px = 0.2;
list<Mesh*> meshs;


void drawTileHallway(vec3 position,vec3 colorSqr,vec3 colorLine,vec3 colorDetail){
    
    float x = position.x;
    float z = position.z;
    float pxX = 5*px;
    float pxZ = 5*  px;


    glPushMatrix();
        glTranslatef(x,0.0,z);
        

        glColor3f(colorSqr.x,colorSqr.y,colorSqr.z);
        glBegin(GL_POLYGON);
            glVertex3f(   0, 0.0,  pxZ); //a
            glVertex3f( pxX, 0.0,  pxZ); //b
            glVertex3f( pxX, 0.0,  0); //c
            glVertex3f(   0, 0.0,  0); //d
        glEnd();
        
        glColor3f(colorLine.x,colorLine.y,colorLine.z);
        glBegin(GL_LINES);
            // 1
            glVertex3f( 0,  0.0,  0);
            glVertex3f( 0,  0.0,  pxZ);

            // 2
            glVertex3f( 0,  0.0,  0);
            glVertex3f( pxX,  0.0,0);

            // 3
            glVertex3f( 0,  0.0,  pxZ);
            glVertex3f( pxX,  0.0,pxZ);

            // 4
            glVertex3f( pxX,  0.0,  pxZ);
            glVertex3f( pxX,  0.0,pxZ);

            glColor3f(colorDetail.x,colorDetail.y,colorDetail.z);
            // d1
            glVertex3f( 0.1,  0.0, 0.2);
            glVertex3f( 0.2,  0.0,0.4);

            // d2
            glVertex3f( 0.4,  0.0, 0.8);
            glVertex3f( 0.3,  0.0,0.9);

            // d3
            glVertex3f( 0.5,  0.0, 0.9);
            glVertex3f( 0.7,  0.0,0.7);
            
        glEnd();
        
    glPopMatrix();
}

void drawFloor(){

    float s = 5.0*px;

	glPushMatrix();

	    glTranslatef(0.0,0.0,0.0);

	    for(int i = 0 ; i < 11 ; i++){
	    	for(int j = -0; j < 45; j++){
				
                drawTileHallway({j*s,0.0,i*s+(s/2)},
                                {0.7,0.7,0.7},
                                {0.5,0.5,0.5},
                                {0.4,0.4,0.4});

	    	}
	    }

	glPopMatrix();
}

void drawMap(){
    meshs.push_back(new Mesh({{  0.0,0.0, 0.0}, 24.0, 2.0,{ 0.3, 0.3, 0.3}, 'R'})); // (0,0)
    drawFloor();
    for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();

}