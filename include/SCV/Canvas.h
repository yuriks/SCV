#ifndef __SCV_CANVAS_H__
#define __SCV_CANVAS_H__

///////////////////////////////////////////////////////////
#include "ComponentWithoutTexture.h"
///////////////////////////////////////////////////////////

namespace scv {

class Canvas : public ComponentWithoutTexture {
public:
   ///////////////////////////////////////////////////////////
   Canvas(const scv::Point &p1, const scv::Point &p2);
   virtual ~Canvas(void);
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void render(void);
   virtual void update(void);
   ///////////////////////////////////////////////////////////


   //Adicional Rendering functions
   void point(int x, int y); //point coordinates
   void line( int x1, int y1, int x2, int y2 ); 

   //rectangles
   void rect( int x1, int y1, int x2, int y2 ); 
   void rectFill( int x1, int y1, int x2, int y2 ); 

   //Convex polygon. Four vertices specify a rectangle
   void polygon(float vx[], float vy[], int n_elems); 
   void polygonFill(float vx[], float vy[], int n_elems); 

   //
   void circle( int x, int y, int raio, int div );
   void circleFill( int x, int y, int raio, int div );

   //Colors for drawing and cleanning
   void color(float r, float g, float b);
   void clear(float r, float g, float b);

   //draw a text
   void text(int x, int y, char *t);

};

} // namespace scv


#endif // __SCV_CANVAS_H__