#ifndef __SCV_POPUP_MENU_STYLE_H__
#define __SCV_POPUP_MENU_STYLE_H__

#include "Point.h"
#include "ComponentTexture.h"

namespace scv {

class ContextMenu;

class PopupMenuStyle {
public:
   virtual bool isInsideItem(const scv::ContextMenu *menu, const scv::Point &pos, int index) const;
   virtual scv::Point getSubItemPosition(const scv::ContextMenu *menu, int index) const;

   virtual void drawItem(const scv::ContextMenu *menu, int index) const = 0;

   virtual int calculateWidth(const scv::ContextMenu *menu) const = 0;
   virtual int calculateHeight(const scv::ContextMenu *menu) const = 0;

protected:
   PopupMenuStyle(void);
   virtual ~PopupMenuStyle(void) {}

   virtual void createTexture(void) = 0;

   int _menuSpacing, _borderHeight, _borderWidth, _menuHeight;
   scv::ComponentTexture *_cTexture;
};

} // namespace scv

#endif // __SCV_POPUP_MENU_STYLE_H__
