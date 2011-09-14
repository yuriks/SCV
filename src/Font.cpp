#include "stdafx.h"
#include "Font.h"

#include <GL/glew.h>
#include <GL/glut.h>

namespace scv {

Font::Font(void* glFont) {
   if (glFont == GLUT_STROKE_ROMAN) {
      _pGLFont = GLUT_STROKE_ROMAN;
      _height = 12;
   } else if (glFont == GLUT_STROKE_MONO_ROMAN) {
      _pGLFont = GLUT_STROKE_MONO_ROMAN;
      _height = 12;
   } else if (glFont == GLUT_BITMAP_9_BY_15) {
      _pGLFont = GLUT_BITMAP_9_BY_15;
      _height = 15;
   } else if (glFont == GLUT_BITMAP_8_BY_13) {
      _pGLFont = GLUT_BITMAP_8_BY_13;
      _height = 13;
   } else if (glFont == GLUT_BITMAP_TIMES_ROMAN_10) {
      _pGLFont = GLUT_BITMAP_TIMES_ROMAN_10;
      _height = 10;
   } else if (glFont == GLUT_BITMAP_TIMES_ROMAN_24) {
      _pGLFont = GLUT_BITMAP_TIMES_ROMAN_24;
      _height = 24;
   } else if (glFont == GLUT_BITMAP_HELVETICA_10) {
      _pGLFont = GLUT_BITMAP_HELVETICA_10;
      _height = 10;
   } else if (glFont == GLUT_BITMAP_HELVETICA_12) {
      _pGLFont = GLUT_BITMAP_HELVETICA_12;
      _height = 12;
   } else if (glFont == GLUT_BITMAP_HELVETICA_18) {
      _pGLFont = GLUT_BITMAP_HELVETICA_18;
      _height = 18;
   } else { // default font
      _pGLFont = GLUT_BITMAP_HELVETICA_12;
      _height = 12;
   }
}

unsigned int Font::getFontHeight(void) const {
   return _height;
}

unsigned int Font::getCharWidth(int character) const {
   return glutBitmapWidth(_pGLFont, character);
}

unsigned int Font::getStringLength(const std::string &str) const {
   return glutBitmapLength(_pGLFont, reinterpret_cast<const unsigned char*>(str.c_str()));
}

void *Font::getFont(void) const {
   return _pGLFont;
}


} // namespace scv