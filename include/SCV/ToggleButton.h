/*!
\file       ToggleButton.h
\brief      Implementation of a Button widget with two states.
\author     SCV Team
*/

#ifndef __SCV_TOGGLE_BUTTON_H__
#define __SCV_TOGGLE_BUTTON_H__

#ifndef DOXYGEN_SKIP_THIS
#include "StateButton.h"
#include "Button.h"
#endif DOXYGEN_SKIP_THIS

namespace scv {

/*! A simple Button with two states.
 *  \ingroup widgets
 */

class ToggleButton : public StateButton, public Button  {
public:
    //! Constructor
   /*!
   \param p1 The initial position of the component.
   \param p2 The final position of component.
   \param state The initial state of the button.
   \param str Name of the component.
   */
   ToggleButton(const scv::Point &p1, const scv::Point &p2, bool state, const std::string &str);
   //! Constructor
   /*!
   \param p1 The initial position of the component.
   \param width The width of the component.
   \param state The initial state of the button.
   \param str Name of the component.
   */
   ToggleButton(const scv::Point &p1, unsigned int width, bool state, const std::string &str);
   //! Constructor
   /*!
    This constructor automatically adjusts the component size based on name.
   \param p1 The initial position of the component.
   \param state The initial state of the button.
   \param str Name of the component.
   */
   ToggleButton(const scv::Point &p1, bool state, const std::string &str);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   //! Callback
   /*!
   This function is called when the component state is changed.
   */
   virtual void onValueChange(void);

   virtual void display(void);

protected:
   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
};

} // namespace scv

#endif // __SCV_TOGGLE_BUTTON_H__