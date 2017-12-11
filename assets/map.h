/* 
    Sergio Teran
    sep-dic 2017
*/
#ifndef MAP_H
#define MAP_H

#include "../mesh/Mesh.cpp"

float px = 0.2;
list<Mesh*> meshsM;

void drawTileHallway(vec3 position,vec3 colorSqr,vec3 colorLine,vec3 colorDetail){
    
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

void drawSquareFloor(float i1, float i2, float j1, float j2, vec3 color){
    float s = 5.0*px;
    for(int i = i1 ; i < i2 ; i++){
        for(int j = j1; j < j2; j++){
            drawTileHallway({j*s,0.0,i*s+(s/2)-0.5},color,{0.5,0.5,0.5},{0.6,0.6,0.6});
        }
    }
}

void drawTileGrass(vec3 position){
    vec3 colorSqr  = {0.3,0.8,0.2};
    vec3 colorLine = {0.4,0.9,0.2};
    
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
        glEnd();
    glPopMatrix();
}

void drawSquareGrass(float i1, float i2, float j1, float j2){
    float s = 5.0*px;
    for(int i = i1 ; i < i2 ; i++){
        for(int j = j1; j < j2; j++){
            drawTileGrass({j*s,0.0,i*s+(s/2)-0.5});
        }
    }
}

void drawSquare(vec3 position,vec3 colorSqr,float timesX,float timesZ){
    float x = position.x;
    float y = position.y;
    float z = position.z;
    float pxX = 1.0f*timesX;
    float pxZ = 1.0f*timesZ;

    glPushMatrix();
        glPointSize(px);
        glTranslatef(x,0.0,z);
        
        glColor3f(colorSqr.x,colorSqr.y,colorSqr.z);
        glBegin(GL_POLYGON);
            glVertex3f(   0, y, -pxZ/2); //a
            glVertex3f(   0, y,  pxZ/2); //d
            glVertex3f( pxX, y,  pxZ/2); //b
            glVertex3f( pxX, y, -pxZ/2); //c
        glEnd();
    glPopMatrix();
}

void drawFloor(){
    vec3 white         = {0.9,0.9,0.9};
    vec3 whiteSombra   = {0.7,0.7,0.7};
    vec3 pasillo       = {0.8235294117647058,0.8235294117647058,0.6352941176470588};
    vec3 pasilloSombra = {0.7254901960784313,0.7254901960784313,0.5372549019607843};
	glPushMatrix();

	    glTranslatef(0.0,0.0,0.0);

        // PASILLO PRINCIPAL Q3 - Q4
        drawSquareFloor(7,21,0,54,pasilloSombra);
        drawSquareFloor(0,7,17,53,pasilloSombra);
        // ILUMINADO
        drawSquareFloor(9,21,6,12,pasillo);
        drawSquareFloor(9,14,11,12,pasillo);
        drawSquareFloor(10,12,12,41,pasillo);
        drawSquareFloor(9,14,18,23,pasillo);
        drawSquareFloor(12,14,22,35,pasillo);
        drawSquareFloor(9,10,30,41,pasillo);
        drawSquareFloor(10,14,41,47,pasillo);
        drawSquareFloor(14,21,41,47,pasillo);
        drawSquareFloor(17,21,47,54,pasillo);
        drawSquareFloor(17,21,0,11,pasillo);
        // PASILLO PRINCIPAL Q1 - Q2
        // SOMBRA
        drawSquareFloor(21,42,0,54,pasilloSombra);
        drawSquareFloor(0,7,17,53,pasilloSombra);
        // ILUMINADO
        drawSquareFloor(21,32,5,12,pasillo);
        drawSquareFloor(21,25,0,5,pasillo);
        drawSquareFloor(28,31,12,18,pasillo);
        drawSquareFloor(27,32,18,34,pasillo);
        drawSquareFloor(28,31,34,39,pasillo);
        drawSquareFloor(28,32,39,41,pasillo);
        drawSquareFloor(27,31,41,46,pasillo);
        drawSquareFloor(27,30,46,47,pasillo);
        drawSquareFloor(21,27,41,47,pasillo);
        drawSquareFloor(21,25,47,54,pasillo);
        // SALA
        drawSquareFloor(0,7,0,13,white);
        drawSquareFloor(4,5,1,10,whiteSombra);
        // LDC
        drawSquareFloor(26,36,1,5,white);
        drawSquareFloor(36,41,1,13,whiteSombra);
        drawSquareFloor(34,37,10,13,whiteSombra);
        // DEPARTAMENTO
        drawSquareFloor(26,36,49,52,white);
        drawSquareFloor(36,41,45,53,whiteSombra);
        drawSquareFloor(26,41,52,53,whiteSombra);
        // COORDINACION
        drawSquareFloor(7,16,0,5,white);
        drawSquareFloor(8,14,0,2,whiteSombra);
        drawSquareFloor(12,14,2,4,whiteSombra);
        // BAÑOS
        drawSquareFloor(16,18,21,33,whiteSombra);
        drawSquareFloor(23,25,21,24,whiteSombra);
        drawSquareFloor(23,25,30,33,whiteSombra);
        // GRAMA
        drawSquareGrass(19,24,13,20);
        drawSquareGrass(20,22,20,25);
        drawSquareGrass(19,24,25,29);
        drawSquareGrass(20,22,29,34);
        drawSquareGrass(19,24,34,40);
	glPopMatrix();
}


    void drawRoofRowV(float xi, float yi, float h, char lado){
        vec3 main  = {0.7843137254901961,0.7529411764705882,0.7215686274509804};
        vec3 light = {0.8784313725490196,0.8470588235294118,0.7529411764705882};
        vec3 borde = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
        
        //vec3 posLight1 = {xPosition+0.5f,0.0,(hTimes/2)+zPosition};
        //vec3 posLight2 = {xPosition-0.6f,0.0,(hTimes/2)+zPosition};
        
        //vec3 posBorde1 = {xPosition+0.6f,0.0,(hTimes/2)+zPosition};
        //vec3 posBorde2 = {xPosition-0.7f,0.0,(hTimes/2)+zPosition};
        //vec3 posBorde3 = {xPosition-0.7f,0.0,zPosition-0.05f};
        //vec3 posBorde4 = {xPosition-0.7f,0.0,zPosition+hTimes+0.06f};

        glPushMatrix();

            meshsM.push_back(new RectanglePoints(main,new glm::vec3[4]{
                                                                    glm::vec3(xi  ,0,(yi  )),   // i
                                                                    glm::vec3(xi  ,0,(yi+h)),   // a
                                                                    glm::vec3(xi+1,0,(yi  )),   // b
                                                                    glm::vec3(xi+1,0,(yi+h))    // f
                                                                    },  
                                                            true,true,true,true )  );
            /*
            drawSquare(posLight1,light, 0.1f,hTimes);
            drawSquare(posLight2,light, 0.1f,hTimes);
            drawSquare(posBorde1,borde, 0.1f,hTimes);
            drawSquare(posBorde2,borde, 0.1f,hTimes);
            drawSquare(posBorde3,borde, 1.4f,0.1f);
            drawSquare(posBorde4,borde, 1.4f,0.1f);
            */
        glPopMatrix();
    }

    void drawRoofRowH(float xi, float yi, float w, char lado){
        vec3 main  = {0.7843137254901961,0.7529411764705882,0.7215686274509804};
        vec3 light = {0.8784313725490196,0.8470588235294118,0.7529411764705882};
        vec3 borde = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
        
        /*
        vec3 posBorde1 = {xPosition,0.0,zPosition+0.56f};
        vec3 posBorde2 = {xPosition,0.0,zPosition+0.56f};
        vec3 posBorde3 = {xPosition,0.0,zPosition+0.56f};

        vec3 posLight1 = {xPosition+0.5f,0.0,zPosition};
        vec3 posLight2 = {xPosition+0.5f,0.0,zPosition};
        */

        glPushMatrix();
            meshsM.push_back(new RectanglePoints(main,new glm::vec3[4]{
                                                                    glm::vec3(xi  ,0,(yi  )),   // i
                                                                    glm::vec3(xi  ,0,(yi+1)),   // a
                                                                    glm::vec3(xi+w,0,(yi  )),   // b
                                                                    glm::vec3(xi+w,0,(yi+1))    // f
                                                                    },  
                                                            true,true,true,true )  );
            /*
            meshsM.push_back(new Mesh({{ (wTimes/2)+xPosition,0.0, zPosition-0.01f}, 1.0f, 1.0f*wTimes,main, 'R'}));
            drawSquare(posBorde1,borde, wTimes+0.2f, 0.1f);

            if(lado == 'r'){
                posLight1 = {xPosition+wTimes,0.0,zPosition};
                posBorde2 = {xPosition+wTimes+0.1f,0.0,zPosition};
                drawSquare(posLight1,light, 0.1f, 1.0f);
                drawSquare(posBorde2,borde, 0.1f, 1.0f);
            }else if (lado == 'l'){
                posLight1 = {xPosition-0.1f,0.0,zPosition};
                posBorde2 = {xPosition-0.2f,0.0,zPosition};
                drawSquare(posLight1,light, 0.1f, 1.0f);
                drawSquare(posBorde2,borde, 0.1f, 1.0f);
            }else if(lado== 'd'){

                posLight2 = {xPosition+wTimes,0.0,zPosition};
                posBorde3 = {xPosition+wTimes+0.1f,0.0,zPosition};
                drawSquare(posLight2,light, 0.1f, 1.0f);
                drawSquare(posBorde3,borde, 0.1f, 1.0f);

                posLight1 = {xPosition-0.1f,0.0,zPosition};
                posBorde2 = {xPosition-0.2f,0.0,zPosition};
                drawSquare(posLight1,light, 0.1f, 1.0f);
                drawSquare(posBorde2,borde, 0.1f, 1.0f);
            }
            */
        glPopMatrix();
    }

    void drawWallDetails(float xi, float yi, float w,char sitio){

        vec3 piso  = {0.4745098039215686,0.45098039215686275,0.333};
        vec3 borde = {0.3176470588235294,0.3215686274509804,0.4};
        vec3 shadow = {0.7333333333333333,0.7490196078431373,0.7215686274509804};
        vec3 madera = {0.45098039215686275,0.2,5.4901960784313725e-2};

        if(sitio =='S'){
            piso  = {0.3,0.3,0.3};
        }else if ( sitio == 'P'){
            piso  = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
            borde  = {0.3137254901960784,0.3137254901960784,0.40784313725490196};
        }else if ( sitio == 'O'){
            piso  = {0.37254901960784315,0.3803921568627451,0.47843137254901963};
        }

        glPushMatrix();
            drawSquare({xi,0.0, yi-0.9},piso,w,0.25);
            /*
            drawSquare({xi-0.1f  ,0.0, yi},borde,0.1f,2.0f);
            drawSquare({xi+0.1f+w,0.0, yi},borde,0.1f,2.0f);
            
            drawSquare({xi  ,0.0, yi-0.1},shadow,0.1f,2.0f);
            drawSquare({xi+w,0.0, yi},shadow,0.1f,2.0f);
            */   
        glPopMatrix();

    }


    void drawWall(float xi, float yi, float w,char sitio){
        vec3 pared = {0.8196078431372549,0.8352941176470589,0.6980392156862745};

        if(sitio =='S'){
            pared = {1,1,1};
        }else if ( sitio == 'P'){
            pared = {0.6274509803921569,0.596078431372549,0.6274509803921569};
        }else if ( sitio == 'O'){
            pared = { 0.5490196078431373,0.5215686274509804,0.5490196078431373};
        }

        glPushMatrix();
            meshsM.push_back(new RectanglePoints(pared,new glm::vec3[4]{
                                                                    glm::vec3(xi  ,0,(yi-0.8)),   // i
                                                                    glm::vec3(xi  ,0,(yi+1  )),   // a
                                                                    glm::vec3(xi+w,0,(yi-0.8)),   // b
                                                                    glm::vec3(xi+w,0,(yi+1  ))    // f
                                                                    },  
                                                            true,true,true,true )  );

        glPopMatrix();
    }
    void drawTriangle(vec3 position,vec3 colorSqr, float directionX,float directionZ){
            float timesX = 1;
            float timesZ = 1;
            float x = position.x;
            float z = position.z;
            float pxX = px*timesX;
            float pxZ = px*timesZ;

            glPushMatrix();
                glPointSize(px);
                glTranslatef(x,0.0,z);
                
                glColor3f(colorSqr.x,colorSqr.y,colorSqr.z);
                glBegin(GL_POLYGON);
                    glVertex3f( 0.0, 0.0, 0.0); //a
                    glVertex3f( 0.0, 0.0, directionZ* pxZ); //b
                    glVertex3f( directionX*pxX, 0.0, 0.0); //c
                glEnd();
                
            glPopMatrix();
    }
/*

    void drawBebedero(float xPosition,float zPosition){
        vec3 main   = {1,0,0};

        float zT = -1;
        float zP = zPosition-0.9f;
        float t = 1.5f;

        glPushMatrix();
            meshsM.push_back(new Mesh({{ 1.0f+xPosition,0.0, zPosition+t}, 2.0f,2.0f-0.4f,main, 'O'}));
        glPopMatrix();
    }
*/

    void drawColumnDetails(float xi, float yi, float h,char dir){
        vec3 shadow = {0.34901960784313724,0.34901960784313724,0.44313725490196076};
        vec3 light  = {0.796078431372549,0.792156862745098,0.8235294117647058};


        float yT = -1;
        float yP = yi-0.9f;
        float t = 0.5f;

        if( dir == 'U'){
            yT = 0;
            t = 0.3f;
            yP = yi+h-1.05f;
        }

            
        glPushMatrix();
            drawSquare({xi     ,0.0, (h/2)+yi-1},shadow,0.2f,h-0.1f);
            drawSquare({xi+1.8f,0.0, (h/2)+yi-1},light ,0.2f,h-0.1f);

            drawTriangle({xi+2.0f-0.4f+0.2f,0.0,yP+0.5f},light , 1,yT);
            drawTriangle({xi+0.2f          ,0.0,yP+0.5f},shadow,-1,yT);
        glPopMatrix();
    }

    void drawColumn(float xi, float yi, float h,char dir){
        vec3 main   = {0.42745098039215684,0.47843137254901963,0.5686274509803921};

        float yT = -1;

        if( dir == 'U'){
            yT = 0;
        }

        glPushMatrix();

            meshsM.push_back(new RectanglePoints(main,new glm::vec3[4]{
                                                                    glm::vec3(xi+0.1,0,(yi+yT)),   // i
                                                                    glm::vec3(xi+0.1,0,(yi+h+yT)),   // a
                                                                    glm::vec3(xi+1.9,0,(yi+yT  )),   // b
                                                                    glm::vec3(xi+1.9,0,(yi+h+yT))    // f
                                                                    },  
                                                            true,true,true,true ));
        glPopMatrix();
    }


void drawDetails(){
    drawWallDetails( 49,35,1,'C');           // wdu1
    drawWallDetails( 45,35,2,'P');           // wdu2
    drawWallDetails( 42,35,1,'P');           // wdu3
    drawWallDetails( 38,35,1,'P');           // wdu4
    drawWallDetails( 35,35,1,'P');           // wdu5
    drawWallDetails( 31,35,1,'P');           // wdu6
    drawWallDetails( 27,35,2,'P');           // wdu7

    drawWallDetails( 49,29,1,'C');           // wdu8
    drawWallDetails( 45,40,8,'C');           // wdu9
    drawWallDetails( 36,40,6,'O');           // wdu10
    drawWallDetails( 27,40,8,'O');           // wdu11

    drawColumnDetails( 29, 34,3,'D');         // cdu1
    drawColumnDetails( 36, 34,3,'D');         // cdu2
    drawColumnDetails( 43, 34,9,'D');         // cdu3
    drawColumnDetails( 47, 34,3,'D');         // cdu4
    drawColumnDetails( 36, 26,1,'U');         // cdu5

    /* ============================================= */

    drawWallDetails( 23,35,2,'P');           // wiu5
    drawWallDetails( 20,35,1,'P');           // wiu4
    drawWallDetails( 16,35,1,'P');           // wiu3
    drawWallDetails( 13,35,1,'P');           // wiu2
    drawWallDetails(  5,35,5,'P');           // wiu1
    
    drawWallDetails(  1,40,4,'C');           // wiu6
    drawWallDetails(  6,40,7,'S');           // wiu7
    drawWallDetails( 17,40,8,'O');           // wiu8

    drawColumnDetails( 25, 34,9,'D');         // ciu1
    drawColumnDetails( 21, 34,3,'D');         // ciu2
    drawColumnDetails( 14, 34,9,'D');         // ciu3
    drawColumnDetails( 14, 26,1,'U');         // ciu4

    /* ============================================= */

    drawWallDetails(  1,15,3,'C');           // wid1
    drawWallDetails(  1, 6,9,'S');           // wid2
    drawWallDetails( 20, 5,5,'P');           // wid3
            
    drawWallDetails( 12,17,2,'P');           // wid5
    drawWallDetails( 16,17,5,'P');           // wid6
    drawWallDetails( 21,18,3,'O');           // wid7

    drawColumnDetails( 14, 0,9,'U');         // cid1
    drawColumnDetails( 25, 0,9,'U');         // cid2

    drawColumnDetails( 14,16,3,'D');         // cid3

    /* ============================================= */

    drawWallDetails( 27, 5,5,'P');           // wdd1
    drawWallDetails( 36, 5,3,'P');           // wdd2
    drawWallDetails( 45, 5,5,'P');           // wdd3
    drawWallDetails( 49, 15,4,'P');          // wdd5
    
    drawWallDetails( 39, 17,2,'P');          // wdd6
    drawWallDetails( 33, 17,4,'P');          // wdd7
    drawWallDetails( 30, 18,3,'O');          // wdd8

    drawColumnDetails( 43, 0,9,'U');         // cdd1
    drawColumnDetails( 47, 7,1,'U');         // cdd2

    drawColumnDetails( 37, 16,3,'D');         // cdd3
}


list<Mesh*> drawMap(){

    // Q1
        /* ===== Paredes  ===== */
            drawWall( 49,35,1,'C');           // wdu1
            drawWall( 45,35,2,'P');           // wdu2
            drawWall( 42,35,1,'P');           // wdu3
            drawWall( 38,35,1,'P');           // wdu4
            drawWall( 35,35,1,'P');           // wdu5
            drawWall( 31,35,1,'P');           // wdu6
            drawWall( 27,35,2,'P');           // wdu7

            drawWall( 49,29,1,'C');           // wdu8
            drawWall( 45,40,8,'C');           // wdu9
            drawWall( 36,40,6,'O');           // wdu10
            drawWall( 27,40,8,'O');           // wdu11
        /* ===== Columnas ===== */
            drawColumn( 29, 34,3,'D');         // cdu1
            drawColumn( 36, 34,3,'D');         // cdu2
            drawColumn( 43, 34,9,'D');         // cdu3
            drawColumn( 47, 34,3,'D');         // cdu4
            drawColumn( 36, 25,1,'U');         // cdu5
        /* ===== Techos   ===== */
            drawRoofRowV(53,25,17,'r');   // vdu1
            drawRoofRowV(40,23, 2,'r');   // vdu2
            drawRoofRowV(33,22, 3,'r');   // vdu3
            drawRoofRowV(29,22, 3,'r');   // vdu4
            drawRoofRowV(48,25,6,'r');    // vdu5
            drawRoofRowV(42,36,5,'r');    // vdu6
            drawRoofRowV(35,36,5,'r');    // vdu7
            drawRoofRowV(49,30,1,'r');    // vdu8

            drawRoofRowH( 30,22,3,'d');    // hdu1
            drawRoofRowH( 34,24,6,'d');    // hdu2
            drawRoofRowH( 49,25,4,'d');    // hdu3
            drawRoofRowH( 27,36,5,'r');    // hdu4
            drawRoofRowH( 35,36,4,'d');    // hdu5
            drawRoofRowH( 45,36,5,'r');    // hdu6
            /*
    // Q2
        /* ===== Paredes  ===== */
            drawWall( 23,35,2,'P');           // wiu5
            drawWall( 20,35,1,'P');           // wiu4
            drawWall( 16,35,1,'P');           // wiu3
            drawWall( 13,35,1,'P');           // wiu2
            drawWall(  5,35,5,'P');           // wiu1
            
            drawWall(  1,40,4,'C');           // wiu6
            drawWall(  6,40,7,'S');           // wiu7
            drawWall( 17,40,8,'O');           // wiu8
        /* ===== Columnas ===== */
            drawColumn( 25, 34,9,'D');         // ciu1
            drawColumn( 21, 34,3,'D');         // ciu2
            drawColumn( 14, 34,9,'D');         // ciu3
            drawColumn( 14, 25,1,'U');         // ciu4
        /* ===== Techos   ===== */
            drawRoofRowV(  0,25,17,'l');    // viu1
            drawRoofRowV( 12,23, 2,'r');   // viu2
            drawRoofRowV( 20,22, 3,'r');   // viu3
            drawRoofRowV( 24,22, 3,'r');   // viu4
            drawRoofRowV(  4,25, 4,'r');    // viu5
            drawRoofRowV(  4,32, 5,'r');    // viu6
            drawRoofRowV(  5,36, 5,'r');    // viu7
            drawRoofRowV( 13,36, 5,'r');    // viu8
            drawRoofRowV( 16,36, 5,'r');    // viu9

            drawRoofRowH( 21,22,3,'d');    // hiu1
            drawRoofRowH( 13,24,7,'d');    // hiu2
            drawRoofRowH(  1,25,3,'d');     // hiu3
            drawRoofRowH( 20,36,5,'l');    // hiu4
            drawRoofRowH(  6,36,4,'r');    // hiu5
    // Q3
        /* ===== Paredes  ===== */
            drawWall(  1,15,3,'C');           // wid1
            drawWall(  1, 6,9,'S');           // wid2
            drawWall( 20, 5,5,'P');           // wid3
            
            drawWall( 12,17,2,'P');           // wid5
            drawWall( 16,17,5,'P');           // wid6
            drawWall( 21,18,3,'O');           // wid7
        /* ===== Columnas ===== */
            drawColumn( 14, 0,8,'U');         // cid1
            drawColumn( 25, 0,8,'U');         // cid2
            
            drawColumn( 14,16,3,'D');         // cid3
        /* ===== Techos   ===== */
            drawRoofRowV(  0, 0,17,'l');    // vid1
            drawRoofRowV(  4,12, 5,'r');     // vid2
            drawRoofRowV( 13, 0, 7,'l');    // vid3
            drawRoofRowV( 16, 0, 7,'l');    // vid4
            
            drawRoofRowV( 12, 18,2,'u');   // vid5
            drawRoofRowV( 20, 18,2,'u');   // vid6
            drawRoofRowV( 24, 18,2,'u');   // vid7

            drawRoofRowH( 1,16,4,'r');     // hid1
            drawRoofRowH( 1, 7,9,'r');      // hid2
            
            drawRoofRowH( 13,18,7,'d');    // hid3
            drawRoofRowH( 21,19,3,'d');    // hid4
            drawRoofRowH( 20, 6,5,'l');    // hid5
    // Q4
        /* ===== Paredes  ===== */
            drawWall( 27, 5,5,'P');           // wdd1
            drawWall( 36, 5,3,'P');           // wdd2
            drawWall( 45, 5,5,'P');           // wdd3
            drawWall( 49, 15,4,'P');          // wdd5
            
            drawWall( 39, 17,2,'P');          // wdd6
            drawWall( 33, 17,4,'P');          // wdd7
            drawWall( 30, 18,3,'O');          // wdd8
        /* ===== Columnas ===== */
            drawColumn( 43, 0,8,'U');         // cdd1
            drawColumn( 47, 7,1,'U');         // cdd2
            
            drawColumn( 37, 16,3,'D');         // cdd3
        /* ===== Techos   ===== */
            drawRoofRowH( 48,16,5,'l');    // hdd1

            drawRoofRowH( 34,18,6,'d');    // hdd2
            drawRoofRowH( 30,19,3,'d');    // hdd3
            
            drawRoofRowH( 27,06,5,'r');    // hdd4
            drawRoofRowH( 36,06,3,'r');    // hdd5
            drawRoofRowH( 45,06,5,'r');    // hdd6

            drawRoofRowV( 53, 0,17,'r');   // vdd1
            drawRoofRowV( 48,12,5,'r');    // vdd2
            drawRoofRowV( 42, 0,7,'r');    // vdd3
            drawRoofRowV( 35, 0,7,'r');    // vdd4

            drawRoofRowV( 40, 18,2,'l');   // vdd5
            drawRoofRowV( 33, 18,2,'l');   // vdd6
            drawRoofRowV( 29, 18,2,'l');   // vdd7
    // DOWN
        drawRoofRowH(  0, 0,54,'d');         // hd
        drawRoofRowH( 25,18, 5,'d');        // hcd
        drawWall( 24, 17,6,'P');              // wcd
        //drawBebedero(26,15);
    // UP
        drawRoofRowH(  0,41,54,'d');        // hu
        drawRoofRowH( 25,24,5,'d');        // hcu
    
    for (list<Mesh*>::iterator m=meshsM.begin(); m != meshsM.end(); ++m) (*m)->draw();
    return meshsM;
}

#endif