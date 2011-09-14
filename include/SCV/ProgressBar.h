/*!
\file       ProgressBar.h
\brief      Implementation of a ProgressBar widget.
\author     SCV Team
*/

#ifndef __SCV_PROGRESSBAR_H__
#define __SCV_PROGRESSBAR_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Label.h"
#include "Counter.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A simple ProgressBar.
 * \ingroup widgets
 */

class ProgressBar : public Label, public Counter {
public:
   //! Constructor
   /*!
   \param p1 The initial position of the component.
   \param p2 The final position of component.
   \param startValue The initial value of the component.
   */
   ProgressBar(const scv::Point &p1, const scv::Point &p2, double startValue);
   //! Constructor
   /*!
   \param p The initial position of the component.
   \param width The width of the component.
   \param startValue The initial value of the component.
   */
   ProgressBar(const scv::Point &p, unsigned int width, double startValue);
   //! Constructor
   /*!
   This constructor automatically takes the default size to the component.
   \param p The initial position of the component.
   \param startValue The initial value of the component.
   */
   ProgressBar(const scv::Point &p, double startValue);

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

   virtual void display(void);

protected:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_PROGRESSBAR_H__