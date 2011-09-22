#include "stdafx.h"
#include "InternalFrame.h"
#include "ColorRGBA.h"
#include "MatrixTemplate.h"
#include "Kernel.h"

#include "FontTahoma.h"
#include "data.h"

namespace scv {

const int InternalFrame::s_borderTop   = 30;
const int InternalFrame::s_borderWidth = 10;

const int InternalFrame::s_closeWidth  = 46;
const int InternalFrame::s_closeHeight = 19;

InternalFrame::InternalFrame(GLsizei width, GLsizei height, const std::string &title) :
      ComponentWithTexture(Point(0, 0), Point(width + s_borderWidth * 2, height + s_borderWidth + s_borderTop)) {
   setDraggable(true);
   setResizable(true);

   _title = title;

   _refreshPosition = true;

   _overClose = _clickClose = false;

   _panel = new Panel(Point(s_borderWidth, s_borderTop), Point(s_borderWidth + width, s_borderTop + height));

   _panel->setDraggable(false);
   _panel->setResizable(false);

   _minSize = Point(60,45);

   _type = window;
}

InternalFrame::~InternalFrame(void) {
   delete _panel;
}

void InternalFrame::onMouseClick(const scv::MouseEvent &evt) {/**/}
void InternalFrame::onMouseHold(const scv::MouseEvent &evt) {/**/}
void InternalFrame::onMouseOver(const scv::MouseEvent &evt) {/**/}
void InternalFrame::onMouseUp(const scv::MouseEvent &evt) {/**/}
void InternalFrame::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void InternalFrame::onKeyUp(const scv::KeyEvent &evt) {/**/}
void InternalFrame::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void InternalFrame::onResizing(void) {/**/}
void InternalFrame::onDragging(void) {/**/}
void InternalFrame::onClose(void) {/**/}


void InternalFrame::setTitle(const std::string &title) {
   _title = title;
}

void InternalFrame::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();

   if (_isVisible == false) return;

   _panel->processMouse(evt);

   Point evtPosition  = evt.getPosition();
   _overClose = false;

   Component::processMouse(evt);

   if (_panel->isFocused() == false) {
      if (isOnCloseButton(evtPosition)) _isDragging = false;
      Point currPosition = getAbsolutePosition();

      if (isDragging() && !evt.doubleClick()) {
         if (_rolluped == true && !isOnTopBar(evtPosition)) {
            _isDragging = false;
         }
         _panel->setRelativePosition(Point(currPosition.x + s_borderWidth, currPosition.y + s_borderTop));

      } else if (isResizing()) {
         _panel->setRelativePosition(Point(currPosition.x + s_borderWidth, currPosition.y + s_borderTop));
         _panel->setWidth(getWidth() - 2 * s_borderWidth);
         _panel->setHeight(getHeight() - s_borderWidth - s_borderTop);
      } else {
         if (isOnTopBar(evtPosition) && kernel->requestMouseUse(this)) {
            if (isOnCloseButton(evtPosition)) {
               _overClose = true;
               if (evt.getState() == MouseEvent::click) {
                  _clickClose = true;
               }
            } else {
               _overClose = false;
               if (evt.getState() == MouseEvent::click) {
                  _isDragging = true;
                  //HACK
                  //_clicked = (evtPosition - currPosition) + _cTranslate;
                  kernel->requestComponentFocus(this);
               }
            }
         }
      }
   }

   if (evt.getState() == MouseEvent::up) {
      if (_clickClose && _overClose) {
         onClose();
         _isVisible = false;
      } else {
         _clickClose = false;
      }
   }
}

void InternalFrame::processKey(const scv::KeyEvent &evt) {
   if (_isVisible == false) return;

   _panel->processKey(evt);
   Component::processKey(evt);
}

