#include "stdafx.h"
#include "Label.h"
#include "Kernel.h"

namespace scv {

Label::Label(const scv::Point &p1, const scv::Point &p2, const std::string& str) : ComponentWithTexture(p1, p2) {
   _isHResizable = _isVResizable = false;
   _str = str;
   _type = label;

   createTexture();
}

Label::Label(const scv::Point &p, const std::string& str) : ComponentWithTexture(p, Point(p.x + FontTahoma::getInstance()->getStringLength(str), p.y + 13)) {
   _isHResizable = _isVResizable = false;
   _str = str;
   _type = label;

   createTexture();
}

Label::Label(const scv::Point &p, unsigned int width, const std::string& str) : ComponentWithTexture(p, Point(p.x + width, p.y + 13)) {
   _isHResizable = _isVResizable = false;
   _str = str;
   _type = label;

   createTexture();
}

void Label::setString(const std::string& str) {
   static Kernel *kernel = Kernel::getInstance();
   if (_str != str) {
      _str = str;
      onStringChange();
   }
}

void Label::display(void) {
   display(getAbsolutePosition());
}

void Label::display(const Point &translate) {
   if (_isVisible == false) return;
   display(translate, getString());
}

void Label::display(const Point &translate, const std::string &label, const Color4f &color) {
   static FontTahoma *font = FontTahoma::getInstance();
   static ComponentTexture *cTexture = font->getTexture();
   static ColorScheme *scheme = ColorScheme::getInstance();

   int strLength = 0;

   cTexture->enable();
   glColor3fv(&color[0]);
   scheme->applyColor(ColorScheme::font);
      for (int i = 0; i < label.size(); i++) {
         cTexture->display(translate.x + strLength, translate.y, label[i] * font->getWidth(), 0, 8, 15);
         strLength += font->getCharWidth(label[i]);
      }
   cTexture->disable();
}

void Label::display(const Point &translate, const std::string &label, int selectStart, int selectEnd) {
   static FontTahoma *font = FontTahoma::getInstance();
   static ComponentTexture *cTexture = font->getTexture();
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (selectStart > selectEnd)
      std::swap(selectStart, selectEnd);

   int strLength = 0;
   cTexture->enable();
      for (int i = 0; i < label.size(); i++) {
         if (label[i] != '\n') {
            // select
            if (selectStart != selectEnd && i > selectStart && i <= selectEnd) {
               scheme->applyColor(ColorScheme::textSelection);
               cTexture->display(strLength + translate.x, translate.y - 2, 1,font->getCharWidth(label[i]), font->getHeight() + 1);
               scheme->applyColor(ColorScheme::textSelected);
            } else scheme->applyColor(ColorScheme::font);

            // string
            cTexture->display(translate.x + strLength, translate.y, label[i] * font->getWidth(), 0, 8, 15);
         }
         strLength += font->getCharWidth(label[i]);
      }
   cTexture->disable();
}

void Label::onMouseClick(const scv::MouseEvent &evt) {/**/}
void Label::onMouseHold(const scv::MouseEvent &evt) {/**/}
void Label::onMouseOver(const scv::MouseEvent &evt) {/**/}
void Label::onMouseUp(const scv::MouseEvent &evt) {/**/}
void Label::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void Label::onKeyUp(const scv::KeyEvent &evt) {/**/}
void Label::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void Label::onStringChange(void) {/**/}
void Label::onResizing(void) {/**/}
void Label::onDragging(void) {/**/}

void Label::createTexture( void ) {

}

} // namespace scv
