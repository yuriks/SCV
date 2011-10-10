#ifndef __SCV_CONTEXT_MENU_H__
#define __SCV_CONTEXT_MENU_H__

#include "Label.h"
#include "Texture2D.h"

#include "PopupItemStyle.h"

namespace scv {
class MenuHolder;

class ContextMenu {
friend class MenuHolder;
friend class MenuBar;
public:
   ///////////////////////////////////////////////////////////
   typedef std::deque<ContextMenu*> MenuList;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   ContextMenu(const std::string& name);
   virtual ~ContextMenu(void);
   ///////////////////////////////////////////////////////////

   //SCV Callbacks
   ///////////////////////////////////////////////////////////
   virtual void onMenuAccessed(const std::deque<std::string> &address);
   virtual void onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address);
   virtual void onMouseOver(const scv::MouseEvent &evt, const std::deque<std::string> &address);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void addMenu(ContextMenu *menu);
   void removeMenu(ContextMenu *menu);
   void removeAllMenus();
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   std::string getString(void);
   void setString(const std::string &label);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setPosition(const scv::Point &position);
   Point getCurrPosition(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   bool getStatus(void) const;
   void setStatus(bool status);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   int getWidth(void) const;
   int getHeight(void) const;
   ///////////////////////////////////////////////////////////

   bool hasSubMenus(void) const;

   void setMenuStyle(const PopupItemStyle* style);

   const MenuList& getMenus() const;

   ///////////////////////////////////////////////////////////
   bool processMouse(const scv::MouseEvent &evt);
   bool processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   void display(void);

private:
   bool isInside(const Point &p);
   bool isInsideThisMenu(const Point &p, int i) const;

   bool hasSubMenuActive(void) const;
      
   void setSubMenusStatus(bool status);
   void registerParentMenu(ContextMenu *parentMenu);
   void processMouseCallback(const MouseEvent &evt, std::deque<std::string> address);
   void processKeyboardCallback(const KeyEvent &evt, std::deque<std::string> address);

   bool _recentlyChange;
   bool _status;
   int _height, _witdh;
   int _currSelectedMenu;

   MenuList _list;
   ContextMenu *_parentMenu;
   Point _currPosition;
   std::string _label;
   const PopupItemStyle* _style;
};

inline const ContextMenu::MenuList& ContextMenu::getMenus() const {
   return _list;
}

inline bool ContextMenu::hasSubMenus(void) const {
   return _list.size() > 0;
}

inline std::string ContextMenu::getString(void) {
   return _label;
}

inline void ContextMenu::setString(const std::string &label) {
   _label = label;
}

inline void ContextMenu::setPosition(const scv::Point &position) {
   _currPosition = position;
}

inline Point ContextMenu::getCurrPosition(void) const {
   return _currPosition;
}

inline bool ContextMenu::getStatus(void) const {
   return _status;
}

inline int ContextMenu::getWidth(void) const {
   return _witdh;
}

inline int ContextMenu::getHeight(void) const {
   return _height;
}

inline bool ContextMenu::isInsideThisMenu(const Point &p, int i) const {
   return _style->isInsideItem(*this, p, i);
}

} // namespace scv


#endif // __SCV_CONTEXT_MENU_H__
