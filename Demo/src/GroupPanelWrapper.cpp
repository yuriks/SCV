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
   switch (_host->getType()) {
   case GroupPanel::HORIZONTAL:
      if (address[1] == "Add Parallel Group") {
         _host->setGroup(GroupPanelWrapper::createHorizontalParallelGroupPanel());
      } else if (address[1] == "Add Sequential Group") {
         _host->setGroup(GroupPanelWrapper::createHorizontalSequentialGroupPanel());
      }
      break;
   case GroupPanel::VERTICAL:
      if (address[1] == "Add Parallel Group") {
         _host->setGroup(GroupPanelWrapper::createVerticalParallelGroupPanel());
      } else if (address[1] == "Add Sequential Group") {
         _host->setGroup(GroupPanelWrapper::createVerticalSequentialGroupPanel());
      }
      break;
   }   
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

GroupPanelWrapper::GroupPanelWrapper(GroupPanel::GroupType type) : scv::Panel(scv::Point(0, 0), scv::Point(940, 600)), _type(type) {
   setResizable(true);

   _group = NULL;

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

///////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////

void GroupPanelWrapper::setGroup(GroupPanel *group) {
   if (_group == NULL) {
      _group = group;
      addChild(group);
      _layout->getHorizontalGroup()->addComponent(group)->addGap(15);
      _layout->getVerticalGroup()->addComponent(group)->addGap(15);

      unregisterContextMenu();
   }
}


std::string GroupPanelWrapper::getGroupCode(void) const {
   if (_group != NULL) {
      return "scv::GroupLayout::createParallelGroup()" + _group->getCode();
   } else {
      return std::string("");
   }
}
