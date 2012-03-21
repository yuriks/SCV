#include "stdafx.h"
#include "Label.h"
#include "Kernel.h"

namespace scv {

Label::Label(const scv::Point &p1, const scv::Point &p2, const std::string& str) : ComponentWithTexture(p1, p2) {
   _isHResizable = _isVResizable = false;
   _str = str;
   _type = LABEL;

   setMaximumSize(getPreferredSize());

   createTexture();
}

Label::Label(const scv::Point &p, const std::string& str) : ComponentWithTexture(p, Point(p.x + FontTahoma::getInstance()->getStringLength(str), p.y + 13)) {
   _isHResizable = _isVResizable = false;
   _str = str;
   _type = LABEL;

   setMaximumSize(getPreferredSize());

   createTexture();
}

Label::Label(const scv::Point &p, unsigned int width, const std::string& str) : ComponentWithTexture(p, Point(p.x + width, p.y + 13)) {
   _isHResizable = _isVResizable = false;
   _str = str;
   _type = LABEL;

   setMaximumSize(getPreferredSize());

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
   static FontTahoma *font = FontTahoma::getInstance();
   static ComponentTexture *cTexture = font->getTexture();
   static ColorScheme *scheme = ColorScheme::getInstance();

   int strLength = 0;
   Point currPosition = getAbsolutePosition();

   cTexture->enable();
   scheme->applyColor(ColorScheme::FONT);
   for (int i = 0; i < getString().size(); i++) {
      cTexture->display(currPosition.x + strLength, currPosition.y, getString()[i] * font->getWidth(), 0, 8, 15);
      strLength += font->getCharWidth(getString()[i]);
   }
   cTexture->disable();
}

} // namespace scv
