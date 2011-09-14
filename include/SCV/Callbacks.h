/*!
\file       Callbacks.h
\brief      Implementation of a Callback class.
\author     SCV Team
*/

#ifndef __SCV_CALLBACKS_H__
#define __SCV_CALLBACKS_H__

#ifndef DOXYGEN_SKIP_THIS
#include "MouseEvent.h"
#include "KeyEvent.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! Callbacks Interface.
 */

class Callbacks {
public:

   Callbacks(void) {};
   virtual ~Callbacks(void) {};

   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;
   virtual void onMouseHold(const scv::MouseEvent &evt) = 0;
   virtual void onMouseOver(const scv::MouseEvent &evt) = 0;
   virtual void onMouseUp(const scv::MouseEvent &evt) = 0;
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;
   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;
   virtual void onKeyUp(const scv::KeyEvent &evt) = 0;

protected:

   virtual void processMouse(const scv::MouseEvent &evt) = 0;
   virtual void processKey(const scv::KeyEvent &evt) = 0;

};

} // namespace scv

#endif // __SCV_CALLBACKS_H__