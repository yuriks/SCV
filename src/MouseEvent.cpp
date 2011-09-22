#include "stdafx.h"
#include "MouseEvent.h"

#include "Point.h"
#include "Kernel.h"

namespace scv {

MouseEvent::MouseEvent(void): _button(MouseEvent::none), _state(MouseEvent::motion), _position(Point(-1,-1)), _doubleClick(false) {}

MouseEvent::MouseEvent(MouseEvent::button button, MouseEvent::state state, const Point &position, bool doubleClick) :
      _button(button), _state(state), _position(position), _doubleClick(doubleClick) {}

MouseEvent& MouseEvent::operator=(const MouseEvent&rhs) {
   _button      = rhs._button;
   _state       = rhs._state;
   _position    = rhs._position;
   _doubleClick = rhs._doubleClick;
   return (*this);
}

Point MouseEvent::getPosition(void) const {
   return _position;
}

Point MouseEvent::getInversePosition(void) const {
   static Kernel *kernel = Kernel::getInstance();
   return Point(_position.x, kernel->getHeight() - _position.y);
}

MouseEvent::button MouseEvent::getButton(void) const {
   return _button;
}

MouseEvent::state MouseEvent::getState(void) const {
   return _state;
}

} // namespace scv

