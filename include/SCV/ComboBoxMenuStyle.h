#ifndef __SCV_COMBOBOX_MENU_STYLE_H__
#define __SCV_COMBOBOX_MENU_STYLE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "PopupMenuStyle.h"
#include "Singleton.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class ComponentTexture;

class ComboBoxMenuStyle : public PopupMenuStyle, public Singleton<ComboBoxMenuStyle> {
public:
   virtual void drawMenu(const ContextMenu& menu, int selected_menu) const;

   virtual bool isInsideMenuItem(const ContextMenu& menu, const Point& pos, int item) const;
   virtual Point getSubmenuPos(const ContextMenu& menu, int menu_index) const;

   virtual int calcWidth(const ContextMenu& menu) const;
   virtual int calcHeight(const ContextMenu& menu) const;

private:
   static const int s_menuSpacing  = 0;
   static const int s_borderHeight = 0;
   static const int s_borderWidth  = 0;
   static const int s_horzMargin   = 4;
   static const int s_menuHeight   = 13;

   ComboBoxMenuStyle();
   void createTexture();

   ComponentTexture* _cTexture;

   friend class Singleton<ComboBoxMenuStyle>;
};

} // namespace scv


#endif // __SCV_COMBOBOX_MENU_STYLE_H__
