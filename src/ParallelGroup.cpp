#include "stdafx.h"
#include "ParallelGroup.h"

namespace scv {

scv::ParallelGroup::ParallelGroup(Spring::Alignment alignment, bool resizable) : Group() {
   _childAlignment = alignment;
   _resizable = resizable;
}

scv::ParallelGroup::~ParallelGroup(void) {

}


ParallelGroup * ParallelGroup::addGroup(Group *group) {
   return (ParallelGroup*)Group::addGroup(group);
}

ParallelGroup * ParallelGroup::addComponent(Component *component) {
   return (ParallelGroup*)Group::addComponent(component);
}

ParallelGroup * ParallelGroup::addComponent(Component *component, int min, int pref, int max) {
   return (ParallelGroup*)Group::addComponent(component, min, pref, max);
}

ParallelGroup * ParallelGroup::addGap(int size) {
   return (ParallelGroup*)Group::addGap(size);
}

ParallelGroup * ParallelGroup::addGap(int min, int pref, int max) {
   return (ParallelGroup*)Group::addGap(min, pref, max);
}

int ParallelGroup::calculateMinimumSize(Spring::Axis axis) {
   if (!isResizable()) {
      return getPreferredSize(axis);
   }
   return Group::calculateMinimumSize(axis);
}

int ParallelGroup::calculateMaximumSize(Spring::Axis axis) {
   if (!isResizable()) {
      return getPreferredSize(axis);
   }
   return Group::calculateMaximumSize(axis);
}

void ParallelGroup::setValidSize(Spring::Axis axis, int origin, int size) {
   for (SpringsList::iterator iter = _springs.begin(); iter != _springs.end(); ++iter) {      
      setChildSize((*iter), axis, origin, size);
      
   }
}

void ParallelGroup::setChildSize(Spring *spring, Spring::Axis axis, int origin, int size) {
   Spring::Alignment alignment = spring->getAlignment();
   int springSize = std::min(std::max(spring->getMinimumSize(axis), size), spring->getMaximumSize(axis));

   if (alignment == NONE) {
      alignment = _childAlignment;
   }
   
   switch (alignment) {
   case Spring::TRAILING:
      break;
   case Spring::CENTER:
      break;
   default: //Spring::LEADING or Spring::BASELINE
      spring->setSize(axis, origin, springSize);
      break;
   }
}

} //namespace scv
