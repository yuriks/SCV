#ifndef __SCV_COMPONENT_INTERFACE_H__
#define __SCV_COMPONENT_INTERFACE_H__

///////////////////////////////////////////////////////////
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "Scissor.h"
///////////////////////////////////////////////////////////

namespace scv {

class ContextMenu;

class SCVObject : public std::enable_shared_from_this<SCVObject> {
public:
   typedef std::shared_ptr<SCVObject> Ptr;
   typedef std::list<Ptr> PtrList;

   enum typeComponent {
      NONE        , panel      , colorPicker , progressBar,
      scrool      , slider     , spinner     , button     ,
      checkBox    , radioButton, toggleButton, textField  ,
      textBox     , separator  , window      , menuBar    ,
      tabbedPane  , scrollPane , image       , table      ,
      comboBox    , canvas     , treeView    , label
   };

   ///////////////////////////////////////////////////////////
   SCVObject(const scv::Point &p1, const scv::Point &p2);
   virtual ~SCVObject(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;   
   virtual void onMouseHold(const scv::MouseEvent &evt) = 0;   
   virtual void onMouseOver(const scv::MouseEvent &evt) = 0;   
   virtual void onMouseUp(const scv::MouseEvent &evt) = 0;   
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;
   ///////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////
   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;   
   virtual void onKeyUp(const scv::KeyEvent &evt) = 0;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void onResizing(void) = 0;
   virtual void onDragging(void) = 0;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setRelativePosition(const Point &position);
   Point getRelativePosition(void) const;
   Point getAbsolutePosition(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int getWidth(void) const;
   virtual int getHeight(void) const;
   virtual Point getSize(void) const;
   virtual void setWidth(const int width);
   virtual void setHeight(const int height);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   bool isOvered(void) const;
   bool isHolded(void) const;
   bool isDragging(void) const;
   bool isResizing(void) const;
   bool isFocused(void) const;
   bool isVisible(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);
   virtual void setVisible(bool state);
   ///////////////////////////////////////////////////////////

   void registerContextMenu(ContextMenu *contextMenu);

   bool isInside(const MouseEvent &evt) const;

   ///////////////////////////////////////////////////////////
   bool isCallbacksActive(void);
   void setCallbacksActive(bool state);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setPanelTranslate(const Point &translate);
   Point getPanelTranslate(void);

   virtual void setPanelScissor(const Scissor::ScissorInfo &scissor);
   const Scissor::ScissorInfo &getPanelScissor(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void) = 0;

   typeComponent getType(void);


   Ptr _parent;
   PtrList _children;

   ///////////////////////////////////////////////////////////

   void deleteChildren();

   void setParent(SCVObject::Ptr& parent);

   inline const SCVObject::Ptr& getParent() const;

   inline const SCVObject::PtrList& getChildren() const;

   void addChild(SCVObject::Ptr& object);

   void removeChild(SCVObject::Ptr& object);

   void pullChildToTop(const SCVObject::PtrList::const_iterator& child);

   ///////////////////////////////////////////////////////////
 protected:  
   typeComponent _type;
   static const int s_mouseBacklash = 4;

   Scissor::ScissorInfo _panelScissor;
   Point _p1, _p2, _cTranslate, _clicked, _minSize;

   bool _receivingCallbacks;
   bool _isResizable, _isResizing;
   bool _isHResizable, _isVResizable;
   bool _isDraggable, _isDragging;
   bool _isOvered, _isHolded;
   bool _isVisible;

   // left, right, top, bottom
   std::vector<bool> _resizing;
   // topLeft, topRight, bottomLeft, bottomRight (0,1,2,3)
   int isInsideCorner(const Point &evtPosition);
   // left, right, top, bottom (0,1,2,3)
   int isInsideSide(const Point &evtPosition);
   void moveComponent(const scv::KeyEvent &evt);

   ContextMenu *_contextMenu;
};

const SCVObject::Ptr& SCVObject::getParent() const {
   return _parent;
}

const SCVObject::PtrList& SCVObject::getChildren() const {
   return _children;
}

} // namespace scv

#endif // __SCV_COMPONENT_INTERFACE_H__
