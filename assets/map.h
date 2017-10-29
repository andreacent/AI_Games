#include "../assets/Mesh.h"

float px = 0.2;
list<Mesh*> meshs;


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
            drawTileHallway({j*s,0.0,i*s+(s/2)},color,{0.5,0.5,0.5},{0.6,0.6,0.6});
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
            drawTileGrass({j*s,0.0,i*s+(s/2)});
        }
    }
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

void drawRoofRowV(float xPosition,float zPosition, float hTimes, char lado){
    vec3 main  = {0.7843137254901961,0.7529411764705882,0.7215686274509804};
    vec3 light = {0.8784313725490196,0.8470588235294118,0.7529411764705882};
    vec3 borde = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
    
    vec3 posLight1 = {xPosition+0.5f,0.0,(hTimes/2)+zPosition};
    vec3 posLight2 = {xPosition-0.6f,0.0,(hTimes/2)+zPosition};
    
    vec3 posBorde1 = {xPosition+0.6f,0.0,(hTimes/2)+zPosition};
    vec3 posBorde2 = {xPosition-0.7f,0.0,(hTimes/2)+zPosition};
    vec3 posBorde3 = {xPosition-0.7f,0.0,zPosition-0.05f};
    vec3 posBorde4 = {xPosition-0.7f,0.0,zPosition+hTimes+0.06f};

    glPushMatrix();
        meshs.push_back(new Mesh({{  xPosition,0.0, (hTimes/2)+zPosition-0.01f}, 1.0f*hTimes, 1.0f,main, 'R'}));
        drawSquare(posLight1,light, 0.1f,hTimes);
        drawSquare(posLight2,light, 0.1f,hTimes);
        drawSquare(posBorde1,borde, 0.1f,hTimes);
        drawSquare(posBorde2,borde, 0.1f,hTimes);
        drawSquare(posBorde3,borde, 1.4f,0.1f);
        drawSquare(posBorde4,borde, 1.4f,0.1f);
    glPopMatrix();
}

void drawRoofRowH(float xPosition,float zPosition, float wTimes, char lado){
    vec3 main  = {0.7843137254901961,0.7529411764705882,0.7215686274509804};
    vec3 light = {0.8784313725490196,0.8470588235294118,0.7529411764705882};
    vec3 borde = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
    
    vec3 posBorde1 = {xPosition,0.0,zPosition+0.56f};
    vec3 posBorde2 = {xPosition,0.0,zPosition+0.56f};
    vec3 posBorde3 = {xPosition,0.0,zPosition+0.56f};

    vec3 posLight1 = {xPosition+0.5f,0.0,zPosition};
    vec3 posLight2 = {xPosition+0.5f,0.0,zPosition};
    
    glPushMatrix();
        meshs.push_back(new Mesh({{ (wTimes/2)+xPosition,0.0, zPosition-0.01f}, 1.0f, 1.0f*wTimes,main, 'R'}));
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
    glPopMatrix();
}

