#ifndef __SCV_CHECKBOX_H__
#define __SCV_CHECKBOX_H__

#include "StateButton.h"
#include "Label.h"

namespace scv {

class CheckBox : public StateButton, public Label {
public:
   CheckBox(const scv::Point &p1, bool state, const std::string &str);

   virtual void onValueChange(void) {}

   void setString(const std::string& str);
   
   void processMouse(const scv::MouseEvent &evt);

   virtual void display(void);

private:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_CHECKBOX_H__