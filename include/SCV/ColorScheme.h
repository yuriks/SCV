/*!
\file       ColorScheme.h
\brief
\author     SCV Team
*/

#ifndef __SCV_COLOR_SCHEME_H__
#define __SCV_COLOR_SCHEME_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "Color4f.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

//! Interface to change colors from SCV components like widgets and font.

/*!
Like a Singleton class, must be called by getInstance().
Example: scv::ColorScheme::getInstance()->loadScheme(scv::ColorScheme::scvDefault);
*/
class ColorScheme : public Singleton<ColorScheme> {
friend class Singleton<ColorScheme>;
public:
   //! SCV components that you can apply color schemes
   enum target { // if added a component refresh the variable 's_nComponents'
      cursor,          // scv cursor
      textSelection,   // color of text selection
      textSelected,    // color of a selected text
      background,      // scv background
      menuBar,         // widget
      progressBar,     // widget
      separator,       // widget
      textField,       // widget
      contextMenu,     // widget
      contextMenuFont, // widget
      panel,           // widget
      scrollPanel,     // widget
      mainComponents,  // if not specified like a special widget
      overComponents,  // if not specified like a special widget
      holdComponents,  // if not specified like a special widget
      font             // font
   };

   //! Predefined color schemes
   enum schemeStyle {
      scvDefault,
      warcraft,
      windows,
      osx,
      clean
   };

   //! Load a predefined SCV color scheme
   void loadScheme(ColorScheme::schemeStyle style);

   /*!
   Set a color to a component.
   \param target SCV component from 'enum target'.
   \param color New color of component
   */
   void setColor(ColorScheme::target target, const Color4f &color);

   //! \return SCV component color.
   const Color4f& getColor(ColorScheme::target target) const;

   //! Restrict function. Not must be called.
   void applyColor(ColorScheme::target target);

   //! Restrict function. Not must be called.
   void applyColor(ColorScheme::target target, float w);

   //! Restrict function. Not must be called.
   void applyDefaultModulate(void);

private:
   ColorScheme(void);
   ~ColorScheme(void);

   static const int s_nComponents = 16;
   Color4f *_pColors[s_nComponents];
   const Color4f _defaultModulateColor;
};

} // namespace scv

#endif // __SCV_COLOR_SCHEME_H__