#include "stdafx.h"
#include "Kernel.h"
#include "ScrollComponent.h"
#include "data.h"

namespace scv {

ScrollComponent::ScrollComponent(const scv::Point &p1, const scv::Point &p2, scv::Component *object) : ComponentWithTexture(p1, p2),
      _holdButton(BUT_NONE), _draggingBar(BUT_NONE) {

   _isHResizable = _isVResizable = true;
   _translateWidth = 0.0f;
   _translateHeight = 0.0f;
   _minimumSize = Point(60,60);
   _type = SCROLLCOMPONENT;

   setComponent(object);

   createTexture();
}

ScrollComponent::~ScrollComponent(void) {

}

void ScrollComponent::onMouseClick(const scv::MouseEvent &evt) {
}
void ScrollComponent::onMouseHold(const scv::MouseEvent &evt) {
}
void ScrollComponent::onMouseOver(const scv::MouseEvent &evt) {
}
void ScrollComponent::onMouseUp(const scv::MouseEvent &evt) {
}
void ScrollComponent::onMouseWheel(const scv::MouseEvent &evt) {
}

void ScrollComponent::onKeyPressed(const scv::KeyEvent &evt) {
}
void ScrollComponent::onKeyUp(const scv::KeyEvent &evt) {
}

void ScrollComponent::onSizeChange(void) {
}
void ScrollComponent::onPositionChange(void) {
}

void ScrollComponent::setComponent(scv::Component *object) {
   if (object == this) return;

   if (_registeredComponent != NULL) {
      removeChild(_registeredComponent);
   }
   
   _registeredComponent = object;
   addChild(_registeredComponent);

   refreshSCrollPaneSize();
   refreshContainerPosition();
}

void ScrollComponent::refreshSCrollPaneSize(void) {
   if (getComponent() == NULL) return;
   
   _containerHeight = getComponent()->getHeight();
   _containerWidth = getComponent()->getWidth();
   
   if (_containerWidth + s_initDesloc > getWidth()) {
      _scrollSizeHorizontal = (getWidth() - s_unnecessaryBorder) * (getWidth()-s_initDesloc)/_containerWidth;
      _maxDeslocWidth = getWidth() - s_unnecessaryBorder - _scrollSizeHorizontal;
   }

   if (_containerHeight + s_initDesloc > getHeight()) {
      _scrollSizeVertical = (getHeight() - s_unnecessaryBorder) * (getHeight()-s_initDesloc)/_containerHeight;
      _maxDeslocHeight = getHeight() - s_unnecessaryBorder - _scrollSizeVertical;
   }
}


void ScrollComponent::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = scv::Kernel::getInstance();
   const Point currPosition = getAbsolutePosition();
      
   if ((isFocused() || (getComponent() && getComponent()->isFocused())) && _receivingCallbacks) {
      if (evt.getState() == MouseEvent::WHEELDOWN && kernel->requestMouseUse(this)) {
         _translateHeight = std::min(_translateHeight + pixelToFloat(10, false), 1.f);
         refreshContainerPosition();
      } else if (evt.getState() == MouseEvent::WHELLUP && kernel->requestMouseUse(this)) {
         _translateHeight = std::max(_translateHeight - pixelToFloat(10, false), 0.f);
         refreshContainerPosition();
      }
   }
      
