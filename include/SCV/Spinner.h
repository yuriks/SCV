#ifndef __SCV_SPINNER_H__
#define __SCV_SPINNER_H__

#include "TextField.h"
#include "Counter.h"
#include "Timer.h"
#include "TextFilter.h"

namespace scv {

class Spinner : public ComponentWithTexture, public Counter {
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

   virtual void onResizing(void);
   virtual void onDragging(void);
   ///////////////////////////////////////////////////////////

   virtual void onValueChange(void);

   void setValue(double value);

   int getWidth(void) const;

   int getHeight(void) const;

   void setDraggable(bool state);

   void setResizable(bool state);

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
      void onResizing(void);
      void onDragging(void);
   private:
      Spinner *_spinner;
   };

   bool isOnUpButton(const Point &p);
   bool isOnDownButton(const Point &p);

   static const int s_spinnerSizeX = 15;
   static const int s_spinnerSizeY = 20;
   static const int s_minSize      = 35;
   bool _UpPress, _DownPress, _UpOver, _DownOver;
   Timer *_whileUp, *_whileDown;
   int _lastTime, _incrementTime;
   TextFilter _filter;
   TextFieldSpinner *_textField;
};

} // namespace scv

#endif // __SCV_SPINNER_H__
