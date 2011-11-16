#include "stdafx.h"
#include "GroupPanelWrapper.h"

GroupPanelWrapperMenu::GroupPanelWrapperMenu(GroupPanelWrapper *host) : scv::ContextMenu("Group Panel") {
   _host = host;

   addMenu(new scv::ContextMenu("Add Parallel Group"));
   addMenu(new scv::ContextMenu("Add Sequential Group"));
}

GroupPanelWrapperMenu::~GroupPanelWrapperMenu(void) {

}

void GroupPanelWrapperMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address[1] == "Add Parallel Group") {
      _host->setVerticalGroup(GroupPanelWrapper::createVerticalParallelGroupPanel());
   } else if (address[1] == "Add Sequential Group") {
      _host->setVerticalGroup(GroupPanelWrapper::createVerticalSequentialGroupPanel());
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

GroupPanelWrapper::GroupPanelWrapper(void) : scv::Panel(scv::Point(0, 0), scv::Point(1280, 720)) {
   setResizable(true);

   _verticalGroup   = NULL;
   _horizontalGroup = NULL;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   _layout->setHorizontalGroup(_layout->createSequentialGroup()->addGap(15));
   _layout->setVerticalGroup(_layout->createSequentialGroup()->addGap(15));

   registerContextMenu(new GroupPanelWrapperMenu(this));
}

GroupPanelWrapper::~GroupPanelWrapper(void) {

}

void GroupPanelWrapper::display(void) {
   scv::Panel::display();
   scv::Scissor::getInstance()->pushScissor(getScissor());
   scv::StaticLabel::display(getAbsolutePosition() + 2, "GroupPanelWrapper");
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
      _layout->getHorizontalGroup()->addComponent(group)->addGap(15);
      _layout->getVerticalGroup()->addComponent(group)->addGap(15);
   }
}

void GroupPanelWrapper::setVerticalGroup(GroupPanel *group) {
   if (_verticalGroup == NULL) {
      _verticalGroup = group;
      addChild(group);
      _layout->getHorizontalGroup()->addComponent(group)->addGap(15);
      _layout->getVerticalGroup()->addComponent(group)->addGap(15);
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
      return "scv::GroupLayout::createParallelGroup()" + _horizontalGroup->getCode();
   } else {
      return std::string("");
   }
}

std::string GroupPanelWrapper::getVerticalGroupCode(void) const {
   if (_verticalGroup != NULL) {
      return "scv::GroupLayout::createParallelGroup()" + _verticalGroup->getCode();
   } else {
      return std::string("");
   }
}

