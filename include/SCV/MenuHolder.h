/*!
\file       MenuHolder.h
\brief      Manages the context menus.
\author     SCV Team
*/

#ifndef __SCV_MENU_HOLDER_H__
#define __SCV_MENU_HOLDER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "SCVObject.h"
#include "Singleton.h"
#include "ContextMenu.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! This class controls the context menus of the application.
 * \ingroup internal
 */

class MenuHolder : public Singleton<MenuHolder> {
   friend class Singleton<MenuHolder>;
public:

   void display(void);

   bool processMouse(const scv::MouseEvent &evt);

   bool processKey(const scv::KeyEvent &evt);

   void registerParentMenu(ContextMenu *menu);

   void activeMenu(ContextMenu *menu, const Point &p);

   void closeAllMenus(void);

   bool hasActiveMenu(void) const;

private:
   MenuHolder(void);

   std::deque<ContextMenu*> _menus;
};

} // namespace scv

#endif // __SCV_MENU_HOLDER_H__
