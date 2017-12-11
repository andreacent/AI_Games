/* 
    Andrea Centeno
    carnet USB: 10-10138
    sep-dic 2017
*/
#ifndef TEXT_CPP
#define TEXT_CPP
#include <string.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

typedef enum { MODE_BITMAP } mode_type;

static mode_type mode;
static int font_index;

void print_bitmap_string(void* font, const char* s){
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

void my_init(){
   mode = MODE_BITMAP;
   font_index = 0;
}

void drawTextBox(glm::vec3 pIni, GLfloat h, GLfloat w){     
    glm::vec3 pF = {pIni.x+w, pIni.y, pIni.z-h};   
    GLfloat trianW = 1.2;
    GLfloat trianH = trianW/2;

    glColor3f(1,1,1);
    glBegin(GL_QUADS);  
        glVertex3f(pIni.x, pIni.y, pIni.z); 
        glVertex3f(pIni.x, pIni.y, pIni.z-h); 
        glVertex3f(pF.x, pF.y, pF.z); 
        glVertex3f(pIni.x+w, pIni.y, pIni.z); 
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(pF.x, pF.y, pF.z); 
        glVertex3f(pF.x-trianW, pF.y, pF.z); 
        glVertex3f(pF.x-trianH, pF.y, pF.z-trianH);
    glEnd();
    glColor3f(0,0,0);
}

void drawText(int n, glm::vec3 pos) {
  if (n > 4) return; //depende de tamano de bitmap_font_names

  void* bitmap_fonts[2] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_HELVETICA_10,   
  };

  const char* bitmap_font_names[6] = {
    "Hola!",
    "Hola! Como estas?",
    "Bien! y tu?",
    "Volver a empezar? s/n",
    "PERDISTE",
    "GANASTE"
  };

  switch(n) //donde opción es la variable a comparar
  {
    case 0:   
      drawTextBox(pos, 1.2f, 2.1f); 
      break;
    case 1:     
      drawTextBox(pos, 1.2f, 7.0f);
      break;
    case 2:     
      drawTextBox(pos, 1.2f, 4.0f); 
      break;
    case 4:   
      drawTextBox(pos, 3.0f, 16.0f); 
      glRasterPos3f(pos.x+1,pos.y,pos.z-1);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[n]);
      glRasterPos3f(pos.x+1,pos.y,pos.z-2);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[3]);
      return;
    case 3:
      drawTextBox(pos, 3.0f, 16.0f); 
      glRasterPos3f(pos.x+1,pos.y,pos.z-1);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[5]);
      glRasterPos3f(pos.x+1,pos.y,pos.z-2);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[n]);
      return;
    default: break;
  }

  glRasterPos3f(pos.x+0.2,pos.y,pos.z-0.8);
  print_bitmap_string(bitmap_fonts[1], bitmap_font_names[n]);
}

#endif