#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) {
   _host = host;

   _autoCreatePadding = false;
   _autoCreateContainerPadding = false;

   setHorizontalGroup(createParallelGroup(Spring::LEADING, true));
   setVerticalGroup(createParallelGroup(Spring::LEADING, true));
}

GroupLayout::~GroupLayout(void) {

}

ParallelGroup *GroupLayout::createParallelGroup(void) {
   return createParallelGroup(Spring::LEADING);
}

ParallelGroup *GroupLayout::createParallelGroup(Spring::Alignment alignment) {
   return createParallelGroup(alignment, true);
}

ParallelGroup *GroupLayout::createParallelGroup(Spring::Alignment alignment, bool resizable) {
   /*
   if (alignment == Spring::Alignment.BASELINE) {
      return new BaselineGroup(resizable);
   }
   /**/
   return new ParallelGroup(alignment, resizable);
}

SequentialGroup *GroupLayout::createSequentialGroup(void) {
   return new SequentialGroup();
}

void GroupLayout::setHorizontalGroup(Group *group) {
   _horizontalGroup = group;
}

void GroupLayout::setVerticalGroup(Group *group) {
   _verticalGroup = group;
}

void GroupLayout::layoutContainer(void) {
   std::cout << _horizontalGroup->calculateMinimumSize(Spring::HORIZONTAL) << std::endl;
}

} //namespace scv