#ifndef __SCV_MENU_HOLDER_H__
#define __SCV_MENU_HOLDER_H__

#include "Component.h"
#include "Singleton.h"
#include "ContextMenu.h"

namespace scv {

class MenuHolder : public Singleton<MenuHolder> {
   friend class Singleton<MenuHolder>;
public:
   ///////////////////////////////////////////////////////////
   typedef std::list<ContextMenu*> ContextMenuList;
   ///////////////////////////////////////////////////////////

   void display(void);

   ///////////////////////////////////////////////////////////
   bool processMouse(const scv::MouseEvent &evt);
   bool processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void registerMenu(ContextMenu *menu);
   void unregisterMenu(ContextMenu *menu);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void activeMenu(ContextMenu *menu, const Point &position);
   void closeAllMenus(void);
   bool hasActiveMenu(void) const;
   ///////////////////////////////////////////////////////////

private:
   MenuHolder(void);
   ContextMenuList _list;
};

} // namespace scv

#endif // __SCV_MENU_HOLDER_H__
