/*!
\file       Slider.h
\brief      Implementation of a Slider widget.
\author     SCV Team
*/

#ifndef __SCV_SLIDER_H__
#define __SCV_SLIDER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ComponentWithTexture.h"
#include "Counter.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! An horizontal bar with a draggable knob for adjustment of numeric values.
 *
 * \ingroup widgets
 */
class Slider : public ComponentWithTexture, public Counter {
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
   Slider(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   //! Constructor
   /*!
   This constructor automatically takes the default size to the component.
   \param p The initial position of the component.
   \param minValue Minimum value for the range.
   \param maxValue Maximum value for the range.
   \param startValue Start value inside the range.
   \param stepValue Step value.
   */
   Slider(const scv::Point &p,                     double minValue, double maxValue, double startValue, double stepValue);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   //! Callback
   /*!
   This function is called when the current value of the component is changed.
   */
   virtual void onValueChange(void);

   virtual void display(void);

protected:
   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   //! Keyboard function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processKey(const scv::KeyEvent &evt);

   void createTexture(void);

};

} // namespace scv

#endif // __SCV_SLIDER_H__