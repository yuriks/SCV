#include "stdafx.h"
#include "Group.h"

namespace scv {

Group::Group(void) {

}

Group::~Group(void) {

}

Group *Group::addComponent(Component *component) {
   return this;
}

Group *Group::addGap(int size) {
   return this;
}

Group *Group::addGroup(Group *group) {
   return this;
}

int Group::calculateMinimumSize(Axis axis) {
   return calculateSize(axis, MIN_SIZE);
}

int Group::calculatePreferredSize(Axis axis) {
   return calculateSize(axis, PREF_SIZE);
}

int Group::calculateMaximumSize(Axis axis) {
   return calculateSize(axis, MAX_SIZE);
}

int Group::calculateSize(Spring::Axis axis, SizeType type) {
   int count = _springs.size();

   if (count == 0) {
      return 0;
   }

   if (count == 1) {
      return getSpringSize(getSpring(0), axis, type);
   }

   int size = constrain(combined(getSpringSize(getSpring(0), axis, type), 
      getSpringSize(getSpring(1), axis, type)));

   for (int i = 2; i < count; ++i) {
      size = constrain(combined(size, getSpringSize(getSpring(i), axis, type)));
   }
}

int Group::getSpringSize(Spring *spring, Spring::Axis axis, SizeType type) {
   switch (type) {
   case MIN_SIZE:
      return spring->getMinimumSize(axis);
      break;
   case PREF_SIZE:
      return spring->getPreferredSize(axis);
      break;
   case MAX_SIZE:
      return spring->getMaximumSize(axis);
      break;
   default:
      return 0;
      break;
   }
}

} //namespace scv