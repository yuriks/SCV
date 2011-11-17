#include "stdafx.h"
#include "Component.h"

#include "Kernel.h"
#include "MenuHolder.h"
#include "Scissor.h"

namespace scv {

Component::Component(const scv::Point &p1, const scv::Point &p2) : _resizing(4, false) {
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

   _isVisible   = true;

   _contextMenu = NULL;

   _type = NONE;

   _parent = NULL;   
   
   setMaximumSize(Point(-1, -1));
   setPreferredSize(Point(getWidth(), getHeight()));
   setMinimumSize(getPreferredSize());
}

Component::~Component(void) {
   setParent(NULL);
   
   Component::List::iterator iter = _children.begin();
   while (iter != _children.end()) {
      Component *pItem = (*iter);
      iter = _children.erase(iter);
      delete pItem;
   }
}

Point Component::getRelativePosition(void) const {
   return _p1;
}

void Component::setRelativePosition(const Point &position) {
   Point diff = _p2 - _p1;
   _p1 = position;
   _p2 = _p1 + diff;

   onPositionChange();
}

Point Component::getAbsolutePosition(void) const {
   if (getParent() != NULL) {
      return getParent()->getAbsolutePosition() + _p1;
   } else {
      return getRelativePosition();
   }
}

void Component::setAbsolutePosition(const Point &position) {
   if (getParent() != NULL) {
      Point diff = _p2 - _p1;

      _p1 = position - getParent()->getAbsolutePosition();
      _p2 = _p1 + diff;

      onPositionChange();
   } else {
      setRelativePosition(position);
   }   
}

void Component::setWidth(const int width) {
   if (width < getMinimumSize().x) {
      _p2.x = _p1.x + getMinimumSize().x;
   } else {
      _p2.x = _p1.x + width;
   }
   onSizeChange();
}

void Component::setHeight(const int height) {
   if (height < getMinimumSize().y) {
      _p2.y = _p1.y + getMinimumSize().y;
   } else {
      _p2.y = _p1.y + height;
   }
   onSizeChange();
}

bool Component::isFocused(void) const {
   return (Kernel::getInstance()->getFocusedComponent() == this);
}

void Component::registerContextMenu(ContextMenu *contextMenu) {
   _contextMenu = contextMenu;
   MenuHolder::getInstance()->registerMenu(_contextMenu);
}


void Component::unregisterContextMenu(void) {
   _contextMenu = NULL;   
}

bool Component::isInside(const Point &evtPosition) const {
   if (isVisible() && getParentScissor().isInside(evtPosition.inverse())) {
      Point currPosition = getAbsolutePosition();
      if (evtPosition.x >= currPosition.x &&
         evtPosition.x < (currPosition.x + getWidth()) &&
         evtPosition.y >= currPosition.y &&
         evtPosition.y < (currPosition.y + getHeight())) {
            return true;
         }
      }
   return false;
}

void Component::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();

   Point evtPosition         = evt.getPosition();
   Point evtInversePosition  = evt.getInversePosition();
   Point currPosition        = getAbsolutePosition();

   if (!_isResizing) std::fill(_resizing.begin(), _resizing.end(), false);

   if (evt.getState() == MouseEvent::UP) {
      std::fill(_resizing.begin(), _resizing.end(), false);
      _isResizing = false;
      kernel->unlockMouseUse(this);

   } else if (_isResizable && _isResizing && evt.getState() == MouseEvent::HOLD && evt.getButton() == MouseEvent::LEFT) {
      if (_isHResizable) {
         if (_resizing[left]) {
            int width = getWidth();
            setWidth(getWidth() + getAbsolutePosition().x - evtPosition.x);            
            setAbsolutePosition(Point(getAbsolutePosition().x + width - getWidth(), getAbsolutePosition().y));
         } else if (_resizing[right]) {            
            setWidth(evtPosition.x - currPosition.x);
         }
      }
      if (_isVResizable) {
         if (_resizing[top]) {
            int height = getHeight();
            setHeight(getHeight() + getAbsolutePosition().y - evtPosition.y);
            setAbsolutePosition(Point(getAbsolutePosition().x, getAbsolutePosition().y + height - getHeight()));         
         } else if (_resizing[bottom]) {
            setHeight(evtPosition.y - currPosition.y);
         }
      }
      if (kernel->lockMouseUse(this)) setResizingCursor();
   }
   
