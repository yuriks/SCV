/*!
\file       Separator.h
\brief      Implementation of a Separator widget.
\author     SCV Team
*/

#ifndef __SCV_SEPARATOR_H__
#define __SCV_SEPARATOR_H__

#ifndef DOXYGEN_SKIP_THIS
#include "MatrixTemplate.h"
#include "ComponentWithTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A line to separate groups of components.
 * \ingroup widgets
 */

class Separator : public ComponentWithTexture {
public:

   enum orientation {
      horizontal,
      vertical
   };

   //! Constructor
   /*!
   \param p1 The upper left corner of the component.
   \param align Separator orientation.
   \param size Length of the component.
   */
   Separator(const scv::Point &p1, Separator::orientation align, unsigned int size);


   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   //! Gets the separator orientation
   Separator::orientation getAlign(void);


   virtual void display(void);

private:

   Separator::orientation _align;
   void createTexture(void);
};

} // namespace scv


#endif // __SCV_SEPARATOR_H__