#include "stdafx.h"
#include "Canvas.h"

namespace scv {

#define PI_2 6.28318530717958
Canvas::Canvas(const scv::Point &p1, const scv::Point &p2) : ComponentWithoutTexture(p1, p2) {
   setType(Component::CANVAS);
}

Canvas::~Canvas(void) {
}

void Canvas::onMouseClick(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseClick(evt);   
}

void Canvas::onMouseHold(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseHold(evt);
}

void Canvas::onMouseOver(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseOver(evt);
}

void Canvas::onMouseUp(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseUp(evt);
}

void Canvas::onMouseWheel(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseWheel(evt);
}

void Canvas::onKeyPressed(const scv::KeyEvent &evt) {
   ComponentWithoutTexture::onKeyPressed(evt);
}

void Canvas::onKeyUp(const scv::KeyEvent &evt) {
   ComponentWithoutTexture::onKeyUp(evt);
}

void Canvas::onSizeChange(void) {
   ComponentWithoutTexture::onSizeChange();
}

void Canvas::onPositionChange(void) {
   ComponentWithoutTexture::onPositionChange();
}

void Canvas::render(void) {
   ComponentWithoutTexture::render();
}

void Canvas::update(void) {
   ComponentWithoutTexture::update();
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