#ifndef __SCV_SCROLL_COMPONENT_H__
#define __SCV_SCROLL_COMPONENT_H__

#include "Panel.h"
#include "ComponentWithTexture.h"

namespace scv {

class ScrollComponent : public ComponentWithTexture {
public:
   ///////////////////////////////////////////////////////////
   ScrollComponent(const scv::Point &p1, const scv::Point &p2, scv::Component *object = NULL);
   virtual ~ScrollComponent(void);
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setComponent(scv::Component *object);
   inline scv::Component *getComponent(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setHeight(int height);
   void setWidth(int width);
   ///////////////////////////////////////////////////////////

   void display(void);

protected:
   virtual void refreshSCrollPaneSize(void);
   virtual void refreshContainerPosition(void);

private:
   ///////////////////////////////////////////////////////////
   enum Button {
      BUT_NONE,
      BUT_UP, BUT_DOWN, BUT_VERT,
      BUT_LEFT, BUT_RIGHT, BUT_HORZ,
      BUT_PAGEUP, BUT_PAGEDOWN,
      BUT_PAGELEFT, BUT_PAGERIGHT
   };
   ///////////////////////////////////////////////////////////

   bool isOnLeftButton(Point p);
   bool isOnRightButton(Point p);
   bool isOnUpButton(Point p);
   bool isOnBottomButton(Point p);

   bool isOnVertButton(Point p);
   bool isOnHorzButton(Point p);
   bool isOnVertBar(Point p);
   bool isOnHorzBar(Point p);

   float pixelToFloat(int pix, bool horz);
   float barPixelToFloat(int pix, bool horz);

   void createTexture(void);

   ///////////////////////////////////////////////////////////
   static const int s_initDesloc = 16;
   static const int s_border = 15;
   static const int s_unnecessaryBorder = (3 * s_initDesloc + 1);

   Button _draggingBar, _overButton;

   float _translateHeight, _translateWidth;
   int _scrollSizeVertical, _scrollSizeHorizontal;   
   int _maxDeslocHeight, _maxDeslocWidth;
   int _containerHeight, _containerWidth;
   int _dragBarOffset;

   Point _minContainerPos;

   bool _holdButton;
   Component *_registeredComponent;
};

///////////////////////////////////////////////////////////
scv::Component *ScrollComponent::getComponent(void) const {
   return _registeredComponent;
}
///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_SCROLL_COMPONENT_H__