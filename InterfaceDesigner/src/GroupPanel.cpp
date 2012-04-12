#include <SCV/SCV.h>
#include "GroupPanel.h"

#include "GroupPanelWrapper.h"

#include "GroupObjectWrapper.h"
#include <SCV/ParallelGroup.h>
#include <SCV/SequentialGroup.h>

#include "Application.h"

#include "CodeGenerator.h"

GroupPanelMenu::GroupPanelMenu(GroupPanel *host) : scv::ContextMenu("Group Panel Menu") {
   _host = host;

   scv::ContextMenu *level1 = new scv::ContextMenu("Add Group Panel");
   level1->addMenu(new scv::ContextMenu("Parallel Group"));
   level1->addMenu(new scv::ContextMenu("Sequential Group"));
   addMenu(level1);
   
   _addableObjects = new scv::ContextMenu("Add SCV Object");
   addMenu(_addableObjects);
   addMenu(new scv::ContextMenu("Remove"));
}

GroupPanelMenu::~GroupPanelMenu(void) {
   std::cout << "GroupPanelMenu::~GroupPanelMenu" << std::endl;
}

void GroupPanelMenu::onMenuAccessed(const std::deque<std::string> &address) {
   static Application *app = static_cast<Application*>(scv::Kernel::getInstance());

   if (address.size() == 2) {
      if (address[1] == "Add SCV Object") {
         app->openComponentSelector(_host);
         setStatus(false);
      } else if (address[1] == "Remove") {
         _host->getParent()->removeChild(_host);
         app->createPreview();
      }
   } else if (address.size() == 3) {
      if (address[1] == "Add SCV Object") {
         ManagedComponent *managed = CodeGenerator::getInstance()->getManagedComponent(address[2]);
         if (managed != NULL) {
            _host->addChild(managed->getComponent());
         }
      } else if (address[1] == "Add Group Panel") {
         switch (_host->getType()) {
         case GroupPanel::HORIZONTAL:
            if (address[2] == "Parallel Group") {
               _host->addChild(GroupPanelWrapper::createHorizontalParallelGroupPanel());
            } else if (address[2] == "Sequential Group") {
               _host->addChild(GroupPanelWrapper::createHorizontalSequentialGroupPanel());
            }
            break;
         case GroupPanel::VERTICAL:
            if (address[2] == "Parallel Group") {
               _host->addChild(GroupPanelWrapper::createVerticalParallelGroupPanel());
            } else if (address[2] == "Sequential Group") {
               _host->addChild(GroupPanelWrapper::createVerticalSequentialGroupPanel());
            }
            break;
         }
      }
   }
}

void GroupPanelMenu::onStatusChange(void) {
   if (getStatus()) {
      _addableObjects->removeAllMenus();
      CodeGenerator::ManagedList list = CodeGenerator::getInstance()->getManagedComponents();
      for (CodeGenerator::ManagedList::iterator iter = list.begin(); iter != list.end(); ++iter) {
         _addableObjects->addMenu(new scv::ContextMenu((*iter)->getClassName()));
      }
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


const std::string GroupPanel::s_defaultTab = "   ";

scv::ComponentTexture * GroupPanel::s_customTexture = NULL;

GroupPanel::GroupPanel(GroupType type) : scv::Panel(scv::Point(), scv::Point()), _type(type) {
   _layout = new scv::GroupLayout(this);
   setLayout(_layout);
   
   registerContextMenu(new GroupPanelMenu(this));

   createTexture();
}

GroupPanel::~GroupPanel(void) {
   std::cout << "GroupPanel::~GroupPanel" << std::endl;
   if (_layout != NULL) {
      delete _layout;
   }
   unregisterContextMenu();
}

void GroupPanel::addChild(scv::Component *object) {
   scv::Component *wrappedObject = NULL;
   if (dynamic_cast<GroupPanel*>(object)) {
      wrappedObject = object;
   } else {
      wrappedObject = new GroupObjectWrapper(object);
   }

   Panel::addChild(wrappedObject);
   _verticalGroup->addComponent(wrappedObject);
   _horizontalGroup->addComponent(wrappedObject);
}

std::string GroupPanel::getCode(const std::string &tab) {
   std::string currTab = s_defaultTab + tab;
   std::string code = currTab;;

   if (dynamic_cast<ParallelGroupPanel *>(this)) {
      code += "->addGroup(scv::GroupLayout::createParallelGroup()\n";
   } else if (dynamic_cast<SequetialGroupPanel *>(this)) {
      code += "->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)\n";
   }

   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if (dynamic_cast<GroupPanel*>(*iter)) {
         code += static_cast<GroupPanel*>(*iter)->getCode(currTab);
      } else {
         GroupObjectWrapper *object = static_cast<GroupObjectWrapper *>(*iter);
         code += currTab + s_defaultTab + "->addComponent(" + CodeGenerator::getInstance()->getManagedComponent(object->getObject())->getPointerName() + ")\n";         
      }
   }
   code += currTab + ")\n";
   return code;
}

GroupPanel::GroupType GroupPanel::getType(void) const {
   return _type;
}

void GroupPanel::createPreview(scv::Group *group) {
   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if (dynamic_cast<GroupPanel*>(*iter)) {
         scv::Group *currGroup = NULL;
         if (dynamic_cast<ParallelGroupPanel *>(*iter)) {
            currGroup = scv::GroupLayout::createParallelGroup();                        
         } else if (dynamic_cast<SequetialGroupPanel *>(*iter)) {
            currGroup = scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true);
         }
         group->addGroup(currGroup);
         (static_cast<GroupPanel *>(*iter))->createPreview(currGroup);
      } else {
         group->addComponent(GroupPanelWrapper::getDesignObjectWrapper(static_cast<GroupObjectWrapper *>(*iter)->getObject()));
      }
   }
}

void GroupPanel::display(void) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   static scv::Scissor *scissor = scv::Scissor::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   scv::Point currPosition = getAbsolutePosition();

   scissor->pushScissor(getScissor());

   _cTexture->enable();
   
   // middle
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);

   // corners
   _cTexture->display(currPosition.x, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + 1, currPosition.y, 0, getWidth() - 2, 1);
   _cTexture->display(currPosition.x + 1, currPosition.y + getHeight() - 1, 0, getWidth() - 2, 1);

   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.0f, 0.0f, 0.0f, 1.0f));
   //border
   _cTexture->display(currPosition.x, currPosition.y, 0, getWidth(), 1);
   _cTexture->display(currPosition.x, currPosition.y, 0, 1, getHeight());

   _cTexture->display(currPosition.x, currPosition.y + getHeight() - 1, 0, getWidth(), 1);
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y, 0, 1, getHeight());


   _cTexture->disable();

   if (_layout != NULL) {
      _layout->layoutContainer();
   }

   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }
   (static_cast<Application *>(Application::getInstance()))->createPreview();

   scissor->popScissor();
}

void GroupPanel::createTexture(void) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   
   if ((_cTexture = s_customTexture) != NULL) return;

   _cTexture = new scv::ComponentTexture(2, 2);
   kernel->setWidgetTexture(scv::Component::PANEL, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // middle
   _cTexture->addTexture(scv::Point(0,0), scv::MatrixTemplate<scv::ColorRGBA>(1, 1, scv::ColorRGBA(255,255,255,255)));

   //border
   _cTexture->addTexture(scv::Point(0,1), scv::MatrixTemplate<scv::ColorRGBA>(1, 1, scv::ColorRGBA(0,0,0,255)));

   _cTexture->createTexture();

   s_customTexture = _cTexture;
}
