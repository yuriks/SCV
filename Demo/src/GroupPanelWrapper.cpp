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
   if (_horizontalGroup == NULL) {
      _horizontalGroup = group;
   }
}

void GroupPanelWrapper::setVerticalGroup(GroupPanel *group) {
   if (_verticalGroup == NULL) {
      _verticalGroup = group;
   }
}

void GroupPanelWrapper::setHorizontalGroupVisible(bool visible) {
   if (_horizontalGroup != NULL) {
      _horizontalGroup->setVisible(visible);
   }
}

void GroupPanelWrapper::setVerticalGroupVisible(bool visible) {
   if (_verticalGroup != NULL) {
      _verticalGroup->setVisible(visible);
   }
}

std::string GroupPanelWrapper::getHorizontalGroupCode(void) const {
   if (_horizontalGroup != NULL) {
      return _horizontalGroup->getCode();
   } else {
      return std::string("");
   }
}

std::string GroupPanelWrapper::getVerticalGroupCode(void) const {
   if (_verticalGroup != NULL) {
      return _verticalGroup->getCode();
   } else {
      return std::string("");
   }
}
