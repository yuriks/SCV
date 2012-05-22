#ifndef __SCV_MENU_BAR_H__
#define __SCV_MENU_BAR_H__

#include "Panel.h"

namespace scv {

class MenuBar : public Panel {
public:
   MenuBar(int width);

   void addMenu(ContextMenu *menu);
   
   bool hasActiveMenu(void) const;
   void activeMenu(int id);

   void closeAllMenus(void);

   int getNumberOfMenus();
   
protected:   
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);

   virtual void createTexture(void);
    
   virtual void display(void);

private:
   static const int s_menuHeight;
   static const int s_menuSpacing;
   static const int s_borderWidth, s_borderHeight;

   int _currSelectedMenu, _currecOverMenu;
   bool _active;

   std::vector<int> _index;
   std::vector<ContextMenu*> _menus;
};

} // namespace scv

#endif // __SCV_MENU_BAR_H__
