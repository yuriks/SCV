#ifndef __SCV_VISTA_MENU_STYLE_H__
#define __SCV_VISTA_MENU_STYLE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "PopupItemStyle.h"
#include "Singleton.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class ComponentTexture;

class VistaMenuStyle : public PopupItemStyle, public Singleton<VistaMenuStyle> {
public:
   ///////////////////////////////////////////////////////////
   virtual void drawItem(const ContextMenu &item, int selectedItem) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual bool isInsideItem(const ContextMenu &item, const Point &pos, int index) const;
   virtual Point getSubItemPosition(const ContextMenu &item, int index) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int calculateWidth(const ContextMenu &item) const;
   virtual int calculateHeight(const ContextMenu &item) const;
   ///////////////////////////////////////////////////////////

private:
   static const int s_menuSpacing  = 10;
   static const int s_borderHeight = 8;
   static const int s_borderWidth  = 8;
   static const int s_leftBorder   = 28;
   static const int s_menuHeight   = 22;

   VistaMenuStyle();
   virtual ~VistaMenuStyle(void) {}

   void createTexture();

   ComponentTexture* _cTexture;

   friend class Singleton<VistaMenuStyle>;
};

} // namespace scv


#endif // __SCV_VISTA_MENU_STYLE_H__
