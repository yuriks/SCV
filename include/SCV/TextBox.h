/*!
\file       TextBox.h
\brief      Implementation of a TextBox widget.
\author     SCV Team
*/

#ifndef __SCV_TEXTBOX_H__
#define __SCV_TEXTBOX_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Label.h"
#include "TextFilter.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A multi-line text editing widget.
 * \ingroup widgets
 */

class TextBox : public Label {
friend class Table;
public:

   /*! Constructor
   \param p1 The initial position of the component.
   \param p2 The final position of component.
   \param str Initial text of the component.
   */
   TextBox(const scv::Point &p1, const scv::Point &p2, const std::string &str);
   /*! Constructor
   \param p The initial position of the component.
   \param width Width of the component.
   \param lines Number of lines of the TextBox.
   \param str Initial text of the TextBox.
   */
   TextBox(const scv::Point &p, unsigned int width, unsigned int lines, const std::string &str);
   /*! Constructor
   \param p The initial position of the component.
   \param width Width of the component.
   \param str Initial text of the TextBox.
   */
   TextBox(const scv::Point &p, unsigned int width, const std::string &str);


   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);

   /*! Sets the TextBox's contents. */
   virtual void setString(const std::string& str);
   /*! Gets the TextBox's contents. */
   virtual const std::string& getString(void);
   /*! Sets the text cursor position in the TextBox.
   \param position The cursor position, in characters from the start of the text.
   */
   void setCursorPosition(int position);
   /*! Specifies the filter used on this TextBox. For more info please consult
    * the TextFilter documentation. */
   void setFilter(TextFilter filter);
   /*! Deselects all text. */
   virtual void removeSelection(void);
   /*! Removes text inside the current selection. */
   virtual void removeSelectedText(void);
   /*! Selects all text in the specified line. */
   virtual void selectLine(int line);
   /*! Selects all text in the TextBox. */
   virtual void selectAll(void);
   virtual void setWidth(const int width);
   virtual void setHeight(const int height);
   /*! Returns true if any text is selected. */
   bool hasSelectedText(void);


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

protected:

   virtual void createTexture(void);
   //! Refresh function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void refreshText(void);
   //! Refresh function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void refreshCursor(void);

   int  _currChar;
   int  _selectStart;
   int  _selectEnd;
   bool _refreshText;
   bool _refreshCursor;
   TextFilter _filter;

private:

   static const int s_lineSpacing  = 16;
   static const int s_borderWidth  = 8;
   static const int s_borderHeight = 3;

   void upLine(void);
   void downLine(void);
   Point _desloc;
   int _firstLine;
   int _nLines;
   std::vector <int> _lineIndex;
};

inline const std::string& TextBox::getString(void) {
   // This is only here so that I can document it. :P
   // TODO: Find out if doxygen lets you do this without creating a new
   // function, and cluttering the vtable. :B
   return Label::getString();
}

} // namespace scv

#endif // __SCV_TEXTBOX_H__