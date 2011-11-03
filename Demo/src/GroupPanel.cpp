#include "stdafx.h"
#include "GroupPanel.h"

#include "ParallelGroup.h"
#include "SequentialGroup.h"

GroupPanel::GroupPanel(scv::Group *group) : scv::Panel(scv::Point(0,0), scv::Point(100,100)) {
   _group = group;
}

GroupPanel::~GroupPanel(void) {

}

scv::Group *GroupPanel::getGroup(void) const {
   return _group;
}

void GroupPanel::addChild(Component *object) {
   if (dynamic_cast<GroupPanel*>(object)) {
      std::cout << "HERE" << std::endl;
   }
}

void GroupPanel::removeChild(Component *object) {
   if (dynamic_cast<GroupPanel*>(object)) {
      std::cout << "HERE" << std::endl;
   }
}

GroupContextMenu::GroupContextMenu(GroupPanel *panel) : scv::ContextMenu("Group") {
   _panel = panel;
}

GroupContextMenu::~GroupContextMenu(void) {

}

void GroupContextMenu::onMenuAccessed(const std::deque<std::string> &address) {
   GroupPanel *group = NULL;
   if (address[1] == "Parallel Group") {
      group = new GroupPanel(new scv::ParallelGroup(scv::Spring::LEADING, true));
   } else if (address[1] == "Sequential Group") {
      group = new GroupPanel(new scv::SequentialGroup());
   }

   _panel->addChild(group);
   _panel->getGroup()->addGroup(group->getGroup());
}
