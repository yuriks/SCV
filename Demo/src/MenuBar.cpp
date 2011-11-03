#include "stdafx.h"
#include "MenuBar.h"

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
   if (address[1] == "Generate") {
      std::cout << "Call Generate Code" << std::endl;
   }
}
