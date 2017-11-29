/* 
    Andrea Centeno
    carnet USB: 10-10138
    Sergio Teran
    carnet USB: 11-11020
    sep-dic 2017
*/    
#include "movements/BlendedSteering.cpp"
#include "graph/graph.cpp"

#include "characters/Character.h"
#include "characters/Marlene.h"
#include "characters/Novich.h"

#include "assets/text.cpp"
#include "assets/map.h"
#include "assets/StateMachine.cpp"
#include "assets/StateMachineS.cpp"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
//#include <GL/glew.h>

#include "mesh/Mesh.cpp"

std::list<Mesh*> meshs;

Graph graph;
std::list<vec3> path;

GLfloat pointSize=1.5;

GLfloat targetRotation = glm::radians(10.0);
GLfloat targetVelocity = 4;

GLfloat maxRotation = 30;

bool activeTriangles = true;
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
Marlene marlene = {target,'t'};

/* sidekick1 */
Kinematic sidekick1 = {{2.0f,0.0f,2.0f},0.0};
//mesh
Marlene sidekick1Mesh = {sidekick1,'s'};
//target list (separation)
std::list<Kinematic*> sidekick1Targets;
//behavior list
std::map<string,Behavior*> sidekick1Behaviors;
//flocking (BlendedSteering)
BlendedSteering sidekick1Flocking = {sidekick1,maxAcceleration,maxRotation,maxSpeed,*new list<BehaviorAndWeight*>()};

/* sidekick2 */
Kinematic sidekick2 = {{36.0f,0,30.0f},0.0};
//mesh
Marlene sidekick2Mesh = {sidekick2,'s'};
//target list (separation)
std::list<Kinematic*> sidekick2Targets;
//behavior list
std::map<string,Behavior*> sidekick2Behaviors;
//flocking (BlendedSteering)
BlendedSteering sidekick2Flocking = {sidekick2,maxAcceleration,maxRotation,maxSpeed,*new list<BehaviorAndWeight*>()};


/* STUDENT IN ROOMS*/
Marlene student_ldc = {*new Kinematic({3.0f,0.0,38.0f},0.0),'s'};
Marlene student_chang = {*new Kinematic({48.0f,0.0,2.0f},0.0),'s'};

/* STUDENT ALERTS*/
Marlene student_alert_1 = {*new Kinematic({8.0f,0.0,19.0f},0.0),'a'};
Marlene student_alert_2 = {*new Kinematic({22.0f,0.0,8.0f},0.0),'a'};

/* STUDENT */
Marlene student = {*new Kinematic({26.0f,0.0,30.0f},0.0),'s'};
/* STUDENT HELLO */
Marlene studentHello = {*new Kinematic({24.0f,0.0,33.0f},0.0),'s'};

/* NOVICH */
Kinematic novich = {{26.0f,0.0,30.0f},0.0};
//mesh
Marlene novichMesh = {novich,'s'};
//behavior list
std::map<string,Behavior*> novichBehaviors;
//follow path
FollowPath* novichFollowPath = new FollowPath(novich,maxAcceleration);
//target list (separation)
std::list<Kinematic*> novichTargets;
//follow target (BlendedSteering)
BlendedSteering novichFollowTarget = {novich,maxAcceleration,maxRotation,maxSpeed, *new list<BehaviorAndWeight*>()};
//follow path with obstacles (BlendedSteering)
BlendedSteering novichFollowPathWithObs = {novich,maxAcceleration,maxRotation,maxSpeed, *new list<BehaviorAndWeight*>()};
BlendedSteering novichblendedWander = {novich,10,30,8, *new list<BehaviorAndWeight*>()};
    

