#include "stdafx.h"
#include "MenuBar.h"

#include "Application.h"

MenuBar::MenuBar(int width) : scv::MenuBar(width) {
   addMenu(new CodeContextMenu());
}

MenuBar::~MenuBar(void) {

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

CodeContextMenu::CodeContextMenu(void) : scv::ContextMenu("Code") {
   addMenu(new scv::ContextMenu("Generate"));
}

CodeContextMenu::~CodeContextMenu(void) {

}

void CodeContextMenu::onMenuAccessed(const std::deque<std::string> &address) {
   static Application *app = static_cast<Application*>(scv::Kernel::getInstance());

   if (address[1] == "Generate") {
      app->getLayoutCode();
   }
}
