#include "stdafx.h"
#include "MenuBar.h"

#include "CodeGenerator.h"

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
      CodeGenerator::getInstance()->generateCode();
   }
}
