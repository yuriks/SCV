#include "stdafx.h"
#include "InternalFrame.h"
#include "ColorRGBA.h"
#include "MatrixTemplate.h"
#include "Kernel.h"
#include "StaticLabel.h"

#include "FontTahoma.h"
#include "data.h"

namespace scv {

const int InternalFrame::s_borderTop   = 30;
const int InternalFrame::s_borderWidth = 10;

const int InternalFrame::s_closeWidth  = 46;
const int InternalFrame::s_closeHeight = 19;

InternalFrame::InternalFrame(GLsizei width, GLsizei height, const std::string &title) :
      Component(Point(0, 0), Point(width + s_borderWidth * 2, height + s_borderWidth + s_borderTop)) {

   _panel = NULL;
   setDraggable(true);
   setResizable(true);

   _title = title;

   _refreshPosition = true;

   _overClose = _clickClose = false;

   setPanel(new Panel(Point(s_borderWidth, s_borderTop), Point(s_borderWidth + width, s_borderTop + height)));
   
   _panel->setDraggable(false);
   _panel->setResizable(false);

   _minimumSize = Point(60,45);

   _type = WINDOW;

   createTexture();
}

void InternalFrame::onOpen(void) {
}

void InternalFrame::onClose(void) {
}

Point InternalFrame::getInternalSize() const{
   Point p;
   p.x = getWidth() - 2*s_borderWidth;
   p.y = getHeight() - s_borderWidth - s_borderTop;

   return p;
}

void InternalFrame::setInternalSize(GLsizei width, GLsizei height) {
   setSize(width + 2*s_borderWidth, height + s_borderWidth + s_borderTop);
}

void InternalFrame::setVisible(bool state) {
   if (state && !isVisible()) {
      Component::setVisible(state);
      onOpen();
   } else if (!state && isVisible()) {
      Component::setVisible(state);
      onClose();
   }   
}

void InternalFrame::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();

   if (isVisible() == false) return;

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
         _panel->setRelativePosition(Point(s_borderWidth, s_borderTop));
      } else if (!isResizing()) {
         if (isOnTopBar(evtPosition) && kernel->requestMouseUse(this)) {
            if (isOnCloseButton(evtPosition)) {
               _overClose = true;
               if (evt.getState() == MouseEvent::CLICK) {
                  _clickClose = true;
               }
            } else {
               _overClose = false;
               if (evt.getState() == MouseEvent::CLICK) {
                  _isDragging = true;
                  kernel->requestComponentFocus(this);
               }
            }
         }
      }
   }

   if (evt.getState() == MouseEvent::UP) {
      if (_clickClose && _overClose) {
         setVisible(false);
         _clickClose = false;
      } else {
         _clickClose = false;
      }
   }
}

void InternalFrame::processKey(const scv::KeyEvent &evt) {
   if (isVisible() == false) return;

   _panel->processKey(evt);
   Component::processKey(evt);
}

void InternalFrame::display(void) {
   static Kernel *kernel = Kernel::getInstance();

   if (isVisible() == false || _cTexture == NULL) return;

   Point currPosition = getAbsolutePosition();
   configPanel();

   Scissor::getInstance()->pushScissor(getScissor());

   _cTexture->enable();

   ColorScheme::getInstance()->applyColor(ColorScheme::MENUBAR);

   _cTexture->display(currPosition.x + 2,currPosition.y + 2, 7, getWidth() - 4, getHeight() - 4);

   // border top
   _cTexture->display(currPosition.x + 5             , currPosition.y + 1, 7, getWidth() - 10, 1);
   // border down
   _cTexture->display(currPosition.x + 5             , currPosition.y + getHeight() - 2, 7, getWidth() - 10, 1);
   // border right
   _cTexture->display(currPosition.x + getWidth() - 2, currPosition.y + 5, 7, 1, getHeight() - 10);
   // border left
   _cTexture->display(currPosition.x + 1             , currPosition.y + 5, 7, 1, getHeight() - 10);

   ColorScheme::getInstance()->applyDefaultModulate();
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

   ColorScheme::getInstance()->applyDefaultModulate();
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

   Scissor::getInstance()->pushScissor(Scissor::Info(currPosition.x + s_borderWidth, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() - s_borderWidth, getHeight() - s_borderTop));
   _panel->display();
   Scissor::getInstance()->popScissor();

   Scissor::getInstance()->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (currPosition.y) - s_borderTop, getWidth() - s_closeWidth - 10, s_borderTop));
   StaticLabel::display(currPosition.x + s_borderWidth, currPosition.y + (s_borderTop - FontTahoma::getInstance()->getHeight()) / 2 + 2, _title);
   Scissor::getInstance()->popScissor();
   Scissor::getInstance()->popScissor();
}

bool InternalFrame::isOnTopBar(const Point &p) {
   return (p.y >= getAbsolutePosition().y && p.y <= getAbsolutePosition().y + s_borderTop &&
      p.x >= getAbsolutePosition().x && p.x <= getAbsolutePosition().x + getWidth())? true : false;
}

bool InternalFrame::isOnCloseButton(const Point &p) {
   return (p.y >= getAbsolutePosition().y && p.y <= getAbsolutePosition().y + s_closeHeight &&
      p.x >= getAbsolutePosition().x + getWidth() - s_closeWidth - 5 && p.x <= getAbsolutePosition().x + getWidth() - 5)? true : false;
}

void InternalFrame::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(WINDOW)) != NULL) return;

   _cTexture = new ComponentTexture(46 * 3 + 10, 19);
   kernel->setWidgetTexture(WINDOW, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   _cTexture->addTexture(Point(0,      0), 46, 19, data::InternalFrameCloseButton);        // 0
   _cTexture->addTexture(Point(46*1,   0), 46, 19, data::InternalFrameCloseButtonHover);   // 1
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

void InternalFrame::configPanel(void) {
   _panel->setRelativePosition(Point(s_borderWidth, s_borderTop));
   _panel->setWidth(getWidth() - 2 * s_borderWidth);
   _panel->setHeight(getHeight() - s_borderWidth - s_borderTop);
}

} // namespace scv
