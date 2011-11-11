#include "stdafx.h"
#include "GroupPanel.h"

#include "GroupPanelWrapper.h"

#include "GroupObjectWrapper.h"
#include "ParallelGroup.h"
#include "SequentialGroup.h"

GroupPanelMenu::GroupPanelMenu(GroupPanel *host) : scv::ContextMenu("class Group Panel") {
   _host = host;

   scv::ContextMenu *level1 = new scv::ContextMenu("Add Group Panel");
   level1->addMenu(new scv::ContextMenu("Parallel Group"));
   level1->addMenu(new scv::ContextMenu("Sequential Group"));
   addMenu(level1);


   addMenu(new scv::ContextMenu("Add SCV Object"));
}

GroupPanelMenu::~GroupPanelMenu(void) {

}

void GroupPanelMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address.size() > 2) {   
      if (address[2] == "Parallel Group") {
         _host->addChild(GroupPanelWrapper::createHorizontalParallelGroupPanel());
      } else if (address[2] == "Sequential Group") {
         _host->addChild(GroupPanelWrapper::createHorizontalSequentialGroupPanel());
      }
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

GroupPanel::GroupPanel(GroupType type) : scv::Panel(scv::Point(0,0), scv::Point(200,200)) {
   _layout = new scv::GroupLayout(this);
   setLayout(_layout);
   
   registerContextMenu(new GroupPanelMenu(this));
}

GroupPanel::~GroupPanel(void) {
   if (_layout != NULL) {
      delete _layout;
   }
}

void GroupPanel::addChild(scv::Component *object) {
   scv::Component *wrappedObject;
   if (dynamic_cast<GroupPanel*>(object)) {
      wrappedObject = object;
   } else {
      wrappedObject = new GroupObjectWrapper(object);
   }

   Panel::addChild(wrappedObject);
   _verticalGroup->addComponent(object);
   _horizontalGroup->addComponent(object);
}

void GroupPanel::removeChild(scv::Component *object) {
   std::cout << "GroupPanel::removeChild" << std::endl;
}

void GroupPanel::display(void) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   static scv::Scissor *scissor = scv::Scissor::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   scv::Point currPosition = getAbsolutePosition();

   scissor->pushScissor(getScissor());

   _cTexture->enable();
   applyColor();
   
   // middle
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);

   // corners
   _cTexture->display(currPosition.x, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + 1, currPosition.y, 0, getWidth() - 2, 1);
   _cTexture->display(currPosition.x + 1, currPosition.y + getHeight() - 1, 0, getWidth() - 2, 1);

   _cTexture->disable();

   if (_layout != NULL) {
      _layout->layoutContainer();
   }

   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }

   scissor->popScissor();
}
