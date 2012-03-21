#ifndef __SCV_TEXTBOX_H__
#define __SCV_TEXTBOX_H__

#include "ComponentWithTexture.h"
#include "TextFilter.h"

namespace scv {

class TextBox : public ComponentWithTexture {
friend class Table;
public:
   TextBox(const scv::Point &p1, const scv::Point &p2, const std::string &str);
   TextBox(const scv::Point &p, unsigned int width, unsigned int lines, const std::string &str);
   TextBox(const scv::Point &p, unsigned int width, const std::string &str);

   virtual void onStringChange(void) {}

   inline virtual bool isEditable(void) const;
   virtual void setEditable(bool editable);

   virtual void setString(const std::string& str);
   inline virtual const std::string& getString(void);

   void setCursorPosition(int position);
   void setFilter(TextFilter filter);

   virtual void removeSelection(void);
   virtual void removeSelectedText(void);

   virtual void selectLine(int line);
   virtual void selectAll(void);

   virtual void setWidth(int width);
   virtual void setHeight(int height);

   bool hasSelectedText(void);

   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

   virtual void display(void);

protected:
   virtual void createTexture(void);
   virtual void refreshText(void);
   virtual void refreshCursor(void);

   bool _editable;

   int  _currChar;
   int  _selectStart, _selectEnd;

   TextFilter _filter;
   std::string _str;

private:
   static const int s_lineSpacing  = 16;
   static const int s_borderWidth  = 8;
   static const int s_borderHeight = 3;

   void upLine(void);
   void downLine(void);
   
   bool _refreshText, _refreshCursor;

   Point _desloc;
   int _firstLine, _nLines;
   std::vector <int> _lineIndex;
};

///////////////////////////////////////////////////////////
bool TextBox::isEditable(void) const {
   return _editable;
}

const std::string& TextBox::getString(void) {
   return _str;
}

} // namespace scv

#endif // __SCV_TEXTBOX_H__