#include "stdafx.h"
#include "GapSpring.h"

#include "Kernel.h"

namespace scv {

GapSpring::GapSpring(int min, int pref, int max) : Spring() {
   if (min < 0) min = 0;
   _min = min;
   
   if (pref < 0) pref = _min;
   _pref = pref;

   _max = max;
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
   } else if (_max == DEFAULT_SIZE) {
      switch(axis) {
         case Spring::HORIZONTAL: return scv::Kernel::getInstance()->getWidth();
         case Spring::VERTICAL: return scv::Kernel::getInstance()->getHeight();
      }
   }
   return _max;
}

} //namespace scv