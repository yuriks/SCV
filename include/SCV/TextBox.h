#ifndef __SCV_TEXTBOX_H__
#define __SCV_TEXTBOX_H__

#include "Label.h"
#include "TextFilter.h"

namespace scv {

class TextBox : public Label {
friend class Table;
public:
   ///////////////////////////////////////////////////////////
   TextBox(const scv::Point &p1, const scv::Point &p2, const std::string &str);
   TextBox(const scv::Point &p, unsigned int width, unsigned int lines, const std::string &str);
   TextBox(const scv::Point &p, unsigned int width, const std::string &str);
   virtual ~TextBox(void);
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

   ///////////////////////////////////////////////////////////
   inline virtual bool isEditable(void) const;
   virtual void setEditable(bool editable);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setString(const std::string& str);
   inline virtual const std::string& getString(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setCursorPosition(int position);
   void setFilter(TextFilter filter);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void removeSelection(void);
   virtual void removeSelectedText(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void selectLine(int line);
   virtual void selectAll(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setWidth(int width);
   virtual void setHeight(int height);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   bool hasSelectedText(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

protected:
   virtual void createTexture(void);
   virtual void refreshText(void);
   virtual void refreshCursor(void);

   int  _currChar;
   int  _selectStart, _selectEnd;
   bool _refreshText, _refreshCursor;
   bool _editable;

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

///////////////////////////////////////////////////////////
bool TextBox::isEditable(void) const {
   return _editable;
}

const std::string& TextBox::getString(void) {
   return Label::getString();
}
///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_TEXTBOX_H__