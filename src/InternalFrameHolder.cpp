#include "stdafx.h"
#include "InternalFrameHolder.h"
#include "InternalFrame.h"

#include "Kernel.h"

namespace scv {

class SCVObject;

void InternalFrameHolder::display(void) {
   static ColorScheme *scheme = ColorScheme::getInstance();

   for (int i = 0; i < _framesDeque.size(); i++) {
      if (i == _framesDeque.size() - 1) {
         scheme->applyColor(ColorScheme::mainComponents);
      } else {
         scheme->applyColor(ColorScheme::mainComponents, + 0.3f);
      }
      _framesDeque[i]->display();
   }
}

bool InternalFrameHolder::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   bool status = false;

   std::deque<InternalFrame*>::reverse_iterator itUp = _framesDeque.rbegin();
   SCVObject *focusedComponent = kernel->getFocusedComponent();

   for (std::deque<InternalFrame*>::reverse_iterator rIt = _framesDeque.rbegin(); rIt < _framesDeque.rend(); rIt++) {
      (*rIt)->processMouse(evt);
      if (focusedComponent != kernel->getFocusedComponent()) {
         focusedComponent = kernel->getFocusedComponent();
         status = true;
         itUp = rIt;
      }
   }

   // swap clicked window to top
   if (itUp != _framesDeque.rbegin()) {
      InternalFrame *component = *itUp;
      _framesDeque.erase(itUp.base() - 1);
      _framesDeque.push_back(component);
   }

   return status;
}

bool InternalFrameHolder::processKey(const scv::KeyEvent &evt) {
   for (int i = _framesDeque.size() - 1; i >= 0; i--) {
      _framesDeque[i]->processKey(evt);
   }
   return false;
}

void InternalFrameHolder::registerFrame(InternalFrame *frame) {
   if (frame != NULL) _framesDeque.push_back(frame);
}

void InternalFrameHolder::closeAllWindows(void) {
   for (int i = 0; i < _framesDeque.size(); i++) {
      _framesDeque[i]->setVisible(false);
   }
}

} // namespace scv