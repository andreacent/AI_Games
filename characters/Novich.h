class Novich : public Character{
public:
	Novich(Kinematic &character,char rl) : Character(character,rl) {}

    // Colors
    vec3 line =  {     0,     0,     0};    
    vec3 skin =  { 0.909, 0.694, 0.419};
    vec3 skinS = { 0.760, 0.580, 0.352};
    vec3 hair =  { 0.20, 0.1490, 0.1294};
    vec3 hairS = { 0.1098, 0.0823, 0.0705};
    vec3 shirt = { 0, 0, 1};

	void drawHair(vec3 positionH){

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
	}

	void draw(){

	    float x = character.position.x;
	    float z = character.position.z;
	    //float px = 0.125;
	    double deg = glm::degrees(-character.rotation);//radianes a grados

	    switch(rol){
	        case 'p':
	        shirt = { 0.4705, 0.03921, 0.42745};
	        break;
	        case 'e':
	        shirt = { 1, 0, 0};
	        break;
	        default:break;
	    }

	    // Draw
	    glPushMatrix();
			glPointSize(px);
	        glTranslatef(x,0.0,z);
	        glRotatef(deg,0,1,0);

	        //drawGuide(7,9);

	        //head
	        drawHead({0*px,0,4*px},line,skin,skinS);

	        //cabello
	        //drawHair({0*px,0,8*px});

	    glPopMatrix();
	}
	
};