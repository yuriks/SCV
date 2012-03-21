#include "stdafx.h"
#include "PopupMenuStyle.h"

#include "Kernel.h"

scv::PopupMenuStyle::PopupMenuStyle(void) {
   _menuSpacing = _borderHeight = _borderWidth = _menuHeight = 0;
   _cTexture = NULL;
}

scv::PopupMenuStyle::~PopupMenuStyle(void) {

}

bool scv::PopupMenuStyle::isInsideItem(const scv::ContextMenu *menu, const scv::Point &pos, int index) const {
   return (
      pos.x >= menu->getCurrPosition().x + 2 &&
      pos.x <  menu->getCurrPosition().x + menu->getWidth() - 2 &&
      pos.y >= menu->getCurrPosition().y + index * _menuHeight + _borderHeight/2.f + 2 &&
      pos.y <  menu->getCurrPosition().y + index * _menuHeight + _menuHeight + _borderHeight/2.f + 2);
}

scv::Point scv::PopupMenuStyle::getSubItemPosition(const scv::ContextMenu *menu, int index) const {
   static Kernel *kernel = Kernel::getInstance();

   if (kernel->getWidth() - (menu->getCurrPosition().x + menu->getWidth() - _borderWidth + 2) < menu->getMenus()[index]->getWidth()) {
      if (kernel->getHeight() < menu->getCurrPosition().y + index * _menuHeight + menu->getMenus()[index]->getMenus().size() * _menuHeight + _borderHeight)
         return Point(menu->getCurrPosition().x - menu->getMenus()[index]->getWidth() + _borderWidth, kernel->getHeight() - (menu->getMenus()[index]->getMenus().size() * _menuHeight) - _borderHeight);
      else
         return Point(menu->getCurrPosition().x - menu->getMenus()[index]->getWidth() + _borderWidth, menu->getCurrPosition().y + index * _menuHeight);
   } else {
      if (kernel->getHeight() < menu->getCurrPosition().y + index * _menuHeight + menu->getMenus()[index]->getMenus().size() * _menuHeight + _borderHeight)
         return Point(menu->getCurrPosition().x + menu->getWidth() - _borderWidth + 2, kernel->getHeight() - (menu->getMenus()[index]->getMenus().size() * _menuHeight) - _borderHeight);
      else
         return Point(menu->getCurrPosition().x + menu->getWidth() - _borderWidth + 2, menu->getCurrPosition().y + index * _menuHeight);
   }
}