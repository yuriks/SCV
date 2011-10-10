#include "stdafx.h"
#include "Kernel.h"
#include "ScrollPane.h"
#include "data.h"

namespace scv {

ScrollPane::ScrollPane(const scv::Point &p1, const scv::Point &p2, scv::Panel * panel) : ComponentWithTexture(p1, p2), _holdButton(BUT_NONE),
      _translateHeight(0.f), _translateWidth(0.f), _draggingBar(BUT_NONE) {
   _isHResizable = _isVResizable = true;   
   _translateWidth = 0.0f;
   _translateHeight = 0.0f;
   _minSize = Point(60,60);
   _type = SCROLLPANE;

   setPanel(panel);
   createTexture();
}

ScrollPane::~ScrollPane(void) {

}

void ScrollPane::onMouseClick(const scv::MouseEvent &evt) {}
void ScrollPane::onMouseHold(const scv::MouseEvent &evt) {}
void ScrollPane::onMouseOver(const scv::MouseEvent &evt) {}
void ScrollPane::onMouseUp(const scv::MouseEvent &evt) {}
void ScrollPane::onMouseWheel(const scv::MouseEvent &evt) {}

void ScrollPane::onKeyPressed(const scv::KeyEvent &evt) {}
void ScrollPane::onKeyUp(const scv::KeyEvent &evt) {}

void ScrollPane::onSizeChange(void) {}
void ScrollPane::onPositionChange(void) {}

void ScrollPane::setPanel(Panel *panel) {
   if (panel == NULL) return;

   _registeredPanel = panel;

   refreshSCrollPaneSize();
   refreshContainerPosition();
}

void ScrollPane::refreshSCrollPaneSize(void) {
   if (getPanel() == NULL) return;
   
   _containerHeight = getPanel()->getHeight();
   _containerWidth = getPanel()->getWidth();
   
   if (_containerWidth + s_initDesloc > getWidth()) {
      _scrollSizeHorizontal = (getWidth() - s_unnecessaryBorder) * (getWidth()-s_initDesloc)/_containerWidth;
      _maxDeslocWidth = getWidth() - s_unnecessaryBorder - _scrollSizeHorizontal;
   }

   if (_containerHeight + s_initDesloc > getHeight()) {
      _scrollSizeVertical = (getHeight() - s_unnecessaryBorder) * (getHeight()-s_initDesloc)/_containerHeight;
      _maxDeslocHeight = getHeight() - s_unnecessaryBorder - _scrollSizeVertical;
   }
}


void ScrollPane::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = scv::Kernel::getInstance();
   const Point currPosition = getAbsolutePosition();

   
   if ((isFocused() || (getPanel() && getPanel()->isFocused())) && _receivingCallbacks) {
      if (evt.getState() == MouseEvent::WHEELDOWN && kernel->requestMouseUse(this)) {
         _translateHeight = std::min(_translateHeight + pixelToFloat(10, false), 1.f);
         refreshContainerPosition();
      } else if (evt.getState() == MouseEvent::WHELLUP && kernel->requestMouseUse(this)) {
         _translateHeight = std::max(_translateHeight - pixelToFloat(10, false), 0.f);
         refreshContainerPosition();
      }
   }

   
   if (getPanel() != NULL) {
      Scissor::Info scissor(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y - s_border - 1), getWidth() - s_border - 1, getHeight() - s_border - 1);
      if ((scissor.isInside(evt.getInversePosition()) && _draggingBar == BUT_NONE) || getPanel()->isResizing()) {
         getPanel()->setDraggable(false);
         getPanel()->processMouse(evt);
         refreshSCrollPaneSize();
      }
   }
   
   Component::processMouse(evt);

   
   if (isDragging())
      refreshContainerPosition();

   if  (isResizing()) {
      /*
      if (getWidth() >= _containerWidth + s_initDesloc)
         setWidth(_containerWidth + s_initDesloc);
      if (getHeight() >= _containerHeight + s_initDesloc)
         setHeight(_containerHeight + s_initDesloc);
      */
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

void ScrollPane::refreshContainerPosition(void) {
   if (getPanel() == NULL) return;

   _minContainerPos.x = getAbsolutePosition().x + getWidth() - s_border - _containerWidth;
   _minContainerPos.y = getAbsolutePosition().y + getHeight() - s_border - _containerHeight;

   getPanel()->setAbsolutePosition(Point(getAbsolutePosition().x - (int)(_translateWidth * (getAbsolutePosition().x - _minContainerPos.x)), getAbsolutePosition().y - (int)(_translateHeight * (getAbsolutePosition().y - _minContainerPos.y))));
}

void ScrollPane::processKey(const scv::KeyEvent &evt) {
   if(getPanel() != NULL)
      getPanel()->processKey(evt);
}

void ScrollPane::display(void) {
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

   /************************************************************************/
   /* VERTICAL SCROLL                                                      */
   /************************************************************************/
   scheme->applyDefaultModulate();
   _cTexture->display(currPositionV.x, currPositionV.y,   3, 15, getHeight() - 1);
   if (_containerHeight + s_initDesloc > getHeight()) {

      scheme->applyColor(ColorScheme::scrollPanel);

      // up button arrow
      _cTexture->display(currPositionV.x, currPositionV.y,  0, 15, 16);

      if (_overButton == BUT_UP) {
         if (_holdButton)
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1, 5, 13, s_initDesloc - 2);
         else
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1, 4, 13, s_initDesloc - 2);
      }

      // down button arrow
      _cTexture->display(currPositionV.x, currPositionV.y + getHeight() - s_initDesloc, 0, 15, -16);

      if (_overButton == BUT_DOWN) {
         if (_holdButton)
            _cTexture->display(currPositionV.x + 1, currPositionV.y + getHeight() - s_initDesloc * 2 + 1, 5, 13, s_initDesloc - 2);
         else
            _cTexture->display(currPositionV.x + 1, currPositionV.y + getHeight() - s_initDesloc * 2 + 1, 4, 13, s_initDesloc - 2);
      }

      // scroll
      scheme->applyColor(ColorScheme::scrollPanel);
      currPositionV.y += s_initDesloc - 1;
      _cTexture->display(currPositionV.x, currPositionV.y + (int)(_translateHeight * (float)_maxDeslocHeight), 1, 15, 2);
      _cTexture->display(currPositionV.x, currPositionV.y + 2 + (int)(_translateHeight * (float)_maxDeslocHeight), 2, 15, _scrollSizeVertical);
      _cTexture->display(currPositionV.x, currPositionV.y + 3 + _scrollSizeVertical + (int)(_translateHeight * (float)_maxDeslocHeight), 1, 15, -2);

      if (_overButton == BUT_VERT) {
         if (_holdButton)
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1 + (int)(_translateHeight * (float)_maxDeslocHeight), 5, 13, _scrollSizeVertical + 1);
         else
            _cTexture->display(currPositionV.x + 1, currPositionV.y + 1 + (int)(_translateHeight * (float)_maxDeslocHeight), 4, 13, _scrollSizeVertical + 1);
      }

   }

   /************************************************************************/
   /* HORIZONTAL SCROLL                                                    */
   /************************************************************************/

   scheme->applyDefaultModulate();
   _cTexture->display(currPositionH.x, currPositionH.y, 3, getWidth() - 1, 15);
   if (_containerWidth + s_initDesloc > getWidth() ) {

      // left button arrow
      scheme->applyColor(ColorScheme::scrollPanel);
      _cTexture->display(currPositionH.x, currPositionH.y,  6, 16, 15);

      if (_overButton == BUT_LEFT) {
         if (_holdButton)
            _cTexture->display(currPositionH.x + 1, currPositionH.y + 1, 5, s_initDesloc - 2, 13);
         else
            _cTexture->display(currPositionH.x + 1, currPositionH.y + 1, 4, s_initDesloc - 2, 13);
      }

      // right button arrow
      scheme->applyColor(ColorScheme::scrollPanel);
      _cTexture->display(currPositionH.x + getWidth() - s_initDesloc, currPositionH.y,  6, -16, 15);

      if (_overButton == BUT_RIGHT) {
         if (_holdButton)
            _cTexture->display(currPositionH.x + getWidth() - s_initDesloc * 2 + 1, currPositionH.y + 1, 5, s_initDesloc - 2, 13);
         else
            _cTexture->display(currPositionH.x + getWidth() - s_initDesloc * 2 + 1, currPositionH.y + 1, 4, s_initDesloc - 2, 13);
      }

      //scroll
      scheme->applyColor(ColorScheme::scrollPanel);
      currPositionH.x += s_initDesloc - 1;
      _cTexture->display(currPositionH.x + (int)(_translateWidth * (float)_maxDeslocWidth), currPositionH.y, 7, 2, 15);
      _cTexture->display(currPositionH.x + 2 + + (int)(_translateWidth * (float)_maxDeslocWidth), currPositionH.y, 8, _scrollSizeHorizontal, 15);
      _cTexture->display(currPositionH.x + 3 + _scrollSizeHorizontal + (int)(_translateWidth * (float)_maxDeslocWidth), currPositionH.y, 7, -2, 15);

      if (_overButton == BUT_HORZ) {
         if (_holdButton)
            _cTexture->display(currPositionH.x + (int)(_translateWidth * (float)_maxDeslocWidth) + 1, currPositionH.y + 1, 5, _scrollSizeHorizontal + 2, 13);
         else
            _cTexture->display(currPositionH.x + (int)(_translateWidth * (float)_maxDeslocWidth) + 1, currPositionH.y + 1, 4, _scrollSizeHorizontal + 2, 13);
      }
   }

   _cTexture->disable();

   /************************************************************************/
   /* PANEL                                                                */
   /************************************************************************/
   if(getPanel() != NULL) {
      Scissor::Info scissorInfo(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y - s_border), getWidth() - s_border, getHeight() - s_border);
      scissor->pushScissor(scissorInfo);
      getPanel()->display();
      scissor->popScissor();
   }
}

