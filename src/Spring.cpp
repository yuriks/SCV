#include "stdafx.h"
#include "Spring.h"

namespace scv {

Spring::Spring(void) {
   _min = _pref = _max = UNSET;
   _alignment = NONE;
}

Spring::~Spring(void) {

}

int Spring::getMinimumSize(Axis axis) {
   if (_min <= 0) {
      _min = constrain(calculateMinimumSize(axis));
   }
   return _min;
}

int Spring::getPreferredSize(Axis axis) {
   if (_pref <= 0) {      
      _pref = constrain(calculatePreferredSize(axis));
   }
   return _pref;
}

int Spring::getMaximumSize(Axis axis) {
   if (_max <= 0) {
      _max = constrain(calculateMaximumSize(axis));
   }
   return _max;
}

bool Spring::isResizable(Axis axis) {
   int min = getMinimumSize(axis);
   int pref = getPreferredSize(axis);
   return (min != pref || pref != getMaximumSize(axis));
}

} //namespace scv