#include "stdafx.h"
#include "ComponentInterface.h"
#include "Kernel.h"
#include "MenuHolder.h"
#include "Scissor.h"

namespace scv {

ComponentInterface::ComponentInterface(const scv::Point &p1, const scv::Point &p2) :
      _clicked(0,0), _cTranslate(0,0), _resizing(4, false) {

   _isComponent = true;

   if (p1 > p2) {
      _p1 = p2;
      _p2 = p1;
   } else if (p1.y > p2.y) {
      _p1 = scv::Point(p1.x,p2.y);
      _p2 = scv::Point(p2.x,p1.y);
   } else if (p1.x > p2.x) {
      _p1 = scv::Point(p2.x,p1.y);
      _p2 = scv::Point(p1.x,p2.y);
   } else {
      _p1 = p1;
      _p2 = p2;
   }

   _receivingCallbacks = true;

   _isDraggable = _isDragging = false;
   _isOvered    = _isHolded   = false;

   _isResizable  = _isResizing   = false;
   _isHResizable = _isVResizable = true;

   _minSize = Point(15,15);

   _isVisible   = true;

   _contextMenu = NULL;

   _type = NONE;

}

ComponentInterface::~ComponentInterface(void) {/*none*/}

Point ComponentInterface::getRelativePosition(void) const {
   return _p1;
}

void ComponentInterface::setRelativePosition(const Point &position) {
   Point diff = position - _p1;
   _p1 += diff;
   _p2 += diff;

   onDragging();
}

void ComponentInterface::setPanelTranslate(const Point &translate) {
   _cTranslate = translate;
   onDragging();
}

Point ComponentInterface::getPanelTranslate(void) {
   return _cTranslate;
}

Point ComponentInterface::getAbsolutePosition(void) const {
   return _p1 + _cTranslate;
}

int ComponentInterface::getWidth(void) const {
   return _p2.x - _p1.x;
}

int ComponentInterface::getHeight(void) const {
   return _p2.y - _p1.y;
}

Point ComponentInterface::getSize(void) const {
   return Point(getWidth(),getHeight());
}

void ComponentInterface::setWidth(const int width) {
   static Kernel *kernel = Kernel::getInstance();
   _p2.x = _p1.x + width;

   kernel->scissorNeedRefresh();
   onResizing();
}

void ComponentInterface::setHeight(const int height) {
   static Kernel *kernel = Kernel::getInstance();
   _p2.y = _p1.y + height;

   kernel->scissorNeedRefresh();
   onResizing();
}

void ComponentInterface::setPanelScissor(const Scissor::ScissorInfo &scissor) {
   _panelScissor = scissor;
}
const Scissor::ScissorInfo &ComponentInterface::getPanelScissor(void) {
   return _panelScissor;
}

bool ComponentInterface::isOvered(void) const {
   return _isOvered;
}

bool ComponentInterface::isHolded(void) const {
   return _isHolded;
}

bool ComponentInterface::isDragging(void) const {
   return _isDragging;
}

bool ComponentInterface::isResizing(void) const {
   return _isResizing;
}

bool ComponentInterface::isFocused(void) const {
   static Kernel *kernel = Kernel::getInstance();
   return (kernel->getFocusedComponent() == this);
}

void ComponentInterface::setDraggable(bool state) {
   _isDraggable = state;
}

void ComponentInterface::setResizable(bool state) {
   _isResizable = state;
}

void ComponentInterface::setVisible(bool state) {
   _isVisible = state;
}

bool ComponentInterface::isVisible(void) {
   return _isVisible;
}

void ComponentInterface::registerContextMenu(ContextMenu *contextMenu) {
   static MenuHolder *menu = MenuHolder::getInstance();
   _contextMenu = contextMenu;
   menu->registerParentMenu(_contextMenu);
}

bool ComponentInterface::isInside(const MouseEvent &evt) const {
   if (_isVisible && _panelScissor.isInside(evt.getInversePosition())) {
      Point currPosition = getAbsolutePosition();
      Point evtPosition  = evt.getPosition();
      if (evtPosition.x >= currPosition.x && evtPosition.x < currPosition.x + getWidth() &&
            evtPosition.y >= currPosition.y && evtPosition.y < currPosition.y + getHeight()) {
         return true;
      }
   }
   return false;
}

void ComponentInterface::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();

