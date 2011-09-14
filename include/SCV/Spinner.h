/*!
\file       Spinner.h
\brief      Implementation of a Spinner widget.
\author     SCV Team
*/

#ifndef __SCV_SPINNER_H__
#define __SCV_SPINNER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "TextField.h"
#include "Counter.h"
#include "Timer.h"
#include "TextFilter.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A TextBox based input for numeric values, with buttons for mouse use.
 *
 * \ingroup widgets
 */
class Spinner : public ComponentWithTexture, public Counter {
public:
   //! Constructor
   /*!
   \param p The initial position of the component.
   \param width The width of the component.
   \param minValue Minimum value for the range.
   \param maxValue Maximum value for the range.
   \param startValue Start value inside the range.
   \param stepValue Step value.
   */
   Spinner(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   //! Constructor
   /*!
   This constructor automatically takes the default size to the component.
   \param p The initial position of the component.
   \param minValue Minimum value for the range.
   \param maxValue Maximum value for the range.
   \param startValue Start value inside the range.
   \param stepValue Step value.
   */
   Spinner(const scv::Point &p,                     double minValue, double maxValue, double startValue, double stepValue);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onResizing(void);
   virtual void onDragging(void);

   //! Callback
   /*!
   This function is called when the current value of the component is changed.
   */
   virtual void onValueChange(void);
   //! Sets a new value to the current value of the component.
   /*!
   \param value New value
   //! \sa Counter::setValue(double value)
   */
   void setValue(double value);
   //! See ComponentInterface::getWidth(void) const documentation.
   int getWidth(void) const;
   //! See ComponentInterface::getHeight(void) const documentation.
   int getHeight(void) const;
   //! See ComponentInterface::setDraggable(bool state) documentation.
   void setDraggable(bool state);
   //! See ComponentInterface::setResizable(bool state) documentation.
   void setResizable(bool state);

   virtual void display(void);
protected:
   //! Mouse function of the component.
   /*!
   \internal IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   //! Keyboard function of the component.
   /*!
   \internal IMPORTANT: This is an internal function and don't must be called!
   */
   void processKey(const scv::KeyEvent &evt);

   void createTexture(void);

private:
   class TextFieldSpinner : public TextField {
   public:
      TextFieldSpinner(Spinner *spinner, const scv::Point &p, unsigned int width, const std::string &str);
      void onStringChange(void);
      void onResizing() { _spinner->setRelativePosition(getRelativePosition()); }
      void onDragging() { _spinner->setRelativePosition(getRelativePosition()); }
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
