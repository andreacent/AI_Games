/* 
    Andrea Centeno
    carnet USB: 10-10138
    Sergio Teran
    carnet USB: 11-11020
    sep-dic 2017
*/  

#include "mesh/Mesh.cpp"
std::list<Mesh*> meshs;

#include "movements/BlendedSteering.cpp"
#include "graph/graph.cpp"

#include "characters/Marlene.h"

#include "assets/text.cpp"
#include "assets/map.h"

#include "stateMachine/StateMachine.cpp"
#include "senseManager/RegionalSenseManager.h"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

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
Marlene marleneAux = {*new Kinematic({33.4,0.0,20.5},0.0),'p'};

Kinematic target = {{3.5f,0.0f,3.5f}};//{{26.0f,0,26.0f},0.0};
Marlene marlene = {target,'t'};

/* STUDENT HELLO */
Marlene studentHello = {*new Kinematic({27.0f,0.0,15.5f},0.0),'e'};
/* STUDENT */
Marlene student = {*new Kinematic({40.0f,0.0,30.0f},0.0),'a'};
std::list<Kinematic*> studentTargets;
/* STUDENT IN ROOMS*/
Marlene studentLDC = {*new Kinematic({7.0f,0.0,38.0f},0.0),'a'};
std::list<Kinematic*> studentLDCTargets;
Marlene studentChang = {*new Kinematic({48.0f,0.0,2.0f},0.0),'a'};
std::list<Kinematic*> studentChangTargets;
/* PROFESOR */
Marlene profesor1 = {*new Kinematic({52.0f,0.0,30.0f},0.0),'s'};
std::list<Kinematic*> profesor1Targets;
Marlene profesor2 = {*new Kinematic({3.0f,0.0,35.0f},0.0),'s'};
std::list<Kinematic*> profesor2Targets;

/****************** Initialize **********************/
void initialize(){
    ini = true;

    /*MAP*/
    meshs = drawMap();

    /*STATE MACHINES*/
    std::list<Kinematic*> studentHelloTargets;
    studentHelloTargets.push_back(&target);   
    studentHelloTargets.push_back(&student.character); 
    studentHelloTargets.push_back(&studentLDC.character);    
    studentHelloTargets.push_back(&studentChang.character);
    studentHello.setStateMachine(HelloStateMachine(studentHello.character,studentHelloTargets));

    studentTargets.push_back(&studentLDC.character);    
    studentTargets.push_back(&studentChang.character);
    student.setStateMachine(StudentStateMachine(student.character,target,collisionDetector,studentTargets,graph));

    studentLDCTargets.push_back(&student.character);   
    studentLDCTargets.push_back(&studentChang.character);
    studentLDC.setStateMachine(StudentStateMachine(studentLDC.character,target,collisionDetector,studentLDCTargets,graph));

    studentChangTargets.push_back(&student.character); 
    studentChangTargets.push_back(&studentLDC.character);
    studentChang.setStateMachine(StudentStateMachine(studentChang.character,target,collisionDetector,studentChangTargets,graph));

    profesor1Targets.push_back(&profesor2.character); 
    profesor1.setStateMachine(FollowStateMachine(profesor1.character,target,profesor1Targets,collisionDetector ));
    profesor2Targets.push_back(&profesor1.character); 
    profesor2.setStateMachine(FollowStateMachine(profesor2.character,target,profesor2Targets,collisionDetector ));

    /*GRAPH*/
    graph.createGameGraphNew();

    glClearColor(0.81960,0.81960,0.81960,1);
}

void reset(){
    target.position = {3.5f,0.0f,3.5f};
    student.character.reset({35.0f,0.0,30.0f});
    studentLDC.character.reset({7.0f,0.0,38.0f});
    studentChang.character.reset({48.0f,0.0,2.0f});
    profesor1.character.reset({52.0f,0.0,30.0f});
    profesor2.character.reset({3.0f,0.0,30.0f});

    /*STATE MACHINES*/
    student.setStateMachine(StudentStateMachine(student.character,target,collisionDetector,studentTargets,graph));
    studentLDC.setStateMachine(StudentStateMachine(studentLDC.character,target,collisionDetector,studentLDCTargets,graph));
    studentChang.setStateMachine(StudentStateMachine(studentChang.character,target,collisionDetector,studentChangTargets,graph));
    profesor1.setStateMachine(FollowStateMachine(profesor1.character,target,profesor1Targets,collisionDetector ));
    profesor2.setStateMachine(FollowStateMachine(profesor2.character,target,profesor2Targets,collisionDetector ));

    /*GRAPH*/
    graph.createGameGraphNew();

    stopGame = false;
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
            showPath = !showPath;
        break;
        case ' ': //mover en y (saltar)
            target.velocity.y = targetVelocity;
            cout<<"pos target "<< target.position.x<<","<<target.position.y<<","<<target.position.z<<endl;
        break;
        case 'n':
            if(!stopGame) break;
        case 27: // Escape key
            graph.printGraph();
            glutDestroyWindow ( WinId );
            exit (0);
        break;
        case 's':
            if(stopGame) reset();
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
            target.position.y = 0.0;
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
    gluLookAt(x,0,z,x,10,z-1.0f,0,1,0);
    //gluLookAt(25,0,21,25,10,21-1.0f,0,1,0);

    drawFloor();
    drawDetails();
    glLineWidth(pointSize);

    if(activeTriangles) graph.drawTriangles(); 
    if(activeMap) for (list<Mesh*>::iterator m=meshs.begin(); m != meshs.end(); ++m) (*m)->draw();

    /* PERSONAJES */
    studentHello.draw();

    student.draw();
    studentLDC.draw();
    studentChang.draw();

    profesor1.draw();
    profesor2.draw();

    marlene.draw();

    if (!stopGame){
        GLfloat timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
        deltaTime = (timeSinceStart - oldTimeSinceStart) * 0.001;
        oldTimeSinceStart = timeSinceStart;

        target.updatePosition(deltaTime,meshs);
        target.updateOrientation(deltaTime);

        //STUDENTS
        studentHello.checkStateMachine();

        student.checkStateMachine();

        studentLDC.checkStateMachine();

        studentChang.checkStateMachine();  
     
        profesor1.checkStateMachine();
        profesor2.checkStateMachine();
    
        /*
        se detiene el juego cuando los personajes rojos estan en la coordinacion
        */
        if( profesor1.character.position.z < 6 && profesor1.character.position.x < 13
            && profesor2.character.position.z < 6 && profesor2.character.position.x < 13 ){
            stopGame = true;
            win = true;
        }
    }
    /*
    else if (win){        
        drawText(3,glm::vec3(19,0.0,24));
        marleneAux.draw();
    }
    else{
        drawText(4,glm::vec3(19,0.0,24));
        marleneAux.draw();
    }
    */
    else if (win){ 
        drawText(3,{target.position.x-6,target.position.y,target.position.z+3.5});
    }
    else{
        drawText(4,{target.position.x-6,target.position.y,target.position.z+3.5});        
    }

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

    //GLfloat widthVP  = 21.0;
    //GLfloat heightVP = 21.0;
    GLfloat widthVP  = 8.0;
    GLfloat heightVP = 8.0;

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