   Point evtPosition         = evt.getPosition();
   Point evtInversePosition  = evt.getInversePosition();
   Point currPosition        = getAbsolutePosition();

   if (evt.getState() == MouseEvent::up) {
      std::fill(_resizing.begin(), _resizing.end(), false);
      _isResizing = false;
      kernel->unlockMouseUse(this);
   } else if (_isResizable && _isResizing && evt.getState() == MouseEvent::hold && evt.getButton() == MouseEvent:: left) {
      /*
         setWidth and setHeight already call onResizing() callback
      */
      if (_isHResizable && _resizing[0]) {
         if (evtPosition.x - _clicked.x > _p2.x - _minSize.x) _p1.x = _p2.x - _minSize.x;
         else _p1.x = evtPosition.x - _clicked.x;
         onResizing();
      }
      if (_isHResizable && _resizing[1]) {
         if (evtPosition.x - currPosition.x < _minSize.x) setWidth(_minSize.x);
         else setWidth(evtPosition.x - currPosition.x);
      }
      if (_isVResizable && _resizing[2]) {
         if (evtPosition.y - _clicked.y > _p2.y - _minSize.y)  _p1.y = _p2.y - _minSize.y;
         else _p1.y = evtPosition.y - _clicked.y;
         onResizing();
      }
      if (_isVResizable && _resizing[3]) {
         if (evtPosition.y - currPosition.y < _minSize.y) setHeight(_minSize.y);
         else setHeight(evtPosition.y - currPosition.y);
      }

      if (kernel->lockMouseUse(this)) {
         if (_resizing[0] && _resizing[2]) cursor->setGlutCursor(GLUT_CURSOR_TOP_LEFT_CORNER);
         else if (_resizing[1] && _resizing[2]) cursor->setGlutCursor(GLUT_CURSOR_TOP_RIGHT_CORNER);
         else if (_resizing[0] && _resizing[3]) cursor->setGlutCursor(GLUT_CURSOR_BOTTOM_LEFT_CORNER);
         else if (_resizing[1] && _resizing[3]) cursor->setGlutCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER);

         else if (_resizing[0]) cursor->setGlutCursor(GLUT_CURSOR_LEFT_RIGHT);
         else if (_resizing[1]) cursor->setGlutCursor(GLUT_CURSOR_LEFT_RIGHT);
         else if (_resizing[2]) cursor->setGlutCursor(GLUT_CURSOR_UP_DOWN);
         else if (_resizing[3]) cursor->setGlutCursor(GLUT_CURSOR_UP_DOWN);
      }
   }

   if (_panelScissor.isInside(evtInversePosition) && !isDragging() && _isResizable) {
      // top left corner
      if (_isVResizable && _isHResizable && isInsideCorner(evtPosition) == 0 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_TOP_LEFT_CORNER);
         if (evt.getState() == MouseEvent::click) {
            _resizing[0] = true; _resizing[2] = true;
            _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
         // top right corner
      } else if (_isVResizable && _isHResizable && isInsideCorner(evtPosition) == 1 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_TOP_RIGHT_CORNER);
         if (evt.getState() == MouseEvent::click) {
            _resizing[1] = true; _resizing[2] = true;
            _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
         // bottom left corner
      } else if (_isVResizable && _isHResizable && isInsideCorner(evtPosition) == 2 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_BOTTOM_LEFT_CORNER);
         if (evt.getState() == MouseEvent::click) {
            _resizing[0] = true; _resizing[3] = true;
            _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
         // bottom right corner
      } else if (_isVResizable && _isHResizable && isInsideCorner(evtPosition) == 3 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER);
         if (evt.getState() == MouseEvent::click) {
            _resizing[1] = true; _resizing[3] = true;
            _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }


         // left
      } else if (_isHResizable && isInsideSide(evtPosition) == 0 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_LEFT_RIGHT);
         if (kernel->requestMouseUse(this) && evt.getState() == MouseEvent::click) {
            _resizing[0] = true; _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
         // right
      } else if (_isHResizable && isInsideSide(evtPosition) == 1 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_LEFT_RIGHT);
         if (kernel->requestMouseUse(this) && evt.getState() == MouseEvent::click) {
            _resizing[1] = true; _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
         // top
      } else if (_isVResizable && isInsideSide(evtPosition) == 2 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_UP_DOWN);
         if (kernel->requestMouseUse(this) && evt.getState() == MouseEvent::click) {
            _resizing[2] = true; _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
         // bottom
      } else if (_isVResizable && isInsideSide(evtPosition) == 3 && kernel->requestMouseUse(this)) {
         if (!_isResizing) cursor->setGlutCursor(GLUT_CURSOR_UP_DOWN);
         if (kernel->requestMouseUse(this) && evt.getState() == MouseEvent::click) {
            _resizing[3] = true; _isResizing = true;
            _clicked = (evtPosition - currPosition) + _cTranslate;
         }
      }
      if (std::find(_resizing.begin(), _resizing.end(), true) != _resizing.end()) {
         kernel->requestComponentFocus(this);
         return;
      }
   }

   
   if (isInside(evt) && kernel->requestMouseUse(this)) {
      if (evt.getState() == MouseEvent::wheelup || evt.getState() == MouseEvent::wheeldown) {
         if (_receivingCallbacks) onMouseWheel(evt);
      } else if (evt.getState() == MouseEvent::up) {
         kernel->unlockMouseUse(this);
         _isDragging = false;
         _isHolded = false;
         if (_receivingCallbacks) onMouseUp(evt - currPosition);
         if (_contextMenu != NULL && evt.getButton() == MouseEvent::right) {
            menu->activeMenu(_contextMenu, evtPosition);
         }
      } else if (evt.getState() == MouseEvent::hold && isFocused()) {
         kernel->requestComponentFocus(this);
         if (isFocused()) {
            if (_isDragging) {
               setRelativePosition(evtPosition - _clicked);
               cursor->setGlutCursor(GLUT_CURSOR_CYCLE);
            }
            if (_receivingCallbacks) {
               _isHolded = true;
               onMouseHold(evt - currPosition);
            }
         } else {
            _isHolded = false;
         }

      } else if (evt.getState() == MouseEvent::motion) {
         if (_receivingCallbacks) {
            _isOvered = true;
            onMouseOver(evt - currPosition);
         }
      } else if (evt.getState() == MouseEvent::click) {
         kernel->requestComponentFocus(this);
         if (evt.getButton() == MouseEvent::left) {
            if (_isDraggable && isFocused()) {
               _isDragging = true;
               _clicked = (evtPosition - currPosition) + _cTranslate;
               kernel->lockMouseUse(this);
            }
            menu->closeAllMenus();
         }
         if (_receivingCallbacks) {
            _isHolded = true;
            onMouseClick(evt - currPosition);
         }
      }
   } else { // outside
      if (evt.getState() == MouseEvent::up || evt.getState() == MouseEvent::click) {
         _isHolded = false;
         _isDragging = false;
         kernel->unlockMouseUse(this);
      } else if (evt.getState() == MouseEvent::motion) {
         _isOvered = false;
      } else if (evt.getState() == MouseEvent::hold) {
         if (_isDragging && _panelScissor.isInside(evt.getInversePosition()) && isFocused()) {
            setRelativePosition(evtPosition - _clicked);
            if (_receivingCallbacks) _isHolded = true;
            cursor->setGlutCursor(GLUT_CURSOR_CYCLE);
         } else if (_isDragging && _receivingCallbacks) {
            _isHolded = true;
         } else {
            _isHolded = false;
            if (_receivingCallbacks) _isDragging = false;
         }
      }
   }
}

