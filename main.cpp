/* 
    Andrea Centeno
    carnet USB: 10-10138
    Sergio Teran
    carnet USB: 11-11020
    sep-dic 2017
*/    
#include "header.h"
#include "draw.cpp"

#include "movements/Seek.h"
#include "movements/Flee.h"
#include "movements/Arrive.h"
#include "movements/Align.h"
#include "movements/VelocityMatch.h"
#include "movements/Pursue.h"
#include "movements/Evade.h"
#include "movements/Face.h"
#include "movements/LookWhereYoureGoing.h"
#include "movements/Wander.h"
#include "movements/Separation.h"
#include "movements/ObstacleAvoidance.h"
#include "movements/BlendedSteering.h"


#include "characters/Character.h"
#include "characters/Marlene.h"
#include "characters/Novich.h"

#include "path/pathfindAStar.h"
#include "path/triangules.h"

GLfloat oldTimeSinceStart = 0.0;
GLfloat pointSize=1.5;

GLfloat targetRotation = glm::radians(10.0);
GLfloat targetVelocity =3;

GLfloat maxSpeed = 4;
GLfloat maxAcceleration = 10;
GLfloat maxPrediction = 0.4;

bool ini = false;
list<Kinematic*> targets;

/******************** CHARACTERES *******************/
Kinematic target = {{2.0f,0.0f,13.0f}};
Kinematic sidekick1 = {{46.0f,0.0,3.0f},0.0};
Kinematic sidekick2 = {{-18.0f,0.0,-6.0f},0.0};
Kinematic enemy = {{-26.0f,0,-7.0f},0.0};

Marlene marlene = {target,'p'};
Marlene novich = {sidekick1,'s'};

/******************** Camera *******************/
float x=target.position.x, z=target.position.z;
// actual vector representing the camera's direction
float deltaMove = 0;

/**************** Behaviors ****************/
    Seek* seek = new Seek(enemy,target,maxAcceleration);
    Flee* flee = new Flee(enemy,target,maxAcceleration); 
    Arrive* arrive = new Arrive(sidekick1,target,10,15,maxAcceleration,maxSpeed);

    //{&enemy,&target,maxAngularAcceleration,maxRotation,slowRadius,targetRadius}
    Align* align = new Align(enemy,target,20,30,5,2);
    VelocityMatch* velocityMatch = new VelocityMatch(enemy,target,maxAcceleration); 

/**************** Delegated Behaviors ****************/
    Pursue* pursue = new Pursue(enemy,target,20,maxPrediction); 
    Evade* evade = new Evade(enemy,target,maxAcceleration,maxPrediction); 

    // Align()
    Face* face = new Face(enemy,target,10,30,5,2);

    // Align()
    LookWhereYoureGoing* lookWhereYoureGoing = new LookWhereYoureGoing(enemy,target,10,30,5,2);

    //{Face(),wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration} 
    Wander* wander = new Wander(enemy,20,30,5,2, 0,4,2,50,10);

    //{enemy,targets,threshold,decayCoefficient,maxAcceleration} 
    Separation* separation = new Separation(enemy,targets,6,10,30);

    /**************** Collisions ****************/
    CollisionDetector collisionDetector = {meshs};

    //Seek(),collisionDetector,avoidDistance,lookahead
    ObstacleAvoidance* obstacleAvoidance = new ObstacleAvoidance(enemy,30,collisionDetector,5,4);

