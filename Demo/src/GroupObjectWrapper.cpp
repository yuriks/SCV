#include "stdafx.h"
#include "GroupObjectWrapper.h"

GroupObjectWrapperMenu::GroupObjectWrapperMenu(GroupObjectWrapper *host) : scv::ContextMenu("Group Object Wrapper Menu") {
   _host = host;

   addMenu(new scv::ContextMenu("Remove"));
   addMenu(new scv::ContextMenu("Edit Object"));
}

GroupObjectWrapperMenu::~GroupObjectWrapperMenu(void) {
   std::cout << "GroupObjectWrapperMenu::~GroupObjectWrapperMenu" << std::endl;
}

void GroupObjectWrapperMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address[1] == "Remove") {
      _host->getParent()->removeChild(_host);
   } else if (address[1] == "Edit Object") {
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

GroupObjectWrapper::GroupObjectWrapper(scv::Component *object, bool createContextMenu) : scv::Panel(scv::Point(0,0), scv::Point(object->getWidth(), object->getHeight())) {
   setObject(object);

   if (createContextMenu) {
      registerContextMenu(new GroupObjectWrapperMenu(this));
   }
}

GroupObjectWrapper::GroupObjectWrapper(const GroupObjectWrapper &source) : scv::Panel(scv::Point(0,0), scv::Point(source.getObject()->getWidth(), source.getObject()->getHeight())) {
   setObject(source.getObject());   
}

GroupObjectWrapper::~GroupObjectWrapper(void) {
   std::cout << "GroupObjectWrapper::~GroupObjectWrapper" << std::endl;
}

void GroupObjectWrapper::setObject(scv::Component *object) {
   _object = object;

   setMinimumSize(getObject()->getMinimumSize());
   setPreferredSize(getObject()->getPreferredSize());
   setMaximumSize(getObject()->getMaximumSize());
}

void GroupObjectWrapper::display(void) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();

   setObject(getObject());

   scv::Scissor::getInstance()->pushScissor(getScissor());

   // Wrapped Object
   ///////////////////////////////////////////////////////////
   getObject()->setAbsolutePosition(getAbsolutePosition());

   scv::Point originalSize = getObject()->getSize();
   getObject()->setSize(getWidth(), getHeight());
   getObject()->display();

   getObject()->setSize(originalSize.x, originalSize.y);

   scv::Scissor::getInstance()->popScissor();
   ///////////////////////////////////////////////////////////
}


