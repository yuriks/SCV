#include "stdafx.h"

#include "Button.h"
#include "Kernel.h"

namespace scv {

Button::Button(const scv::Point &p1, const scv::Point &p2, const std::string &str) : Label(p1, p2, str) {
   _isHResizable = _isVResizable = true;
   _type = BUTTON;
   text = str;

   setMaximumSize(Point(-1, -1));

   createTexture();
}

Button::Button(const scv::Point &p1, unsigned int width, const std::string &str) : Label(p1, Point(p1.x + width, p1.y + 24), str) {
   _isHResizable = _isVResizable = true;
   _type = BUTTON;
   text = str;

   setMaximumSize(Point(-1, -1));

   createTexture();
}

Button::Button(const scv::Point &p1, const std::string &str) : Label(p1, Point(p1.x + FontTahoma::getInstance()->getStringLength(str) + 10, p1.y + 24), str) {
   _isHResizable = _isVResizable = true;
   _type = BUTTON;
   text = str;

   setMaximumSize(Point(-1, -1));

   createTexture();
}

Button::~Button(void) {
}

std::string Button::getString() {
   return text;
}

void Button::onMouseClick(const scv::MouseEvent &evt) {
}
void Button::onMouseHold(const scv::MouseEvent &evt) {
}
void Button::onMouseOver(const scv::MouseEvent &evt) {
}
void Button::onMouseUp(const scv::MouseEvent &evt) {
}
void Button::onMouseWheel(const scv::MouseEvent &evt) {
}

void Button::onKeyPressed(const scv::KeyEvent &evt) {
}
void Button::onKeyUp(const scv::KeyEvent &evt) {
}

void Button::onSizeChange(void) {
}
void Button::onPositionChange(void) {
}

void Button::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
      scheme->applyColor(ColorScheme::MAINCOMPONENTS);
      // middle
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 4, getWidth() - 2, getHeight() - 2);

      if (isHolded()) {
         scheme->applyColor(ColorScheme::HOLDCOMPONENTS);
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 6, getWidth() - 2, getHeight() - 2);
      } else if (isOvered()) {
         scheme->applyColor(ColorScheme::OVERCOMPONENTS);
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 5, getWidth() - 2, getHeight() - 2);
      }

      scheme->applyColor(ColorScheme::MAINCOMPONENTS);
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

   scissor->pushScissor(Scissor::Info(currPosition.x + 3, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() - 6, getHeight()));

   StaticLabel::display(currPosition.x + getWidth() / 2 - font->getStringLength(Label::getString()) / 2 , currPosition.y + getHeight() / 2 - 6, Label::getString());

   scissor->popScissor();
}

void Button::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();

   if ((_cTexture = kernel->getWidgetTexture(BUTTON)) != NULL) return;

   ColorRGBA colorBotao1(250, 250, 250, 255);
   ColorRGBA colorBotao2(210, 210, 210, 255);

   ColorRGBA colorOver(220, 220, 220, 100);
   ColorRGBA colorClick(colorOver[0] - 100, colorOver[1] - 100, colorOver[2] - 100, colorOver[3]);

   // create texture object
   _cTexture = new ComponentTexture(8, 16);
   kernel->setWidgetTexture(BUTTON, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // left up
   MatrixTemplate<ColorRGBA> lUp(3, 3, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(lUp, Point(0,1), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(lUp, Point(1,1), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(lUp, Point(1,0), ColorRGBA(144,144,144,230));

   Texture2D::drawPoint(lUp, Point(1,2), ColorRGBA(202,202,202,200));
   Texture2D::drawPoint(lUp, Point(2,2), ColorRGBA(240,240,240,240));
   Texture2D::drawPoint(lUp, Point(2,1), ColorRGBA(202,202,202,200));

   _cTexture->addTexture(Point(0,0), lUp);

   // right up
   MatrixTemplate<ColorRGBA> rUp(3, 3, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(rUp, Point(1, 1), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(rUp, Point(1, 0), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(rUp, Point(2, 1), ColorRGBA(144,144,144,230));

   Texture2D::drawPoint(rUp, Point(1, 2), ColorRGBA(202,202,202,200));
   Texture2D::drawPoint(rUp, Point(0, 2), ColorRGBA(240,240,240,240));
   Texture2D::drawPoint(rUp, Point(0, 1), ColorRGBA(202,202,202,200));

   _cTexture->addTexture(Point(0,3), rUp);

   // left down
   MatrixTemplate<ColorRGBA> lDown(3, 3, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(lDown, Point(0,1), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(lDown, Point(1,1), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(lDown, Point(1,2), ColorRGBA(144,144,144,230));

   Texture2D::drawPoint(lDown, Point(1,0), ColorRGBA(202,202,202,200));
   Texture2D::drawPoint(lDown, Point(2,0), ColorRGBA(240,240,240,240));
   Texture2D::drawPoint(lDown, Point(2,1), ColorRGBA(202,202,202,200));

   _cTexture->addTexture(Point(0,6), lDown);

   // right down
   MatrixTemplate<ColorRGBA> rDown(3, 3, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(rDown, Point(1,2), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(rDown, Point(2,1), ColorRGBA(144,144,144,230));
   Texture2D::drawPoint(rDown, Point(1,1), ColorRGBA(144,144,144,230));

   Texture2D::drawPoint(rDown, Point(1,0), ColorRGBA(202,202,202,200));
   Texture2D::drawPoint(rDown, Point(0,0), ColorRGBA(240,240,240,240));
   Texture2D::drawPoint(rDown, Point(0,1), ColorRGBA(202,202,202,200));

   _cTexture->addTexture(Point(0,9), rDown);

   // normal middle
   MatrixTemplate<ColorRGBA> nMiddle(1, 16, ColorRGBA(0,0,0,0));
   for (int i = 0, j = 15; i < 8; i++, j--) {
      Texture2D::drawPoint(nMiddle, Point(0,i), colorBotao1 - i * 2);
      Texture2D::drawPoint(nMiddle, Point(0,j), colorBotao2 - i * 2);
   }
   _cTexture->addTexture(Point(3,0), nMiddle);

   // over middle
   MatrixTemplate<ColorRGBA> oMiddle(1, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(oMiddle, Point(0,0), colorOver);

   _cTexture->addTexture(Point(4,0), oMiddle);

   // click middle
   MatrixTemplate<ColorRGBA> cMiddle(1, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(cMiddle, Point(0,0), colorClick);

   _cTexture->addTexture(Point(5,0), cMiddle);

   // up line
   MatrixTemplate<ColorRGBA> uLine(1, 2, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(uLine, Point(0,0), ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(uLine, Point(0,1), ColorRGBA(255,255,255,255));

   _cTexture->addTexture(Point(6,0), uLine);

   // down line
   MatrixTemplate<ColorRGBA> dLine(1, 2, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(dLine, Point(0,0), ColorRGBA(255,255,255,255));
   Texture2D::drawPoint(dLine, Point(0,1), ColorRGBA(112,112,112,255));

   _cTexture->addTexture(Point(7,0), dLine);

   // left line
   MatrixTemplate<ColorRGBA> lLine(2, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(lLine, Point(0,0), ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(lLine, Point(1,0), ColorRGBA(255,255,255,255));

   _cTexture->addTexture(Point(6,2), lLine);

   // right line
   MatrixTemplate<ColorRGBA> rLine(2, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(rLine, Point(1,0), ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(rLine, Point(0,0), ColorRGBA(255,255,255,255));

   _cTexture->addTexture(Point(6,3), rLine);

   // generate texture
   _cTexture->createTexture();
}

} // namespace scv