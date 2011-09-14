/*!
\file       ContextMenu.h
\brief      Implementation of a drop down menu.
\author     SCV Team
*/

#ifndef __SCV_CONTEXT_MENU_H__
#define __SCV_CONTEXT_MENU_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Label.h"
#include "Texture2D.h"

#include "PopupMenuStyle.h"
#endif DOXYGEN_SKIP_THIS

namespace scv {
class MenuHolder;

/*! A drop down menu that can be displayed in any position.
 * \ingroup widgets
 */

class ContextMenu {
friend class MenuHolder;
friend class MenuBar;
public:
   typedef std::deque<ContextMenu*> MenuList;

   /*! Constructor
   \param name The text in the menu's label.
   */
   ContextMenu(const std::string& name);
   /*! Default Destructor
   */
   virtual ~ContextMenu();

   /*! Main Callback
   \param address Returns a deque with the path to the current sub menu accessed.
   */
   virtual void onMenuAccessed(const std::deque<std::string> &address);
   /*! Mouse Callback
   This function is called when mouse clicks on this component.
   \param evt Contains the event information.
   \param address Returns a deque with the path to the current sub menu accessed.
   */
   virtual void onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address);
   /*! Mouse Callback
   This function is called when the user moves your mouse over this component.
   \param evt Contains the event information.
   \param address Returns a deque with the path to the current sub menu accessed.
   */
   virtual void onMouseOver(const scv::MouseEvent &evt, const std::deque<std::string> &address);

   /*! Adds a menu item to the context menu.
   \param menu New context menu.
   */
   void addMenu(ContextMenu *menu);
   /*! Removes a menu item of the context menu.
   \param menu The context menu to be removed.
   */
   void removeMenu(ContextMenu *menu);
   /*! Removes all menus of the context menu.
   */
   void removeAllMenus();
   /*! Gets the name of the context menu.
   */
   std::string getString(void);
   /*! Sets a name to the context menu.
   \param label The new name of the context menu.
   */
   void setString(const std::string &label);
   /*! Sets a position to the context menu.
   \param p The new position of the component.
   */
   void setPosition(const scv::Point &p);
   /*! Gets the position of the context menu.
   */
   Point getCurrPosition(void) const;
   /*! Verifies if the context menu is active.
   */
   bool isActive(void);
   /*! Close the context menu.
   */
   void close(void);
   /*! Gets the with of the context menu.
   */
   int getWidth() const;
   /*! Gets the height of the context menu.
   */
   int getHeight() const;
   /*! Verifies if the context menu have submenus.
   */
   bool hasSubMenus(void) const;
   /*! Sets a new style to the context menu.
   * If you have no experience with the scv don't to use this function.
   */
   void setMenuStyle(const PopupMenuStyle* style);
   /*! Gets a reference to the menus of the context menu.
   * If you have no experience with the scv don't to use this function.
   */
   const MenuList& getMenus() const;
   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   bool processMouse(const scv::MouseEvent &evt);
   //! Keyboard function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   bool processKey(const scv::KeyEvent &evt);
   void display(void);

private:

   
   

   bool isInside(const Point &p);
   bool isInsideThisMenu(const Point &p, int i) const;

   bool hasSubMenuActive(void) const;

   void setMenuStatus(bool status);
   void setSubMenusStatus(bool status);
   void registerParentMenu(ContextMenu *parentMenu);
   void processMouseCallback(const MouseEvent &evt, std::deque<std::string> address);
   void processKeyboardCallback(const KeyEvent &evt, std::deque<std::string> address);

   bool _recentlyChange;
   bool _active;
   int _height, _witdh;
   int _currSelectedMenu;

   MenuList _menus;
   ContextMenu *_parentMenu;
   Point _currPosition;
   std::string _label;
   const PopupMenuStyle* _style;
};

inline const ContextMenu::MenuList& ContextMenu::getMenus() const {
   return _menus;
}

inline bool ContextMenu::hasSubMenus(void) const {
   return _menus.size() > 0;
}

inline std::string ContextMenu::getString(void) {
   return _label;
}

inline void ContextMenu::setString(const std::string &label) {
   _label = label;
}

inline void ContextMenu::setPosition(const scv::Point &p) {
   _currPosition = p;
}

inline Point ContextMenu::getCurrPosition(void) const {
   return _currPosition;
}

inline bool ContextMenu::isActive(void) {
   return _active;
}

inline void ContextMenu::close(void) {
   _active = false;
}

inline int ContextMenu::getWidth() const {
   return _witdh;
}

inline int ContextMenu::getHeight() const {
   return _height;
}

inline bool ContextMenu::isInsideThisMenu(const Point &p, int i) const {
   return _style->isInsideMenuItem(*this, p, i);
}

} // namespace scv


#endif // __SCV_CONTEXT_MENU_H__
