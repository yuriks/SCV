#include "stdafx.h"
#include "CheckBox.h"
#include "Kernel.h"
#include "GlslShader.h"
#include "data.h"
namespace scv {

CheckBox::CheckBox(const scv::Point &p1, bool state, const std::string &str) : StateButton(state), Label(p1, Point( p1.x + 13 + FontTahoma::getInstance()->getStringLength(str) + 3,p1.y + 13), str) {
   _isHResizable = _isVResizable = false;
   _type = checkBox;

   createTexture();
}

void CheckBox::onMouseClick(const scv::MouseEvent &evt) {/**/}
void CheckBox::onMouseHold(const scv::MouseEvent &evt) {/**/}
void CheckBox::onMouseOver(const scv::MouseEvent &evt) {/**/}
void CheckBox::onMouseUp(const scv::MouseEvent &evt) {/**/}
void CheckBox::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void CheckBox::onKeyUp(const scv::KeyEvent &evt) {/**/}
void CheckBox::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void CheckBox::onValueChange(void) {/**/}
void CheckBox::onSizeChange(void) {/**/}
void CheckBox::onPositionChange(void) {/**/}

void CheckBox::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
      scheme->applyDefaultModulate();
      if (getState() == false) {
         _cTexture->display(getAbsolutePosition(), 0);
      } else {
         _cTexture->display(getAbsolutePosition(), 1);
      }

      if (isHolded()) {
         scheme->applyColor(ColorScheme::holdComponents);
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 2, 13 - 2, 13 - 2);
      } else if (isOvered()) {
         scheme->applyColor(ColorScheme::overComponents);
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 3, 13 - 2, 13 - 2);
      }
   _cTexture->disable();

   scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() + font->getStringLength(Label::getString()) + 3, getHeight()));

   Label::display(currPosition.x + 13 + 3, currPosition.y);

   scissor->popScissor();
}

void CheckBox::createTexture(void) {
   if ((_cTexture = kernel->getWidgetTexture(Kernel::checkBox)) != NULL) return;

   ColorRGBA  pColor1(183,191,213,255);
   ColorRGBA  pColor2( 71, 92,148,255);
   ColorRGBA  pColor3(100,118,165,255);
   ColorRGBA  pColor4(207,212,226,255);

   ColorRGBA colorClick(170,220,255,60);
   ColorRGBA colorOver(colorClick[0] - 100,colorClick[1] - 80,colorClick[2] - 40, colorClick[3]);

   ColorRGBA BackgroundColor(112,112,112,0);

   // create texture object
   _cTexture = new ComponentTexture(32, 16);
   kernel->setWidgetTexture(Kernel::checkBox, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // !selected
   _cTexture->addTexture(Point(0,0), 13, 13, data::CheckBox);

   // selected
   _cTexture->addTexture(Point(13,0), 13, 13, data::CheckBoxPressed);

   // over
   MatrixTemplate<ColorRGBA> over(1, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(over, Point(0,0), colorOver);
   _cTexture->addTexture(Point(0,13), over);

   // hold
   MatrixTemplate<ColorRGBA> hold(1, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(hold, Point(0,0), colorClick);
   _cTexture->addTexture(Point(1,13), hold);

   _cTexture->createTexture();
}

void CheckBox::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Component::processMouse(evt);

   if (!_receivingCallbacks) return;

   if (isInside(evt.getPosition())) {
      if (evt.getState() == MouseEvent::CLICK && isFocused())
         setState(!getState());
   }
}

void CheckBox::setString(const std::string& str) {
   static FontTahoma *font = FontTahoma::getInstance();
   Label::setString(str);
   setWidth(font->getStringLength(str) + 16);
}

} // namespace scv