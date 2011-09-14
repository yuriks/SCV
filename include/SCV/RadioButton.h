/*!
\file       RadioButton.h
\brief      Implementation of a RadioButton widget.
\author     SCV Team
*/

#ifndef __SCV_RADIO_BUTTON_H__
#define __SCV_RADIO_BUTTON_H__

#ifndef DOXYGEN_SKIP_THIS
#include "StateButton.h"
#include "Label.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A selectable RadioButton, similar to a CheckBox. However, unlike a
 * CheckBox, a RadioButton can't be unselected, and is designed to be used
 * on non-optional, mutually-exclusive choices, inside a ButtonGroup.
 * \ingroup widgets
 */
class RadioButton : public StateButton, public Label  {
public:

   /*! Constructor
    \param p1 The upper left corner of the component.
    \param state The state of the RadioButton.
    \param str The name of the RadioButto.n
    */
   RadioButton(const scv::Point &p1, bool state, const std::string &str);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);
   virtual void onValueChange(void);

   /*! Set a new name to the RadioButton.*/
   void setString(const std::string& str);

   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   virtual void display(void);

private:

   void createTexture(void);
};

} // namespace scv

#endif // __SCV_RADIO_BUTTON_H__