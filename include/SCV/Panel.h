#ifndef __SCV_PANEL_INTERFACE_H__
#define __SCV_PANEL_INTERFACE_H__

#include "ComponentWithTexture.h"

namespace scv {

class Panel : public ComponentWithTexture {
public:
   ///////////////////////////////////////////////////////////
   Panel(const scv::Point &p1, const scv::Point &p2);
   virtual ~Panel(void);
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

   virtual void onResizing(void);
   virtual void onDragging(void);
   ///////////////////////////////////////////////////////////

   virtual void addChild(Component *object);

   ///////////////////////////////////////////////////////////
   virtual void setPanelScissor(const Scissor::ScissorInfo &scissor);

   virtual void setRelativePosition(const Point &position);
   virtual void setPanelTranslate(const Point &translate);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void);
protected:
   void refresh(bool cScissor, bool cTranslate);
   virtual void createTexture(void);
};

} // namespace scv

#endif // __SCV_PANEL_INTERFACE_H__
