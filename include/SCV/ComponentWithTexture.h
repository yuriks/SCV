/*!
\file       ComponentWithTexture.h
\brief      Implementation of a Component With Texture.
\author     SCV Team
*/

#ifndef __SCV_COMPONENT_WITH_TEXTURE_H__
#define __SCV_COMPONENT_WITH_TEXTURE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "SCVObject.h"
#include "ComponentTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class Kernel;

/*! A base class of a component with texture.
 \ingroup internal
 */

class ComponentWithTexture : public SCVObject {
friend class Kernel;
public:

   /************************************************************************/
   /* Constructors                                                         */
   /************************************************************************/
   ComponentWithTexture(const scv::Point &p1, const scv::Point &p2);
   virtual ~ComponentWithTexture(void);

   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;
   virtual void onMouseHold(const scv::MouseEvent &evt) = 0;
   virtual void onMouseOver(const scv::MouseEvent &evt) = 0;
   virtual void onMouseUp(const scv::MouseEvent &evt) = 0;
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;
   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;
   virtual void onKeyUp(const scv::KeyEvent &evt) = 0;
   virtual void onResizing(void) = 0;
   virtual void onDragging(void) = 0;

   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);
   virtual void setVisible(bool state);

   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   virtual void display(void) = 0;

   virtual int getWidth(void) const;
   virtual int getHeight(void) const;
   virtual void setWidth(const int width);
   virtual void setHeight(const int height);
   virtual void setRelativePosition(const Point &position);

protected:
   /*! Called to create the texture of the component.
    * This should only be re-implemented if you're creating a new type of component.
    */
   virtual void createTexture(void) = 0;
   ComponentTexture *_cTexture;
};

} // namespace scv

#endif // __SCV_COMPONENT_WITH_TEXTURE_H__
