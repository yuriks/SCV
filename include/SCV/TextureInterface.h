/*!
\file       TextureInterface.h
\brief      Implementation of a interface with OpenGL Texture.
\author     SCV Team
*/

#ifndef __SCV_TEXTURE_INTERFACE_H__
#define __SCV_TEXTURE_INTERFACE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Point.h"
#include "MatrixTemplate.h"
#include <GL/glew.h>
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! This class encapsulates OpenGL texture.
*/

class TextureInterface {
public:
   TextureInterface(void) {
      _textureId = 0;
      _textureEnvMode = GL_REPLACE;
      _textureSize[0] = _textureSize[1] = -1;
   }

   virtual ~TextureInterface() {
      if (_textureId != 0) {
         glDeleteTextures(1, &_textureId);
         _textureId = 0;
      }
   };

   virtual void display(const Point &translate) = 0;

   inline void setTextureEnvMode(GLfloat param) {
      _textureEnvMode = param;
   }

   inline GLuint getTextureId(void) const {
      return _textureId;
   }

   inline GLsizei getWidth(void) const {
      return _textureSize[0];
   }
   inline GLsizei getHeight(void) const {
      return _textureSize[1];
   }

protected:
   GLuint _textureId;
   GLsizei _textureSize[2]; // width, height
   GLfloat _textureEnvMode;
};

} // namespace scv

#endif // __SCV_TEXTURE_INTERFACE_H__