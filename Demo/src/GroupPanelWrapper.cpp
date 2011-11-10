#include "stdafx.h"
#include "GroupPanelWrapper.h"

GroupPanelWrapperMenu::GroupPanelWrapperMenu(GroupPanelWrapper *host) : scv::ContextMenu("Group Panel") {
   _host = host;

   addMenu(new scv::ContextMenu("Set Parallel Group"));
   addMenu(new scv::ContextMenu("Set Sequential Group"));
}

GroupPanelWrapperMenu::~GroupPanelWrapperMenu(void) {

}

void GroupPanelWrapperMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address[1] == "Set Parallel Group") {
      _host->setHorizontalGroup(GroupPanelWrapper::createHorizontalParallelGroupPanel());
   } else if (address[1] == "Set Sequential Group") {
      _host->setHorizontalGroup(GroupPanelWrapper::createHorizontalSequentialGroupPanel());
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

GroupPanelWrapper::GroupPanelWrapper(void) : scv::Panel(scv::Point(10, 10), scv::Point(1280 - 10, 720 - 10)) {
   setResizable(true);

   _verticalGroup   = NULL;
   _horizontalGroup = NULL;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   _layout->setHorizontalGroup(_layout->createParallelGroup()/*->addGap(15)*/);
   _layout->setVerticalGroup(_layout->createParallelGroup()/*->addGap(15)*/);

   registerContextMenu(new GroupPanelWrapperMenu(this));
}

GroupPanelWrapper::~GroupPanelWrapper(void) {

}

void GroupPanelWrapper::display(void) {
   scv::Panel::display();
   scv::Scissor::getInstance()->pushScissor(getScissor());
   scv::StaticLabel::display(getAbsolutePosition(), "GroupPanelWrapper");
   scv::Scissor::getInstance()->popScissor();
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
      addChild(group);
      _layout->getHorizontalGroup()->addComponent(group);
      _layout->getVerticalGroup()->addComponent(group);
   }
}

void GroupPanelWrapper::setVerticalGroup(GroupPanel *group) {
   if (_verticalGroup == NULL) {
      _verticalGroup = group;
      addChild(group);
      _layout->getHorizontalGroup()->addComponent(group);
      _layout->getVerticalGroup()->addComponent(group);
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