/**************** Blended Behaviors ****************/
// Follow Target

    list<BehaviorAndWeight*> behaviorsFlocking1;
    BlendedSteering flocking1 = {sidekick1,maxAcceleration,30,maxSpeed,behaviorsFlocking1};
    list<Kinematic*> targets1;

    list<BehaviorAndWeight*> behaviorsFlocking2;
    BlendedSteering flocking2 = {sidekick2,maxAcceleration,30,maxSpeed,behaviorsFlocking2};
    list<Kinematic*> targets2;

    void followTarget(Kinematic &target, Kinematic &sidekick,list<BehaviorAndWeight*> &behaviors,list<Kinematic*> &targets){
        GLfloat maxPrediction = 0.4;

        Separation* separation = new Separation(sidekick,targets,4,4,maxAcceleration);
        Arrive* arrive1 = new Arrive(sidekick,target,0.5,20,maxAcceleration,maxSpeed);
        Seek* seek = new Seek(sidekick,target,maxAcceleration);
        LookWhereYoureGoing* lookWhereYoureGoing = new LookWhereYoureGoing(sidekick,target,10,30,5,2); // Align()  

        ObstacleAvoidance* obstacleAvoidance = new ObstacleAvoidance(sidekick,10,collisionDetector,2,1);

        behaviors.push_back(new BehaviorAndWeight(lookWhereYoureGoing,3));
        behaviors.push_back(new BehaviorAndWeight(obstacleAvoidance,0.8));
        behaviors.push_back(new BehaviorAndWeight(separation,0.3));
        behaviors.push_back(new BehaviorAndWeight(arrive1,0.1));
    }

    void initialize(){
        ini = true;

        glClearColor(0.81960,0.81960,0.81960,1);

        /* FOLLOW TARGET */
        followTarget(target, sidekick1,behaviorsFlocking1,targets1);
        followTarget(target, sidekick2,behaviorsFlocking2,targets2);

        targets1.push_back(&sidekick2);
        targets1.push_back(&target);

        targets2.push_back(&sidekick1);
        targets2.push_back(&target);
    }

    void moveListTargets(GLfloat deltaTime){
        for (list<Kinematic*>::iterator t=targets.begin(); t != targets.end(); ++t){
            glColor3f(1,0,0);
            drawFace((*t)->position,(*t)->orientation,pointSize);
        }
    }

/******************************* KEYBOARD *****************************/
void controlKey (unsigned char key, int xmouse, int ymouse){  
    switch (key){
        case 'a': 
            target.rotation = targetRotation;
        break;
        case 'd': 
            target.rotation = -targetRotation;
        break;
        default: break;
    }  
}

void controlKeyReleased (unsigned char key, int xmouse, int ymouse){   
    switch (key){
        case 'a': 
        case 'd': 
            target.rotation = 0.0;
        break;
        default: break;
    } 
}

void handleSpecialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            target.velocity = {-targetVelocity,0.0,0.0};
        break;
        case GLUT_KEY_RIGHT:
            target.velocity = {targetVelocity,0.0,0.0};
        break;
        case GLUT_KEY_UP:
            deltaMove = -0.1f;
            target.velocity = {0.0,0.0,targetVelocity};
        break;
        case GLUT_KEY_DOWN:
            deltaMove = 0.1f;
            target.velocity = {0.0,0.0,-targetVelocity};
        break;
        default: break;
    }
}

void handleSpecialKeyReleased(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_UP:
            deltaMove = 0.0f;
        case GLUT_KEY_DOWN:
            deltaMove = 0.0f;
            target.velocity = {0.0,0.0,0.0};
        break;
        default: break;
    }
}

/************************** Display **************************/
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH); 
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float z = target.position.z;
    float x = target.position.x;
    gluLookAt(x,0,z,x,10,z-1.0f,0,1,0);
    
    list<Mesh*> meshs = drawMap();
    drawTriangleMap();

    glLineWidth(pointSize);

    //TEST CHARACTER
    marlene.draw();
    novich.draw();

   
    GLfloat timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    GLfloat deltaTime = (timeSinceStart - oldTimeSinceStart) * 0.001;
    oldTimeSinceStart = timeSinceStart;

    //moveListTargets(deltaTime);

    target.updatePosition(deltaTime);
    target.updateOrientation(deltaTime);

    //flocking1.update(maxSpeed,deltaTime);
    //flocking2.update(maxSpeed,deltaTime);
    
    glFlush();
    glutPostRedisplay();
}

/************************* Viewport **************************/
void reshape(GLsizei w, GLsizei h) {

    float aspectradio;
    aspectradio = (float) w / (float) h;
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat widthVP  = 20.0;
    GLfloat heightVP = 20.0;
    GLfloat deepVP = 40.0;
    
    if (w < h){
        heightVP = heightVP/aspectradio;
    }
    else{
        widthVP = widthVP*aspectradio;
    }
    glOrtho(-widthVP,widthVP,-heightVP,heightVP,deepVP,-deepVP);
}

/*************************** MAIN ***************************/
int main (int argc, char** argv) {
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(1000,600);
    glutCreateWindow("AI VideoGame");

    if(!ini) initialize();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);

    glutKeyboardFunc(controlKey); 
    glutKeyboardUpFunc(controlKeyReleased); 
    
    glutMainLoop();
    return 0;
}