#include "stdafx.h"
#include "ColorScheme.h"

#include "ColorRGBA.h"

#include <GL/glew.h>

namespace scv {

ColorScheme::ColorScheme(void) : _defaultModulateColor(1.f, 1.f, 1.f, 1.f) {
   std::memset(_pColors, NULL, sizeof(Color4f*) * s_nComponents);
   loadScheme(scvDefault);
}

ColorScheme::~ColorScheme(void) {
   for (int i = 0; i < s_nComponents; i++)
      delete _pColors[i];
}

void ColorScheme::loadScheme(ColorScheme::schemeStyle style) {
   switch (style) {
   case scvDefault:
      _pColors[cursor]          = new Color4f(ColorRGBA(255, 255,   0, 255));
      _pColors[textSelection]   = new Color4f(ColorRGBA( 96, 176, 255, 200));
      _pColors[textSelected]    = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[background]      = new Color4f(ColorRGBA( 50,  50,  50, 255));
      _pColors[menuBar    ]     = new Color4f(ColorRGBA(189, 199, 216, 255));
      _pColors[progressBar]     = new Color4f(ColorRGBA(  0,   0, 255, 200));
      _pColors[separator]       = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[textField]       = new Color4f(ColorRGBA( 90,  90,  90, 255));
      _pColors[contextMenu]     = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[contextMenuFont] = new Color4f(ColorRGBA(  0,   0,   0, 255));
      _pColors[panel]           = new Color4f(ColorRGBA( 80,  80,  80, 100));
      _pColors[scrollPanel]     = new Color4f(ColorRGBA(200, 200, 200, 255));
      _pColors[mainComponents]  = new Color4f(ColorRGBA( 51,  97, 136, 255));
      _pColors[overComponents]  = new Color4f(ColorRGBA(  0, 220, 255, 70));
      _pColors[holdComponents]  = new Color4f(ColorRGBA(116,   0, 163, 255));
      _pColors[font]            = new Color4f(ColorRGBA(255, 255, 255, 255));
      break;
   case windows:
      break;
   case osx:
	   _pColors[cursor]          = new Color4f(ColorRGBA(  0,   0,   0, 255));
	   _pColors[textSelection]   = new Color4f(ColorRGBA( 50, 104, 166, 200));
	   _pColors[textSelected]    = new Color4f(ColorRGBA(255, 255, 255, 255));
	   _pColors[background]      = new Color4f(ColorRGBA( 33,  59, 116, 255));
	   _pColors[menuBar    ]     = new Color4f(ColorRGBA(240, 240, 240, 255));
	   _pColors[progressBar]     = new Color4f(ColorRGBA(106, 168, 229, 200));
	   _pColors[separator]       = new Color4f(ColorRGBA(115, 115, 115, 255));
	   _pColors[textField]       = new Color4f(ColorRGBA(255, 255, 255, 255));
	   _pColors[contextMenu]     = new Color4f(ColorRGBA(240, 240, 240, 255));
	   _pColors[contextMenuFont] = new Color4f(ColorRGBA(  0,   0,   0, 255));
	   _pColors[panel]           = new Color4f(ColorRGBA( 49, 100, 155, 100));
	   _pColors[scrollPanel]     = new Color4f(ColorRGBA( 88, 139, 204, 255));
	   _pColors[mainComponents]  = new Color4f(ColorRGBA(210, 210, 210, 255));
	   _pColors[overComponents]  = new Color4f(ColorRGBA(  0, 220, 255, 70));
	   _pColors[holdComponents]  = new Color4f(ColorRGBA(116,   0, 163, 255));
	   _pColors[font]            = new Color4f(ColorRGBA(  0,   0,   0, 255));
      break;
   case warcraft:
      _pColors[cursor]          = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[textSelection]   = new Color4f(ColorRGBA( 70, 164,  76, 200));
      _pColors[textSelected]    = new Color4f(ColorRGBA(  0,   0,   0, 255));
      _pColors[background]      = new Color4f(ColorRGBA( 50,  50,  50, 255));
      _pColors[menuBar    ]     = new Color4f(ColorRGBA(223,  47,   8, 255));
      _pColors[progressBar]     = new Color4f(ColorRGBA(  0,  55,   0, 200));
      _pColors[separator]       = new Color4f(ColorRGBA(  5,  70,   0, 255));
      _pColors[textField]       = new Color4f(ColorRGBA( 63, 101,  61, 255));
      _pColors[contextMenu]     = new Color4f(ColorRGBA( 63,  94,  53, 255));
      _pColors[contextMenuFont] = new Color4f(ColorRGBA(219, 157,   0, 255));
      _pColors[panel]           = new Color4f(ColorRGBA( 63,  94,  53, 100));
      _pColors[scrollPanel]     = new Color4f(ColorRGBA(200, 200, 200, 255));
      _pColors[mainComponents]  = new Color4f(ColorRGBA(  5, 130,  15, 255));
      _pColors[overComponents]  = new Color4f(ColorRGBA(240, 240, 255, 150));
      _pColors[holdComponents]  = new Color4f(ColorRGBA(116,   0, 163, 255));
      _pColors[font]            = new Color4f(ColorRGBA(219, 157,   0, 255));
      break;
   case clean:
      _pColors[cursor]          = new Color4f(ColorRGBA(  0,   0,   0, 255));
      _pColors[textSelection]   = new Color4f(ColorRGBA( 96, 176, 255, 200));
      _pColors[textSelected]    = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[background]      = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[menuBar    ]     = new Color4f(ColorRGBA(189, 199, 216, 255));
      _pColors[progressBar]     = new Color4f(ColorRGBA(100, 100, 255, 200));
      _pColors[separator]       = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[textField]       = new Color4f(ColorRGBA(200, 200, 200, 255));
      _pColors[contextMenu]     = new Color4f(ColorRGBA(255, 255, 255, 255));
      _pColors[contextMenuFont] = new Color4f(ColorRGBA(  0,   0,   0, 255));
      _pColors[panel]           = new Color4f(ColorRGBA( 80,  80,  80, 200));
      _pColors[scrollPanel]     = new Color4f(ColorRGBA(200, 200, 200, 255));
      _pColors[mainComponents]  = new Color4f(ColorRGBA(151, 197, 236, 255));
      _pColors[overComponents]  = new Color4f(ColorRGBA(  0, 220, 255, 70));
      _pColors[holdComponents]  = new Color4f(ColorRGBA(116,   0, 163, 255));
      _pColors[font]            = new Color4f(ColorRGBA(  0,   0,   0, 255));
      break;
   default:
      loadScheme(scvDefault);
      break;
   }
}

void ColorScheme::setColor(ColorScheme::target target, const Color4f &color) {
   (*_pColors[target]) = color;
}

const Color4f& ColorScheme::getColor(ColorScheme::target target) const {
   return (*_pColors[target]);
}

void ColorScheme::applyColor(ColorScheme::target target) {
   if (target == ColorScheme::background) {
      glClearColor((*_pColors[target])[0], (*_pColors[target])[1], (*_pColors[target])[2], (*_pColors[target])[3]);
   } else {
      glColor4fv(&(*_pColors[target])[0]);
   }
}

void ColorScheme::applyColor(ColorScheme::target target, float w) {
   if (target == ColorScheme::background) {
      glClearColor((*_pColors[target] + w)[0], (*_pColors[target] + w)[1], (*_pColors[target] + w)[2], (*_pColors[target])[3]);
   } else {
      glColor3fv(&(*_pColors[target] + w)[0]);
   }
}

void ColorScheme::applyDefaultModulate(void) {
   glColor4fv(&_defaultModulateColor[0]);
}

} // namespace scv