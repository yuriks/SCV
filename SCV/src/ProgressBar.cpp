#include "stdafx.h"
#include "ProgressBar.h"
#include "Kernel.h"
#include "util.h"
#include "StaticLabel.h"

namespace scv {

ProgressBar::ProgressBar(const scv::Point &p, unsigned int width , double startValue) :
      Label(p,Point(p.x+width,p.y+24), toString(startValue) + "%"), Counter(0,100,startValue<0?0:startValue>100?100:startValue,1) {
   _isHResizable = _isVResizable = true;
   _type = PROGRESSBAR;

   createTexture();
}

ProgressBar::ProgressBar(const scv::Point &p1, const scv::Point &p2, double startValue) :
      Label(p1,p2,toString(startValue) + "%"), Counter(0,100,startValue<0?0:startValue>100?100:startValue,1) {
   _isHResizable = _isVResizable = true;
   _type = PROGRESSBAR;

   createTexture();
}

ProgressBar::ProgressBar(const scv::Point &p, double startValue) :
      Label(p,Point(p.x+100,p.y+24),toString(startValue) + "%"), Counter(0,100,startValue<0?0:startValue>100?100:startValue,1) {
   _isHResizable = _isVResizable = true;
   _type = PROGRESSBAR;

   createTexture();
}

ProgressBar::~ProgressBar(void) {
}

void ProgressBar::onMouseClick(const scv::MouseEvent &evt) {
}
void ProgressBar::onMouseHold(const scv::MouseEvent &evt) {
}
void ProgressBar::onMouseOver(const scv::MouseEvent &evt) {
}
void ProgressBar::onMouseUp(const scv::MouseEvent &evt) {
}
void ProgressBar::onMouseWheel(const scv::MouseEvent &evt) {
}

void ProgressBar::onKeyPressed(const scv::KeyEvent &evt) {
}
void ProgressBar::onKeyUp(const scv::KeyEvent &evt) {
}

void ProgressBar::onSizeChange(void) {
}
void ProgressBar::onPositionChange(void) {
}

void ProgressBar::onValueChange(void) {
}

void ProgressBar::display(void) {
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
   scheme->applyDefaultModulate();
      // middle
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 4, getWidth() - 3, getHeight() - 2);

      scheme->applyColor(ColorScheme::PROGRESSBAR);
      //selection
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 9, static_cast<int>((getValue() / 100.f) * (getWidth() - 4)) + 1, getHeight() - 2);

      scheme->applyDefaultModulate();
      // horizontal lines
      _cTexture->display(currPosition.x + 2, currPosition.y, 5, getWidth() - 4, 2);
      _cTexture->display(currPosition.x + 2, currPosition.y + getHeight() - 2, 6, getWidth() - 4, 2);

      // vertical lines
      _cTexture->display(currPosition.x, currPosition.y + 2, 7, 2, getHeight() - 4);
      _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 2, 7, 2, getHeight() - 4);

      // corners
      _cTexture->display(currPosition, 0);
      _cTexture->display(currPosition.x + getWidth() - 3, currPosition.y, 1);
      _cTexture->display(currPosition.x, currPosition.y + getHeight()- 3, 2);
      _cTexture->display(currPosition.x + getWidth() - 3, currPosition.y + getHeight() - 3, 3);
   _cTexture->disable();

   StaticLabel::display(currPosition.x + getWidth() / 2 - font->getStringLength(Label::getString()) / 2 , currPosition.y + getHeight() / 2 - 6, Label::getString());
}

void ProgressBar::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(PROGRESSBAR)) != NULL) return;

   ColorRGBA colorBotao1(250, 250, 250, 255);
   ColorRGBA colorBotao2(210, 210, 210, 255);

   ColorRGBA colorOver(209, 209, 209, 80);
   ColorRGBA colorClick(colorOver[0] - 60, colorOver[1] - 60, colorOver[2] - 60, colorOver[3]);

   // create texture object
   _cTexture = new ComponentTexture(8, 16);
   kernel->setWidgetTexture(PROGRESSBAR, _cTexture);

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

   // selection
   MatrixTemplate<ColorRGBA> selection(1, 1, ColorRGBA(200,200,200,200));
   _cTexture->addTexture(Point(7,3), selection);

   // generate texture
   _cTexture->createTexture();
}

void ProgressBar::setValue(double value) {
   Counter::setValue(value);
   Label::setString(toString(getValue()) + "%");
}

} // namespace scv