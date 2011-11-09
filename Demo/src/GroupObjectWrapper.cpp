#include "stdafx.h"
#include "GroupObjectWrapper.h"

GroupObjectWrapper::GroupObjectWrapper(scv::Component *objet) : scv::Panel(scv::Point(0,0), scv::Point(objet->getWidth(), objet->getHeight())) {
   setMinimumSize(objet->getMinimumSize());
   setPreferredSize(objet->getPreferredSize());
   setMaximumSize(objet->getMaximumSize());

   std::cout << getMinimumSize() << std::endl;
}

GroupObjectWrapper::~GroupObjectWrapper(void) {

}

void GroupObjectWrapper::display(void) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   static scv::Scissor *scissor = scv::Scissor::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   scv::Point currPosition = getAbsolutePosition();

   scissor->pushScissor(getScissor());

   _cTexture->enable();
   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.4f, 0.4f, 0.3f, 1.0f));

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

   scissor->popScissor();
}