void drawWall(float xPosition,float zPosition, float wTimes,char sitio){
    vec3 pared = {0.8196078431372549,0.8352941176470589,0.6980392156862745};
    vec3 piso  = {0.4745098039215686,0.45098039215686275,0.333};
    vec3 borde = {0.3176470588235294,0.3215686274509804,0.4};
    vec3 shadow = {0.7333333333333333,0.7490196078431373,0.7215686274509804};
    vec3 madera = {0.45098039215686275,0.2,5.4901960784313725e-2};

    if(sitio =='S'){
        pared = {1,1,1};
        piso  = {0.3,0.3,0.3};
    }else if ( sitio == 'P'){
        pared = {0.6274509803921569,0.596078431372549,0.6274509803921569};
        piso  = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
        borde  = {0.3137254901960784,0.3137254901960784,0.40784313725490196};
    }else if ( sitio == 'O'){
        pared = { 0.5490196078431373,0.5215686274509804,0.5490196078431373};
        piso  = {0.37254901960784315,0.3803921568627451,0.47843137254901963};
    }

    glPushMatrix();
        meshs.push_back(new Mesh({{ (wTimes/2)+xPosition,0.0, zPosition+0.6f}, 2.0f, (1.0f)*wTimes-0.4f,pared, 'W'}));

        drawSquare({xPosition,0.0, zPosition-0.5f},piso,wTimes,0.25f);
        
        drawSquare({xPosition,0.0, zPosition+0.6f},borde,0.1f,2.0f);
        drawSquare({xPosition+wTimes-0.1f,0.0, zPosition+0.6f},borde,0.1f,2.0f);
        
        drawSquare({xPosition+0.1f,0.0, zPosition+0.6f},shadow,0.1f,2.0f);
        drawSquare({xPosition+wTimes-0.2f,0.0, zPosition+0.6f},shadow,0.1f,2.0f);
        
        if( sitio == 'S' ){
            meshs.push_back(new Mesh({{ (wTimes/2)+xPosition,0.0, zPosition+0.6f}, 0.5f, (1.0f)*wTimes-0.4f,madera, 'W'}));
        }
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

void drawBebedero(float xPosition,float zPosition){
    vec3 main   = {1,0,0};

    float zT = -1;
    float zP = zPosition-0.9f;
    float t = 1.5f;

    glPushMatrix();
        meshs.push_back(new Mesh({{ 1.0f+xPosition,0.0, zPosition+t}, 2.0f,2.0f-0.4f,main, 'O'}));
    glPopMatrix();
}

void drawColumn(float xPosition,float zPosition, float hTimes,char dir){
    vec3 main   = {0.42745098039215684,0.47843137254901963,0.5686274509803921};
    vec3 shadow = {0.34901960784313724,0.34901960784313724,0.44313725490196076};
    vec3 light  = {0.796078431372549,0.792156862745098,0.8235294117647058};

    float zT = -1;
    float zP = zPosition-0.9f;
    float t = 0.5f;

    if( dir == 'U'){
        zT = 1;
        t = 0.3f;
        zP = zPosition+hTimes-1.05f;
    }
    glPushMatrix();

        meshs.push_back(new Mesh({{ 1.0f+xPosition,0.0, (hTimes/2)-t+zPosition}, (1.0f)*hTimes,2.0f-0.4f,main, 'W'}));
        
        drawSquare({xPosition,0.0, (hTimes/2)-0.5f+zPosition},shadow,0.2f,hTimes-0.1f);
        drawSquare({xPosition+1.8f,0.0, (hTimes/2)-0.5f+zPosition},light,0.2f,hTimes-0.1f);

        drawTriangle({xPosition+2.0f-0.4f+0.2f,0.0,zP+0.5f},light,1,zT);
        drawTriangle({xPosition+0.2f,0.0,zP+0.5f},shadow,-1,zT);
    glPopMatrix();
}

list<Mesh*> drawMap(){
    drawFloor();
    // Q1
        /* ===== Paredes  ===== */
            drawWall( 49.0f,35.0f,1,'C');           // wdu1
            drawWall( 45.0f,35.0f,2,'P');           // wdu2
            drawWall( 42.0f,35.0f,1,'P');           // wdu3
            drawWall( 38.0f,35.0f,1,'P');           // wdu4
            drawWall( 35.0f,35.0f,1,'P');           // wdu5
            drawWall( 31.0f,35.0f,1,'P');           // wdu6
            drawWall( 27.0f,35.0f,2,'P');           // wdu7

            drawWall( 49.0f,29.0f,1,'C');           // wdu8
            drawWall( 45.0f,40.0f,8,'C');           // wdu9
            drawWall( 36.0f,40.0f,6,'O');           // wdu10
            drawWall( 27.0f,40.0f,8,'O');           // wdu11
        /* ===== Columnas ===== */
            drawColumn( 29.0f, 34.0f,3,'D');         // cdu1
            drawColumn( 36.0f, 34.0f,3,'D');         // cdu2
            drawColumn( 43.0f, 34.0f,9,'D');         // cdu3
            drawColumn( 47.0f, 34.0f,3,'D');         // cdu4
            drawColumn( 36.0f, 26.0f,1,'U');         // cdu5
        /* ===== Techos   ===== */
            drawRoofRowV( 53.5f,25.5f,17.0f,'r');   // vdu1
            drawRoofRowV( 40.5f,23.0f, 2.5f,'r');   // vdu2
            drawRoofRowV( 33.5f,22.5f, 3.0f,'r');   // vdu3
            drawRoofRowV( 29.5f,22.5f, 3.0f,'r');   // vdu4

            drawRoofRowV( 48.5f, 25.5f,6.0f,'r');    // vdu5

            drawRoofRowV( 42.5f, 36.5f,5.0f,'r');    // vdu6
            drawRoofRowV( 35.5f, 36.5f,5.0f,'r');    // vdu7
            drawRoofRowV( 49.5f, 30.5f,1.0f,'r');    // vdu8

            drawRoofRowH( 30.0f,23.0f,3.0f,'d');    // hdu1
            drawRoofRowH( 34.0f,25.0f,6.5f,'d');    // hdu2
            drawRoofRowH( 49.0f,26.0f,4.5f,'d');    // hdu3
            drawRoofRowH( 27.0f,37.0f,5.0f,'r');    // hdu4
            drawRoofRowH( 35.0f,37.0f,4.0f,'d');    // hdu5
            drawRoofRowH( 45.0f,37.0f,5.0f,'r');    // hdu6
    // Q2
        /* ===== Paredes  ===== */
            drawWall( 23.0f,35.0f,2,'P');           // wiu5
            drawWall( 20.0f,35.0f,1,'P');           // wiu4
            drawWall( 16.0f,35.0f,1,'P');           // wiu3
            drawWall( 13.0f,35.0f,1,'P');           // wiu2
            drawWall(  5.0f,35.0f,5,'P');           // wiu1
            
            drawWall(  1.0f,40.0f,4,'C');           // wiu6
            drawWall(  6.0f,40.0f,7,'S');           // wiu7
            drawWall( 17.0f,40.0f,8,'O');           // wiu8
        /* ===== Columnas ===== */
            drawColumn( 25.0f, 34.0f,9,'D');         // ciu1
            drawColumn( 21.0f, 34.0f,3,'D');         // ciu2
            drawColumn( 14.0f, 34.0f,9,'D');         // ciu3
            drawColumn( 14.0f, 26.0f,1,'U');         // ciu4
        /* ===== Techos   ===== */
            drawRoofRowV( 0.5f,25.5f,17.0f,'l');    // viu1
            drawRoofRowV( 12.5f,23.0f, 2.5f,'r');   // viu2
            drawRoofRowV( 20.5f,22.5f, 3.0f,'r');   // viu3
            drawRoofRowV( 24.5f,22.5f, 3.0f,'r');   // viu4
            drawRoofRowV( 4.5f, 25.5f,4.0f,'r');    // viu5
            drawRoofRowV( 4.5f, 32.5f,5.0f,'r');    // viu6
            drawRoofRowV( 5.5f, 36.5f,5.0f,'r');    // viu7
            drawRoofRowV( 13.5f, 36.5f,5.0f,'r');    // viu8
            drawRoofRowV( 16.5f, 36.5f,5.0f,'r');    // viu9

            drawRoofRowH( 21.0f,23.0f,3.0f,'d');    // hiu1
            drawRoofRowH( 13.0f,25.0f,7.0f,'d');    // hiu2
            drawRoofRowH( 1.0f,26.0f,3.5f,'d');     // hiu3
            drawRoofRowH( 20.0f,37.0f,5.0f,'l');    // hiu4
            drawRoofRowH( 6.0f,37.0f,4.0f,'r');    // hiu5
    // Q3
        /* ===== Paredes  ===== */
            drawWall(  1.0f,15.0f,3,'C');           // wid1
            drawWall(  1.0f, 6.0f,9,'S');           // wid2
            drawWall( 20.0f, 5.0f,5,'P');           // wid3
            
            drawWall( 12.0f,17.0f,2,'P');           // wid5
            drawWall( 16.0f,17.0f,5,'P');           // wid6
            drawWall( 21.0f,18.0f,3,'O');           // wid7
        /* ===== Columnas ===== */
            drawColumn( 14.0f, 0.0f,9,'U');         // cid1
            drawColumn( 25.0f, 0.0f,9,'U');         // cid2
            
            drawColumn( 14.0f,16.0f,3,'D');         // cid3
        /* ===== Techos   ===== */
            drawRoofRowV( 0.5f, 0.0f,17.5f,'l');    // vid1
            drawRoofRowV( 4.5f,12.5f,5.0f,'r');     // vid2
            drawRoofRowV( 13.5f, 0.0f,7.5f,'l');    // vid3
            drawRoofRowV( 16.5f, 0.0f,7.5f,'l');    // vid4
            
            drawRoofRowV( 12.5f, 18.5f,2.0f,'u');   // vid5
            drawRoofRowV( 20.5f, 18.5f,2.0f,'u');   // vid6
            drawRoofRowV( 24.5f, 18.5f,2.0f,'u');   // vid7

            drawRoofRowH( 0.5f,17.0f,4.5f,'r');     // hid1
            drawRoofRowH( 0.5f,8.0f,9.5f,'r');      // hid2
            
            drawRoofRowH( 13.0f,19.0f,7.0f,'d');    // hid3
            drawRoofRowH( 21.0f,20.0f,3.0f,'d');    // hid4
            drawRoofRowH( 20.0f,07.0f,5.0f,'l');    // hid5
    // Q4
        /* ===== Paredes  ===== */
            drawWall( 27.0f, 5.0f,5,'P');           // wdd1
            drawWall( 36.0f, 5.0f,3,'P');           // wdd2
            drawWall( 45.0f, 5.0f,5,'P');           // wdd3
            drawWall( 49.0f, 15.0f,4,'P');          // wdd5
            
            drawWall( 39.0f, 17.0f,2,'P');          // wdd6
            drawWall( 33.0f, 17.0f,4,'P');          // wdd7
            drawWall( 30.0f, 18.0f,3,'O');          // wdd8
        /* ===== Columnas ===== */
            drawColumn( 43.0f, 0.0f,9,'U');         // cdd1
            drawColumn( 47.0f, 7.8f,1,'U');         // cdd2
            
            drawColumn( 37.0f, 16.0f,3,'D');         // cdd3
        /* ===== Techos   ===== */
            drawRoofRowH( 48.0f,17.0f,5.0f,'l');    // hdd1

            drawRoofRowH( 34.0f,19.0f,6.0f,'d');    // hdd2
            drawRoofRowH( 30.0f,20.0f,3.0f,'d');    // hdd3
            
            drawRoofRowH( 27.0f,07.0f,5.0f,'r');    // hdd4
            drawRoofRowH( 36.0f,07.0f,3.0f,'r');    // hdd5
            drawRoofRowH( 45.0f,07.0f,5.0f,'r');    // hdd6

            drawRoofRowV( 53.5f, 0.0f,17.5f,'r');   // vdd1
            drawRoofRowV( 48.5f,12.5f,5.0f,'r');    // vdd2
            drawRoofRowV( 42.5f, 0.0f,7.5f,'r');    // vdd3
            drawRoofRowV( 35.5f, 0.0f,7.5f,'r');    // vdd4

            drawRoofRowV( 40.5f, 18.5f,2.0f,'l');   // vdd5
            drawRoofRowV( 33.5f, 18.5f,2.0f,'l');   // vdd6
            drawRoofRowV( 29.5f, 18.5f,2.0f,'l');   // vdd7
    // DOWN
        drawRoofRowH( 0.0f,0.0f,54.0f,'d');         // hd
        drawRoofRowH( 25.0f,19.0f,5.0f,'d');        // hcd
        drawWall( 24.0f, 17.0f,6,'P');              // wcd
        drawBebedero(26.0f,15.0f);
    // UP
        drawRoofRowH( 0.0f,42.0f,54.0f,'d');        // hu
        drawRoofRowH( 25.0f,25.0f,5.0f,'d');        // hcu
    for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();
    return meshs;
}