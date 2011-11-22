#ifndef __SCV_PROGRESSBAR_H__
#define __SCV_PROGRESSBAR_H__

#include "Label.h"
#include "Counter.h"

namespace scv {

class ProgressBar : public Label, public Counter {
public:
   ///////////////////////////////////////////////////////////
   ProgressBar(const scv::Point &p1, const scv::Point &p2, double startValue);
   ProgressBar(const scv::Point &p, unsigned int width, double startValue);
   ProgressBar(const scv::Point &p, double startValue);
   virtual ~ProgressBar(void);
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
   
   ///////////////////////////////////////////////////////////
   void setValue(double value);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

protected:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_PROGRESSBAR_H__