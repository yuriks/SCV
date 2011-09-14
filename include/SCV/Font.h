/*!
\file       Font.h
\brief      Implementation of the SCV Font.
\author     SCV Team
*/

#ifndef __SCV_FONT_H__
#define __SCV_FONT_H__

#include <string>

namespace scv {

/*! Font Class
* \ingroup internal
*/

class Font {
public:
   Font(void* glFont);

   unsigned int getFontHeight(void) const;
   unsigned int getCharWidth(int character) const;
   unsigned int getStringLength(const std::string &str) const;

   void *getFont(void) const;
protected:

private:
   unsigned int _height;
   void *_pGLFont;
};

} // namespace scv

#endif // __SCV_FONT_H__