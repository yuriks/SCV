#include "stdafx.h"
#include "ComponentTexture.h"

#include <cstring>

namespace scv {

namespace {

inline void tex_coord_pix(GLuint x, GLuint y, GLsizei width, GLsizei height) {
   glTexCoord2f(float(x)/width, float(y)/height);
}

}

// Arredonda um numero para a proxima potencia de 2.
int ceil_pot2(int x)
{
   int num_bits = 0;
   int max_bit;

   int t = x;
   for (int i = 0; t != 0; ++i) {
      if (t & 1) {
         ++num_bits;
         max_bit = i;
      }
      t >>= 1;
   }

   if (num_bits == 0) {
      return 0;
   } else if (num_bits == 1) {
      return x;
   } else {
      return 1 << (max_bit + 1);
   }
}

ComponentTexture::ComponentTexture(GLsizei width, GLsizei height) {
   width = ceil_pot2(width);
   height = ceil_pot2(height);

   _textureId = 0;
   _textureSize[0] = width;
   _textureSize[1] = height;

   _textureEnvMode = GL_REPLACE;

   _texture = new MatrixTemplate<ColorRGBA>(width, height, ColorRGBA(0,0,0,0));
}

ComponentTexture::~ComponentTexture(void) {
   if (_textureId != 0) glDeleteTextures(1, &_textureId);
}

void ComponentTexture::display(void) {
   glBegin(GL_QUADS);
   // 0,0
   glTexCoord2i(0, 0);
   glVertex2i(0, 0);

   // 0,1
   glTexCoord2i(0, 1);
   glVertex2i(0, _textureSize[1]);

   // 1,1
   glTexCoord2i(1, 1);
   glVertex2i(_textureSize[0], _textureSize[1]);

   // 1,0
   glTexCoord2i(1, 0);
   glVertex2i(_textureSize[0], 0);

   glEnd();

}

void ComponentTexture::display(const int translateX, const int translateY, GLuint clipX, GLuint clipY, GLsizei clipWidth, GLsizei clipHeight) {
   const GLsizei w = _textureSize[0];
   const GLsizei h = _textureSize[1];

   glBegin(GL_QUADS);

   // 0,0
   tex_coord_pix(clipX, clipY, w, h);
   glVertex2i(translateX, translateY);

   // 0,1
   tex_coord_pix(clipX, clipY + clipHeight, w, h);
   glVertex2i(translateX, translateY + clipHeight);

   // 1,1
   tex_coord_pix(clipX + clipWidth, clipY + clipHeight, w, h);
   glVertex2i(translateX + clipWidth, translateY + clipHeight);

   // 1,0
   tex_coord_pix(clipX + clipWidth, clipY, w, h);
   glVertex2i(translateX + clipWidth, translateY);

   glEnd();

}


void ComponentTexture::display(const Point &translate, int id) {
   const GLsizei w = _textureSize[0];
   const GLsizei h = _textureSize[1];

   glBegin(GL_QUADS);
   // 0,0
   tex_coord_pix(_textCoords[id].x, _textCoords[id].y, w, h);
   glVertex2i(translate.x, translate.y);

   // 0,1
   tex_coord_pix(_textCoords[id].x, _textCoords[id].y + _textSize[id].y, w, h);
   glVertex2i(translate.x, translate.y + _textSize[id].y);

   // 1,1
   tex_coord_pix(_textCoords[id].x + _textSize[id].x, _textCoords[id].y + _textSize[id].y, w, h);
   glVertex2i(translate.x + _textSize[id].x, translate.y + _textSize[id].y);

   // 1,0
   tex_coord_pix(_textCoords[id].x + _textSize[id].x, _textCoords[id].y, w, h);
   glVertex2i(translate.x + _textSize[id].x, translate.y);

   glEnd();

}

void ComponentTexture::display(const Point &translate, int id, const Point &textSize) {
   const GLsizei w = _textureSize[0];
   const GLsizei h = _textureSize[1];

   glBegin(GL_QUADS);
   // 0,0
   tex_coord_pix(_textCoords[id].x, _textCoords[id].y, w, h);
   glVertex2i(translate.x, translate.y);

   // 0,1
   tex_coord_pix(_textCoords[id].x, _textCoords[id].y + _textSize[id].y, w, h);
   glVertex2i(translate.x, translate.y + textSize.y);

   // 1,1
   tex_coord_pix(_textCoords[id].x + _textSize[id].x, _textCoords[id].y + _textSize[id].y, w, h);
   glVertex2i(translate.x + textSize.x, translate.y + textSize.y);

   // 1,0
   tex_coord_pix(_textCoords[id].x + _textSize[id].x, _textCoords[id].y, w, h);
   glVertex2i(translate.x + textSize.x, translate.y);

   glEnd();

}

int ComponentTexture::addTexture(const Point &textCoords, MatrixTemplate<ColorRGBA> clip) {
   for (int l = 0; l < clip.getHeight(); l++) {
      std::memcpy(&_texture->get(textCoords.y + l, textCoords.x), &clip.get(l, 0), clip.getWidth() * sizeof(ColorRGBA));
   }

   return addTextureId(textCoords, clip.getWidth(), clip.getHeight());
}

int ComponentTexture::addTexture(const Point &textCoords, ColorRGBA color) {
   _texture->get(textCoords.y, textCoords.x) = color;

   return addTextureId(textCoords, 1, 1);
}

int ComponentTexture::addTexture(const Point &textCoords, unsigned int w, unsigned int h, const unsigned char* data) {
   for (int y = 0; y < h; ++y) {
      std::memcpy(&_texture->get(textCoords.y + y, textCoords.x), &data[y*(w*4)], w * sizeof(ColorRGBA));
   }

   return addTextureId(textCoords, w, h);
}

void ComponentTexture::clearTextureIds(void) {
   _textCoords.clear();
   _textSize.clear();
}

int ComponentTexture::addTextureId(const Point &textCoords, unsigned int w, unsigned int h) {
   _textCoords.push_back(textCoords);
   _textSize.push_back(Point(w, h));
   return _textCoords.size() - 1;
}

void ComponentTexture::setTexture(const Point &textCoords, MatrixTemplate<ColorRGBA> clip, int id) {
   for (int l = 0; l < _textSize[id].y; l++) {
      std::memcpy(&_texture->get(_textCoords[id].y + l, _textCoords[id].x), &clip.get(l, 0), _textSize[id].x * sizeof(ColorRGBA));
   }
}

void ComponentTexture::createTexture(void) {
   if (_texture == NULL) return;

   glEnable(GL_TEXTURE_2D);
   glGenTextures(1, &_textureId);

   glBindTexture  (GL_TEXTURE_2D, _textureId);

   //if (kernel->getFilterType()==Kernel::linear) {
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   //} else {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   //}
   glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGBA8, _textureSize[0], _textureSize[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, &_texture->getData()[0]);

   glBindTexture(GL_TEXTURE_2D, 0);

   delete _texture;
   _texture = NULL;
}

} // namespace scv
