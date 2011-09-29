#ifndef __SCV_COMPONENT__H__
#define __SCV_COMPONENT__H__

///////////////////////////////////////////////////////////
#include "SCVCallbacks.h"
#include "Point.h"
#include "Scissor.h"
///////////////////////////////////////////////////////////

namespace scv {

class ContextMenu;
class Kernel;

class Component : public SCVCallbacks {
public:
   typedef std::list<Component*> List;

   enum objectType {
      NONE        , panel      , colorPicker , progressBar,
      scrool      , slider     , spinner     , button     ,
      checkBox    , radioButton, toggleButton, textField  ,
      textBox     , separator  , window      , menuBar    ,
      tabbedPane  , scrollPane , image       , table      ,
      comboBox    , canvas     , treeView    , label
   };

   ///////////////////////////////////////////////////////////
   Component(const scv::Point &p1, const scv::Point &p2);
   virtual ~Component(void);
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;
   virtual void onMouseHold (const scv::MouseEvent &evt) = 0;
   virtual void onMouseOver (const scv::MouseEvent &evt) = 0;
   virtual void onMouseUp   (const scv::MouseEvent &evt) = 0;
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;
      
   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;
   virtual void onKeyUp     (const scv::KeyEvent &evt) = 0;
   
   virtual void onResizing(void) = 0;
   virtual void onDragging(void) = 0;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual Point getRelativePosition(void) const;
   virtual void setRelativePosition(const Point &position);
   
   virtual void setAbsolutePosition(const Point &position);
   virtual Point getAbsolutePosition(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int getWidth(void) const;
   virtual void setWidth(int width);

   virtual int getHeight(void) const;   
   virtual void setHeight(int height);

   virtual Point getSize(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual bool isOvered(void) const;
   virtual bool isHolded(void) const;
   virtual bool isDragging(void) const;
   virtual bool isResizing(void) const;
   virtual bool isFocused(void) const;
   virtual bool isVisible(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);
   virtual void setVisible(bool state);
   ///////////////////////////////////////////////////////////

   virtual void registerContextMenu(ContextMenu *contextMenu);

   virtual bool isInside(const Point &evtPosition) const;

   ///////////////////////////////////////////////////////////
   virtual bool getCallbacksStatus(void) const;
   virtual void setCallbacksStatus(bool state);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual Scissor::Info getParentScissor(void) const;
   virtual Scissor::Info getScissor(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void) = 0;

   ///////////////////////////////////////////////////////////
   objectType getType(void) const;
   void setType(objectType type);
   ///////////////////////////////////////////////////////////

   //Memory Management
   ///////////////////////////////////////////////////////////
   void setParent(Component *parent);   
   inline Component *getParent(void) const;

   inline const Component::List &getChildren(void) const;

   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);

   void pullChildToTop(Component *child);

   bool hasChild(Component *child) const;
   ///////////////////////////////////////////////////////////

protected:  
   ///////////////////////////////////////////////////////////
   Component *_parent;
   Component::List _children;
   ///////////////////////////////////////////////////////////

   static Kernel *kernel;

   objectType _type;
   static const int s_mouseBacklash = 4;

   Point _p1, _p2, _clicked, _clickDiff, _minSize;

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

   ContextMenu *_contextMenu;
};

Component *Component::getParent(void) const {
   return _parent;
}

const Component::List &Component::getChildren(void) const {
   return _children;
}

} // namespace scv

#endif // __SCV_COMPONENT__H__
