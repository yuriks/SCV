#include <SCV/SCV.h>
#include "MenuBar.h"

#include "CodeGenerator.h"

#include "ObjectEditor.h"

CodeMenu::CodeMenu(void) : scv::ContextMenu("Code") {
   addMenu(new scv::ContextMenu("Generate"));
}

CodeMenu::~CodeMenu(void) {
}

void CodeMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address[1] == "Generate") {
      CodeGenerator::getInstance()->generateCode();
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ManagedObjectsMenu::ManagedObjectsMenu(void) : scv::ContextMenu("Managed Objects") {
   addMenu(new scv::ContextMenu("- Empty -"));
}

ManagedObjectsMenu::~ManagedObjectsMenu(void) {
}

void ManagedObjectsMenu::onMenuAccessed(const std::deque<std::string> &address) {
   if (address[1] != "- Empty -") {
      ManagedComponent *object = CodeGenerator::getInstance()->getManagedComponent(address[1]);
      if (object != NULL) {
         ObjectEditor::getInstance()->setComponent(object->getComponent());
      }      
   }
}

void ManagedObjectsMenu::onStatusChange(void) {
   if (getStatus() && CodeGenerator::getInstance()->getManagedComponents().size() > 0) {
      removeAllMenus();
      CodeGenerator::ManagedList list = CodeGenerator::getInstance()->getManagedComponents();
      for (CodeGenerator::ManagedList::iterator iter = list.begin(); iter != list.end(); ++iter) {
         addMenu(new scv::ContextMenu((*iter)->getClassName()));
      }
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

MenuBar::MenuBar(int width) : scv::MenuBar(width) {
   addMenu(new CodeMenu());

   addMenu(new ManagedObjectsMenu());

   scv::ContextMenu *about = new scv::ContextMenu("About");
   addMenu(about);
   about->addMenu(new scv::ContextMenu("More info: http://www.inf.ufsm.br/~pozzer/scv"));
}

MenuBar::~MenuBar(void) {
}