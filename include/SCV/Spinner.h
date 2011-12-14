#ifndef __SCV_SPINNER_H__
#define __SCV_SPINNER_H__

#include "TextField.h"
#include "Counter.h"
#include "Timer.h"
#include "TextFilter.h"
#include "Panel.h"
#include "GroupLayout.h"

namespace scv {

class Spinner : public scv::Panel, public Counter {
public:
   ///////////////////////////////////////////////////////////
   Spinner(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   virtual ~Spinner(void);
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
   void setValue(double value);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

   inline bool getRefreshOnKeyStatus(void) const;
   inline std::string getRefreshOnKey(void) const;
   inline void setRefreshOnKey(const std::string &keyString);

protected:
   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   void createTexture(void);

private:
   ///////////////////////////////////////////////////////////
   class TextFieldSpinner : public TextField {
   public:
      ///////////////////////////////////////////////////////////
      TextFieldSpinner(Spinner *spinner, unsigned int width, const std::string &str);
      ///////////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////////
      void onStringChange(void);
      ///////////////////////////////////////////////////////////

   private:
      Spinner *_spinner;
   };
   ///////////////////////////////////////////////////////////

   bool isOnUpButton(const Point &p);
   bool isOnDownButton(const Point &p);

   static const int s_spinnerSizeX = 15;
   static const int s_spinnerSizeY = 20;
   static const int s_minSize      = 35;

   bool _upPress, _downPress, _upOver, _downOver;
   scv::Timer _whileUp, _whileDown;

   int _lastTime, _incrementTime;

   static TextFilter s_filter;
   TextFieldSpinner *_textField;

   std::string _keyString;
};

///////////////////////////////////////////////////////////

bool Spinner::getRefreshOnKeyStatus(void) const {
   return !_keyString.empty();
}


std::string Spinner::getRefreshOnKey(void) const {
   return _keyString;
}

void Spinner::setRefreshOnKey(const std::string &keyString) {
   _keyString = keyString;
}

///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_SPINNER_H__