bool ScrollPane::isOnLeftButton(Point p) {
   return (p > getAbsolutePosition() + Point(0, getHeight() - 17) && p < getAbsolutePosition() + Point(s_initDesloc - 1, getHeight()));
}

bool ScrollPane::isOnRightButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc * 2, getHeight() - 17) && p < getAbsolutePosition() + Point(getWidth() - s_initDesloc, getHeight()));
}

bool ScrollPane::isOnUpButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, -1) && p < getAbsolutePosition() + Point(getWidth()-1, s_initDesloc-1));
}

bool ScrollPane::isOnBottomButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, getHeight() - s_initDesloc * 2) && p < getAbsolutePosition() + Point(getWidth()-1, getHeight() - s_initDesloc));
}

bool ScrollPane::isOnVertButton(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, s_initDesloc - 1 + (int)(_translateHeight * (float)_maxDeslocHeight)) && p < getAbsolutePosition() + Point(getWidth() - 1, s_initDesloc - 1 + (int)(_translateHeight * (float)_maxDeslocHeight) + _scrollSizeVertical + 2));
}

bool ScrollPane::isOnHorzButton(Point p) {
   return (p > getAbsolutePosition() + Point(s_initDesloc - 1 + (int)(_translateWidth * (float)_maxDeslocWidth), getHeight() - (s_initDesloc - 1)) && p < getAbsolutePosition() + Point(s_initDesloc + (int)(_translateWidth * (float)_maxDeslocWidth) + _scrollSizeHorizontal + 1, getHeight()));
}

