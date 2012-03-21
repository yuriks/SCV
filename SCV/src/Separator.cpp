#include "stdafx.h"
#include "Separator.h"
#include "Kernel.h"

namespace scv {

Separator::Separator(const scv::Point &p1, Separator::Orientation align, unsigned int size) :
      ComponentWithTexture(p1, (align == Separator::HORIZONTAL) ? Point(p1.x + size, p1.y + 2) : Point(p1.x + 2, p1.y + size)) {
   _align = align;

   if (_align == Separator::HORIZONTAL) {
      _isVResizable = false;
      setMaximumSize(Point(-1, 2));
   } else {
      _isHResizable = false;
      setMaximumSize(Point(2, -1));
   }
   _type = SEPARATOR;

   createTexture();
}

Separator::~Separator(void) {
}

void Separator::onMouseClick(const scv::MouseEvent &evt) {
}
void Separator::onMouseHold(const scv::MouseEvent &evt) {
}
void Separator::onMouseOver(const scv::MouseEvent &evt) {
}
void Separator::onMouseUp(const scv::MouseEvent &evt) {
}
void Separator::onMouseWheel(const scv::MouseEvent &evt) {
}

void Separator::onKeyPressed(const scv::KeyEvent &evt) {
}
void Separator::onKeyUp(const scv::KeyEvent &evt) {
}

void Separator::onSizeChange(void) {
}
void Separator::onPositionChange(void) {
}

void Separator::display(void) {
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
   scheme->applyColor(ColorScheme::SEPARATOR);
      if (_align == Separator::HORIZONTAL) {
         _cTexture->display(currPosition.x, currPosition.y, 0, getWidth(), 2);
      } else /*Separator::vertical*/ {
         _cTexture->display(currPosition.x, currPosition.y, 1, 2, getHeight());
      }
   _cTexture->disable();
}

void Separator::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(SEPARATOR)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(4, 4);
   kernel->setWidgetTexture(SEPARATOR, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   MatrixTemplate<ColorRGBA> horizontal(1, 2, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(horizontal, Point(0,0), ColorRGBA(150,150,170,255));
   Texture2D::drawPoint(horizontal, Point(0,1), ColorRGBA(230,230,230,255));
   _cTexture->addTexture(Point(0,0), horizontal);

   MatrixTemplate<ColorRGBA> vertical(2, 1, ColorRGBA(0,0,0,0));
   Texture2D::drawPoint(vertical,Point(0,0), ColorRGBA(150,150,170,255));
   Texture2D::drawPoint(vertical,Point(1,0), ColorRGBA(230,230,230,255));
   _cTexture->addTexture(Point(2,2), vertical);

   _cTexture->createTexture();
}

} // namespace scv