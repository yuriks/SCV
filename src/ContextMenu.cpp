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
   _status = false;
   _recentlyChange = false;
   _style = VistaMenuStyle::getInstance();
}

ContextMenu::~ContextMenu() {
   removeAllMenus();
   if (_parentMenu == NULL) {
      MenuHolder::getInstance()->unregisterMenu(this);
   } else {
      _parentMenu->removeMenu(this);
   }
}

void ContextMenu::removeMenu(ContextMenu *menu) {
   if (menu == NULL) return;

   MenuList::iterator iter = std::find(_list.begin(), _list.end(), menu);
   if (iter == _list.end()) return;

   _list.erase(iter);

   _height = _style->calculateHeight(*this);
   _witdh = _style->calculateWidth(*this);
}

void ContextMenu::removeAllMenus() {
   MenuList::iterator iter = _list.begin();
   while (iter != _list.end()) {
      ContextMenu *pItem = (*iter);
      iter = _list.erase(iter);
      delete pItem;
   }
   
   _height = _style->calculateHeight(*this);
   _witdh = _style->calculateWidth(*this);
}

void ContextMenu::onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address) {}

void ContextMenu::onMouseOver(const scv::MouseEvent &evt, const std::deque<std::string> &address) {}

void ContextMenu::onMenuAccessed(const std::deque<std::string> &address) {}

void ContextMenu::addMenu(ContextMenu *menu) {
   static FontTahoma *font = FontTahoma::getInstance();
   if (menu == NULL) return;

   menu->registerParentMenu(this);
   _list.push_back(menu);

   _height = _style->calculateHeight(*this);
   _witdh = _style->calculateWidth(*this);
}

bool ContextMenu::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();

   if (getStatus() == false || hasSubMenus() == false) return false;

   if (_currSelectedMenu != -1 && _list[_currSelectedMenu]->processMouse(evt) == true) {
      return true;
   } else {
      if (isInside(evt.getPosition())) {
         for (int i = 0; i < _list.size(); i++) {
            if (isInsideThisMenu(evt.getPosition(), i)) {
                  _currSelectedMenu = i;
                  _list[_currSelectedMenu]->setStatus(true);

                  if (_list[_currSelectedMenu]->hasSubMenus() == false)
                     processMouseCallback(evt, std::deque<std::string>(1, _list[i]->_label));

            } else if (i != _currSelectedMenu || ((_currSelectedMenu != -1)? !_list[_currSelectedMenu]->isInside(evt.getPosition()) : true)) {
               _list[i]->setStatus(false);
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

   if (getStatus() == false || !hasSubMenus()) return false;
   else if (evt.getState() == KeyEvent::UP) return true;

   _recentlyChange = false;

   for (int i = 0; i < _list.size() ; i++) {
      if (_list[i]->getStatus() && _list[i]->hasSubMenus()) {
         _list[i]->processKey(evt);
         return true;
      }
   }
   if (getStatus() == true) {
      if (evt.getKeyString() == "Down") {
         if (_currSelectedMenu == -1) {
            _currSelectedMenu = 0;
         } else {
            _list[_currSelectedMenu]->setStatus(false);
            _currSelectedMenu = ((_currSelectedMenu + 1) % _list.size());
         }
      } else if (evt.getKeyString() == "Up") {
         if (_currSelectedMenu == -1 || (_currSelectedMenu - 1) == -1) {
            _currSelectedMenu = _list.size() - 1;
         } else {
            _list[_currSelectedMenu]->setStatus(false);
            _currSelectedMenu--;
         }
      } else if (evt.getKeyString() == "Right" && _currSelectedMenu != -1) {
         _list[_currSelectedMenu]->setStatus(true);
         _list[_currSelectedMenu]->_recentlyChange = true;
         _list[_currSelectedMenu]->_currSelectedMenu = 0;
      } else if (evt.getKeyString() == "Left" && _parentMenu != NULL) {
         setStatus(false);
         if (_parentMenu!=NULL) {
            _parentMenu->_recentlyChange = true;
         }
      } else if (evt.getKeyString() == "Esc") {
         setStatus(false);
      } else if (evt.getKeyString() == "Enter") {
         if (_currSelectedMenu != -1)
            processKeyboardCallback(evt, std::deque<std::string>(1, _list[_currSelectedMenu]->_label));
         menu->closeAllMenus();
      }
   }
   return true;
}

void ContextMenu::display(void) {
   static Kernel *kernel = Kernel::getInstance();

   if (getStatus() == false || !hasSubMenus()) return;

   if (_currPosition.x + _witdh > kernel->getWidth()) {
      _currPosition.x = kernel->getWidth() - _witdh;
   }
   if (_currPosition.y + _height > kernel->getHeight()) {
      _currPosition.y = _currPosition.y - _height;
   }

   _style->drawItem(*this, _currSelectedMenu);

   // sub-menus
   for (int i = 0; i < _list.size(); i++) {
      _list[i]->display();
      _list[i]->setPosition(_style->getSubItemPosition(*this, i));
   }
}

bool ContextMenu::isInside(const Point &p) {
   if (p.x >= _currPosition.x && p.x <= _currPosition.x + _witdh &&
         p.y >= _currPosition.y && p.y <= _currPosition.y + _height) {
      return true;
   }
   return false;
}


void ContextMenu::setStatus(bool status) {
   _status = status;
   _currSelectedMenu = -1;

   for (int i = 0; i < _list.size(); i++) {
      _list[i]->setStatus(false);
   }
}

void ContextMenu::setSubMenusStatus(bool status) {
   for (int i = 0; i < _list.size(); i++) {
      _list[i]->setStatus(status);
      _list[i]->setSubMenusStatus(status);
   }
}

void ContextMenu::registerParentMenu(ContextMenu *parentMenu) {
   _parentMenu = parentMenu;
}

void ContextMenu::processMouseCallback(const MouseEvent &evt, std::deque<std::string> address) {
   static MenuHolder *holder = MenuHolder::getInstance();

   address.push_front(_label);
   if (_parentMenu == NULL) {
      if (evt.getState() == MouseEvent::UP) {
         holder->closeAllMenus();
         onMouseClick(evt, address);
         onMenuAccessed(address);
      } else if (evt.getState() == MouseEvent::MOTION) {
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
   else if (_list[_currSelectedMenu]->hasSubMenus()) {
      if (_list[_currSelectedMenu]->getStatus()) {
         return true;
      }
   }
   return false;
}

void ContextMenu::setMenuStyle(const PopupItemStyle* style) {
   _style = style;
}

} // namespace scv
