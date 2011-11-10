#include "stdafx.h"
#include "Group.h"

#include "GapSpring.h"
#include "ComponentSpring.h"

namespace scv {

Group::Group(void) {
   //_autoCreateContainerPadding = false;
}

Group::~Group(void) {

}

Group *Group::addGroup(Group *group) {
   return addSpring(group);
}

Group *Group::addComponent(Component *component) {
   return addComponent(component, Spring::DEFAULT_SIZE, Spring::DEFAULT_SIZE, Spring::DEFAULT_SIZE);
}

Group * Group::addComponent(Component *component, int min, int pref, int max) {
   return addSpring(new ComponentSpring(component, min, pref, max));
}

Group *Group::addGap(int size) {
   return addGap(size, size, size);
}

Group * Group::addGap(int min, int pref, int max) {
   return addSpring(new GapSpring(min, pref, max));
}

Group * Group::addSpring(Spring *spring) {
   _springs.push_back(spring);
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
   return size;
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

void Group::setSize(Spring::Axis axis, int origin, int size) {
   Spring::setSize(axis, origin, size);
   if (size == Spring::UNSET) {
      for (int counter = _springs.size() - 1; counter >= 0; --counter) {
         getSpring(counter)->setSize(axis, origin, size);
      }
   } else {
      setValidSize(axis, origin, size);
   }
}

/*
Group *Group::enableAutoCreateContainerGaps(void) {
   _autoCreateContainerPadding = true;
}

bool Group::getAutoCreateContainerGaps(void) const {
   return _autoCreateContainerPadding;
}*/

} //namespace scv