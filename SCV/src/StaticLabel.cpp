#include "stdafx.h"
#include "StaticLabel.h"

namespace scv {

namespace StaticLabel {

void display(int x, int y, const std::string &label, const Color4f &color) {
   display(Point(x, y), label, color);
}

void display(const Point &translate, const std::string &label, const Color4f &color) {
   static FontTahoma *font = FontTahoma::getInstance();
   static ComponentTexture *cTexture = font->getTexture();
   static ColorScheme *scheme = ColorScheme::getInstance();

   int strLength = 0;

   cTexture->enable();
   scheme->applyColor(color);
   for (int i = 0; i < label.size(); i++) {
      cTexture->display(translate.x + strLength, translate.y, label[i] * font->getWidth(), 0, 8, 15);
      strLength += font->getCharWidth(label[i]);
   }
   cTexture->disable();
}

void display(int x, int y, const std::string &label, int selectStart, int selectEnd, const Color4f &textColor, const Color4f &selectedTextColor, const Color4f &selectionColor) {
   display(Point(x, y), label, selectStart, selectEnd, textColor, selectedTextColor, selectionColor);
}

void display(const Point &translate, const std::string &label, int selectStart, int selectEnd, const Color4f &textColor, const Color4f &selectedTextColor, const Color4f &selectionColor) {
   static FontTahoma *font = FontTahoma::getInstance();
   static ComponentTexture *cTexture = font->getTexture();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (selectStart > selectEnd)
      std::swap(selectStart, selectEnd);

   int strLength = 0;
   cTexture->enable();
   for (int i = 0; i < label.size(); i++) {
      if (label[i] != '\n') {
         // select
         if (selectStart != selectEnd && i > selectStart && i <= selectEnd) {
            scheme->applyColor(selectionColor);
            cTexture->display(strLength + translate.x, translate.y - 2, 1,font->getCharWidth(label[i]), font->getHeight() + 1);
            scheme->applyColor(selectedTextColor);
         } else {
            scheme->applyColor(textColor);
         }

         // string
         cTexture->display(translate.x + strLength, translate.y, label[i] * font->getWidth(), 0, 8, 15);
      }
      strLength += font->getCharWidth(label[i]);
   }
   cTexture->disable();
}

} // namespace StaticLabel

} //namespace scv