   if (getParentScissor().isInside(evtInversePosition) && !isDragging() && _isResizable) {
      if (_isHResizable && !_resizing[left] && !_resizing[right]) {
         if (isInsideSide(left, evtPosition) && kernel->requestMouseUse(this)) {
            _resizing[left] = true;
         } else if (isInsideSide(right, evtPosition) && kernel->requestMouseUse(this)) {
            _resizing[right] = true;
         }
      }      

      if (_isVResizable && !_resizing[top] && !_resizing[bottom]) {
         if (isInsideSide(top, evtPosition) && kernel->requestMouseUse(this)) {
            _resizing[top] = true;
         } else if (isInsideSide(bottom, evtPosition) && kernel->requestMouseUse(this)) {
            _resizing[bottom] = true;            
         }
      }      

      setResizingCursor();
      if (std::find(_resizing.begin(), _resizing.end(), true) != _resizing.end()) {
         if (evt.getState() == MouseEvent::CLICK) _isResizing = true;
         kernel->requestComponentFocus(this);  
         return;
      }
   }

   //inside
   if (isInside(evt.getPosition()) && kernel->requestMouseUse(this)) {
      if (evt.getState() == MouseEvent::WHELLUP || evt.getState() == MouseEvent::WHEELDOWN) {
         onMouseWheel(evt);

      } else if (evt.getState() == MouseEvent::UP) {
         kernel->unlockMouseUse(this);
         _isDragging = false;
         _isHolded = false;
         onMouseUp(evt - currPosition);
         if (_contextMenu != NULL && evt.getButton() == MouseEvent::RIGHT) {
            menu->activeMenu(_contextMenu, evtPosition);
         }

      } else if (evt.getState() == MouseEvent::HOLD && isFocused()) {
         kernel->requestComponentFocus(this);
         if (isFocused()) {
            if (_isDragging) {
               setAbsolutePosition(evtPosition + _clickDiff);
               cursor->setGlutCursor(GLUT_CURSOR_CYCLE);
            }
            _isHolded = true;
            onMouseHold(evt - currPosition);
         } else {
            _isHolded = false;
         }

      } else if (evt.getState() == MouseEvent::MOTION) {
         _isOvered = true;
         onMouseOver(evt - currPosition);

      } else if (evt.getState() == MouseEvent::CLICK) {
         kernel->requestComponentFocus(this);
         if (evt.getButton() == MouseEvent::LEFT) {
            if (_isDraggable && isFocused()) {
               _isDragging = true;
               _clickDiff = getAbsolutePosition() - evtPosition;
               kernel->lockMouseUse(this);
            }
            menu->closeAllMenus();
         }
         _isHolded = true;
         onMouseClick(evt - currPosition);
      }
   } else { // outside
      if (evt.getState() == MouseEvent::UP || evt.getState() == MouseEvent::CLICK) {
         _isHolded = false;
         _isDragging = false;
         kernel->unlockMouseUse(this);
      } else if (evt.getState() == MouseEvent::MOTION) {
         _isOvered = false;
      } else if (evt.getState() == MouseEvent::HOLD) {
         if (_isDragging && getParentScissor().isInside(evt.getInversePosition()) && isFocused()) {
            setAbsolutePosition(evtPosition + _clickDiff);
            _isHolded = true;
            cursor->setGlutCursor(GLUT_CURSOR_CYCLE);
         } else if (_isDragging) {
            _isHolded = true;
         } else {
            _isHolded = false;
            _isDragging = false;
         }
      }
   }
}

void Component::processKey(const scv::KeyEvent &evt) {
   if (isFocused()) {
      if (evt.getState() == KeyEvent::DOWN) {
         onKeyPressed(evt);
      } else if (evt.getState() == KeyEvent::UP) {
         onKeyUp(evt);
      }
   }
}

bool Component::isInsideSide(Component::Side side, const Point &evtPosition) {
   Point currPosition = getAbsolutePosition();
   switch (side) {
   case left:
      if (evtPosition.x >= currPosition.x - s_mouseBacklash && evtPosition.x <= currPosition.x + s_mouseBacklash
         && evtPosition.y >= currPosition.y - s_mouseBacklash && evtPosition.y <= currPosition.y + s_mouseBacklash + getHeight()) {
            return true;
         }
      break;
   case right:
      if (evtPosition.x >= currPosition.x - s_mouseBacklash + getWidth() && evtPosition.x <= currPosition.x + s_mouseBacklash + getWidth()
         && evtPosition.y >= currPosition.y - s_mouseBacklash && evtPosition.y <= currPosition.y + s_mouseBacklash + getHeight()) {
            return true;
         }
      break;
   case top:
      if (evtPosition.x >= currPosition.x - s_mouseBacklash && evtPosition.x <= currPosition.x + s_mouseBacklash + getWidth()
         && evtPosition.y >= currPosition.y - s_mouseBacklash && evtPosition.y <= currPosition.y + s_mouseBacklash) {
            return true;
         }
      break;
   case bottom:
      if (evtPosition.x >= currPosition.x - s_mouseBacklash && evtPosition.x <= currPosition.x + s_mouseBacklash + getWidth()
         && evtPosition.y >= currPosition.y - s_mouseBacklash + getHeight() && evtPosition.y <= currPosition.y + s_mouseBacklash + getHeight()) {
            return true;
         }
      break;
   }
   return false;    
}