/****************** Initialize **********************/
void initialize(){
    ini = true;


    student_ldc.setStateMachine(StudentStateMachineS(student_ldc.character,target,student_alert_1.character,collisionDetector,graph));
    student_chang.setStateMachine(StudentStateMachineS(student_chang.character,target,student_alert_2.character,collisionDetector,graph));
    
    student_alert_1.setStateMachine(AlertStateMachine(student_alert_1.character,target,student_ldc.character,collisionDetector,graph));
    student_alert_2.setStateMachine(AlertStateMachine(student_alert_2.character,target,student_chang.character,collisionDetector,graph));

    student.setStateMachine(StudentStateMachine(student.character,target,collisionDetector,graph));
   
    std::list<Kinematic*> studentHelloTargets;
    studentHelloTargets.push_back(&target);   
    studentHelloTargets.push_back(&student.character);   
    studentHello.setStateMachine(HelloStateMachine(studentHello.character,studentHelloTargets));

    meshs = drawMap();

    graph.createGameGraphNew();
    //graph.createGameGraphSquare();
    glClearColor(0.81960,0.81960,0.81960,1);

    // NOVICH : behaviors and blended 
    createMapAllBehaviors(novich, target,  collisionDetector,novichTargets, novichBehaviors);
    novichBehaviors["followPath"] = novichFollowPath;
    novichTargets.push_back(&target);   
    followTarget(novichBehaviors, novichFollowTarget);
    followPathWithObstacle(novichBehaviors, novichFollowPathWithObs);
    wanderWithObs(novichBehaviors,novichblendedWander);

    /* sidekick1 : behaviors and flocking */
    createMapAllBehaviors(sidekick1, target, collisionDetector, sidekick1Targets, sidekick1Behaviors);
    flocking( sidekick1Behaviors, sidekick1Flocking );
    sidekick1Targets.push_back(&sidekick2);
    sidekick1Targets.push_back(&target);

    /* sidekick2 : behaviors and flocking */
    createMapAllBehaviors(sidekick2, target, collisionDetector, sidekick2Targets, sidekick2Behaviors);
    flocking( sidekick2Behaviors, sidekick2Flocking );
    sidekick2Targets.push_back(&sidekick1);
    sidekick2Targets.push_back(&target);
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
        case '0': 
            cout<<"pos target "<< target.position.x<<","<<target.position.y<<","<<target.position.z<<endl;
            //prueba de calcular el camino
            // /path = pathfindAStar(graph, novich.position, target.position);
            //novichFollowPath->setPath(path);   
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
            marlene.setOrientation();
        break;
        case GLUT_KEY_RIGHT:
            target.velocity.x = targetVelocity;
            marlene.setOrientation();
        break;
        case GLUT_KEY_UP:
            deltaMove = -0.1f;
            target.velocity.z = targetVelocity;
            marlene.setOrientation();
        break;
        case GLUT_KEY_DOWN:
            deltaMove = 0.1f;
            target.velocity.z =  -targetVelocity;
            marlene.setOrientation();
        break;
        default: break;
    }
}

void handleSpecialKeyReleased(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            target.velocity.x = 0.0;
            marlene.setOrientation();
        break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0.0f;
            target.velocity.z = 0.0;
            marlene.setOrientation();
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
    //gluLookAt(x,0,z,x,10,z-1.0f,0,1,0);
    gluLookAt(25,0,21,25,10,21-1.0f,0,1,0);

    GLfloat timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (timeSinceStart - oldTimeSinceStart) * 0.001;
    oldTimeSinceStart = timeSinceStart;

    drawFloor();
    drawDetails();
    //cout<<meshs.size()<<endl;

    glLineWidth(pointSize);

    if(activeTriangles) {
        graph.drawTriangles();
        //if (int(novichFollowPath->getPath().size) > 0) novichFollowPath->getPath().draw();
    }
    if(activeMap) for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();

    target.updatePosition(deltaTime,meshs);
    target.updateOrientation(deltaTime);

    //TEST CHARACTER
    studentHello.checkStateMachine();
    studentHello.draw();
    student.checkStateMachine();
    student.draw();
    //sidekick2Mesh.draw(); 

    student_ldc.draw();
    student_chang.draw();
    
    student_alert_1.draw();
    student_alert_2.draw();

    student_ldc.checkStateMachine();
    student_chang.checkStateMachine();
    
    student_alert_1.checkStateMachine();
    student_alert_2.checkStateMachine();  

    marlene.draw();

    //novichblendedWander.update(maxSpeed,deltaTime); 

    //sidekick1Flocking.update(maxSpeed,deltaTime);
    //sidekick1Mesh.draw();
    //sidekick2Flocking.update(maxSpeed,deltaTime);

    //sidekick2Behaviors["wander"]->update(maxSpeed,deltaTime);

    //if (int(novichFollowPath->getPath().size) > 0) novichFollowPathWithObs.update(maxSpeed,deltaTime);
    
    //TEXTO
    //drawText(2,glm::vec3(2,0.0,10));

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