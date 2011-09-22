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
   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;
   virtual void onMouseHold (const scv::MouseEvent &evt) = 0;
   virtual void onMouseOver (const scv::MouseEvent &evt) = 0;
   virtual void onMouseUp   (const scv::MouseEvent &evt) = 0;
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;

   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;
   virtual void onKeyUp     (const scv::KeyEvent &evt) = 0;

   virtual void onResizing(void) = 0;
   virtual void onDragging(void) = 0;
   ///////////////////////////////////////////////////////////
};

} //namespace scv

#endif //__SCV_CALLBACKS_H__