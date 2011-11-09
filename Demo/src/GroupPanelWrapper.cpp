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
   return new ParallelGroupPanel(GroupPanel::HORIZONTAL);
}

SequetialGroupPanel *GroupPanelWrapper::createHorizontalSequentialGroupPanel(void) {
   return new SequetialGroupPanel(GroupPanel::HORIZONTAL);
}

ParallelGroupPanel *GroupPanelWrapper::createVerticalParallelGroupPanel(void) {
   return new ParallelGroupPanel(GroupPanel::VERTICAL);
}

SequetialGroupPanel *GroupPanelWrapper::createVerticalSequentialGroupPanel(void) {
   return new SequetialGroupPanel(GroupPanel::VERTICAL);
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