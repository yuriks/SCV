/*!
\file       ComponentTexture.h
\brief      Implementation of a ComponentTexture.
\author     SCV Team
*/

#ifndef __SCV_COMPONENT_TEXTURE_H__
#define __SCV_COMPONENT_TEXTURE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Point.h"
#include "ColorRGBA.h"
#include "MatrixTemplate.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! The class texture of a component
   This class implements all texture operations to store the texture of the component.
   \ingroup internal
 */

class ComponentTexture {
public:
   ComponentTexture(GLsizei width, GLsizei height);
   virtual ~ComponentTexture(void);

   inline void setTextureEnvMode(GLfloat param) {
      _textureEnvMode = param;
   }

   //initializes the current ComponentTexture texture
   inline void enable(void) {
      glBindTexture(GL_TEXTURE_2D, _textureId);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, _textureEnvMode);
   }

   inline void disable(void) {
	  //disables de current texture
	  glBindTexture(GL_TEXTURE_2D, 0);
   }

   inline GLsizei getWidth(void) const {
      return _textureSize[0];
   }
   inline GLsizei getHeight(void) const {
      return _textureSize[1];
   }
   inline GLuint getTextureId(void) const {
      return _textureId;
   }

   void display(void);

   void display(const int translateX, const int translateY, GLuint clipX, GLuint clipY, GLsizei clipWidth, GLsizei clipHeight);

   void display(const Point &translate, int id);
   void display(const int translateX, const int translateY, int id);

   void display(const Point &translate, int id, const Point &textSize);
   void display(const int translateX, const int translateY, int id, const int textSizeX, const int textSizeY);

   int addTexture(const Point &textCoords, MatrixTemplate<ColorRGBA> clip);
   int addTexture(const Point &textCoords, unsigned int w, unsigned int h, const unsigned char* data);
   int addTexture(const Point &textCoords, ColorRGBA color);
   void clearTextureIds(void);
   int addTextureId(const Point &textCoords, unsigned int w, unsigned int h);
   void setTexture(const Point &textCoords, MatrixTemplate<ColorRGBA> clip, int id);
   void createTexture(void);

private:
   GLuint _textureId;
   GLsizei _textureSize[2]; // width, height
   GLfloat _textureEnvMode;

   MatrixTemplate<ColorRGBA> *_texture;
   std::vector<Point> _textCoords;
   std::vector<Point> _textSize;
};

inline void ComponentTexture::display(const int translateX, const int translateY, int id) {
   display(Point(translateX, translateY), id);
}

inline void ComponentTexture::display(const int translateX, const int translateY, int id, const int textSizeX, const int textSizeY) {
   display(Point(translateX, translateY), id, Point(textSizeX, textSizeY));
}

} // namespace scv

#endif // __SCV_COMPONENT_TEXTURE_H__
