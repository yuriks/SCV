/*!
\file       FontTahoma.h
\brief      Implementation of the Tahoma Font.
\author     SCV Team
*/

#ifndef __SCV_FONT_TAHOMA_H__
#define __SCV_FONT_TAHOMA_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "ComponentTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! FontTahoma Class
* \ingroup internal
*/

class FontTahoma : public Singleton<FontTahoma> {
friend class Singleton<FontTahoma>;

public:
   inline int getStringLength(const std::string &str) const {
      unsigned int stringLength = 0;
      for (unsigned int i = 0; i < str.size(); i++)
         stringLength += getCharWidth(str[i]);
      return stringLength;
   }

   inline int getCharWidth(unsigned char character) const {
      return (character == ' ')? s_spaceSize : s_charactersWidth[character];
   }

   inline int getHeight(void) const {
      return s_height;
   }

   inline int getWidth(void) const {
      return s_width;
   }

   inline ComponentTexture* getTexture(void) const {
      return _cTexture;
   }



private:
   FontTahoma(void);
   void genTexture(void);

   ComponentTexture *_cTexture;

   static const int s_height;
   static const int s_width;
   static const int s_spaceSize;

   static const unsigned int s_charactersWidth[256];
};

} // namespace scv

#endif // __SCV_FONT_TAHOMA_H__