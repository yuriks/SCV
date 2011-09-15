#include "stdafx.h"
#include "ContextMenu.h"
#include "Kernel.h"
#include "Label.h"
#include "MenuHolder.h"

#include "VistaMenuStyle.h"

namespace scv {

ContextMenu::ContextMenu(const std::string& name) : _label(name) {
   _height = _witdh = 0;
   _currSelectedMenu = -1;
   _parentMenu = NULL;
   _active = false;
   _recentlyChange = false;
   _style = VistaMenuStyle::getInstance();
}

ContextMenu::~ContextMenu() {
   removeAllMenus();
}

void ContextMenu::addMenu(ContextMenu *menu) {
   static FontTahoma *font = FontTahoma::getInstance();
   if (menu == NULL) return;

   menu->registerParentMenu(this);
   _menus.push_back(menu);

   _height = _style->calcHeight(*this);
   _witdh = _style->calcWidth(*this);
}

void ContextMenu::removeMenu(ContextMenu *menu) {
   if (menu == NULL) return;

   MenuList::iterator i = std::find(_menus.begin(), _menus.end(), menu);

   if (i == _menus.end())
      return;

   _menus.erase(i);

   _height = _style->calcHeight(*this);
   _witdh = _style->calcWidth(*this);
}

void ContextMenu::removeAllMenus() {
   for (MenuList::iterator i = _menus.begin(); i != _menus.end(); ++i) {
      delete *i;
   }

   _menus.clear();

   _height = _style->calcHeight(*this);
   _witdh = _style->calcWidth(*this);
}

void ContextMenu::onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address) {/*none*/}
void ContextMenu::onMouseOver(const scv::MouseEvent &evt, const std::deque<std::string> &address) {/*none*/}

void ContextMenu::onMenuAccessed(const std::deque<std::string> &address) {/*none*/}

bool ContextMenu::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();

   if (isActive() == false || hasSubMenus() == false) return false;

   if (_currSelectedMenu != -1 && _menus[_currSelectedMenu]->processMouse(evt) == true) {
      return true;
   } else {
      if (isInside(evt.getPosition())) {
         for (int i = 0; i < _menus.size(); i++) {
            if (isInsideThisMenu(evt.getPosition(), i)) {
                  _currSelectedMenu = i;
                  _menus[_currSelectedMenu]->setMenuStatus(true);

                  if (_menus[_currSelectedMenu]->hasSubMenus() == false)
                     processMouseCallback(evt, std::deque<std::string>(1, _menus[i]->_label));

            } else if (i != _currSelectedMenu || ((_currSelectedMenu != -1)? !_menus[_currSelectedMenu]->isInside(evt.getPosition()) : true)) {
               _menus[i]->setMenuStatus(false);
            }
         }
         return true;
      } else if (!hasSubMenuActive()) {
         _currSelectedMenu = -1;
      }
   }


   return false;
}

bool ContextMenu::processKey(const scv::KeyEvent &evt) {
   static MenuHolder *menu = MenuHolder::getInstance();

   if (isActive() == false || !hasSubMenus()) return false;
   else if (evt.getState() == KeyEvent::up) return true;

   _recentlyChange = false;

   for (int i = 0; i < _menus.size() ; i++) {
      if (_menus[i]->isActive() && _menus[i]->hasSubMenus()) {
         _menus[i]->processKey(evt);
         return true;
      }
   }
   if (isActive() == true) {
      if (evt.getKeyString() == "Down") {
         if (_currSelectedMenu == -1) {
            _currSelectedMenu = 0;
         } else {
            _menus[_currSelectedMenu]->setMenuStatus(false);
            _currSelectedMenu = ((_currSelectedMenu + 1) % _menus.size());
         }
      } else if (evt.getKeyString() == "Up") {
         if (_currSelectedMenu == -1 || (_currSelectedMenu - 1) == -1) {
            _currSelectedMenu = _menus.size() - 1;
         } else {
            _menus[_currSelectedMenu]->setMenuStatus(false);
            _currSelectedMenu--;
         }
      } else if (evt.getKeyString() == "Right" && _currSelectedMenu != -1) {
         _menus[_currSelectedMenu]->setMenuStatus(true);
         _menus[_currSelectedMenu]->_recentlyChange = true;
         _menus[_currSelectedMenu]->_currSelectedMenu = 0;
      } else if (evt.getKeyString() == "Left" && _parentMenu != NULL) {
         setMenuStatus(false);
         if (_parentMenu!=NULL) {
            _parentMenu->_recentlyChange = true;
         }
      } else if (evt.getKeyString() == "Esc") {
         setMenuStatus(false);
      } else if (evt.getKeyString() == "Enter") {
         if (_currSelectedMenu != -1)
            processKeyboardCallback(evt, std::deque<std::string>(1, _menus[_currSelectedMenu]->_label));
         menu->closeAllMenus();
      }
   }
   return true;
}

void ContextMenu::display(void) {
   static Kernel *kernel = Kernel::getInstance();

   if (isActive() == false || !hasSubMenus()) return;

   if (_currPosition.x + _witdh > kernel->getWidth()) {
      _currPosition.x = kernel->getWidth() - _witdh;
   }
   if (_currPosition.y + _height > kernel->getHeight()) {
      _currPosition.y = _currPosition.y - _height;
   }

   _style->drawMenu(*this, _currSelectedMenu);

   // sub-menus
   for (int i = 0; i < _menus.size(); i++) {
      _menus[i]->display();
      _menus[i]->setPosition(_style->getSubmenuPos(*this, i));
   }
}

bool ContextMenu::isInside(const Point &p) {
   if (p.x >= _currPosition.x && p.x <= _currPosition.x + _witdh &&
         p.y >= _currPosition.y && p.y <= _currPosition.y + _height) {
      return true;
   }
   return false;
}


void ContextMenu::setMenuStatus(bool status) {
   _active = status;
   _currSelectedMenu = -1;

   for (int i = 0; i < _menus.size(); i++) {
      _menus[i]->setMenuStatus(false);
   }
}

void ContextMenu::setSubMenusStatus(bool status) {
   for (int i = 0; i < _menus.size(); i++) {
      _menus[i]->setMenuStatus(status);
      _menus[i]->setSubMenusStatus(status);
   }
}

void ContextMenu::registerParentMenu(ContextMenu *parentMenu) {
   _parentMenu = parentMenu;
}

void ContextMenu::processMouseCallback(const MouseEvent &evt, std::deque<std::string> address) {
   static MenuHolder *holder = MenuHolder::getInstance();

   address.push_front(_label);
   if (_parentMenu == NULL) {
      if (evt.getState() == MouseEvent::up) {
         holder->closeAllMenus();
         onMouseClick(evt, address);
         onMenuAccessed(address);
      } else if (evt.getState() == MouseEvent::motion) {
         onMouseOver(evt, address);
      }
   } else _parentMenu->processMouseCallback(evt, address);
}

void ContextMenu::processKeyboardCallback(const KeyEvent &evt, std::deque<std::string> address) {
   address.push_front(_label);
   if (_parentMenu == NULL) {
      onMenuAccessed(address);
   } else _parentMenu->processKeyboardCallback(evt, address);
}

bool ContextMenu::hasSubMenuActive(void) const {
   if (_currSelectedMenu == -1) return false;
   else if (_menus[_currSelectedMenu]->hasSubMenus()) {
      if (_menus[_currSelectedMenu]->isActive()) {
         return true;
      }
   }
   return false;
}

void ContextMenu::setMenuStyle(const PopupMenuStyle* style) {
   _style = style;
}

} // namespace scv
