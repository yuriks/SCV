#ifndef __SCV_TEXTFIELD_H__
#define __SCV_TEXTFIELD_H__

#include "TextBox.h"

namespace scv {

class TextField : public TextBox {
public:
   TextField(const scv::Point &p, unsigned int width, const std::string &str);

   virtual void onStringChange(void) {}

   virtual void setString(const std::string& str);

   virtual void setHeight(int height);

   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

   virtual void display(void);

private:
   static const int s_lineSpacing = 18;
   static const int s_borderWidth = 8;
   static const int s_borderHeight = 3;

   void refreshText(void);
   void selectLine(int line);

   int _deslocString, _deslocCursor;
   int _lastCharVisible;
};

} // namespace scv

#endif // __SCV_TEXTFIELD_H__