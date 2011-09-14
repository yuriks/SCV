/*!
\file       Texture2D.h
\brief      Implementation of a texture object.
\author     SCV Team
*/

#ifndef __SCV_TEXTURE_2D_H__
#define __SCV_TEXTURE_2D_H__

#ifndef DOXYGEN_SKIP_THIS
#include "TextureInterface.h"
#include "MatrixTemplate.h"
#include "ColorRGBA.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! This class implements the functions to draw in the component textures.
*/

class Texture2D : public TextureInterface {
public:

   /************************************************************************/
   /* Draw functions                                                       */
   /************************************************************************/
   static void drawPoint(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p, const ColorRGBA& color);
   static void rect(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& color);
   static void rect(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& color, int thickness);
   static void rectFill(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& color);
   static void rectFill(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& colorBorder, const ColorRGBA& colorFill);
   static void line(MatrixTemplate<ColorRGBA>& matrix, Point p1, Point p2, const ColorRGBA& color);

};

} // namespace scv

#endif // __SCV_TEXTURE_2D_H__