   if (getComponent() != NULL) {
      Scissor::Info scissor(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y - s_border - 1), getWidth() - s_border - 1, getHeight() - s_border - 1);
      if ((scissor.isInside(evt.getInversePosition()) && _draggingBar == BUT_NONE) || getComponent()->isResizing()) {
         getComponent()->setDraggable(false);
         getComponent()->processMouse(evt);
         refreshSCrollPaneSize();
      }
   }
   
   Component::processMouse(evt);
      
   if  (isResizing()) {
      refreshContainerPosition();
      refreshSCrollPaneSize();
   }

   _holdButton = ((evt.getState() == MouseEvent::CLICK || evt.getState() == MouseEvent::HOLD) && evt.getButton() == MouseEvent::LEFT);

   if (!_holdButton) {
      _draggingBar = BUT_NONE;

      if (isOnLeftButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
         _overButton = BUT_LEFT;
      } else if (isOnRightButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
         _overButton = BUT_RIGHT;
      } else if (isOnUpButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
         _overButton = BUT_UP;
      } else if (isOnBottomButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
         _overButton = BUT_DOWN;
      } else if (isOnVertBar(evt.getPosition()) && kernel->requestMouseUse(this)) {
         if (isOnVertButton(evt.getPosition())) {
            _draggingBar = _overButton = BUT_VERT;
            _dragBarOffset = (evt.getPosition() - getAbsolutePosition()).y - s_initDesloc - (int)(_translateHeight * (float)_maxDeslocHeight);
         } else {
            if (evt.getPosition().y - getAbsolutePosition().y <= s_initDesloc - 1 + (int)(_translateHeight * (float)_maxDeslocHeight)) {
               _overButton = BUT_PAGEUP;
            } else {
               _overButton = BUT_PAGEDOWN;
            }
         }
      } else if (isOnHorzBar(evt.getPosition()) && kernel->requestMouseUse(this)) {
         if (isOnHorzButton(evt.getPosition())) {
            _draggingBar = _overButton = BUT_HORZ;
            _dragBarOffset = (evt.getPosition() - getAbsolutePosition()).x - s_initDesloc - (int)(_translateWidth * (float)_maxDeslocWidth);
         } else {
            if (evt.getPosition().x - getAbsolutePosition().x <= s_initDesloc - 1 + (int)(_translateWidth * (float)_maxDeslocWidth)) {
               _overButton = BUT_PAGELEFT;
            } else {
               _overButton = BUT_PAGERIGHT;
            }
         }
      } else {
         _overButton = BUT_NONE;
         _draggingBar = BUT_NONE;
      }
   }

   // handling of dragging
   if (_draggingBar != BUT_NONE) {
      if (kernel->requestMouseUse(this)) {
         if (evt.getState() == MouseEvent::HOLD) {
            if (_draggingBar == BUT_HORZ) {
               int x = (evt.getPosition() - getAbsolutePosition()).x - s_initDesloc - _dragBarOffset;
               _translateWidth = std::max(0.f, std::min(barPixelToFloat(x, true), 1.f));
            } else if (_draggingBar == BUT_VERT) {
               int y = (evt.getPosition() - getAbsolutePosition()).y - s_initDesloc - _dragBarOffset;
               _translateHeight = std::max(0.f, std::min(barPixelToFloat(y, false), 1.f));
            }

            refreshContainerPosition();

         } else if (evt.getState() == MouseEvent::UP) {
            _draggingBar = BUT_NONE;
         }
         _overButton = _draggingBar;
         _holdButton = true;
      }
   }

   if (_holdButton && evt.getState() == MouseEvent::CLICK) {
      switch (_overButton) {
      case BUT_UP:
         _translateHeight = std::max(_translateHeight - pixelToFloat(10, false), 0.f);
         break;
      case BUT_DOWN:
         _translateHeight = std::min(_translateHeight + pixelToFloat(10, false), 1.f);
         break;
      case BUT_LEFT:
         _translateWidth = std::max(_translateWidth - pixelToFloat(10, true), 0.f);
         break;
      case BUT_RIGHT:
         _translateWidth = std::min(_translateWidth + pixelToFloat(10, true), 1.f);
         break;
      case BUT_PAGEUP:
         _translateHeight = std::max(_translateHeight - pixelToFloat(getHeight() - s_border - 1, false), 0.f);
         break;
      case BUT_PAGEDOWN:
         _translateHeight = std::min(_translateHeight + pixelToFloat(getHeight() - s_border - 1, false), 1.f);
         break;
      case BUT_PAGELEFT:
         _translateWidth = std::max(_translateWidth - pixelToFloat(getWidth() - s_border - 1, true), 0.f);
         break;
      case BUT_PAGERIGHT:
         _translateWidth = std::min(_translateWidth + pixelToFloat(getWidth() - s_border - 1, true), 1.f);
         break;
      }
      refreshContainerPosition();
   }
}

void ScrollComponent::refreshContainerPosition(void) {
   if (getComponent() == NULL) return;

   if (!getComponent()->isResizing()) {
      _minContainerPos.x = getAbsolutePosition().x + getWidth() - s_border - _containerWidth;
      _minContainerPos.y = getAbsolutePosition().y + getHeight() - s_border - _containerHeight;

      int x = static_cast<int>(_translateWidth * (getAbsolutePosition().x - _minContainerPos.x));
      int y = static_cast<int>(_translateHeight * (getAbsolutePosition().y - _minContainerPos.y));

      if (x < 0) x = 0;
      if (y < 0) y = 0;

      getComponent()->setRelativePosition(Point(- x, - y));
   }
}

void ScrollComponent::processKey(const scv::KeyEvent &evt) {
   if (getComponent() != NULL)
      getComponent()->processKey(evt);
}

