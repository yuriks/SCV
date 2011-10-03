#include "stdafx.h"
#include "GapSpring.h"

namespace scv {

GapSpring::GapSpring(int min, int pref, int max) : Spring() {
   _min = min;
   _pref = pref;
   _max = max;
}

GapSpring::~GapSpring(void) {

}

int GapSpring::calculateMinimumSize(Spring::Axis axis) {
   if (_min == PREFERRED_SIZE) {
      return getPreferredSize(axis);
   }
   return _min;
}

int GapSpring::calculatePreferredSize(Spring::Axis axis) {
   return _pref;
}

int GapSpring::calculateMaximumSize(Spring::Axis axis) {
   if (_max == PREFERRED_SIZE) {
      return getPreferredSize(axis);
   }
   return _max;
}

} //namespace scv