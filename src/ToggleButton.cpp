#include "stdafx.h"
#include "ToggleButton.h"
#include "Kernel.h"


namespace scv {

ToggleButton::ToggleButton( const scv::Point &p1, const scv::Point &p2, bool state, const std::string &str ) : StateButton(state), Button(p1,p2,str) {
   _type = toggleButton;
}

ToggleButton::ToggleButton( const scv::Point &p1, unsigned int width , bool state, const std::string &str ) : StateButton(state), Button(p1,width,str) {
   _type = toggleButton;
}

ToggleButton::ToggleButton( const scv::Point &p1 , bool state, const std::string &str ) : StateButton(state), Button(p1,str) {
   _type = toggleButton;
}

void ToggleButton::onMouseClick(const scv::MouseEvent &evt) {/**/}
void ToggleButton::onMouseHold(const scv::MouseEvent &evt) {/**/}
void ToggleButton::onMouseOver(const scv::MouseEvent &evt) {/**/}
void ToggleButton::onMouseUp(const scv::MouseEvent &evt) {/**/}
void ToggleButton::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void ToggleButton::onKeyUp(const scv::KeyEvent &evt) {/**/}
void ToggleButton::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void ToggleButton::onValueChange(void) {/**/}
void ToggleButton::onResizing(void) {/**/}
void ToggleButton::onDragging(void) {/**/}

void ToggleButton::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
      scheme->applyColor(ColorScheme::mainComponents);
      // middle
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 4, getWidth() - 2, getHeight() - 2);

      if (getState() || isHolded()) {
         scheme->applyColor(ColorScheme::holdComponents);
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 6, getWidth() - 2, getHeight() - 2);
      }
      if (isOvered() && !isHolded()) {
         scheme->applyColor(ColorScheme::overComponents);
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 5, getWidth() - 2, getHeight() - 2);
      }

      scheme->applyColor(ColorScheme::mainComponents);
      // horizontal lines
      _cTexture->display(currPosition.x + 2, currPosition.y, 7, getWidth() - 4, 2);
      _cTexture->display(currPosition.x + 2, currPosition.y + getHeight() - 2, 8, getWidth() - 4, 2);

      // vertical lines
      _cTexture->display(currPosition.x, currPosition.y + 2, 9, 2, getHeight() - 4);
      _cTexture->display(currPosition.x + getWidth() - 2, currPosition.y + 2, 10, 2, getHeight() - 4);

      // corners
      _cTexture->display(currPosition, 0);
      _cTexture->display(currPosition.x + getWidth() - 3, currPosition.y, 1);
      _cTexture->display(currPosition.x, currPosition.y + getHeight()- 3, 2);
      _cTexture->display(currPosition.x + getWidth() - 3, currPosition.y + getHeight() - 3, 3);
   _cTexture->disable();


   scissor->pushScissor(Scissor::Info(getAbsolutePosition().x + 3, kernel->getHeight() - (getHeight() + getAbsolutePosition().y), getWidth() - 6, getHeight()));
   Label::display(getAbsolutePosition().x + getWidth() / 2 - font->getStringLength(Label::getString()) / 2 , getAbsolutePosition().y + getHeight() / 2 - 6);
   scissor->popScissor();
}


void ToggleButton::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Component::processMouse(evt);

   if (!_receivingCallbacks) return;

   if (isInside(evt.getPosition())) {
      if (evt.getState() == MouseEvent::up && isFocused())
         setState(!getState());
   }
}

} // namespace scv