void InternalFrame::display(void) {
   static ColorScheme *scheme = ColorScheme::getInstance();
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();

   if (_isVisible == false || _cTexture == NULL) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
   _cTexture->display(currPosition.x + 2,currPosition.y + 2, 7, getWidth() - 4, getHeight() - 4);

   // border top
   _cTexture->display(currPosition.x + 5             , currPosition.y + 1, 7, getWidth() - 10, 1);
   // border down
   _cTexture->display(currPosition.x + 5             , currPosition.y + getHeight() - 2, 7, getWidth() - 10, 1);
   // border right
   _cTexture->display(currPosition.x + getWidth() - 2, currPosition.y + 5, 7, 1, getHeight() - 10);
   // border left
   _cTexture->display(currPosition.x + 1             , currPosition.y + 5, 7, 1, getHeight() - 10);

   scheme->applyDefaultModulate();
   // border top
   _cTexture->display(currPosition.x + 5             , currPosition.y, 8 , getWidth() - 10, 1);
   // border down
   _cTexture->display(currPosition.x + 5             , currPosition.y + getHeight() - 1, 8, getWidth() - 10, 1);
   // border right
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 5, 8, 1, getHeight() - 10);
   // border left
   _cTexture->display(currPosition.x                 , currPosition.y + 5, 8, 1, getHeight() - 10);

   // cantos
   _cTexture->display(currPosition.x + getWidth() - 5, currPosition.y, 3, 5, 5);
   _cTexture->display(currPosition.x                 , currPosition.y, 4, 5, 5);
   _cTexture->display(currPosition.x + getWidth() - 5, currPosition.y + getHeight() - 5, 5, 5, 5);
   _cTexture->display(currPosition.x                 , currPosition.y + getHeight() - 5, 6, 5, 5);

   scheme->applyDefaultModulate();
   if (_clickClose && _overClose) {
      _cTexture->display(currPosition.x + getWidth() - s_closeWidth - 5, currPosition.y, 2, 46,19);
   } else if (_overClose) {
      _cTexture->display(currPosition.x + getWidth() - s_closeWidth - 5, currPosition.y, 1, 46,19);
   } else if (_clickClose) {
      _cTexture->display(currPosition.x + getWidth() - s_closeWidth - 5, currPosition.y, 1, 46,19);
   } else {
      _cTexture->display(currPosition.x + getWidth() - s_closeWidth - 5, currPosition.y, 0, 46,19);
   }
   _cTexture->disable();

   _panel->display();

   scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (currPosition.y) - s_borderTop, getWidth() - s_closeWidth - 10, s_borderTop));
   Label::display(currPosition.x + s_borderWidth, currPosition.y + (s_borderTop - font->getHeight()) / 2 + 2, _title);
   scissor->popScissor();
}

bool InternalFrame::isOnTopBar(const Point &p) {
   return (p.y >= getAbsolutePosition().y && p.y <= getAbsolutePosition().y + s_borderTop &&
      p.x >= getAbsolutePosition().x && p.x <= getAbsolutePosition().x + getWidth())? true : false;
}

bool InternalFrame::isOnCloseButton(const Point &p) {
   return (p.y >= getAbsolutePosition().y && p.y <= getAbsolutePosition().y + s_closeHeight &&
      p.x >= getAbsolutePosition().x + getWidth() - s_closeWidth - 5 && p.x <= getAbsolutePosition().x + getWidth() - 5)? true : false;
}

void InternalFrame::addChild(Component *object) {
   _panel->addChild(object);
}

void InternalFrame::setRelativePosition(const Point &position) {
   ComponentWithTexture::setRelativePosition(position);
   Point currPosition = getAbsolutePosition();
   _panel->setRelativePosition(Point(currPosition.x + s_borderWidth, currPosition.y + s_borderTop));
}

void InternalFrame::createTexture(void) {
   static Kernel *kernel = Kernel::getInstance();

   if ((_cTexture = kernel->getWidgetTexture(Kernel::window)) != NULL) return;

   _cTexture = new ComponentTexture(46 * 3 + 10, 19);
   kernel->setWidgetTexture(Kernel::window, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   _cTexture->addTexture(Point(0,      0), 46, 19, data::InternalFrameCloseButton);       // 0
   _cTexture->addTexture(Point(46*1,   0), 46, 19, data::InternalFrameCloseButtonHover); // 1
   _cTexture->addTexture(Point(46*2,   0), 46, 19, data::InternalFrameCloseButtonPressed); // 2
   _cTexture->addTexture(Point(46*3,   0), 5,  5,  data::InternalFrameBorderRightUp);      // 3
   _cTexture->addTexture(Point(46*3,   5), 5,  5,  data::InternalFrameBorderLeftUp);       // 4
   _cTexture->addTexture(Point(46*3+5, 0), 5,  5,  data::InternalFrameBorderRightDown);    // 5
   _cTexture->addTexture(Point(46*3+5, 5), 5,  5,  data::InternalFrameBorderLeftDown);     // 6

   MatrixTemplate<ColorRGBA> _boardTexture(1, 1, ColorRGBA(210,210,210,200));
   _cTexture->addTexture(Point(46*3, 5*2), _boardTexture); // 7

   MatrixTemplate<ColorRGBA> _borderTexture(1, 1, ColorRGBA(59,59,59,240));
   _cTexture->addTexture(Point(46*3, 5*2+1), _borderTexture); // 8

   _cTexture->createTexture();
}

std::string InternalFrame::getTitle(void) {
   return _title;
}

Panel * InternalFrame::getPanel(void) {
   return _panel;
}

} // namespace scv
