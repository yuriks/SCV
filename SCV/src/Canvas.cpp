#include "stdafx.h"
#include "Canvas.h"

#include "Kernel.h"

namespace scv {

#define PI_2 6.28318530717958
Canvas::Canvas(const scv::Point &p1, const scv::Point &p2) : Component(p1, p2) {
   setType(Component::CANVAS);
}

void Canvas::display()
{
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();

   update();

   if (_isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, getWidth(), getHeight(), 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glViewport(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());

   scissor->pushScissor(getScissor());
   glPushAttrib(GL_ALL_ATTRIB_BITS);

   glClearColor(1.f, 1.f, 1.f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glDisable(GL_TEXTURE_2D);

   render();

   glPopAttrib();

   scissor->popScissor();

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);

   if (glUseProgram) glUseProgram(0);

   kernel->applyDefaultTransformMatrix();
}

void Canvas::point(int x, int y)
{
   glBegin(GL_POINTS);
      glVertex2d(x, y);
   glEnd();
}

void Canvas::line( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
   glEnd();
}

void Canvas::rect( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_LINE_LOOP);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void Canvas::rectFill( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_QUADS);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void Canvas::polygon(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_LINE_LOOP);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void Canvas::polygonFill(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_POLYGON);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void Canvas::text(int x, int y, char *t)
{
    int tam = (int)strlen(t);
    int c;

    for(c=0; c<tam; c++)
    {
      glRasterPos2i(x + c*10, y);
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void Canvas::clear(float r, float g, float b)
{
   glClearColor( r, g, b, 1 );
}

void Canvas::circle( int x, int y, int raio, int div )
{
   double ang, x1, y1;
   double inc = PI_2/div;
   glBegin(GL_LINE_LOOP);
      for(ang=0; ang<6.27; ang+=inc) 
      {
         x1 = (cos(ang)*raio);
         y1 = (sin(ang)*raio);
         glVertex2d(x1+x, y1+y);
      }
   glEnd();
}

void Canvas::circleFill( int x, int y, int raio, int div )
{
   double ang, x1, y1;
   double inc = PI_2/div;
   glBegin(GL_POLYGON);
      for(ang=0; ang<6.27; ang+=inc)
      {
         x1 = (cos(ang)*raio);
         y1 = (sin(ang)*raio);
         glVertex2d(x1+x, y1+y);
      }
   glEnd();
}

void Canvas::color(float r, float g, float b)
{
   glColor3d(r, g, b  );
}

} // namespace scv