#ifndef __SCV_VISTA_MENU_STYLE_H__
#define __SCV_VISTA_MENU_STYLE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "PopupMenuStyle.h"
#include "Singleton.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class ComponentTexture;

class VistaMenuStyle : public PopupMenuStyle, public Singleton<VistaMenuStyle> {
public:
   virtual void drawMenu(const ContextMenu& menu, int selected_menu) const;

   virtual bool isInsideMenuItem(const ContextMenu& menu, const Point& pos, int item) const;
   virtual Point getSubmenuPos(const ContextMenu& menu, int menu_index) const;

   virtual int calcWidth(const ContextMenu& menu) const;
   virtual int calcHeight(const ContextMenu& menu) const;

private:
   static const int s_menuSpacing  = 10;
   static const int s_borderHeight = 8;
   static const int s_borderWidth  = 8;
   static const int s_leftBorder   = 28;
   static const int s_menuHeight   = 22;

   VistaMenuStyle();
   void createTexture();

   ComponentTexture* _cTexture;

   friend class Singleton<VistaMenuStyle>;
};

} // namespace scv


#endif // __SCV_VISTA_MENU_STYLE_H__
