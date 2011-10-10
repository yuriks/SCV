#ifndef __SCV_COLOR_SCHEME_H__
#define __SCV_COLOR_SCHEME_H__

#include "Singleton.h"
#include "Color4f.h"

namespace scv {

class ColorScheme : public Singleton<ColorScheme> {
friend class Singleton<ColorScheme>;
public:
   ///////////////////////////////////////////////////////////
   enum Target {
      CURSOR,
      TEXT,
      TEXTSELECTION,
      TEXTSELECTED,
      BACKGROUND,
      MENUBAR,
      PROGRESSBAR,
      SEPARATOR,
      TEXTFIELD,
      CONTEXTMENU,
      CONTEXTMENUFONT,
      PANEL,
      SCROLLPANEL,
      MAINCOMPONENTS,
      OVERCOMPONENTS,
      HOLDCOMPONENTS,
      FONT
   };

   //! Predefined color schemes
   enum SchemeStyle {
      SCVDEFAULT,
      WARCRAFT,
      WINDOWS,
      OSX,
      CLEAN
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void loadScheme(ColorScheme::SchemeStyle style);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setColor(ColorScheme::Target target, const Color4f &color);
   const Color4f& getColor(ColorScheme::Target target) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void applyColor(const Color4f &color);
   void applyColor(ColorScheme::Target target);
   void applyColor(ColorScheme::Target target, float w);
   ///////////////////////////////////////////////////////////

   void applyDefaultModulate(void);

private:
   ///////////////////////////////////////////////////////////
   ColorScheme(void);
   ~ColorScheme(void);
   ///////////////////////////////////////////////////////////

   static const int s_nComponents = 17;
   Color4f *_pColors[s_nComponents];
   const Color4f _defaultModulateColor;
};

} // namespace scv

#endif // __SCV_COLOR_SCHEME_H__