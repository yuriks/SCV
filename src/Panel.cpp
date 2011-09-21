#include "stdafx.h"
#include "Panel.h"
#include "Kernel.h"

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

   //REVIEW
   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(iter->get()))
         (*iter)->display();
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

//REVIEW
void Panel::addObject(SCVObject::Ptr& object) {
   static Kernel *kernel = Kernel::getInstance();

   object->setPanelScissor(Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight()));
   object->setPanelTranslate(getAbsolutePosition());

   addChild(object);

   /*
   if (component) {
      component->setPanelScissor(Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight()));
      component->setPanelTranslate(getAbsolutePosition());

      std::cout << component->shared_from_this() << std::endl;
      addChild(component->shared_from_this());
   }*/
}

void Panel::setRelativePosition(const Point &position) {
   SCVObject::setRelativePosition(position);
   refresh(true, true);
}

void Panel::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   if (isDragging() || isResizing()) {
      SCVObject::processMouse(evt);
      refresh(true, true);
   } else {
      SCVObject *focusedComponent = kernel->getFocusedComponent();
      List::const_reverse_iterator itUp = getChildren().rbegin();

      Scissor::ScissorInfo scissor;
      if (kernel->scissorNeedRefresh())
         scissor = Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight());

      //REVIEW
      for (SCVObject::List::const_reverse_iterator iter = getChildren().rbegin(); iter != getChildren().rend(); ++iter) {
         if (kernel->scissorNeedRefresh())
            (*iter)->setPanelScissor(scissor);

         (*iter)->processMouse(evt);
         if (focusedComponent != kernel->getFocusedComponent()) {
            focusedComponent = kernel->getFocusedComponent();
            itUp = iter;
         }
      }

      //REVIEW
      // swap clicked window to top
      if (itUp != getChildren().rbegin() && (*itUp)->isDragging()) {
         SCVObject::Ptr removed_child = (*itUp);
         _children.remove(*itUp);
         _children.push_back(removed_child);
      } else {
         SCVObject::processMouse(evt);
      }
   }
}

void Panel::processKey(const scv::KeyEvent &evt) {
   SCVObject::processKey(evt);

   //REVIEW
   for (SCVObject::List::const_reverse_iterator iter = getChildren().rbegin(); iter != getChildren().rend(); ++iter) {
      (*iter)->processKey(evt);
   }
}

void Panel::setPanelScissor(const Scissor::ScissorInfo &scissor)  {
   static Kernel *kernel = Kernel::getInstance();
   SCVObject::setPanelScissor(scissor);

   //REVIEW
   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      (*iter)->setPanelScissor(Scissor::ScissorInfo(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight()));
   }
}

void Panel::setPanelTranslate(const Point &translate) {
   SCVObject::setPanelTranslate(translate);

   //REVIEW
   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      (*iter)->setPanelTranslate(getAbsolutePosition());
   }
}

void Panel::refresh(bool cScissor, bool cTranslate) {
   static Kernel *kernel = Kernel::getInstance();

   Scissor::ScissorInfo scissor(getAbsolutePosition().x, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth(), getHeight());

   //REVIEW
   for (SCVObject::List::const_reverse_iterator iter = getChildren().rbegin(); iter != getChildren().rend(); ++iter) {
      if (cScissor) (*iter)->setPanelScissor(scissor);
      if (cTranslate) (*iter)->setPanelTranslate(getAbsolutePosition());
   }
}

void Panel::setDraggable(bool state) {
   SCVObject::setDraggable(state);
}

void Panel::setResizable(bool state) {
   SCVObject::setResizable(state);
}


} // namespace scv
