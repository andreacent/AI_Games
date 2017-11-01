#ifndef MESH_H
#define MESH_H
#include <string.h>
#include <GL/glut.h>

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

void drawText(int n) {
  void* bitmap_fonts[2] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_HELVETICA_10,   
  };

  const char* bitmap_font_names[4] = {
    "¡FELICIDADES!",
    "PERDISTE",  
    "Cambio de estado",
  };

  glColor3f(0.0,0.0,1.0);

  switch (n) {
    case 0:
      glRasterPos2f(-2,-9.0);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[n]);   
    break;
    case 1:
      glRasterPos2f(-1.5,-9.0);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[n]);
    break;
    case 2:
    case 3:
      glRasterPos2f(-5.5,8);
      print_bitmap_string(bitmap_fonts[0], bitmap_font_names[n]);
    break;
    default: break;
  }

}
#endif