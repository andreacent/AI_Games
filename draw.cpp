/* 
    Andrea Centeno
    sep-dic 2017
*/

void drawCircle(float px, float pz, float radio, float pointSize) {
    float x,z;
    glPointSize(pointSize);
    glBegin(GL_POINTS);
        for(double i=0.0; i<10; i+=0.001){
            x=radio*cos(i)+px;
            z=radio*sin(i)+pz;
            glVertex3f(x,0,z);
        }
    glEnd();
}

void drawFace(vec2 position,float rot, float pointSize){
    float x = position.x;
    float z = position.y;
    double deg = glm::degrees(-rot);//radianes a grados
    
    glPushMatrix();
        glTranslatef(x,0.0,z);
        glRotatef(deg,0,1,0);

        //head
        drawCircle(0.0,0.0,1.5,pointSize);
        //eyebrows
        glBegin(GL_LINES);
            glVertex3f(-0.3,0.0, 0.6);
            glVertex3f(-1.0,0.0, 0.7);
            glVertex3f(0.3,0.0, 0.6);
            glVertex3f(1.0,0.0, 0.7);
        glEnd();
        //eyes
        glColor3f(1,1,1);
        drawCircle(-0.6, 0.2, 0.2,pointSize);
        drawCircle(0.6, 0.2, 0.2,pointSize);
        //mouth
        glBegin(GL_POLYGON);
            glVertex3f(0.6,0.0,-0.4);
            glVertex3f(-0.6,0.0, -0.4);
            glVertex3f(-0.4,0.0, -0.6);
            glVertex3f(-0.2,0.0, -1.0);
            glVertex3f(0.2, 0.0,-1.0);
            glVertex3f(0.4, 0.0,-0.6);
        glEnd();
        //tongue
        glBegin(GL_POLYGON);
            glColor3f(1,0,0);
            glVertex3f(0,0.0, -0.8);
            glVertex3f(-0.3,0.0, -1.0);
            glVertex3f(0.2,0.0, -1.0);
            glVertex3f(0.4,0.0, -0.8);
        glEnd();

    glPopMatrix();
}