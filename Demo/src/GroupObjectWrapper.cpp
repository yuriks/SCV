#include "stdafx.h"
#include "GroupObjectWrapper.h"

#include "CodeGenerator.h"
#include "ObjectEditor.h"

GroupObjectWrapperMenu::GroupObjectWrapperMenu(GroupObjectWrapper *host) : scv::ContextMenu("Group Object Wrapper Menu") {
   _host = host;

   addMenu(new scv::ContextMenu("Remove"));
   addMenu(new scv::ContextMenu("Edit Object"));
}

GroupObjectWrapperMenu::~GroupObjectWrapperMenu(void) {
   //std::cout << "GroupObjectWrapperMenu::~GroupObjectWrapperMenu" << std::endl;
}

void GroupObjectWrapperMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address[1] == "Remove") {
      _host->getParent()->removeChild(_host);
   } else if (address[1] == "Edit Object") {
      if (CodeGenerator::getInstance()->hasComponent(_host->getObject())) {
         ObjectEditor::getInstance()->setComponent(_host->getObject());
      }
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

   
   
   ManagedComponent *managed = CodeGenerator::getInstance()->getManagedComponent(getObject());
   if (managed != NULL) {
      _cTexture->enable();
      int width = scv::FontTahoma::getInstance()->getStringLength(managed->getClassName()) + 1;
      int height = scv::FontTahoma::getInstance()->getHeight();

      scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.5f, 0.5f, 0.5f, 1.f));

      _cTexture->display(getAbsolutePosition().x, getAbsolutePosition().y, 0, width, height);

      _cTexture->display(getAbsolutePosition().x, getAbsolutePosition().y + 1, 0, 1, height - 2);
      _cTexture->display(getAbsolutePosition().x + width - 1, getAbsolutePosition().y + 1, 0, 1, height - 2);
      _cTexture->display(getAbsolutePosition().x + 1, getAbsolutePosition().y, 0, width - 2, 1);
      _cTexture->display(getAbsolutePosition().x + 1, getAbsolutePosition().y + height - 1, 0, width - 2, 1);

      _cTexture->disable();

      scv::StaticLabel::display(scv::Point(getAbsolutePosition().x + 1, getAbsolutePosition().y), managed->getClassName());      
   }   
   scv::Scissor::getInstance()->popScissor();
   ///////////////////////////////////////////////////////////
}


