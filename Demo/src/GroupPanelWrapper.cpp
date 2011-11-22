#include "stdafx.h"
#include "GroupPanelWrapper.h"

GroupPanelWrapperMenu::GroupPanelWrapperMenu(GroupPanelWrapper *host) : scv::ContextMenu("Group Panel") {
   _host = host;

   addMenu(new scv::ContextMenu("Add Parallel Group"));
   addMenu(new scv::ContextMenu("Add Sequential Group"));
}

GroupPanelWrapperMenu::~GroupPanelWrapperMenu(void) {
   std::cout << "GroupPanelWrapperMenu::~GroupPanelWrapperMenu" << std::endl;
}

void GroupPanelWrapperMenu::onMenuAccessed(const std::deque<std::string> &address) {
   switch (_host->getType()) {
   case GroupPanel::HORIZONTAL:
      if (address[1] == "Add Parallel Group") {
         _host->addChild(GroupPanelWrapper::createHorizontalParallelGroupPanel());
      } else if (address[1] == "Add Sequential Group") {
         _host->addChild(GroupPanelWrapper::createHorizontalSequentialGroupPanel());
      }
      break;
   case GroupPanel::VERTICAL:
      if (address[1] == "Add Parallel Group") {
         _host->addChild(GroupPanelWrapper::createVerticalParallelGroupPanel());
      } else if (address[1] == "Add Sequential Group") {
         _host->addChild(GroupPanelWrapper::createVerticalSequentialGroupPanel());
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

   _hGroup = scv::GroupLayout::createParallelGroup();
   _vGroup = scv::GroupLayout::createParallelGroup();   

   _layout->setHorizontalGroup(_layout->createSequentialGroup()->addGap(15)->addGroup(_hGroup)->addGap(15));
   _layout->setVerticalGroup(_layout->createSequentialGroup()->addGap(15)->addGroup(_vGroup)->addGap(15));

   _contextMenu = new GroupPanelWrapperMenu(this);
   registerContextMenu(_contextMenu);
}

GroupPanelWrapper::~GroupPanelWrapper(void) {
   std::cout << "GroupPanelWrapper::~GroupPanelWrapper" << std::endl;
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

void GroupPanelWrapper::addChild(Component *object) {
   GroupPanel *group = dynamic_cast<GroupPanel *>(object);
   if (group != NULL && _group == NULL) {
      _group = group;
      Panel::addChild(group);
      _hGroup->addComponent(group);
      _vGroup->addComponent(group);

      unregisterContextMenu();
   }
}

void GroupPanelWrapper::removeChild(Component *object) {
   GroupPanel *group = dynamic_cast<GroupPanel *>(object);
   if (group != NULL && _group != NULL) {
      Panel::removeChild(group);
      registerContextMenu(_contextMenu);
      _group = NULL;
   }
}

std::string GroupPanelWrapper::getGroupCode(void) const {
   static const std::string s_defaultTab = "      ";

   if (_group != NULL) {
      return s_defaultTab + "scv::GroupLayout::createParallelGroup()\n" + _group->getCode(s_defaultTab);
   } else {
      return s_defaultTab + "NULL\n";
   }
}
