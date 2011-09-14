/*!
\file       Canvas.h
\brief      Implementation of a Canvas widget.
\author     SCV Team
*/

#ifndef __SCV_CANVAS_H__
#define __SCV_CANVAS_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ComponentWithoutTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A OpenGL Canvas Interface.
 * \ingroup widgets
 */

class Canvas : public ComponentWithoutTexture {
public:
   /*! Constructor
   \param p1 Initial point of the component.
   \param width Width of the component.
   \param height Height of the component.
   */
   Canvas(const scv::Point &p1, unsigned int width, unsigned int height);
   /*! Constructor
   \param p1 Initial point of the component.
   \param p2 Final point of the component.
   */
   Canvas(const scv::Point &p1, const scv::Point &p2);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onResizing(void);
   virtual void onDragging(void);

   virtual void update(void);
   virtual void render(void);

protected:
private:
};

} // namespace scv


#endif // __SCV_CANVAS_H__