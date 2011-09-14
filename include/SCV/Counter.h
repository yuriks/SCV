/*!
\file       Counter.h
\brief      Implementation of a numeric range used in some components.
\author     SCV Team
*/

#ifndef __SCV_COUNTER_H__
#define __SCV_COUNTER_H__

namespace scv {

//! Class that control some numeric range components

class Counter {
public:
   //! Constructor
   /*!
   \param minValue Minimum value for the range.
   \param maxValue Maximum value for the range.
   \param startValue Start value inside the range.
   \param stepValue Step value.
   */
   Counter(double minValue, double maxValue, double startValue, double stepValue);
   //! Sets a value to the current value.
   /*!
   \param value New value
   */
   virtual void setValue(double value);
   //! Sets a step value.
   /*!
   \param value New value
   */
   void setStep(double value);
   //! Sets a minimum value for the range.
   /*!
   \param value New value
   */
   void setMinValue(double value);
   //! Sets a maximum value for the range.
   /*!
   \param value New value
   */
   void setMaxValue(double value);
   //! Gets the step value.
   double getStep(void) const;
   //! Gets the current value.
   double getValue(void) const;
   //! Gets the minimum value of the range.
   double getMinValue(void) const;
   //! Gets the maximum value of the range.
   double getMaxValue(void) const;
   //! Sets the current value to (current value + step value).
   void IncrementStep(void);
   //! Sets the current value to (current value - step value).
   void DecrementStep(void);
   //! Internal callback function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void onValueChange(void) = 0;

private:
   double _currValue;
   double _maxValue;
   double _minValue;
   double _stepValue;

};

} // namespace scv

#endif // __SCV_COUNTER_H__