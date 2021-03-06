/* 
    Andrea Centeno
    carnet USB: 10-10138
    Sergio Teran
    carnet USB: 11-11020
    sep-dic 2017
*/    
#include "../movements/BlendedSteering.cpp"
#include "../graph/graph.cpp"

#include "../characters/Character.h"
#include "../characters/Marlene.h"
#include "../characters/Novich.h"

#include "../assets/text.cpp"
#include "../assets/map.h"
#include "../assets/draw.cpp"
//#include "assets/StateMachineS.cpp"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
//#include <GL/glew.h>

#include "../mesh/Mesh.cpp"

std::list<Mesh*> meshs;

Graph graph;
std::list<vec3> path;

GLfloat pointSize=1.5;

GLfloat targetRotation = glm::radians(10.0);
GLfloat targetVelocity = 4;

GLfloat maxRotation = 30;

bool activeTriangles = false;
bool activeMap = true;
bool ini = false;

int WinId;

/******************** Camera *******************/
// actual vector representing the camera's direction
float deltaMove = 0;

/**************** Collisions ****************/
CollisionDetector collisionDetector = {meshs};

/******************** CHARACTERES *******************/
Kinematic target = {{3.5f,0.0f,3.5f}};//{{26.0f,0,26.0f},0.0};

/* STUDENT */
Kinematic student = {{26.0f,0.0,30.0f},0.0};
//behavior list
std::map<string,Behavior*> studentBehaviors;
//follow path
FollowPath* studentFollowPath = new FollowPath(student,maxAcceleration);
//target list (separation)
std::list<Kinematic*> studentTargets;
//follow target (BlendedSteering)
BlendedSteering studentFollowTarget = {student,maxAcceleration,maxRotation,maxSpeed, *new list<BehaviorAndWeight*>()};
//follow path with obstacles (BlendedSteering)
BlendedSteering studentblendedWander = {student,10,30,8, *new list<BehaviorAndWeight*>()};
    
/****************** Initialize **********************/
void initialize(){
    ini = true;

    meshs = drawMap();

    graph.createGameGraphNew();
    glClearColor(0.81960,0.81960,0.81960,1);

    // STUDENT : behaviors and blended 
    createMapAllBehaviors(student, target,  collisionDetector,studentTargets, studentBehaviors);
    studentBehaviors["followPath"] = studentFollowPath;
    studentTargets.push_back(&target);   
    followTarget(studentBehaviors, studentFollowTarget);
    wanderWithObs(studentBehaviors,studentblendedWander);
}

/******************************* KEYBOARD *****************************/
void controlKey (unsigned char key, int xmouse, int ymouse){  
    switch (key){
        case 'a': 
            target.rotation = -targetRotation;
        break;
        case 'd': 
            target.rotation = targetRotation;
        break;
        case 'x': 
            activeTriangles = !activeTriangles;
        break;
        case 'z':
            activeMap = !activeMap;
        break;
        case ' ': //mover en y (saltar)
            target.velocity.y = targetVelocity;
        break;
        case 27: // Escape key
            glutDestroyWindow ( WinId );
            exit (0);
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
        case ' ': //dejar de mover en y (saltar)
            target.velocity.y = 0.0;
        break;
        default: break;
    } 
}

void handleSpecialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            target.velocity.x = -targetVelocity;
        break;
        case GLUT_KEY_RIGHT:
            target.velocity.x = targetVelocity;
        break;
        case GLUT_KEY_UP:
            target.velocity.z = targetVelocity;
        break;
        case GLUT_KEY_DOWN:
            target.velocity.z =  -targetVelocity;
        break;
        default: break;
    }
}

void handleSpecialKeyReleased(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            target.velocity.x = 0.0;
        break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0.0f;
            target.velocity.z = 0.0;
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

    //float z = target.position.z;
    //float x = target.position.x;
    //gluLookAt(x,0,z,x,10,z-1.0f,0,1,0);
    gluLookAt(25,0,21,25,10,21-1.0f,0,1,0);

    GLfloat timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (timeSinceStart - oldTimeSinceStart) * 0.001;
    oldTimeSinceStart = timeSinceStart;

    //drawFloor();
    drawDetails();

    glLineWidth(pointSize);

    if(activeTriangles) {
        graph.drawTriangles();
    }
    if(activeMap) for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();

    target.updatePosition(deltaTime,meshs);
    target.updateOrientation(deltaTime);

    // STUDENT
    glColor3f(0.0,0.6,0.8);
    drawFace(student.position,student.orientation,pointSize);
    
    // TARGET
    glColor3f(0,0,0);
    drawFace(target.position,target.orientation,pointSize);

    //studentBehaviors["seek"]->update(maxSpeed,deltaTime);
    //studentBehaviors["flee"]->update(maxSpeed,deltaTime);
    //studentBehaviors["arrive"]->update(maxSpeed,deltaTime);
    //studentBehaviors["align"]->update(maxSpeed,deltaTime);
    //studentBehaviors["velocityMatch"]->update(maxSpeed,deltaTime);
    studentBehaviors["pursue"]->update(maxSpeed,deltaTime);
    //studentBehaviors["evade"]->update(maxSpeed,deltaTime);
    //studentBehaviors["face"]->update(maxSpeed,deltaTime);
    studentBehaviors["lwyg"]->update(maxSpeed,deltaTime);
    //studentBehaviors["wander"]->update(maxSpeed,deltaTime);
    //studentBehaviors["separation"]->update(maxSpeed,deltaTime);
    //studentBehaviors["obstacle"]->update(maxSpeed,deltaTime);
    //studentFollowTarget.update(maxSpeed,deltaTime);

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

    GLfloat widthVP  = 21.0;
    GLfloat heightVP = 21.0;
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
    WinId = glutCreateWindow("AI Game");
    //glutFullScreen();

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