void ScrollComponent::display(void) {
   static ColorScheme *scheme = ColorScheme::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static Kernel *kernel = Kernel::getInstance();

   if (_cTexture == NULL) return;

   refreshContainerPosition();
   refreshSCrollPaneSize();

   Point currPositionV = getAbsolutePosition() + Point(getWidth() - 15, 0);
   Point currPositionH = getAbsolutePosition() + Point(0, getHeight() - 15);
   const Point currPosition = getAbsolutePosition();

   _cTexture->enable();

   scissor->pushScissor(getScissor());

   // VERTICAL
   ///////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////
   scheme->applyDefaultModulate();
   _cTexture->display(currPositionV.x, currPositionV.y,   3, 15, getHeight() - 1);
   
   scheme->applyColor(ColorScheme::SCROLLPANEL);

   // up button arrow
   _cTexture->display(currPositionV.x, currPositionV.y,  0, 15, 16);
   // down button arrow
   _cTexture->display(currPositionV.x, currPositionV.y + getHeight() - s_initDesloc, 0, 15, -16);

   if (_containerHeight + s_initDesloc > getHeight()) {
      if (_overButton == BUT_UP) {
         if (_holdButton) {
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1, 5, 13, s_initDesloc - 2);
         } else {
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1, 4, 13, s_initDesloc - 2);
         }
      } else if (_overButton == BUT_DOWN) {
         if (_holdButton) {
            _cTexture->display(currPositionV.x + 1, currPositionV.y + getHeight() - s_initDesloc * 2 + 1, 5, 13, s_initDesloc - 2);
         } else {
            _cTexture->display(currPositionV.x + 1, currPositionV.y + getHeight() - s_initDesloc * 2 + 1, 4, 13, s_initDesloc - 2);
         }
      }

      // scroll
      scheme->applyColor(ColorScheme::SCROLLPANEL);
      currPositionV.y += s_initDesloc - 1;
      _cTexture->display(currPositionV.x, currPositionV.y + (int)(_translateHeight * (float)_maxDeslocHeight), 1, 15, 2);
      _cTexture->display(currPositionV.x, currPositionV.y + 2 + (int)(_translateHeight * (float)_maxDeslocHeight), 2, 15, _scrollSizeVertical);
      _cTexture->display(currPositionV.x, currPositionV.y + 3 + _scrollSizeVertical + (int)(_translateHeight * (float)_maxDeslocHeight), 1, 15, -2);

      if (_overButton == BUT_VERT) {
         if (_holdButton) {
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1 + (int)(_translateHeight * (float)_maxDeslocHeight), 5, 13, _scrollSizeVertical + 1);
         } else {
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1 + (int)(_translateHeight * (float)_maxDeslocHeight), 4, 13, _scrollSizeVertical + 1);
         }
      }
   }

   // HORIZONTAL
   ///////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////
   scheme->applyDefaultModulate();
   _cTexture->display(currPositionH.x, currPositionH.y, 3, getWidth() - 1, 15);
   
   scheme->applyColor(ColorScheme::SCROLLPANEL);

   // left button arrow   
   _cTexture->display(currPositionH.x, currPositionH.y,  6, 16, 15);
   // right button arrow
   _cTexture->display(currPositionH.x + getWidth() - s_initDesloc, currPositionH.y,  6, -16, 15);

   if (_containerWidth + s_initDesloc > getWidth()) {
      if (_overButton == BUT_RIGHT) {
         if (_holdButton) {
            _cTexture->display(currPositionH.x + getWidth() - s_initDesloc * 2 + 1, currPositionH.y + 1, 5, s_initDesloc - 2, 13);
         } else {
            _cTexture->display(currPositionH.x + getWidth() - s_initDesloc * 2 + 1, currPositionH.y + 1, 4, s_initDesloc - 2, 13);
         }
      } else if (_overButton == BUT_LEFT) {
         if (_holdButton) {
            _cTexture->display(currPositionH.x + 1, currPositionH.y + 1, 5, s_initDesloc - 2, 13);
         } else {
            _cTexture->display(currPositionH.x + 1, currPositionH.y + 1, 4, s_initDesloc - 2, 13);
         }
      }

      //scroll
      scheme->applyColor(ColorScheme::SCROLLPANEL);
      currPositionH.x += s_initDesloc - 1;
      _cTexture->display(currPositionH.x + (int)(_translateWidth * (float)_maxDeslocWidth), currPositionH.y, 7, 2, 15);
      _cTexture->display(currPositionH.x + 2 + + (int)(_translateWidth * (float)_maxDeslocWidth), currPositionH.y, 8, _scrollSizeHorizontal, 15);
      _cTexture->display(currPositionH.x + 3 + _scrollSizeHorizontal + (int)(_translateWidth * (float)_maxDeslocWidth), currPositionH.y, 7, -2, 15);

      if (_overButton == BUT_HORZ) {
         if (_holdButton) {
            _cTexture->display(currPositionH.x + (int)(_translateWidth * (float)_maxDeslocWidth) + 1, currPositionH.y + 1, 5, _scrollSizeHorizontal + 2, 13);
         } else {
            _cTexture->display(currPositionH.x + (int)(_translateWidth * (float)_maxDeslocWidth) + 1, currPositionH.y + 1, 4, _scrollSizeHorizontal + 2, 13);
         }
      }
   }

   _cTexture->disable();

   /************************************************************************/
   /* PANEL                                                                */
   /************************************************************************/
   if(getComponent() != NULL) {
      scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y - s_border), getWidth() - s_border, getHeight() - s_border));
      getComponent()->display();
      scissor->popScissor();
   }
   scissor->popScissor();
}

