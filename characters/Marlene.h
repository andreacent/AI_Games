class Marlene : public Character{
public:
	Marlene(Kinematic &character,char rl) : Character(character,rl) {}

    // Colors
    vec3 line =  {     0,     0,     0};    
    vec3 skin =  { 0.909, 0.694, 0.419};
    vec3 skinS = { 0.760, 0.580, 0.352};
    vec3 hair =  { 0.20, 0.1490, 0.1294};
    vec3 hairS = { 0.1098, 0.0823, 0.0705};
    vec3 dress = { 0, 0, 1};


	/**************** HAIR ****************/
	void drawFullHair(vec3 positionH,char dir){
	    // Cabello
	    drawMirrorX(positionH,0,-1,hairS,3, 1);

	    drawSquare({  2*positionH.x+(-8)*px,character.position.y,2*positionH.z+(-6)*px },hairS, 4, 4);
	    drawSquare({  2*positionH.x+(-4)*px,character.position.y,2*positionH.z+(-6)*px },hair, 12, 4);

	    drawMirrorX(positionH,0,-4,hairS,3, 1);
	    
	    drawMirrorX(positionH,5,-6,hairS,1, 1);
	    drawMirrorX(positionH,4,-9,hairS,2, 1);
	    drawMirrorX(positionH,4,-10,hairS,1, 1);

	    // Lineas
	    drawMirrorX(positionH,0,+0 ,line,3, 1);
	    drawMirrorX(positionH,3,-1 ,line,1, 1);
	    drawMirrorX(positionH,4,-1 ,line,1,-2);
	    drawMirrorX(positionH,5,-3 ,line,1,-2);
	    drawMirrorX(positionH,3,-4 ,line,1, 1);
	    drawMirrorX(positionH,0,-5 ,line,3, 1);
	    drawMirrorX(positionH,6,-5 ,line,1,-4);
	    drawMirrorX(positionH,5,-10,line,1, 1);
	    drawMirrorX(positionH,4,-11,line,1, 1);

	    // Back
	    if(dir == 'u'){	

	    	drawMirrorX(positionH,0,-12,line,4, 1);
    		drawSquare({ 2*(positionH.x+0*px),positionH.y,2*(positionH.z+ -1*px) },hair, 2*3, 2* 1);
    		
    		// shadow
    		drawSquare({ 2*(positionH.x+-3*px),positionH.y,2*(positionH.z+ -1*px) },hairS, 2*3, 2* 1);
    		drawSquare({ 2*(positionH.x+-4*px),positionH.y,2*(positionH.z+ -2*px) },hairS, 2*3, 2* 1);
    		drawSquare({ 2*(positionH.x+-4*px),positionH.y,2*(positionH.z+ -3*px) },hairS, 2*2, 2* 1);
    		drawSquare({ 2*(positionH.x+-5*px),positionH.y,2*(positionH.z+ -3*px) },hairS, 2*2, 2* -2);
    		drawSquare({ 2*(positionH.x+-6*px),positionH.y,2*(positionH.z+ -5*px) },hairS, 2*2, 2* -4);
    		drawSquare({ 2*(positionH.x+-5*px),positionH.y,2*(positionH.z+ -10*px) },hairS, 2*2, 2* 2);
    		
	    	drawMirrorX(positionH,0,-11,hairS,4, 1);

    		//hair
    		drawSquare({ 2*(positionH.x+-0*px),positionH.y,2*(positionH.z+ -1*px) },hair, 2*4, 2* -9);
    		drawSquare({ 2*(positionH.x+-3*px),positionH.y,2*(positionH.z+ -3*px) },hair, 2*4, 2* -7);
    		drawSquare({ 2*(positionH.x+ 4*px),positionH.y,2*(positionH.z+ -5*px) },hair, 2*1, 2* 1);
    		drawSquare({ 2*(positionH.x+ 4*px),positionH.y,2*(positionH.z+ -5*px) },hair, 2*2, 2* -4);
    		drawSquare({ 2*(positionH.x+ -4*px),positionH.y,2*(positionH.z+ -8*px) },hair, 2*1, 2* 3);
	    }
	}
	
	void drawSideHair(vec3 positionH,char dir){
    	
    	float x = positionH.x;
		float y = positionH.y;
    	float z = positionH.z-1*px;

    	float w = 1;
    	float t = 0;
    	float tc = 0;

    	if( dir == 'r'){w = -1;t = -2;tc=2;}

    	// Hair
    	drawSquare({   2*(x+-( 5+t        )*px),y,2*(z+  0*px) },hair, 2*8, 2* -3);
    	drawSquare({ w*2*(x+-(-3+t+ (tc/2))*px),y,2*(z+ -3*px) },hair, 2*1, 2* -3);
    	drawSquare({ w*2*(x+-(-4+t+ (tc/2))*px),y,2*(z+ -5*px) },hair, 2*1, 2* -4);
    	drawSquare({ w*2*(x+-(-3+t+ (tc/2))*px),y,2*(z+ -8*px) },hair, 2*1, 2* -2);
    	drawSquare({ w*2*(x+-(-2+t+ (tc/2))*px),y,2*(z+ -9*px) },hair, 2*1, 2* -1);

    	// Lines
    	drawSquare({   2*(x+-(4+t)*px),y,2*(z+ 0*px) },line, 2*6, 2* 1);
    	
    	drawSquare({ w*2*(x+-( 5+(t/2))*px),y,2*(z+ -1*px) },line, 2*1, 2* 1);
    	drawSquare({ w*2*(x+-( 6+(t/2))*px),y,2*(z+ -1*px) },line, 2*1, 2* -2);
    	drawSquare({ w*2*(x+-( 5+(t/2))*px),y,2*(z+ -4*px) },line, 2*1, 2* 1);
    	drawSquare({   2*(x+-( 4+ t   )*px),y,2*(z+ -5*px) },line, 2*6, 2* 1);
    	
    	drawSquare({ w*2*(x+-(-2+(t/2))*px),y,2*(z+ -1*px) },line, 2*1, 2* 1);
    	drawSquare({ w*2*(x+-(-3+(t/2))*px),y,2*(z+ -1*px) },line, 2*1, 2* -2);
    	drawSquare({ w*2*(x+-(-4+(t/2))*px),y,2*(z+ -3*px) },line, 2*1, 2* -2);
    	drawSquare({ w*2*(x+-(-5+(t/2))*px),y,2*(z+ -5*px) },line, 2*1, 2* -4);
    	drawSquare({ w*2*(x+-(-4+(t/2))*px),y,2*(z+ -9*px) },line, 2*1, 2* -1);
    	drawSquare({ w*2*(x+-(-1+(t+(t/2)))*px),y,2*(z+ -10*px) },line, 2*3, 2* -1);

    	// Shadow
    	drawSquare({ w*2*(x+-( 4+(t+(t/2)))        *px),y,2*(z+  0*px) },hairS, 2*3, 2* -1);
    	drawSquare({ w*2*(x+-( 5+(t+(t/2)+ (tc/2)))*px),y,2*(z+ -1*px) },hairS, 2*2, 2* -2);
    	drawSquare({ w*2*(x+-( 4+(t+(t/2)+-(tc*2)))*px),y,2*(z+ -3*px) },hairS, 2*7, 2* -1);
    	drawSquare({ w*2*(x+-(-2+(t+(t/2)+  tc   ))*px),y,2*(z+ -4*px) },hairS, 2*1, 2* -2);
    	drawSquare({ w*2*(x+-(-3+(t+(t/2)+  tc   ))*px),y,2*(z+ -6*px) },hairS, 2*1, 2* -2);
    	drawSquare({ w*2*(x+-(-1+(t+(t/2)+ (tc/2)))*px),y,2*(z+ -8*px) },hairS, 2*2, 2* -1);
    	drawSquare({ w*2*(x+-(-1+(t+(t/2)+  tc   ))*px),y,2*(z+ -9*px) },hairS, 2*1, 2* -1);
	}

	void drawHair(vec3 positionH){
		vec3 facing = character.velocity;

		if(facing.x < 0 && abs(facing.x) > abs(facing.z)){
			
	    	drawSideHair(positionH,'l');
		
		}else if(facing.x > 0 && abs(facing.x) > abs(facing.z)){
			
	    	drawSideHair(positionH,'r');
		
		}else if(facing.z > 0 && abs(facing.x) < abs(facing.z)){
		
	    	drawFullHair(positionH,'u');
		
		}else{
		
	    	//drawSideHair(positionH,'r');
	    	drawFullHair(positionH,'d');
		
		}
	}

	/**************** HAIR ****************/
	void drawSideDress(vec3 positionD,char dir){

    	float x = positionD.x;
		float y = positionD.y;
    	float z = positionD.z-1*px;

    	float w = 1;
    	float t = 0;
    	float tc = 0;

    	if( dir == 'r'){w = -1;t = -2;tc=2;}

    	drawSquare({ w*2*(x+-( 2+t+    tc)*px),y,2*(z+  0*px) },line, 2*3*w, 2* 1);
    	drawSquare({ w*2*(x+-( 2+t+(tc/2))*px),y,2*(z+  0*px) },line, 2*1, 2*-1);
    	drawSquare({ w*2*(x+-( 3+t+(tc/2))*px),y,2*(z+ -1*px) },line, 2*1, 2*-2);
    	
    	drawSquare({ w*2*(x+-( 3      )*px),y,2*(z+ -2*px) },line, 2*8*w, 2*-1);
    	drawSquare({ w*2*(x+-(-4+t+(tc/2))*px),y,2*(z+ -2*px) },line, 2*1, 2* 1);
    	drawSquare({ w*2*(x+-(-3+t+(tc/2))*px),y,2*(z+ -1*px) },line, 2*1, 2* 1);

    	drawSquare({ w*2*(x+-( 1      )*px),y,2*(z+ -3*px) },line, 2*4*w, 2*-1);
    	
    	drawSquare({ w*2*(x+-( 1      )*px),y,2*(z+ 0*px) },dress, 2*4*w, 2*-1);
    	drawSquare({ w*2*(x+-( 2      )*px),y,2*(z+ -1*px) },dress, 2*6*w, 2*-1);
	}
	
	void drawFullDress(vec3 positionD,char dir){
	    // Dress
	    drawMirrorX(positionD,0,0,dress,2, -2);
	    drawMirrorX(positionD,2,1,dress,2, -4);
	    drawMirrorX(positionD,4,-2,dress,1, 1);
	    
	    //Lineas
	    drawMirrorX(positionD,0,0,line,2, 1);
	    drawMirrorX(positionD,4,-1,line,1, 2);
	    drawMirrorX(positionD,5,-3,line,1, 2);
	    drawMirrorX(positionD,0,-3,line,1, 1);
	    drawMirrorX(positionD,1,-4,line,4, 2);
	}

	void drawDress(vec3 positionD){
		vec3 facing = character.velocity;

		if(facing.x < 0 && abs(facing.x) > abs(facing.z)){			
	    	drawSideDress(positionD,'l');
		
		}else if(facing.x > 0 && abs(facing.x) > abs(facing.z)){			
	    	drawSideDress(positionD,'r');
		
		}else if(facing.z > 0 && abs(facing.x) < abs(facing.z)){		
	    	drawFullDress(positionD,'u');
		
		}else{		
	    	//drawSideDress(positionD,'r');
	    	drawFullDress(positionD,'d');
		
		}

	}

	/**************** MAIN ****************/
	void draw(){

	    float x = character.position.x;
	    float z = character.position.z;
	    double deg = glm::degrees(-character.rotation);//radianes a grados

	    switch(rol){
	        case 'p':
	        dress = { 0.4705, 0.03921, 0.42745};
	        break;
	        case 'a':
	        dress = { 1, 0, 0};
	        break;
	        case 's':
	        dress = { 0, 1, 0};
	        break;
	        default:break;
	    }

	    // Draw
	    glPushMatrix();
			glPointSize(px);
	        glTranslatef(x,0.0,z);
	        glRotatef(deg,0,1,0);


	        //head
	        drawHead({0*px,0,4*px},line,skin,skinS);

	        //vestido
	        drawDress({0*px,0,-3*px});
	        
	        //cabello
	        drawHair({0*px,0,8*px});
	        
	        //drawGuide(7,9);


	    glPopMatrix();
	}
	
};