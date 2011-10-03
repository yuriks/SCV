#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) {

}

GroupLayout::~GroupLayout(void) {

}

ParallelGroup *GroupLayout::createParallelGroup(void) {
   return new ParallelGroup();
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