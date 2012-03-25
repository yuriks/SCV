/*!
\file       StateButton.h
\brief      Implementation of a StateButton.
\author     SCV Team
*/

#ifndef __SCV_STATEBUTTON_H__
#define __SCV_STATEBUTTON_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ButtonGroup.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A base class for toggleable widgets. */
class StateButton {
friend class ButtonGroup;
public:

   /************************************************************************/
   /* Constructors                                                         */
   /************************************************************************/
   StateButton(bool state);

   /************************************************************************/
   /* User Functions                                                       */
   /************************************************************************/
   bool getState(void) const;
   void setState(bool state);
   /*! Registers the widget in a button group. See the ButtonGroup docs for
    * more information.
    */
   void registerButtonGroup(ButtonGroup *buttonGroup);

   /************************************************************************/
   /* Restrict Functions                                                   */
   /************************************************************************/
   /*! Callback called when the widget's state changes.
    * \bug Called even when setState(bool) sets the state to the same value as before.
    */
   virtual void onValueChange(void) = 0;

private:

   bool _state;
   ButtonGroup *_buttonGroup;
};

} // namespace scv

#endif // __SCV_STATEBUTTON_H__