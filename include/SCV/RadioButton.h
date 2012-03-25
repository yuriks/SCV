/*!
\file       RadioButton.h
\brief      Implementation of a RadioButton.
\author     SCV Team
*/

#ifndef __SCV_RADIO_BUTTON_H__
#define __SCV_RADIO_BUTTON_H__

#include "StateButton.h"
#include "Label.h"

namespace scv {

class RadioButton : public StateButton, public Label  {
public:
   RadioButton(const scv::Point &p1, bool state, const std::string &str);

   virtual void onValueChange() {}
   
   void setString(const std::string& str);

   void processMouse(const scv::MouseEvent &evt);

   virtual void display(void);

private:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_RADIO_BUTTON_H__