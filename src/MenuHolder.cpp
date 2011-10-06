#include "stdafx.h"
#include "MenuHolder.h"
#include "ContextMenu.h"

namespace scv {

MenuHolder::MenuHolder(void) {/**/}

void MenuHolder::display(void) {
   for (ContextMenuList::iterator iter = _list.begin(); iter != _list.end(); ++iter) {
      (*iter)->display();
   }
}

bool MenuHolder::processMouse(const scv::MouseEvent &evt) {
   bool status = false;

   for (ContextMenuList::iterator iter = _list.begin(); iter != _list.end(); ++iter) {
      if ((*iter)->processMouse(evt)) status = true;
   }

   if (status == false && evt.getState() == MouseEvent::CLICK) {
      closeAllMenus();
   }
   return status;
}

bool MenuHolder::processKey(const scv::KeyEvent &evt) {
   bool status = false;
   for (ContextMenuList::iterator iter = _list.begin(); iter != _list.end(); ++iter) {
      if ((*iter)->processKey(evt)) status = true;
   }
   return status;
}

void MenuHolder::registerMenu(ContextMenu *menu) {
   if (std::find(_list.begin(), _list.end(), menu) == _list.end()) {
      _list.push_back(menu);
   }
}


void MenuHolder::unregisterMenu(ContextMenu *menu) {
   if (std::find(_list.begin(), _list.end(), menu) != _list.end()) {
      _list.remove(menu);
   }
}

void MenuHolder::activeMenu(ContextMenu *menu, const Point &position) {
   for (ContextMenuList::iterator iter = _list.begin(); iter != _list.end(); ++iter) {
      (*iter)->setStatus(false);
   }
   menu->setStatus(true);
   menu->setPosition(position);
}

void MenuHolder::closeAllMenus(void) {
   for (ContextMenuList::iterator iter = _list.begin(); iter != _list.end(); ++iter) {
      (*iter)->setStatus(false);
      (*iter)->setSubMenusStatus(false);
   }
}

bool MenuHolder::hasActiveMenu(void) const {
   for (ContextMenuList::const_iterator iter = _list.begin(); iter != _list.end(); ++iter) {
      if ((*iter)->getStatus()) return true;
   }
   return false;
}

} // namespace scv