bool ScrollComponent::isOnLeftButton(Point p) {
   return (p > getAbsolutePosition() + Point(0, getHeight() - 17) && p < getAbsolutePosition() + Point(s_initDesloc - 1, getHeight()));
}

bool ScrollComponent::isOnRightButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc * 2, getHeight() - 17) && p < getAbsolutePosition() + Point(getWidth() - s_initDesloc, getHeight()));
}

bool ScrollComponent::isOnUpButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, -1) && p < getAbsolutePosition() + Point(getWidth()-1, s_initDesloc-1));
}

bool ScrollComponent::isOnBottomButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, getHeight() - s_initDesloc * 2) && p < getAbsolutePosition() + Point(getWidth()-1, getHeight() - s_initDesloc));
}

bool ScrollComponent::isOnVertButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, s_initDesloc - 1 + (int)(_translateHeight * (float)_maxDeslocHeight)) && p < getAbsolutePosition() + Point(getWidth() - 1, s_initDesloc - 1 + (int)(_translateHeight * (float)_maxDeslocHeight) + _scrollSizeVertical + 2));
}

bool ScrollComponent::isOnHorzButton(Point p) {
   return (p > getAbsolutePosition() + Point(s_initDesloc - 1 + (int)(_translateWidth * (float)_maxDeslocWidth), getHeight() - (s_initDesloc - 1)) && p < getAbsolutePosition() + Point(s_initDesloc + (int)(_translateWidth * (float)_maxDeslocWidth) + _scrollSizeHorizontal + 1, getHeight()));
}

bool ScrollComponent::isOnVertBar(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, s_initDesloc - 1) && p < getAbsolutePosition() + Point(getWidth() - 1, getHeight() - (2*s_initDesloc) - 2));
}

bool ScrollComponent::isOnHorzBar(Point p) {
   return (p > getAbsolutePosition() + Point(s_initDesloc, getHeight() - (s_initDesloc - 1)) && p < getAbsolutePosition() + Point(getWidth() - (2*s_initDesloc), getHeight()));
}

float ScrollComponent::pixelToFloat(int pix, bool horz) {
   unsigned int tam = (horz ? (_containerWidth - (getWidth() - s_border)) : (_containerHeight - (getHeight() - s_border)));
   return (float)pix / (float)tam;
}

float ScrollComponent::barPixelToFloat(int pix, bool horz) {
   unsigned int tam = (horz ? getWidth() - _scrollSizeHorizontal : getHeight() - _scrollSizeVertical) - (s_initDesloc * 3);
   return (float)pix / (float)tam;
}

void ScrollComponent::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(SCROLLCOMPONENT)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(19, 39);
   kernel->setWidgetTexture(SCROLLCOMPONENT, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   _cTexture->addTexture(Point(0, 0), 15, 16, data::ScrollPaneVerticalButton); // 0
   _cTexture->addTexture(Point(0, 16), 15, 2, data::ScrollPaneVerticalUp); // 1
   _cTexture->addTexture(Point(0, 18), 15, 1, data::ScrollPaneVerticalMiddle); // 2

   //background
   _cTexture->addTexture(Point(0, 19), ColorRGBA(150,150,150,255)); // 3

   //over
   _cTexture->addTexture(Point(1, 19), ColorRGBA(120,120,120,120)); // 4

   //click
   _cTexture->addTexture(Point(2, 19), ColorRGBA(80,80,80,120)); // 5

   _cTexture->addTexture(Point(0, 20), 16, 15, data::ScrollPaneHorizontalButton); // 6
   _cTexture->addTexture(Point(16, 0), 2, 15,  data::ScrollPaneHorizontalUp); // 7
   _cTexture->addTexture(Point(18, 0), 1, 15,  data::ScrollPaneHorizontalMiddle); // 8

   _cTexture->createTexture();

}

void ScrollComponent::setWidth(const int width) {
   Component::setWidth(width);
   refreshSCrollPaneSize();
}

void ScrollComponent::setHeight(const int height) {
   Component::setHeight(height);
   refreshSCrollPaneSize();
}

} // namespace scv