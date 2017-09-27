/* 
    Andrea Centeno
    carnet USB: 10-10138
    sep-dic 2017
*/    
#include "header.h"
#include "draw.cpp"
#include "movements/KinematicSeek.h"
#include "movements/KinematicFlee.h"
#include "movements/KinematicArrive.h"
#include "movements/KinematicWander.h"

GLfloat ang = 1.0,
        trans = 0.3,
        pointSize=3.0;

Static target = {{-16.0f,-4.0f},0.0f};
Static character = {{12.0f,8.0f},0.0f};

KinematicSeek kinematicSeek = {character,target};
KinematicFlee kinematicFlee = {character,target};
KinematicArrive kinematicArrive = {character,target};
KinematicWander kinematicWander = {character};

GLfloat oldTimeSinceStart = 0;

/************************* KEYBOARD **************************/
void controlKey (unsigned char key, int xmouse, int ymouse){   
    switch (key){
        case 'a': //Trasladarse a la izquierda.  
            target.position.x-=trans; break;
        case 'd': //Trasladarse a la derecha.  
            target.position.x+=trans; break;
        case 'w': //Trasladarse arriba. 
            target.position.y+=trans; break;
        case 's': //Trasladarse abajo.   
            target.position.y-=trans; break;
        case 'z': //Rotar anti horario.  
            target.orientation -=ang; break;
        case 'c': //Rotar horario. 
            target.orientation +=ang; break;
        default: break;
    }
    //glutPostRedisplay(); 
}

GLfloat getDeltaTime(){    
    GLfloat timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    GLfloat deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;
    return deltaTime;
}

void kinematicSeekMovement(){  
    KinematicSteeringOutput kso = kinematicSeek.getSteering();
    character.update(kso.velocity,kso.rotation,getDeltaTime());
}

void kinematicFleeMovement(){  
    KinematicSteeringOutput kso = kinematicFlee.getSteering();
    character.update(kso.velocity,kso.rotation,getDeltaTime());
}

void kinematicArriveMovement(){  
    KinematicSteeringOutput kso = kinematicArrive.getSteering();
    if(distance(kso.velocity,{0,0}) != 0){
        character.update(kso.velocity,kso.rotation,getDeltaTime());
    }
}

void kinematicWanderMovement(){  
    KinematicSteeringOutput kso = kinematicWander.getSteering();
    character.update(kso.velocity,kso.rotation,getDeltaTime());
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

    glLineWidth(pointSize);
    glColor3f(0,0.6,0.6);
    drawFace(target.position,target.orientation,pointSize);
    glColor3f(0.4,0.2,0.8);
    drawFace(character.position,character.orientation,pointSize);

    //kinematicSeekMovement();
    //kinematicFleeMovement();
    //kinematicArriveMovement();
    kinematicWanderMovement();
  

    glFlush();
    glutPostRedisplay();
}

/************************* Viewport **************************/
void reshape(int w, int h) {
    GLfloat aspectratio = (GLfloat) w / (GLfloat) h;
    GLfloat zoom = 20.0;

    glMatrixMode(GL_PROJECTION);   
    glLoadIdentity(); 
    glViewport(0, 0, w, h);
    /*
    gluPerspective( 45 ,        // �ngulo de visi�n
      (float)h/(float)w, // Raz�n entre el largo y el ancho, para calcular la perspectiva
      1,                        // Cuan cerca se puede ver
      1000);
    */
    if (w <= h){
        glOrtho(-zoom, zoom, -zoom/aspectratio, zoom/aspectratio, -1.0, 1.0); 
    }else{
        glOrtho(-zoom*aspectratio, zoom*aspectratio, -zoom, zoom, -1.0, 1.0);
    }
    
}

/*************************** MAIN ***************************/
int main (int argc, char** argv) {
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("AI VideoGame");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutKeyboardFunc(controlKey);
    
    glutMainLoop();
    return 0;
}