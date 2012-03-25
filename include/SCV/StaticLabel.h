/*!
\file       StaticLabel.h
\brief      Implementation of a StaticLabel.
\author     SCV Team
*/

#ifndef __SCV_STATIC_LABEL_H__
#define __SCV_STATIC_LABEL_H__

#include "FontTahoma.h"
#include "Color4f.h"
#include "ColorScheme.h"

namespace scv {

namespace StaticLabel {

   void display(int x, int y, const std::string &label, 
      const Color4f &color = ColorScheme::getInstance()->getColor(ColorScheme::FONT));

   void display(const Point &translate, const std::string &label, 
      const Color4f &color = ColorScheme::getInstance()->getColor(ColorScheme::FONT));

   void display(int x, int y, const std::string &label, int selectStart, int selectEnd, 
      const Color4f &textColor = ColorScheme::getInstance()->getColor(ColorScheme::FONT),
      const Color4f &selectedTextColor = ColorScheme::getInstance()->getColor(ColorScheme::TEXTSELECTED),
      const Color4f &selectionColor = ColorScheme::getInstance()->getColor(ColorScheme::TEXTSELECTION));

   void display(const Point &translate, const std::string &label, int selectStart, int selectEnd, 
      const Color4f &textColor = ColorScheme::getInstance()->getColor(ColorScheme::FONT),
      const Color4f &selectedTextColor = ColorScheme::getInstance()->getColor(ColorScheme::TEXTSELECTED),
      const Color4f &selectionColor = ColorScheme::getInstance()->getColor(ColorScheme::TEXTSELECTION));

} // namespace StaticLabel

} //namespace scv

#endif //__SCV_STATIC_LABEL_H__