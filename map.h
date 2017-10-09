
    float px = 0.2;

void drawTile(vec3 position,vec3 colorSqr,vec3 colorLine){
    float x = position.x;
    float z = position.z;
    float pxX = 5*px;
    float pxZ = 5*px;

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
            glVertex3f( 0,  0.0,  0);
            glVertex3f( 0,  0.0,  pxZ);

            glVertex3f( 0,  0.0,  0);
            glVertex3f( pxX,  0.0,0);

            glVertex3f( 0,  0.0,  pxZ);
            glVertex3f( pxX,  0.0,pxZ);

            glVertex3f( pxX,  0.0,  pxZ);
            glVertex3f( pxX,  0.0,pxZ);
            
        glEnd();
        
    glPopMatrix();
}

void drawFloor(){
	glPushMatrix();

	    glTranslatef(0.0,0.0,0.0);
	    for(int i = -9 ; i < 11 ; i++){
	    	for(int j = -45; j < 45; j++){
				drawTile({j*5.0*px,0.0,i*5.0*px+px*2.5},{0.7,0.7,0.7},{0.5,0.5,0.5});
	    	}
	    }

	glPopMatrix();
}