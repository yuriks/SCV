#include "stdafx.h"
#include "Spring.h"

namespace scv {

Spring::Spring(void) {
   _min = _pref = _max = Size::UNSET;
}

Spring::~Spring(void) {

}

int Spring::getMinimumSize(Axis axis) {
   if (_min == Size::UNSET) {
      _min = constrain(calculateMinimumSize(axis));
   }
   return _min;
}

int Spring::getPreferredSize(Axis axis) {
   if (_pref == Size::UNSET) {
      _pref = constrain(calculatePreferredSize(axis));
   }
   return _pref;
}

int Spring::getMaximumSize(Axis axis) {
   if (_max == Size::UNSET) {
      _max = constrain(calculateMaximumSize(axis));
   }
   return _max;
}

} //namespace scv