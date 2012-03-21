#ifndef __SCV_COUNTER_H__
#define __SCV_COUNTER_H__

namespace scv {

class Counter {
public:
   Counter(double minValue, double maxValue, double startValue, double stepValue);
   virtual ~Counter(void);

   inline double getStartValue(void) const;

   virtual void setValue(double value);
   inline virtual double getValue(void) const;

   inline void setStepValue(double value);
   inline double getStepValue(void) const;
   
   inline void setMinValue(double value);
   inline double getMinValue(void) const;
   
   inline void setMaxValue(double value);
   inline double getMaxValue(void) const;

   void IncrementStep(void);
   void DecrementStep(void);

   virtual void onValueChange(void) = 0;

private:
   double _minValue, _maxValue, _currValue, _stepValue;
   const double _startValue;
};

///////////////////////////////////////////////////////////

double Counter::getStartValue(void) const {
   return _startValue;
}

double Counter::getValue(void) const {
   return _currValue;
}

void Counter::setStepValue(double value) {
   _stepValue = value;
}

double Counter::getStepValue(void) const {
   return _stepValue;
}

void Counter::setMinValue(double value) {
   _minValue = value;
}

double Counter::getMinValue(void) const {
   return _minValue;
}

void Counter::setMaxValue(double value) {
   _maxValue = value;
}

double Counter::getMaxValue(void) const {
   return _maxValue;
}

///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_COUNTER_H__