bool ScrollPane::isOnVertBar(Point p) {
   return (p > getAbsolutePosition() + Point(getWidth() - s_initDesloc, s_initDesloc - 1) && p < getAbsolutePosition() + Point(getWidth() - 1, getHeight() - (2*s_initDesloc) - 2));
}

bool ScrollPane::isOnHorzBar(Point p) {
   return (p > getAbsolutePosition() + Point(s_initDesloc, getHeight() - (s_initDesloc - 1)) && p < getAbsolutePosition() + Point(getWidth() - (2*s_initDesloc), getHeight()));
}

float ScrollPane::pixelToFloat(int pix, bool horz) {
   unsigned int tam = (horz ? (_containerWidth - (getWidth() - s_border)) : (_containerHeight - (getHeight() - s_border)));
   return (float)pix / (float)tam;
}

float ScrollPane::barPixelToFloat(int pix, bool horz) {
   unsigned int tam = (horz ? getWidth() - _scrollSizeHorizontal : getHeight() - _scrollSizeVertical) - (s_initDesloc * 3);
   return (float)pix / (float)tam;
}

void ScrollPane::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(Kernel::scrollPanel)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(19, 39);
   kernel->setWidgetTexture(Kernel::scrollPanel, _cTexture);

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

void ScrollPane::setWidth(const int width) {
   Component::setWidth(width);
   refreshSCrollPaneSize();
}

void ScrollPane::setHeight(const int height) {
   Component::setHeight(height);
   refreshSCrollPaneSize();
}

} // namespace scv