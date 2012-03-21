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
   enum Type {
      NONE        , PANEL           , COLORPICKER , PROGRESSBAR,
      SCROLL      , SLIDER          , SPINNER     , BUTTON     ,
      CHECKBOX    , RADIOBUTTON     , TOGGLEBUTTON, TEXTFIELD  ,
      TEXTBOX     , SEPARATOR       , WINDOW      , MENUBAR    ,
      TABBEDPANE  , SCROLLCOMPONENT , IMAGE       , TABLE      ,
      COMBOBOX    , CANVAS          , TREEVIEW    , LABEL      ,
      CONTEXTMENU , GENERICTREE     ,
      /**/
      NOFWIDGETS
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   Component(const scv::Point &p1, const scv::Point &p2);
   virtual ~Component(void);
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
   virtual inline void setSize(int width, int height);

   virtual void setMinimumSize(const scv::Point &size);
   virtual Point getMinimumSize(void) const;

   virtual void setPreferredSize(const scv::Point &size);
   virtual Point getPreferredSize(void) const;

   virtual void setMaximumSize(const scv::Point &size);
   virtual Point getMaximumSize(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual inline bool isOvered(void) const;
   virtual inline bool isHolded(void) const;
   virtual inline bool isDragging(void) const;
   virtual inline bool isResizing(void) const;   
   ///////////////////////////////////////////////////////////

   virtual bool isFocused(void) const;

   ///////////////////////////////////////////////////////////
   virtual inline void setDraggable(bool state);
   virtual inline bool isDraggable(void) const;

   virtual inline void setResizable(bool state);
   virtual inline bool isResizable(void) const;

   virtual inline void setVisible(bool state);
   virtual inline bool isVisible(void) const;
   ///////////////////////////////////////////////////////////

   inline ContextMenu *getContextMenu(void) const;
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
   Type getType(void) const;
   void setType(Type type);
   ///////////////////////////////////////////////////////////

   //memory management
   ///////////////////////////////////////////////////////////
   void setParent(Component *parent);   
   inline Component *getParent(void) const;

   inline const Component::List &getChildren(void) const;

   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);
   virtual void removeAllChild(void);

   virtual Component *getChild(int index) const;

   void pullChildToTop(Component *child);

   bool hasChild(Component *child) const;
   ///////////////////////////////////////////////////////////

protected:  
   ///////////////////////////////////////////////////////////
   Component *_parent;
   Component::List _children;
   ///////////////////////////////////////////////////////////

   Type _type;
   static const int s_mouseBacklash = 4;

   Point _p1, _p2, _clickDiff;
   Point _minimumSize, _preferredSize, _maximumSize;

   bool _receivingCallbacks;
   bool _isResizable, _isResizing;
   bool _isHResizable, _isVResizable;
   bool _isDraggable, _isDragging;
   bool _isOvered, _isHolded;
   bool _isVisible;

   void setResizingCursor(void);

   enum Side { LEFT, RIGHT, TOP, BOTTOM };
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

void Component::setSize(int width, int height) {
   setWidth(width);
   setHeight(height);
}

Point Component::getSize(void) const {
   return Point(getWidth(), getHeight());
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

///////////////////////////////////////////////////////////

void Component::setDraggable(bool state) {
   _isDraggable = state;
}

bool Component::isDraggable(void) const {
   return _isDraggable;
}

void Component::setResizable(bool state) {
   _isResizable = state;
}

bool Component::isResizable(void) const {
   return _isResizable;
}

void Component::setVisible(bool state) {
   _isVisible = state;
}

bool Component::isVisible(void) const {
   return _isVisible;
}

///////////////////////////////////////////////////////////

ContextMenu *Component::getContextMenu(void) const {
   return _contextMenu;
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
