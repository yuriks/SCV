#include "stdafx.h"
#include "GroupPanelWrapper.h"

GroupPanelWrapper::GroupPanelWrapper(scv::Panel *host) {
   _host = host;
   _verticalGroup   = NULL;
   _horizontalGroup = NULL;
}

GroupPanelWrapper::~GroupPanelWrapper(void) {

}

ParallelGroupPanel *GroupPanelWrapper::createHorizontalParallelGroupPanel(void) {

}

ParallelGroupPanel *GroupPanelWrapper::createHorizontalSequentialGroupPanel(void) {

}

ParallelGroupPanel *GroupPanelWrapper::createVerticalParallelGroupPanel(void) {

}

ParallelGroupPanel *GroupPanelWrapper::createVerticalSequentialGroupPanel(void) {

}

void GroupPanelWrapper::setHorizontalGroup(GroupPanel *group) {
   if (_horizontalGroup != NULL) {
      _horizontalGroup = group;
   }
}

void GroupPanelWrapper::setVerticalGroup(GroupPanel *group) {
   if (_verticalGroup != NULL) {
      _verticalGroup = group;
   }
}