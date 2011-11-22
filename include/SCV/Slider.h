#ifndef __SCV_SLIDER_H__
#define __SCV_SLIDER_H__

#include "ComponentWithTexture.h"
#include "Counter.h"

namespace scv {

class Slider : public ComponentWithTexture, public Counter {
public:
   ///////////////////////////////////////////////////////////
   Slider(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   Slider(const scv::Point &p,                     double minValue, double maxValue, double startValue, double stepValue);
   virtual ~Slider(void);
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

   virtual void onValueChange(void);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

protected:
   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   void createTexture(void);
};

} // namespace scv

#endif // __SCV_SLIDER_H__