void Component::setCallbacksStatus(bool state) {
   _receivingCallbacks = state;
}

bool Component::getCallbacksStatus(void) const {
   return _receivingCallbacks;
}

Component::ObjectType Component::getType(void) const {
   return _type;
}

void Component::setType(ObjectType type) {
   _type = type;
}

void Component::setParent(Component *parent) {
   if (_parent != NULL) _parent->removeChild(this);

   _parent = parent;

   if (_parent != NULL) _parent->addChild(this);
}

void Component::addChild(Component *object) {
   object->setParent(NULL);

   object->_parent = this;
   _children.push_back(object);
}

void Component::removeChild(Component *object) {
   if (hasChild(object)) {
      object->_parent = NULL;
      _children.remove(object);
   }
}

Component *Component::getChild(int index) {
   if (index < _children.size()) {
      Component::List::iterator iter = _children.begin();
      while(index != 0) {
         ++iter;
         --index;
      }
      return (*iter);
   } else {
      return NULL;
   }
}

void Component::pullChildToTop(Component *child) {
   if (hasChild(child)) {
      _children.remove(child);
      _children.push_back(child);
   }
}

bool Component::hasChild(Component *child) const {
   return std::find(_children.begin(), _children.end(), child) != _children.end();
}

Scissor::Info Component::getScissor(void) const {
   return Scissor::Info(getAbsolutePosition().x, Kernel::getInstance()->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight());
}

Scissor::Info Component::getParentScissor(void) const {
   if (getParent() == NULL) {
      return Scissor::Info();
   } else {
      return getParent()->getScissor();
   }
}

void Component::setResizingCursor(void) {
   static Cursor *cursor = Cursor::getInstance();

   if (_resizing[left] && _resizing[top]) {
      cursor->setGlutCursor(GLUT_CURSOR_TOP_LEFT_CORNER);

   } else if (_resizing[right] && _resizing[top]) {
      cursor->setGlutCursor(GLUT_CURSOR_TOP_RIGHT_CORNER);

   } else if (_resizing[left] && _resizing[bottom]) {
      cursor->setGlutCursor(GLUT_CURSOR_BOTTOM_LEFT_CORNER);

   } else if (_resizing[right] && _resizing[bottom]) {
      cursor->setGlutCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER);

   } else if (_resizing[left] || _resizing[right]) {
      cursor->setGlutCursor(GLUT_CURSOR_LEFT_RIGHT);

   } else if (_resizing[top] || _resizing[bottom]) {
      cursor->setGlutCursor(GLUT_CURSOR_UP_DOWN);
   }
}

Point Component::getMinimumSize(void) const {
   return _minimumSize;
}

Point Component::getPreferredSize(void) const {
   return _preferredSize;
}

Point Component::getMaximumSize(void) const {
   if (_maximumSize.x <= 0 || _maximumSize.y <= 0) {
      scv::Point size;
      if (_maximumSize.x <= 0) {
         size.x = Kernel::getInstance()->getWidth();
      } else {
         size.x = _maximumSize.x;
      }
      if (_maximumSize.y <= 0) {
         size.y = Kernel::getInstance()->getHeight();
      } else {
         size.y = _maximumSize.y;
      }
      return size;
   } else {
      return _maximumSize;
   }
}

void Component::setMinimumSize(const scv::Point &size) {
   if (size <= getPreferredSize() && size <= getMaximumSize() && size > Point(0, 0)) {
      _minimumSize = size;
   }
}

void Component::setPreferredSize(const scv::Point &size) {
   if (size >= getMinimumSize() && size <= getMaximumSize()) {
      _preferredSize = size;
   }
}

void Component::setMaximumSize(const scv::Point &size) {
   if (size >= getMinimumSize() && size >= getPreferredSize() || size.x <= 0 ||  size.y <= 0) {      
      _maximumSize = size;
   }
}

} // namespace scv
