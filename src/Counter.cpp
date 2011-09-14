#include "stdafx.h"
#include "Counter.h"
#include "Kernel.h"

namespace scv {

Counter::Counter(double minValue, double maxValue, double startValue, double stepValue ) {
   _currValue = startValue;
   _stepValue = stepValue;
   _minValue = minValue;
   _maxValue = maxValue;
}

double Counter::getValue(void) const {
   return _currValue;
}

void Counter::setValue(double value) {
   static Kernel *kenel = Kernel::getInstance();

   if(value >= _maxValue)
      _currValue = _maxValue;
   else if (value <= _minValue)
      _currValue = _minValue;
   else
      _currValue = value;

   onValueChange();
}

double Counter::getMaxValue(void) const {
   return _maxValue;
}

void Counter::setMaxValue(double value) {
   _maxValue = value;
}

double Counter::getMinValue(void) const {
   return _minValue;
}

void Counter::setMinValue(double value) {
   _minValue = value;
}

double Counter::getStep(void) const {
   return _stepValue;
}

void Counter::setStep(double value) {
   _stepValue = value;
}

void Counter::IncrementStep(void) {
   setValue(getValue() + getStep());
}
void Counter::DecrementStep(void) {
   setValue(getValue() - getStep());
}

} // namespace scv