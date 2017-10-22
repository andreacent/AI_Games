
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

void drawSqaureFloor(float i1, float i2, float j1, float j2, vec3 color){
    float s = 5.0*px;
    for(int i = i1 ; i < i2 ; i++){
        for(int j = j1; j < j2; j++){
            
            drawTileHallway({j*s,0.0,i*s+(s/2)},
                            color,
                            {0.5,0.5,0.5},
                            {0.6,0.6,0.6});
        }
    }
}

void drawFloor(){

    vec3 white = {0.9,0.9,0.9};
    vec3 whiteSombra = {0.7,0.7,0.7};
    vec3 pasillo = {0.8235294117647058,0.8235294117647058,0.6352941176470588};
    vec3 pasilloSombra = {0.7254901960784313,0.7254901960784313,0.5372549019607843};
	glPushMatrix();

	    glTranslatef(0.0,0.0,0.0);

        // PASILLO PRINCIPAL Q3 - Q4
        // PASILLO 1-Q3/Q4 SOMBRA
        drawSqaureFloor(7,21,0,54,pasilloSombra);
        drawSqaureFloor(0,7,17,53,pasilloSombra);

       
        // PASILLO 1-Q3/Q4 LUZ
        drawSqaureFloor(9,21,6,12,pasillo);
        drawSqaureFloor(9,14,11,12,pasillo);
        drawSqaureFloor(10,12,12,41,pasillo);
        drawSqaureFloor(9,14,18,23,pasillo);
        drawSqaureFloor(12,14,22,35,pasillo);
        drawSqaureFloor(9,10,30,41,pasillo);
        drawSqaureFloor(10,14,41,47,pasillo);
        drawSqaureFloor(14,21,41,47,pasillo);
        drawSqaureFloor(17,21,47,54,pasillo);
        drawSqaureFloor(17,21,0,11,pasillo);

        // SALA
        drawSqaureFloor(0,7,0,13,white);
        drawSqaureFloor(4,5,1,10,whiteSombra);

        // COORDINACION
        drawSqaureFloor(7,16,0,5,white);
        drawSqaureFloor(8,14,0,2,whiteSombra);
        drawSqaureFloor(12,14,2,4,whiteSombra);

        // BAÑOS
        drawSqaureFloor(16,18,21,33,whiteSombra);

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
    vec3 main = {0.7843137254901961,0.7529411764705882,0.7215686274509804};
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
    vec3 main = {0.7843137254901961,0.7529411764705882,0.7215686274509804};
    vec3 light = {0.8784313725490196,0.8470588235294118,0.7529411764705882};
    vec3 borde = {0.4666666666666667,0.47058823529411764,0.5333333333333333};
    
    vec3 posBorde1 = {xPosition,0.0,zPosition+0.56f};
    vec3 posBorde2 = {xPosition,0.0,zPosition+0.56f};

    vec3 posLight1 = {xPosition+0.5f,0.0,zPosition};
    
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
        }
    

    glPopMatrix();
}

void drawPaper(float xPosition,float zPosition, float wTimes,char sitio){
    vec3 pared = {1,1,1};

    glPushMatrix();

        meshs.push_back(new Mesh({{ (wTimes/2)+xPosition,0.0, zPosition+0.6f}, 1.0f, (1.0f)*wTimes-0.4f,pared, 'W'}));

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
    
    /* ==========
    Paredes
        C -> Coordinacion
        S -> Sala
        P -> Pasillo
        O -> Pasillo Oscuro
    =========== */

    // Q1
        /* ===== Paredes  ===== */
        /* ===== Columnas ===== */
        /* ===== Techos   ===== */
    // Q2
        /* ===== Paredes  ===== */
        /* ===== Columnas ===== */
        /* ===== Techos   ===== */
    // Q3
        /* ===== Paredes  ===== */
            drawWall(  1.0f,15.0f,3,'C');           // wid1
            drawWall(  1.0f, 6.0f,9,'S');           // wid2
            drawWall( 20.0f, 6.0f,5,'P');           // wid3
            
            drawWall( 12.0f,17.0f,2,'P');           // wid5
            drawWall( 16.0f,17.0f,5,'P');           // wid6
            drawWall( 21.0f,18.0f,3,'O');           // wid7

        /* ===== Papeles  ===== */
            drawPaper(17.0f,17.0f,2,'O');

        /* ===== Columnas ===== */
            drawColumn( 14.0f, 0.0f,9,'U');         // cid1
            drawColumn( 25.0f, 0.0f,9,'U');         // cid2
            
            drawColumn( 14.0f,16.0f,3,'D');         // cid3
        /* ===== Techos   ===== */
            drawRoofRowV( 0.5f, 0.0f,17.5f,'l');    // vid1
            drawRoofRowV( 0.5f,25.0f,17.0f,'l');    // viu1
            drawRoofRowV( 4.5f,12.5f,5.0f,'r');     // vid2
            drawRoofRowV( 53.5f,25.0f,17.0f,'r');   // vdu1
            drawRoofRowV( 13.5f, 0.0f,7.5f,'l');    // vid3
            drawRoofRowV( 16.5f, 0.0f,7.5f,'l');    // vid4
            
            drawRoofRowV( 12.5f, 18.5f,2.0f,'u');   // vid5
            drawRoofRowV( 20.5f, 18.5f,2.0f,'u');   // vid6
            drawRoofRowV( 24.5f, 18.5f,2.0f,'u');   // vid7

            drawRoofRowH( 0.5f,17.0f,4.5f,'r');     // hid1
            drawRoofRowH( 0.5f,8.0f,9.5f,'r');      // hid2
            
            drawRoofRowH( 13.0f,19.0f,7.0f,'d');    // hid3
            drawRoofRowH( 21.0f,20.0f,3.0f,'d');    // hid4        
    // Q4
        /* ===== Paredes  ===== */
            drawWall( 27.0f, 6.0f,5,'P');           // wdd1
            drawWall( 36.0f, 6.0f,3,'P');           // wdd2
            drawWall( 45.0f, 5.85f,5,'P');           // wdd3
            drawWall( 49.0f, 15.0f,4,'P');          // wdd5
            
            drawWall( 39.0f, 17.0f,2,'P');          // wdd6
            drawWall( 33.0f, 17.0f,4,'P');          // wdd7
            drawWall( 30.0f, 18.0f,3,'O');          // wdd8
        /* ===== Columnas ===== */
            drawColumn( 43.0f, 0.0f,9,'U');         // cdd1
            drawColumn( 47.0f, 7.8f,1,'U');         // cdd2
            
            drawColumn( 37.0f, 16.0f,3,'D');         // cdd3
        /* ===== Techos   ===== */
            drawRoofRowH( 48.0f,17.0f,5.0f,'l');     // hdd1

            drawRoofRowH( 34.0f,19.0f,6.0f,'d');    // hdd2
            drawRoofRowH( 30.0f,20.0f,3.0f,'d');    // hdd3

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

    for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();

    return meshs;
}