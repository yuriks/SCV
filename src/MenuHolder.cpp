#include "stdafx.h"
#include "MenuHolder.h"
#include "ContextMenu.h"

namespace scv {

MenuHolder::MenuHolder(void) {/**/}

void MenuHolder::display(void) {
   for (int i = 0; i < _menus.size(); i++) {
      _menus[i]->display();
   }
}

bool MenuHolder::processMouse(const scv::MouseEvent &evt) {
   bool status = false;

   for (int i = 0; i < _menus.size(); i++) {
      if (_menus[i]->processMouse(evt)) status = true;
   }

   if (status == false && evt.getState() == MouseEvent::click) {
      closeAllMenus();
   }
   return status;
}

bool MenuHolder::processKey(const scv::KeyEvent &evt) {
   bool status = false;
   for (int i = 0; i < _menus.size(); i++) {
      if (_menus[i]->processKey(evt)) status = true;
   }
   return status;
}

void MenuHolder::registerParentMenu(ContextMenu *menu) {
   _menus.push_back(menu);
}

void MenuHolder::activeMenu(ContextMenu *menu, const Point &p) {
   for (int i = 0; i < _menus.size(); i++) {
      _menus[i]->setMenuStatus(false);
   }
   menu->_active = true;
   menu->setPosition(p);
}

void MenuHolder::closeAllMenus(void) {
   for (int i = 0; i < _menus.size(); i++) {
      _menus[i]->setMenuStatus(false);
      _menus[i]->setSubMenusStatus(false);
   }
}

bool MenuHolder::hasActiveMenu(void) const {
   for (int i = 0; i < _menus.size(); i++)
      if (_menus[i]->isActive()) return true;
   return false;
}

} // namespace scv