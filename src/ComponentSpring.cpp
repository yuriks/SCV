#include "stdafx.h"
#include "ComponentSpring.h"

namespace scv {

ComponentSpring::ComponentSpring(Component *component, int min, int pref, int max) : Spring() {
   _component = component;

   _min = min;
   _pref = pref;
   _max = max;
}

ComponentSpring::~ComponentSpring(void) {

}

int ComponentSpring::calculateMinimumSize(Axis axis) {
   if (!isVisible()) {
      return 0;
   }

   if (_min >= 0) {
      return _min;
   }
   if (_min == PREFERRED_SIZE) {
      return calculatePreferredSize(axis);
   }
   assert (_min == DEFAULT_SIZE);
   return getSizeAlongAxis(axis, _component->getMinimumSize());
}

int ComponentSpring::calculatePreferredSize(Axis axis) {
   if (!isVisible()) {
      return 0;
   }
   if (_pref >= 0) {
      return _pref;
   }
   assert (_pref == DEFAULT_SIZE || _pref == PREFERRED_SIZE);
   return getSizeAlongAxis(axis, _component->getPreferredSize());
}

int ComponentSpring::calculateMaximumSize(Axis axis) {
   if (!isVisible()) {
      return 0;
   }
   if (_max >= 0) {
      return _max;
   }
   if (_max == PREFERRED_SIZE) {
      return calculatePreferredSize(axis);
   }
   assert (_max == DEFAULT_SIZE);
   return getSizeAlongAxis(axis, _component->getMaximumSize());
}

int ComponentSpring::getSizeAlongAxis(Axis axis, Point size) {
   return (axis == HORIZONTAL)? size.x : size.y;
}

} //namespace scv
