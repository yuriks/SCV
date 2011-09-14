/*!
\file       ComponentWithoutTexture.h
\brief      Implementation of a Component Without Texture.
\author     SCV Team
*/

#ifndef __SCV_COMPONENT_WITHOUT_TEXTURE_H__
#define __SCV_COMPONENT_WITHOUT_TEXTURE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ComponentInterface.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A base class of a component without texture.
 \ingroup internal
 */

class ComponentWithoutTexture : public ComponentInterface {
public:


   ComponentWithoutTexture(const scv::Point &p1, const scv::Point &p2);
   virtual ~ComponentWithoutTexture(void);


   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;
   virtual void onMouseHold(const scv::MouseEvent &evt) = 0;
   virtual void onMouseOver(const scv::MouseEvent &evt) = 0;
   virtual void onMouseUp(const scv::MouseEvent &evt) = 0;
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;
   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;
   virtual void onKeyUp(const scv::KeyEvent &evt) = 0;
   virtual void onResizing(void) = 0;
   virtual void onDragging(void) = 0;

   /*! This function is the rendering function of this abstract component.
       This function is called ever after the update.
   */
   virtual void render(void) = 0;
   /*! This function is the update function of this abstract component.
       This function is called ever before the render.
   */
   virtual void update(void) = 0;
   void display(void);

protected:

private:
};

} // namespace scv


#endif // __SCV_COMPONENT_WITHOUT_TEXTURE_H__