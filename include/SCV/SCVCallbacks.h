#ifndef __SCV_CALLBACKS_H__
#define __SCV_CALLBACKS_H__

#include "MouseEvent.h"
#include "KeyEvent.h"

namespace scv {

class SCVCallbacks {
public:
   ///////////////////////////////////////////////////////////
   virtual ~SCVCallbacks() {};
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt) {}
   virtual void onMouseHold (const scv::MouseEvent &evt) {}
   virtual void onMouseOver (const scv::MouseEvent &evt) {}
   virtual void onMouseUp   (const scv::MouseEvent &evt) {}
   virtual void onMouseWheel(const scv::MouseEvent &evt) {}

   virtual void onKeyPressed(const scv::KeyEvent &evt) {}
   virtual void onKeyUp     (const scv::KeyEvent &evt) {}

   virtual void onSizeChange(void) {}
   virtual void onPositionChange(void) {}
   ///////////////////////////////////////////////////////////
};

} //namespace scv

#endif //__SCV_CALLBACKS_H__