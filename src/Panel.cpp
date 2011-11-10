#include "stdafx.h"
#include "Panel.h"
#include "Kernel.h"

#include "GroupLayout.h"

namespace scv {

Panel::Panel(const scv::Point &p1, const scv::Point &p2) : ComponentWithTexture(p1, p2) {
   _type = PANEL;

   _layout = NULL;
   _leftToRight = true;

   setMinimumSize(Point(15, 15));

   createTexture();
}

Panel::~Panel(void) {}

void Panel::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   //scissor->pushScissor(getScissor());

   _cTexture->enable();
   scheme->applyColor(ColorScheme::PANEL);

   // middle
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);

   // corners
   _cTexture->display(currPosition.x, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + 1, currPosition.y, 0, getWidth() - 2, 1);
   _cTexture->display(currPosition.x + 1, currPosition.y + getHeight() - 1, 0, getWidth() - 2, 1);

   _cTexture->disable();

   if (_layout != NULL) {
      _layout->layoutContainer();
   }
   
   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }

   //scissor->popScissor();
}

void Panel::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(Kernel::PANEL)) != NULL) return;

   _cTexture = new ComponentTexture(2, 2);
   kernel->setWidgetTexture(Kernel::PANEL, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // middle
   MatrixTemplate<ColorRGBA> middle(1, 1, ColorRGBA(255,255,255,255));
   _cTexture->addTexture(Point(0,0), middle);

   _cTexture->createTexture();
}

void Panel::onMouseClick(const scv::MouseEvent &evt) {
}
void Panel::onMouseHold(const scv::MouseEvent &evt) {
}
void Panel::onMouseOver(const scv::MouseEvent &evt) {
}
void Panel::onMouseUp(const scv::MouseEvent &evt) {
}
void Panel::onMouseWheel(const scv::MouseEvent &evt) {
}

void Panel::onKeyPressed(const scv::KeyEvent &evt) {
}
void Panel::onKeyUp(const scv::KeyEvent &evt) {
}

void Panel::onSizeChange(void) {
}
void Panel::onPositionChange(void) {
}

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

Point Panel::getMinimumSize(void) const {
   return Component::getMinimumSize();
   if (_layout != NULL) {
      scv::Point size(_layout->getMinimumSize(Spring::HORIZONTAL), _layout->getMinimumSize(Spring::VERTICAL));
      if (size.x == Spring::DEFAULT_SIZE) size.x = Component::getMinimumSize().x;
      if (size.y == Spring::DEFAULT_SIZE) size.y = Component::getMinimumSize().y;
      return size;
   } else {
      return Component::getMinimumSize();
   }
}

Point Panel::getPreferredSize(void) const {
   return Component::getPreferredSize();
   if (_layout != NULL) {
      scv::Point size(_layout->getPreferredSize(Spring::HORIZONTAL), _layout->getPreferredSize(Spring::VERTICAL));
      if (size.x == Spring::DEFAULT_SIZE) size.x = Component::getPreferredSize().x;
      if (size.y == Spring::DEFAULT_SIZE) size.y = Component::getPreferredSize().y;
      return size;
   } else {
      return Component::getPreferredSize();
   }
}

Point Panel::getMaximumSize(void) const {
   return Component::getMaximumSize();
   /*
   if (_layout != NULL) {
      scv::Point size(_layout->getMaximumSize(Spring::HORIZONTAL), _layout->getMaximumSize(Spring::VERTICAL));
      if (size.x == Spring::DEFAULT_SIZE) size.x = Component::getMaximumSize().x;
      if (size.y == Spring::DEFAULT_SIZE) size.y = Component::getMaximumSize().y;
      return size;
   } else {
      return Component::getMaximumSize();
   }
   /**/
}

void Panel::addChild(Component *object) {
   ComponentWithTexture::addChild(object);
}

void Panel::removeChild(Component *object) {
   ComponentWithTexture::removeChild(object);
}

} // namespace scv
