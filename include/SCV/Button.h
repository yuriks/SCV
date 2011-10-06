/*!
\file       Button.h
\brief      Implementation of a Button widget.
\author     SCV Team
*/

#ifndef __SCV_BUTTON_H__
#define __SCV_BUTTON_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Label.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A command Button, made to execute an action when pressed.
 * \ingroup widgets
 */
class Button : public Label {
public:
   /*! Constructor
   \param p1 The upper left corner of the component.
   \param p2 The bottom right corner of the component.
   \param str The text in the button's label.
   */
   Button(const scv::Point &p1, const scv::Point &p2,  const std::string &str);
   /*! Constructor
   \param p The upper left corner of the component.
   \param width The width of the component.
   \param str The text in the button's label.
   */
   Button(const scv::Point &p, unsigned int width,  const std::string &str);
   /*! Constructor
   This constructor automatically adjusts the component size based on name.
   \param p The upper left corner of the component.
   \param str The text in the button's label.
   */
   Button(const scv::Point &p, const std::string &str);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   virtual void display(void);

protected:
   void createTexture(void);

};

} // namespace scv

#endif // __SCV_BUTTON_H__