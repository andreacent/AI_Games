void drawPoint(vec3 position){
        
    glBegin(GL_POINTS);
        glVertex3f(position.x,position.y,position.z);
    glEnd();
}

void drawTriangleMap(){
    //vec3 t1 = {};
    vec3 t1[3] = {vec3(5,0,34),vec3(5,0,25),vec3(14,0,30)};
    vec3 t2[3] = {vec3(5,0,34),vec3(14,0,30),vec3(14,0,34)};
    vec3 t3[3] = {vec3(5,0,25),vec3(14,0,25),vec3(14,0,30)};
    std::list<vec3*> triangles;
    triangles.push_back( t1 );
    triangles.push_back( t2 );
    triangles.push_back( t3 );

    glColor3f(1,0,0);
    for (list<vec3*>::iterator it = triangles.begin(); it != triangles.end(); ++it ){
        glBegin(GL_LINE_LOOP);
            for (int i=0; i < 3;i++){
                glVertex3f((*it)[i].x,(*it)[i].y,(*it)[i].z);
            }
        glEnd();
    }
}