/*!
\file       TextField.h
\brief      Implementation of a TextField widget.
\author     SCV Team
*/

#ifndef __SCV_TEXTFIELD_H__
#define __SCV_TEXTFIELD_H__

#ifndef DOXYGEN_SKIP_THIS
#include "TextBox.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A single line text editing widget.
 * \ingroup widgets
 */

class TextField : public TextBox {
public:

   /*! Constructor
   \param p The upper left corner of the component.
   \param width The width of the component.
   \param str The initial string within the component.
   */
   TextField(const scv::Point &p, unsigned int width, const std::string &str);


   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);


   /*! Set a new String to the component.*/
   virtual void setString(const std::string& str);
   /*! Has no effect. */
   virtual void setHeight(int height);


   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   //! Key function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processKey(const scv::KeyEvent &evt);
   virtual void display(void);

private:

   static const int s_lineSpacing = 18;
   static const int s_borderWidth = 8;
   static const int s_borderHeight = 3;

   void refreshText(void);
   void selectLine(int line);

   int _deslocString;
   int _deslocCursor;
   int _lastCharVisible;


};

} // namespace scv

#endif // __SCV_TEXTFIELD_H__