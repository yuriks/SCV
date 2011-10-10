#ifndef __SCV_BUTTON_H__
#define __SCV_BUTTON_H__

#include "Label.h"
#include "StaticLabel.h"

namespace scv {

class Button : public Label {
public:
   ///////////////////////////////////////////////////////////
   Button(const scv::Point &p1, const scv::Point &p2, const std::string &str);
   Button(const scv::Point &p, unsigned int width, const std::string &str);
   Button(const scv::Point &p, const std::string &str);
   virtual ~Button(void);
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
   ///////////////////////////////////////////////////////////

   virtual void display(void);

protected:
   void createTexture(void);

};

} // namespace scv

#endif // __SCV_BUTTON_H__