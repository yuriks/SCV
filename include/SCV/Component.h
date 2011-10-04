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
   ///////////////////////////////////////////////////////////
   typedef std::list<Component*> List;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   enum ObjectType {
      NONE        , panel      , colorPicker , progressBar,
      scrool      , slider     , spinner     , button     ,
      checkBox    , radioButton, toggleButton, textField  ,
      textBox     , separator  , window      , menuBar    ,
      tabbedPane  , scrollPane , image       , table      ,
      comboBox    , canvas     , treeView    , label
   };
   ///////////////////////////////////////////////////////////

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

   //position
   ///////////////////////////////////////////////////////////
   virtual Point getRelativePosition(void) const;
   virtual void setRelativePosition(const Point &position);
   
   virtual Point getAbsolutePosition(void) const;
   virtual void setAbsolutePosition(const Point &position);   
   ///////////////////////////////////////////////////////////

   //size
   ///////////////////////////////////////////////////////////
   virtual inline int getWidth(void) const;
   virtual void setWidth(int width);

   virtual inline int getHeight(void) const;   
   virtual void setHeight(int height);

   virtual inline Point getSize(void) const;

   virtual inline Point getMinimumSize(void) const;
   virtual inline Point getPreferredSize(void) const;
   virtual inline Point getMaximumSize(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual inline bool isOvered(void) const;
   virtual inline bool isHolded(void) const;
   virtual inline bool isDragging(void) const;
   virtual inline bool isResizing(void) const;   
   virtual inline bool isVisible(void) const;
   ///////////////////////////////////////////////////////////

   virtual bool isFocused(void) const;

   ///////////////////////////////////////////////////////////
   virtual inline void setDraggable(bool state);
   virtual inline void setResizable(bool state);
   virtual inline void setVisible(bool state);
   ///////////////////////////////////////////////////////////

   virtual void registerContextMenu(ContextMenu *contextMenu);
   virtual void unregisterContextMenu(void);

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
   ObjectType getType(void) const;
   void setType(ObjectType type);
   ///////////////////////////////////////////////////////////

   //memory management
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

   ObjectType _type;
   static const int s_mouseBacklash = 4;

   Point _p1, _p2, _clickDiff, _minSize;

   bool _receivingCallbacks;
   bool _isResizable, _isResizing;
   bool _isHResizable, _isVResizable;
   bool _isDraggable, _isDragging;
   bool _isOvered, _isHolded;
   bool _isVisible;

   void setResizingCursor(void);

   enum Side { left, right, top, bottom };
   std::vector<bool> _resizing;
   bool isInsideSide(Component::Side side, const Point &evtPosition);   

   ContextMenu *_contextMenu;
};

///////////////////////////////////////////////////////////

int Component::getWidth(void) const {
   return _p2.x - _p1.x;
}

int Component::getHeight(void) const {
   return _p2.y - _p1.y;
}

Point Component::getSize(void) const {
   return Point(getWidth(), getHeight());
}

Point Component::getMinimumSize(void) const {
   return _minSize;
}

Point Component::getPreferredSize(void) const {
   return getSize();
}

Point Component::getMaximumSize(void) const {
   return scv::Point(200, 200);
}

///////////////////////////////////////////////////////////

bool Component::isOvered(void) const {
   return _isOvered;
}

bool Component::isHolded(void) const {
   return _isHolded;
}

bool Component::isDragging(void) const {
   return _isDragging;
}

bool Component::isResizing(void) const {
   return _isResizing;
}

bool Component::isVisible(void) const {
   return _isVisible;
}

///////////////////////////////////////////////////////////

void Component::setDraggable(bool state) {
   _isDraggable = state;
}

void Component::setResizable(bool state) {
   _isResizable = state;
}

void Component::setVisible(bool state) {
   _isVisible = state;
}

///////////////////////////////////////////////////////////

Component *Component::getParent(void) const {
   return _parent;
}

const Component::List &Component::getChildren(void) const {
   return _children;
}

///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_COMPONENT__H__
