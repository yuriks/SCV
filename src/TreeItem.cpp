#include "stdafx.h"
#include "TreeItem.h"
#include "VistaMenuStyle.h"

namespace scv {

TreeItem::TreeItem(const std::string& name) : Component(Point(100,100), Point(100, 100)) {
   _type = NONE;

   _label = name;

   _currSelectedItem = -1;
   _parentItem = NULL;
   _status = true;
   _recentlyChange = false;

   _style = new DefaultSytle();
}

TreeItem::~TreeItem(void) {
}

///////////////////////////////////////////////////////////
void TreeItem::onMouseClick(const scv::MouseEvent &evt) {
}
void TreeItem::onMouseHold(const scv::MouseEvent &evt) {
}
void TreeItem::onMouseOver(const scv::MouseEvent &evt) {
}
void TreeItem::onMouseUp(const scv::MouseEvent &evt) {
}
void TreeItem::onMouseWheel(const scv::MouseEvent &evt) {
}

void TreeItem::onKeyPressed(const scv::KeyEvent &evt) {
}
void TreeItem::onKeyUp(const scv::KeyEvent &evt) {
}

void TreeItem::onSizeChange(void) {
}
void TreeItem::onPositionChange(void) {
}
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
void TreeItem::onItemAccessed(const std::deque<std::string> &address) {
}
void TreeItem::onItemSelection(const std::deque<std::string> &address) {
}
void TreeItem::onItemOver(const std::deque<std::string> &address) {
}
///////////////////////////////////////////////////////////

void TreeItem::addChild(Component *object) {
   TreeItem *pItem = dynamic_cast<TreeItem*>(object);
   if (pItem == NULL) return;

   Component::addChild(object);
   
   setHeight(_style->calculateHeight(*this));
   setWidth(_style->calculateWidth(*this));

   setPreferredSize(getSize());
   setMinimumSize(getSize());
}

void TreeItem::removeChild(Component *object) {
   TreeItem *pItem = dynamic_cast<TreeItem*>(object);
   if (pItem == NULL) return;

   Component::removeChild(object);

   setHeight(_style->calculateHeight(*this));
   setWidth(_style->calculateWidth(*this));

   setPreferredSize(getSize());
   setMinimumSize(getSize());   
}

std::string TreeItem::getString(void) {
   return _label;
}

void TreeItem::setString(const std::string &label) {
   _label = label;
}

bool TreeItem::getStatus(void) const {
   return _status;
}

void TreeItem::setStatus(bool status) {
   _status = status;
}

bool TreeItem::hasSubItems(void) const {
   return _children.size() > 0;
}

void TreeItem::setItemStyle(const scv::PopupItemStyle *style) {

}

void TreeItem::processMouse(const scv::MouseEvent &evt) {
   Component::processMouse(evt);
}

void TreeItem::processKey(const scv::KeyEvent &evt) {
   Component::processKey(evt);
}

void TreeItem::display(void) {
   if (getStatus() == false || !hasSubItems()) return;

   Point currPosition = getAbsolutePosition();

   _style->drawItem(*this, _currSelectedItem);
   
   //subItems
   int i = 0;
   for (Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter, ++i) {
      (*iter)->setRelativePosition(_style->getSubItemPosition(*this, i));
      (*iter)->display();
   }   
}

bool TreeItem::isInsideItem(const scv::Point &position, int index) const {
   //return _style->isInsideItem(*this, p, i);
   return true;
}

bool TreeItem::hasSubMenuActive(void) {
   if (_currSelectedItem == -1) {
      return false;
   } else {
      TreeItem *pItem = static_cast<TreeItem*>(getChild(_currSelectedItem));
      if (pItem->hasSubItems() && pItem->getStatus()) {
         return true;
      } else {
         return false;
      }
   }
   return false;
}

void TreeItem::setSubItemsStatus(bool status) {
   TreeItem *pItem;
   for (Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      pItem = static_cast<TreeItem*>(*iter);
      pItem->setStatus(status);
      pItem->setSubItemsStatus(status);
   }
}

void TreeItem::processMouseCallback(const scv::MouseEvent &evt, std::deque<std::string> address) {

}

void TreeItem::processKeyboardCallback(const scv::KeyEvent &evt, std::deque<std::string> address) {

}

} //namespace scv