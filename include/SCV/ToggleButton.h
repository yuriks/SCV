#ifndef __SCV_TOGGLE_BUTTON_H__
#define __SCV_TOGGLE_BUTTON_H__

#include "StateButton.h"
#include "Button.h"

namespace scv {

class ToggleButton : public StateButton, public Button  {
public:
   ToggleButton(const scv::Point &p1, const scv::Point &p2, bool state, const std::string &str);
   ToggleButton(const scv::Point &p1, unsigned int width, bool state, const std::string &str);
   ToggleButton(const scv::Point &p1, bool state, const std::string &str);
   virtual ~ToggleButton(void);

   virtual void onValueChange(void);

   virtual void display(void);

protected:
   void processMouse(const scv::MouseEvent &evt);
};

} // namespace scv

#endif // __SCV_TOGGLE_BUTTON_H__