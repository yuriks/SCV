/*!
\file       CheckBox.h
\brief      Implementation of a CheckBox widget.
\author     SCV Team
*/

#ifndef __SCV_CHECKBOX_H__
#define __SCV_CHECKBOX_H__

#ifndef DOXYGEN_SKIP_THIS
#include "StateButton.h"
#include "Label.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A toggleable CheckBox for selecting options. Unlike RadioButtons, it is not
 * recommended to use them with ButtonGroups.
 *
 * \ingroup widgets
 */
class CheckBox : public StateButton, public Label {
public:

   /*! Constructor
    \param p1 The upper left corner of the component.
    \param state The state of the checkbox.
    \param str The name of the checkbox.
    */
   CheckBox(const scv::Point &p1, bool state, const std::string &str);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   virtual void onValueChange(void);

   /*! Set a new name to the checkbox.*/
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

#endif // __SCV_CHECKBOX_H__