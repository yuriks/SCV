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
   Spinner(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   virtual ~Spinner();

   virtual void onValueChange(void);

   void setValue(double value);

   virtual void display(void);

protected:
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

   void createTexture(void);

private:
   class TextFieldSpinner : public TextField {
   public:
      TextFieldSpinner(Spinner *spinner, unsigned int width, const std::string &str);

      void onStringChange(void);

   private:
      Spinner *_spinner;
   };

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
};

} // namespace scv

#endif // __SCV_SPINNER_H__
