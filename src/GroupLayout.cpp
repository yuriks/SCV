#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) {
   _host = NULL;

   _autoCreatePadding = false;
   _autoCreateContainerPadding = false;

   _horizontalGroup = NULL;
   _verticalGroup = NULL;
}

GroupLayout::~GroupLayout(void) {

}

ParallelGroup *GroupLayout::createParallelGroup(void) {
   return createParallelGroup(LEADING);
}

ParallelGroup * GroupLayout::createParallelGroup(Alignment alignment) {
   return new ParallelGroup();
}

SequentialGroup *GroupLayout::createSequentialGroup(void) {
   return new SequentialGroup();
}

void GroupLayout::setHorizontalGroup(Group *group) {

}

void GroupLayout::setVerticalGroup(Group *group) {

}

} //namespace scv