void ComponentInterface::processKey(const scv::KeyEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   if (isFocused()) {
      if (evt.getState() == KeyEvent::down) {
         onKeyPressed(evt);
      } else if (evt.getState() == KeyEvent::up) {
         onKeyUp(evt);
      }
      if (_isDraggable) {
         moveComponent(evt);
      }
   }
}

int ComponentInterface::isInsideCorner(const Point &evtPosition) {
   Point currPosition = getAbsolutePosition();

   // top left corner
   if (evtPosition.x >= currPosition.x - s_mouseBacklash && evtPosition.x <= currPosition.x + s_mouseBacklash  * 2
         && evtPosition.y >= currPosition.y  - s_mouseBacklash && evtPosition.y <= currPosition.y + s_mouseBacklash * 2) {
      return 0;
   // top right corner
   } else if (evtPosition.x >= currPosition.x + getWidth() - s_mouseBacklash * 2 && evtPosition.x <= currPosition.x + getWidth() + s_mouseBacklash
         && evtPosition.y >= currPosition.y - s_mouseBacklash * 2 && evtPosition.y <= currPosition.y + s_mouseBacklash) {
      return 1;
   // bottom left corner
   } else if (evtPosition.x >= currPosition.x - s_mouseBacklash && evtPosition.x <= currPosition.x + s_mouseBacklash * 2
         && evtPosition.y >= currPosition.y + getHeight() - s_mouseBacklash && evtPosition.y <= currPosition.y + getHeight() + s_mouseBacklash * 2) {
      return 2;
   // bottom right corner
   } else if (evtPosition.x >= currPosition.x  + getWidth() - s_mouseBacklash * 2 && evtPosition.x <= currPosition.x  + getWidth() + s_mouseBacklash
         && evtPosition.y >= currPosition.y + getHeight() - s_mouseBacklash * 2 && evtPosition.y <= currPosition.y + getHeight() + s_mouseBacklash) {
      return 3;
   } else {
      return -1;
   }
}

