/* 
    Andrea Centeno
    carnet USB: 10-10138
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
#include "movements/CollisionAvoidance.h"
#include "movements/ObstacleAvoidance.h"
#include "movements/Jump.h"

GLfloat oldTimeSinceStart = 0.0;
GLfloat pointSize=1.5;

GLfloat targetRotation = glm::radians(10.0);
GLfloat targetVelocity = 10;

GLfloat maxSpeed = 8;
GLfloat maxAcceleration = 40;
GLfloat maxPrediction = 0.4;

Kinematic target = {{-16.0f,0.0,-4.0f}};
Kinematic character = {{10.0f,0.0,-5.0f},0.0,{-3,0.0,0}};//,

bool ini = false;
list<Kinematic*> targets;
list<Mesh*> meshs;

/**************** Behaviors ****************/
Seek* seek = new Seek(character,target,maxAcceleration);
Flee* flee = new Flee(character,target,maxAcceleration); 
Arrive* arrive = new Arrive(character,target,3,5,maxAcceleration,maxSpeed); 
Align* align = new Align(character,target,20,30,5,2);//{&character,&target,maxAngularAcceleration,maxRotation,slowRadius,targetRadius} 
VelocityMatch* velocityMatch = new VelocityMatch(character,target,maxAcceleration); 

/**************** Delegated Behaviors ****************/
Pursue* pursue = new Pursue(character,target,20,maxPrediction); 
Evade* evade = new Evade(character,target,maxAcceleration,maxPrediction); 
Face* face = new Face(character,target,10,30,5,2); // Align() 
LookWhereYoureGoing* lookWhereYoureGoing = new LookWhereYoureGoing(character,target,10,30,5,2); // Align() 
Wander* wander = new Wander(character,20,30,5,2, -1,6,2,30,10);//{Face(),wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration} 
Separation* separation = new Separation(character,targets,6,10,30);//{character,targets,threshold,decayCoefficient,maxAcceleration} 

/**************** Collisions ****************/
CollisionAvoidance* collisionAvoidance = new CollisionAvoidance(character,targets,4,2);//{character,targets,maxAcceleration,radius}
CollisionDetector collisionDetector = {meshs};
ObstacleAvoidance* obstacleAvoidance = new ObstacleAvoidance(character,30,collisionDetector,5,3);//Seek(),collisionDetector,avoidDistance,lookahead

list<Behavior*> behaviors;

void initialize(){
    ini = true;
    // WALLS
    meshs.push_back(new Mesh({{0.0,0.0,11},0.2,70,{1,0,0},'W'}));//up
    meshs.push_back(new Mesh({{0.0,0.0,-9},0.2,70,{1,0,0},'W'}));//down
    meshs.push_back(new Mesh({{6,0.0,7.5},7,0.2,{1,0,0},'W'}));
    meshs.push_back(new Mesh({{-10,0.0,-5.5},7,0.2,{1,0,0},'W'}));
    meshs.push_back(new Mesh({{-35,0.0,0},22,0.2,{1,0,0},'W'}));//left
    meshs.push_back(new Mesh({{35,0.0,0},22,0.2,{1,0,0},'W'}));//right
    // OBSTACLE
    meshs.push_back(new Mesh({{-10,0.0,8},4,4,{1,0,1},'O'}));

    //ListTargets
    for(int i ; i< 10; i++){
        targets.push_back(new Kinematic({-30.0 + i*7,0.0,8.0f},0.0,{0.0,0.0,-1}));
    }

    //BEHAVIORS
    behaviors.push_back(seek);
    behaviors.push_back(flee);
    behaviors.push_back(arrive);
    behaviors.push_back(align); 
    behaviors.push_back(velocityMatch);                           
    behaviors.push_back(pursue);
    behaviors.push_back(evade);
    behaviors.push_back(face);
    behaviors.push_back(lookWhereYoureGoing);
    behaviors.push_back(wander);    
    behaviors.push_back(separation);
    behaviors.push_back(collisionAvoidance);
    behaviors.push_back(obstacleAvoidance);
}

void moveListTargets(GLfloat deltaTime){
    for (list<Kinematic*>::iterator t=targets.begin(); t != targets.end(); ++t){
        glColor3f(0,0.6,0.6);
        drawFace((*t)->position,(*t)->orientation,pointSize);
    }

    for (list<Kinematic*>::iterator t=targets.begin(); t != targets.end(); ++t){
        if((*t)->position.y > 8 || (*t)->position.y < -6) (*t)->velocity.y *= (-1);
        (*t)->updatePosition(deltaTime);
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
            target.velocity = {0.0,0.0,targetVelocity};
        break;
        case GLUT_KEY_DOWN:
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
        case GLUT_KEY_DOWN:
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
    gluLookAt(0, 0, 1, 0, 10, 0, 0, 1, 0);
    
    for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();

    glLineWidth(pointSize);
    glColor3f(0.6,0.6,0.6);
    drawFace(target.position,target.orientation,pointSize);
    glColor3f(0.4,0.2,0.8);
    drawFace(character.position,character.orientation,pointSize);

   
    GLfloat timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    GLfloat deltaTime = (timeSinceStart - oldTimeSinceStart) * 0.001;
    oldTimeSinceStart = timeSinceStart;

    //moveListTargets(deltaTime);

    target.updatePosition(deltaTime);
    target.updateOrientation(deltaTime);

    obstacleAvoidance->update(maxSpeed,deltaTime);
    //seek->update(maxSpeed,deltaTime);
    //flee->update(maxSpeed,deltaTime);
    //arrive->update(maxSpeed,deltaTime);
    //align->update(maxSpeed,deltaTime);
    //velocityMatch->update(maxSpeed,deltaTime);
    pursue->update(maxSpeed,deltaTime);
    //evade->update(maxSpeed,deltaTime);
    //face->update(maxSpeed,deltaTime);
    //lookWhereYoureGoing->update(maxSpeed,deltaTime);
    //wander->update(maxSpeed,deltaTime);
    //separation->update(maxSpeed,deltaTime);
    //collisionAvoidance->update(maxSpeed,deltaTime);
    obstacleAvoidance->update(maxSpeed,deltaTime);

    
    glFlush();
    glutPostRedisplay();
}

/************************* Viewport **************************/
void reshape(int w, int h) {
    float aspectradio;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectradio = (float) w / (float) h;
    GLfloat number = 30;
    if (w <= h)
        glOrtho(-number,number,-number/aspectradio,number/aspectradio,1.0,-1.0);
    else
        glOrtho(-number*aspectradio,number*aspectradio,-number,number,1.0,-1.0);
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