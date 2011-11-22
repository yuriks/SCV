#ifndef __SCV_CHECKBOX_H__
#define __SCV_CHECKBOX_H__

#include "StateButton.h"
#include "Label.h"

namespace scv {

class CheckBox : public StateButton, public Label {
public:
   ///////////////////////////////////////////////////////////
   CheckBox(const scv::Point &p1, bool state, const std::string &str);
   virtual ~CheckBox(void);
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   virtual void onValueChange(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setString(const std::string& str);
   ///////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

private:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_CHECKBOX_H__