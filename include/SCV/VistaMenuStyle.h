#ifndef __SCV_VISTA_MENU_STYLE_H__
#define __SCV_VISTA_MENU_STYLE_H__

#include "PopupMenuStyle.h"
#include "Singleton.h"

namespace scv {

/*!
\ingroup internal
*/

class VistaMenuStyle : public PopupMenuStyle, public Singleton<VistaMenuStyle> {
friend class Singleton<VistaMenuStyle>;
public:
   virtual void drawItem(const scv::ContextMenu *menu, int index) const;

   virtual int calculateWidth(const scv::ContextMenu *menu) const;
   virtual int calculateHeight(const scv::ContextMenu *menu) const;

protected:
   VistaMenuStyle(void);

   virtual void createTexture(void);

   int _leftBorder;
};

} // namespace scv

#endif // __SCV_VISTA_MENU_STYLE_H__
