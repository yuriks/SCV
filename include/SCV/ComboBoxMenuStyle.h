#ifndef __SCV_COMBOBOX_MENU_STYLE_H__
#define __SCV_COMBOBOX_MENU_STYLE_H__

#include "PopupMenuStyle.h"
#include "Singleton.h"

namespace scv {
 
/*! 
\ingroup internal
*/

class ComboBoxMenuStyle : public PopupMenuStyle, public Singleton<ComboBoxMenuStyle> {
friend class Singleton<ComboBoxMenuStyle>;
public:
   virtual void drawItem(const scv::ContextMenu *menu, int index) const;

   virtual int calculateWidth(const scv::ContextMenu *menu) const;
   virtual int calculateHeight(const scv::ContextMenu *menu) const;

protected:
   ComboBoxMenuStyle(void);

   virtual void createTexture(void);

   int _horzMargin;   
};

} // namespace scv

#endif // __SCV_COMBOBOX_MENU_STYLE_H__