int ComponentInterface::isInsideSide(const Point &evtPosition) {
   Point currPosition = getAbsolutePosition();

   // left
   if (evtPosition.x >= currPosition.x - s_mouseBacklash && evtPosition.x <= currPosition.x + s_mouseBacklash
      && evtPosition.y >= currPosition.y && evtPosition.y <= currPosition.y + getHeight()) {
         return 0;
   // right
   } else if (evtPosition.x >= currPosition.x + getWidth() - s_mouseBacklash && evtPosition.x <= currPosition.x + getWidth() + s_mouseBacklash
      && evtPosition.y >= currPosition.y && evtPosition.y <= currPosition.y + getHeight()) {
         return 1;
   // top
   } else if (evtPosition.x >= currPosition.x && evtPosition.x <= currPosition.x + getWidth()
      && evtPosition.y >= currPosition.y - s_mouseBacklash && evtPosition.y <= currPosition.y + s_mouseBacklash) {
         return 2;
   // bottom
   } else if (evtPosition.x >= currPosition.x && evtPosition.x <= currPosition.x + getWidth()
      && evtPosition.y >= currPosition.y + getHeight() - s_mouseBacklash && evtPosition.y <= currPosition.y + getHeight() + s_mouseBacklash) {
         return 3;
   } else {
      return -1;
   }
}

void ComponentInterface::setCallbacksActive(bool state) {
   _receivingCallbacks = state;
}

bool ComponentInterface::isCallbacksActive(void) {
   return _receivingCallbacks;
}

void ComponentInterface::moveComponent(const scv::KeyEvent &evt) {
   if (evt.getState() == KeyEvent::down) {
      if (evt.getKeyString() == "Up") {
         
         setRelativePosition(Point(_p1.x, _p1.y - 1));
         onDragging();
      }
      else if (evt.getKeyString() == "Down") {
         setRelativePosition(Point(_p1.x, _p1.y + 1));
         onDragging();
      }
      else if (evt.getKeyString() == "Left") {
         setRelativePosition(Point(_p1.x - 1, _p1.y));
         onDragging();
      }
      else if (evt.getKeyString() == "Right") {
         setRelativePosition(Point(_p1.x + 1, _p1.y));
         onDragging();
      }
   }
}

ComponentInterface::typeComponent ComponentInterface::getType(void) {
   return _type;
}



} // namespace scv
