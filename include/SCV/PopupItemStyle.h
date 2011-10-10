#ifndef __SCV_POPUP_ITEM_STYLE_H__
#define __SCV_POPUP_ITEM_STYLE_H__

namespace scv {

class ContextMenu;
class Point;

class PopupItemStyle {
public:
   ///////////////////////////////////////////////////////////
   virtual ~PopupItemStyle(void) {}
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void drawItem(const ContextMenu &item, int selectedItem) const = 0;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual bool isInsideItem(const ContextMenu &item, const Point &pos, int index) const = 0;
   virtual Point getSubItemPosition(const ContextMenu &item, int index) const = 0;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int calculateWidth(const ContextMenu &item) const = 0;
   virtual int calculateHeight(const ContextMenu &item) const = 0;
   ///////////////////////////////////////////////////////////
};

} // namespace scv

#endif // __SCV_POPUP_ITEM_STYLE_H__
