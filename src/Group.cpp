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

} //namespace scv