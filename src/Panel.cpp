#include "stdafx.h"
#include "Panel.h"
#include "Kernel.h"

#include "GroupLayout.h"

namespace scv {

Panel::Panel(const scv::Point &p1, const scv::Point &p2) : ComponentWithTexture(p1, p2) {
   _type = panel;

   _layout = NULL;
   _leftToRight = true;

   createTexture();
}

Panel::~Panel(void) {}

void Panel::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   scissor->pushScissor(getScissor());

   _cTexture->enable();
   scheme->applyColor(ColorScheme::panel);

   // middle
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);

   // corners
   _cTexture->display(currPosition.x, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + 1, currPosition.y, 0, getWidth() - 2, 1);
   _cTexture->display(currPosition.x + 1, currPosition.y + getHeight() - 1, 0, getWidth() - 2, 1);

   _cTexture->disable();

   //REVIEW
   if (_layout != NULL) {
      _layout->layoutContainer();
   }

   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }

   scissor->popScissor();
}

void Panel::createTexture(void) {
   if ((_cTexture = kernel->getWidgetTexture(Kernel::panel)) != NULL) return;

   _cTexture = new ComponentTexture(2, 2);
   kernel->setWidgetTexture(Kernel::panel, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // middle
   MatrixTemplate<ColorRGBA> middle(1, 1, ColorRGBA(255,255,255,255));
   _cTexture->addTexture(Point(0,0), middle);

   _cTexture->createTexture();
}

void Panel::onMouseClick(const scv::MouseEvent &evt) {}
void Panel::onMouseHold(const scv::MouseEvent &evt) {}
void Panel::onMouseOver(const scv::MouseEvent &evt) {}
void Panel::onMouseUp(const scv::MouseEvent &evt) {}
void Panel::onKeyPressed(const scv::KeyEvent &evt) {}
void Panel::onKeyUp(const scv::KeyEvent &evt) {}
void Panel::onMouseWheel(const scv::MouseEvent &evt) {}
void Panel::onResizing(void) {}
void Panel::onDragging(void) {}

void Panel::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   if (isDragging() || isResizing()) {
      Component::processMouse(evt);
   } else {
      Component *focusedComponent = kernel->getFocusedComponent();
      Component *child = NULL; 

      for (Component::List::const_reverse_iterator iter = getChildren().rbegin(); iter != getChildren().rend(); ++iter) {
         (*iter)->processMouse(evt);
         if (focusedComponent != kernel->getFocusedComponent()) {
            focusedComponent = kernel->getFocusedComponent();
            child = (*iter);
         }
      }

      if (child != NULL && child->isDragging()) {
         pullChildToTop(child);
      } else {
         Component::processMouse(evt);
      }      
   }
}

void Panel::processKey(const scv::KeyEvent &evt) {
   Component::processKey(evt);

   for (Component::List::const_reverse_iterator iter = getChildren().rbegin(); iter != getChildren().rend(); ++iter) {
      (*iter)->processKey(evt);
   }
}

} // namespace scv
