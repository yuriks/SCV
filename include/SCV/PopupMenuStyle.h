#ifndef __SCV_POPUP_MENU_STYLE_H__
#define __SCV_POPUP_MENU_STYLE_H__

namespace scv {

class ContextMenu;
class Point;

class PopupMenuStyle {
public:
   virtual ~PopupMenuStyle() {};

   virtual void drawMenu(const ContextMenu& menu, int selected_menu) const = 0;

   virtual bool isInsideMenuItem(const ContextMenu& menu, const Point& pos, int item) const = 0;
   virtual Point getSubmenuPos(const ContextMenu& menu, int menu_index) const = 0;

   virtual int calcWidth(const ContextMenu& menu) const = 0;
   virtual int calcHeight(const ContextMenu& menu) const = 0;
};

} // namespace scv


#endif // __SCV_POPUP_MENU_STYLE_H__
