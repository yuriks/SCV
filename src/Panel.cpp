#include "stdafx.h"
#include "Panel.h"
#include "Kernel.h"
#include "DynamicCastIterator.h"

namespace scv {

Panel::Panel(const scv::Point &p1, const scv::Point &p2) : ComponentWithTexture(p1, p2) {
   _type = panel;
   // none
}

Panel::Panel(const scv::Point &p1, unsigned int width, unsigned int height) : ComponentWithTexture(p1, Point(p1.x+width,p1.y+height)) {
   _type = panel;
   // none
}

Panel::Panel() : ComponentWithTexture(Point(10,10), Point(100,100)) {
   _type = panel;
   // none
}

void Panel::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   Scissor::ScissorInfo scissorInfo(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());

   scissor->pushScissor(scissorInfo);

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

   for (DynamicCastIterator<ComponentInterface, ObjectList::const_iterator> i (getChildren()); i.valid(); ++i) {
      if (kernel->willAppearOnScreen(*i))
         i->display();
   }

   scissor->popScissor();
}

void Panel::createTexture(void) {
   _cTexture = new ComponentTexture(2, 2);
   _cTexture->setTextureEnvMode(GL_MODULATE);

   // middle
   MatrixTemplate<ColorRGBA> middle(1, 1, ColorRGBA(255,255,255,255));
   _cTexture->addTexture(Point(0,0), middle);

   _cTexture->createTexture();
}

void Panel::onMouseClick(const scv::MouseEvent &evt) {/**/}
void Panel::onMouseHold(const scv::MouseEvent &evt) {/**/}
void Panel::onMouseOver(const scv::MouseEvent &evt) {/**/}
void Panel::onMouseUp(const scv::MouseEvent &evt) {/**/}
void Panel::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void Panel::onKeyUp(const scv::KeyEvent &evt) {/**/}
void Panel::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void Panel::onResizing(void) {/**/}
void Panel::onDragging(void) {/**/}

void Panel::addComponent(ComponentInterface *component) {
   static Kernel *kernel = Kernel::getInstance();
   if (component) {
      component->setPanelScissor(Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight()));
      component->setPanelTranslate(getAbsolutePosition());
      addChild(component);
   }
}

void Panel::setRelativePosition(const Point &position) {
   ComponentInterface::setRelativePosition(position);
   refresh(true, true);
}

void Panel::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   if (isDragging() || isResizing()) {
      ComponentInterface::processMouse(evt);
      refresh(true, true);
   } else {
      ComponentInterface *focusedComponent = kernel->getFocusedComponent();
      ObjectList::const_reverse_iterator itUp = getChildren().rbegin();

      Scissor::ScissorInfo scissor;
      if (kernel->scissorNeedRefresh())
         scissor = Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight());

      for (DynamicCastIterator<ComponentInterface, ObjectList::const_reverse_iterator> i
            (getChildren().rbegin(), getChildren().rend()); i.valid(); ++i) {
         if (kernel->scissorNeedRefresh())
            i->setPanelScissor(scissor);

         i->processMouse(evt);
         if (focusedComponent != kernel->getFocusedComponent()) {
            focusedComponent = kernel->getFocusedComponent();
            itUp = i.base();
         }
      }

      // swap clicked window to top
      if (itUp != getChildren().rbegin() && static_cast<ComponentInterface*>(*itUp)->isDragging()) {
         ObjectList::const_iterator tmp = itUp.base();
         --tmp;
         pullChildToTop(tmp);
      } else {
         ComponentInterface::processMouse(evt);
      }

   }
}

void Panel::processKey(const scv::KeyEvent &evt) {
   ComponentInterface::processKey(evt);

   for (DynamicCastIterator<ComponentInterface, ObjectList::const_reverse_iterator> i
      (getChildren().rbegin(), getChildren().rend()); i.valid(); ++i) {
      i->processKey(evt);
   }
}

void Panel::setPanelScissor(const Scissor::ScissorInfo &scissor)  {
   static Kernel *kernel = Kernel::getInstance();

   ComponentInterface::setPanelScissor(scissor);
   for (DynamicCastIterator<ComponentInterface, ObjectList::const_iterator> i(getChildren()); i.valid(); ++i) {
      i->setPanelScissor(Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight()));
   }
}

void Panel::setPanelTranslate(const Point &translate) {
   ComponentInterface::setPanelTranslate(translate);
   for (DynamicCastIterator<ComponentInterface, ObjectList::const_iterator> i
      (getChildren()); i.valid(); ++i) {
      i->setPanelTranslate(getAbsolutePosition());
   }
}

void Panel::refresh(bool cScissor, bool cTranslate) {
   static Kernel *kernel = Kernel::getInstance();

   Scissor::ScissorInfo scissor(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight());
   for (DynamicCastIterator<ComponentInterface, ObjectList::const_reverse_iterator> i
         (getChildren().rbegin(), getChildren().rend()); i.valid(); ++i) {
      if (cScissor) i->setPanelScissor(scissor);
      if (cTranslate) i->setPanelTranslate(getAbsolutePosition());
   }
}

void Panel::setDraggable(bool state) {
   ComponentInterface::setDraggable(state);
}

void Panel::setResizable(bool state) {
   ComponentInterface::setResizable(state);
}


} // namespace scv
