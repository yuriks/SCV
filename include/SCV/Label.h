/*!
\file       Label.h
\brief      Implementation of a Label widget.
\author     SCV Team
*/

#ifndef __SCV_WIDGET_LABEL_H__
#define __SCV_WIDGET_LABEL_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ComponentWithTexture.h"
#include "FontTahoma.h"
#include "Color4f.h"
#include "ColorScheme.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A plain text label.
 *  \ingroup widgets
 */

class Label : public ComponentWithTexture {
public:

   /*! Constructor
   \param p1 The initial position of the component.
   \param p2 The final position of component.
   \param str Text of the Label.
   */
   Label(const scv::Point &p1, const scv::Point &p2, const std::string& str);
   /*! Constructor
   \param p The initial position of the component.
   \param width Width of the component.
   \param str Text of the Label.
   */
   Label(const scv::Point &p, unsigned int width, const std::string& str);
   /*! Constructor
   This constructor automatically adjusts the component size based on name.
   \param p The initial position of the component.
   \param str Text of the Label.
   */
   Label(const scv::Point &p, const std::string& str);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);

   /*! Callback. Called when the Label's text is changed. */
   virtual void onStringChange(void);

   /*! Returns the current Label's text. */
   const std::string& getString(void) const;
   /*! Sets the Label's text. */
   virtual void setString(const std::string& str);
   /*! Sets the Label's width. */
   virtual void setWidth(const int width);
   /*! Sets the Label's height. */
   virtual void setHeight(const int height);

   /*! Displays a string at a certain position. */
   static void display(int x, int y, const std::string &label, const Color4f &color = ColorScheme::getInstance()->getColor(ColorScheme::font));
   /*! Displays a string at a certain position. */
   static void display(const Point &translate, const std::string &label, const Color4f &color = ColorScheme::getInstance()->getColor(ColorScheme::font));
   /*! Displays a string at a certain position, with parts of the text selected. */
   static void display(int x, int y, const std::string &label, int selectStart, int selectEnd);
   /*! Displays a string at a certain position, with parts of the text selected. */
   static void display(const Point &translate, const std::string &label, int selectStart, int selectEnd);

   virtual void display(void);

protected:
   /*! Displays the text at a given position. */
   virtual void display(const int translateX, const int translateY);
   /*! Displays the text at a given position. */
   virtual void display(const Point &translate);

   Label(const scv::Point &p1, const scv::Point &p2, const std::string& str, bool refreshOnOver, bool refreshOnHold);
   std::string _str;
};

inline const std::string& Label::getString(void) const {
   return _str;
}

inline void Label::setWidth(const int width) {
   ComponentInterface::setWidth(width);
}

inline void Label::setHeight(const int height) {
   ComponentInterface::setHeight(height);
}

inline void Label::display(const int translateX, const int translateY) {
   display(Point(translateX, translateY));
}

inline void Label::display(int x, int y, const std::string &label, const Color4f &color) {
   display(Point(x, y), label, color);
}

inline void Label::display(int x, int y, const std::string &label, int selectStart, int selectEnd) {
   display(Point(x, y), label, selectStart, selectEnd);
}


} // namespace scv


#endif // __SCV_WIDGET_LABEL_H__