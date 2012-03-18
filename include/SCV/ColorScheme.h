/*!
\file       ColorScheme.h
\brief
\author     SCV Team
*/

#ifndef __SCV_COLOR_SCHEME_H__
#define __SCV_COLOR_SCHEME_H__

#include "Singleton.h"
#include "Color4f.h"

namespace scv {

/*! Functionality to customize SCV component color themes.

Since it's a Singleton class, it must be acessed via getInstance().

%Example: \code
   scv::ColorScheme::getInstance()->loadScheme(scv::ColorScheme::scvDefault);
\endcode
*/
class ColorScheme : public Singleton<ColorScheme> {
friend class Singleton<ColorScheme>;
public:
   //! Possible color values that can be customized.
   enum Target {
      CURSOR,          //!< SCV cursor
      TEXT,            //!< Text color
      TEXTSELECTION,   //!< Color of text selection rectangle
      TEXTSELECTED,    //!< Color of selected text
      BACKGROUND,      //!< Main window background
      MENUBAR,         //!< widget
      PROGRESSBAR,     //!< ProgressBar widget
      SEPARATOR,       //!< Separator widget
      TEXTFIELD,       //!< TextField widget
      CONTEXTMENU,     //!< Context menus
      CONTEXTMENUFONT, //!< Context menu text
      PANEL,           //!< Panel background
      SCROLLPANEL,     //!< Scrollable panel background
      MAINCOMPONENTS,  // if not specified like a special widget
      OVERCOMPONENTS,  // if not specified like a special widget
      HOLDCOMPONENTS,  // if not specified like a special widget
      FONT,            //!< General text
      s_nComponents    //!< Total number of color settings
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

   void loadScheme(ColorScheme::SchemeStyle style);

   void setColor(ColorScheme::Target target, const Color4f &color);
   const Color4f& getColor(ColorScheme::Target target) const;

   void applyColor(const Color4f &color);
   void applyColor(ColorScheme::Target target);
   void applyColor(ColorScheme::Target target, float w);

   void applyDefaultModulate();

private:
   ColorScheme();

   Color4f _pColors[s_nComponents];
   const Color4f _defaultModulateColor;
};

} // namespace scv

#endif // __SCV_COLOR_SCHEME_H__