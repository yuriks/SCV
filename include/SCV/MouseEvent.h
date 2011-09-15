/*!
\file       MouseEvent.h
\brief      Implementation of the Mouse Event.
\author     SCV Team
*/

#ifndef __SCV_MOUSE_EVENT_H__
#define __SCV_MOUSE_EVENT_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Point.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A class that store all interaction with the mouse in a object.
 \ingroup internal
*/

class MouseEvent {
public:
   enum button {
      left   = GLUT_LEFT_BUTTON,
      middle = GLUT_MIDDLE_BUTTON,
      right  = GLUT_RIGHT_BUTTON,
      none
   };
   enum state {
      click = GLUT_DOWN,
      up = GLUT_UP,
      hold,
      motion,
      wheelup,
      wheeldown
   };

   MouseEvent(void);
   MouseEvent(MouseEvent::button button, MouseEvent::state state, const Point &location, bool doubleClick = false);

   MouseEvent& operator=(const MouseEvent&rhs);

   Point getPosition(void) const;
   Point getInversePosition(void) const;
   MouseEvent::button getButton(void) const;
   MouseEvent::state getState(void) const;

   inline bool doubleClick(void) const {
      return _doubleClick;
   }

   MouseEvent operator-(const Point &p) const {
      return MouseEvent(_button, _state, _position - p);
   }

private:
   MouseEvent::button _button;
   MouseEvent::state _state;
   Point _position;
   bool _doubleClick;
};

} // namespace scv

#endif // __SCV_MOUSE_EVENT_H__