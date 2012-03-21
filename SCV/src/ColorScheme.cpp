#include "stdafx.h"
#include "ColorScheme.h"

#include "ColorRGBA.h"

namespace scv {

ColorScheme::ColorScheme() : _defaultModulateColor(1.f, 1.f, 1.f, 1.f) {
   loadScheme(SCVDEFAULT);
}

//! Load a predefined SCV color scheme
void ColorScheme::loadScheme(ColorScheme::SchemeStyle style) {
   switch (style) {
   case SCVDEFAULT:
      _pColors[CURSOR]          = Color4f::fromByte(255, 255,   0, 255);
      _pColors[TEXT]            = Color4f::fromByte(255, 255, 255, 255);
      _pColors[TEXTSELECTION]   = Color4f::fromByte( 96, 176, 255, 200);
      _pColors[TEXTSELECTED]    = Color4f::fromByte(255, 255, 255, 255);
      _pColors[BACKGROUND]      = Color4f::fromByte( 50,  50,  50, 255);
      _pColors[MENUBAR]         = Color4f::fromByte(214, 214, 214, 255);
      _pColors[PROGRESSBAR]     = Color4f::fromByte(  0,   0, 255, 200);
      _pColors[SEPARATOR]       = Color4f::fromByte(255, 255, 255, 255);
      _pColors[TEXTFIELD]       = Color4f::fromByte( 90,  90,  90, 255);
      _pColors[CONTEXTMENU]     = Color4f::fromByte(255, 255, 255, 255);
      _pColors[CONTEXTMENUFONT] = Color4f::fromByte(  0,   0,   0, 255);
      _pColors[PANEL]           = Color4f::fromByte( 49, 100, 155, 100);
      _pColors[SCROLLPANEL]     = Color4f::fromByte(200, 200, 200, 255);
      _pColors[MAINCOMPONENTS]  = Color4f::fromByte( 51,  97, 136, 255);
      _pColors[OVERCOMPONENTS]  = Color4f::fromByte(  0, 220, 255, 70);
      _pColors[HOLDCOMPONENTS]  = Color4f::fromByte(116,   0, 163, 255);
      _pColors[FONT]            = Color4f::fromByte(255, 255, 255, 255);
      break;
   case WINDOWS:
      break;
   case OSX:
	   _pColors[CURSOR]          = Color4f::fromByte(  0,   0,   0, 255);
      _pColors[TEXT]            = Color4f::fromByte(  0,   0,   0, 255);
	   _pColors[TEXTSELECTION]   = Color4f::fromByte( 50, 104, 166, 200);
	   _pColors[TEXTSELECTED]    = Color4f::fromByte(255, 255, 255, 255);
	   _pColors[BACKGROUND]      = Color4f::fromByte( 33,  59, 116, 255);
	   _pColors[MENUBAR]         = Color4f::fromByte(240, 240, 240, 255);
	   _pColors[PROGRESSBAR]     = Color4f::fromByte(106, 168, 229, 200);
	   _pColors[SEPARATOR]       = Color4f::fromByte(115, 115, 115, 255);
	   _pColors[TEXTFIELD]       = Color4f::fromByte(255, 255, 255, 255);
	   _pColors[CONTEXTMENU]     = Color4f::fromByte(240, 240, 240, 255);
	   _pColors[CONTEXTMENUFONT] = Color4f::fromByte(  0,   0,   0, 255);
	   _pColors[PANEL]           = Color4f::fromByte( 49, 100, 155, 100);
	   _pColors[SCROLLPANEL]     = Color4f::fromByte( 88, 139, 204, 255);
	   _pColors[MAINCOMPONENTS]  = Color4f::fromByte(210, 210, 210, 255);
	   _pColors[OVERCOMPONENTS]  = Color4f::fromByte(  0, 220, 255, 70);
	   _pColors[HOLDCOMPONENTS]  = Color4f::fromByte(116,   0, 163, 255);
	   _pColors[FONT]            = Color4f::fromByte(  0,   0,   0, 255);
      break;
   case WARCRAFT:
      _pColors[CURSOR]          = Color4f::fromByte(255, 255, 255, 255);
      _pColors[TEXT]            = Color4f::fromByte(255, 255, 255, 255);
      _pColors[TEXTSELECTION]   = Color4f::fromByte( 70, 164,  76, 200);
      _pColors[TEXTSELECTED]    = Color4f::fromByte(  0,   0,   0, 255);
      _pColors[BACKGROUND]      = Color4f::fromByte( 50,  50,  50, 255);
      _pColors[MENUBAR]         = Color4f::fromByte(223,  47,   8, 255);
      _pColors[PROGRESSBAR]     = Color4f::fromByte(  0,  55,   0, 200);
      _pColors[SEPARATOR]       = Color4f::fromByte(  5,  70,   0, 255);
      _pColors[TEXTFIELD]       = Color4f::fromByte( 63, 101,  61, 255);
      _pColors[CONTEXTMENU]     = Color4f::fromByte( 63,  94,  53, 255);
      _pColors[CONTEXTMENUFONT] = Color4f::fromByte(219, 157,   0, 255);
      _pColors[PANEL]           = Color4f::fromByte( 63,  94,  53, 100);
      _pColors[SCROLLPANEL]     = Color4f::fromByte(200, 200, 200, 255);
      _pColors[MAINCOMPONENTS]  = Color4f::fromByte(  5, 130,  15, 255);
      _pColors[OVERCOMPONENTS]  = Color4f::fromByte(240, 240, 255, 150);
      _pColors[HOLDCOMPONENTS]  = Color4f::fromByte(116,   0, 163, 255);
      _pColors[FONT]            = Color4f::fromByte(219, 157,   0, 255);
      break;
   case CLEAN:
      _pColors[CURSOR]          = Color4f::fromByte(  0,   0,   0, 255);
      _pColors[TEXT]            = Color4f::fromByte(255, 255, 255, 255);
      _pColors[TEXTSELECTION]   = Color4f::fromByte( 96, 176, 255, 200);
      _pColors[TEXTSELECTED]    = Color4f::fromByte(255, 255, 255, 255);
      _pColors[BACKGROUND]      = Color4f::fromByte(255, 255, 255, 255);
      _pColors[MENUBAR]         = Color4f::fromByte(189, 199, 216, 255);
      _pColors[PROGRESSBAR]     = Color4f::fromByte(100, 100, 255, 200);
      _pColors[SEPARATOR]       = Color4f::fromByte(255, 255, 255, 255);
      _pColors[TEXTFIELD]       = Color4f::fromByte(200, 200, 200, 255);
      _pColors[CONTEXTMENU]     = Color4f::fromByte(255, 255, 255, 255);
      _pColors[CONTEXTMENUFONT] = Color4f::fromByte(  0,   0,   0, 255);
      _pColors[PANEL]           = Color4f::fromByte( 80,  80,  80, 200);
      _pColors[SCROLLPANEL]     = Color4f::fromByte(200, 200, 200, 255);
      _pColors[MAINCOMPONENTS]  = Color4f::fromByte(151, 197, 236, 255);
      _pColors[OVERCOMPONENTS]  = Color4f::fromByte(  0, 220, 255,  70);
      _pColors[HOLDCOMPONENTS]  = Color4f::fromByte(116,   0, 163, 255);
      _pColors[FONT]            = Color4f::fromByte(  0,   0,   0, 255);
      break;
   default:
      loadScheme(SCVDEFAULT);
      break;
   }
}

/*! Sets a color value in the color scheme.
\param target Color scheme entry that should be modified.
\param color New color of component.
*/
void ColorScheme::setColor(ColorScheme::Target target, const Color4f &color) {
   _pColors[target] = color;
}

//! Returns component's current color in the color scheme.
const Color4f& ColorScheme::getColor(ColorScheme::Target target) const {
   return _pColors[target];
}

//! Prepares the graphics system to draw a component with the specified color. Should be called only by widget implementations.
void ColorScheme::applyColor(const Color4f &color) {
   glColor4fv(&color[0]);
}


//! Prepares to draw component with specified color target.
void ColorScheme::applyColor(ColorScheme::Target target) {
   if (target == ColorScheme::BACKGROUND) {
      glClearColor(_pColors[target][0], _pColors[target][1], _pColors[target][2], _pColors[target][3]);
   } else {
      glColor4fv(&_pColors[target][0]);
   }
}

//! Prepares to draw a component with the specified color target, brightened/darkened by the value w.
void ColorScheme::applyColor(ColorScheme::Target target, float w) {
   Color4f adjusted = _pColors[target] + w;
   if (target == ColorScheme::BACKGROUND) {
      glClearColor(adjusted[0], adjusted[1], adjusted[2], adjusted[3]);
   } else {
      glColor3fv(&adjusted[0]);
   }
}

void ColorScheme::applyDefaultModulate() {
   applyColor(_defaultModulateColor);
}

} // namespace scv