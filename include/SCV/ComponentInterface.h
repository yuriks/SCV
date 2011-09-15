/*!
\file       ComponentInterface.h
\brief      Implementation of a generic component.
\author     SCV Team
*/

#ifndef __SCV_COMPONENT_INTERFACE_H__
#define __SCV_COMPONENT_INTERFACE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Scissor.h"
#include "Callbacks.h"
#include "SCVObject.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class ContextMenu;

/*! The main class of all components.
 *  If you want to create a new component this is the class you are looking for.
    This class implements all basic component interaction with the user.
    \ingroup internal
 */

class ComponentInterface : public Callbacks, public SCVObject {
public:

   enum typeComponent {
      NONE        , panel      ,
      colorPicker , progressBar,
      scrool      , slider     ,
      spinner     , button     ,
      checkBox    , radioButton,
      toggleButton, textField  ,
      textBox     , separator  ,
      window      , menuBar    ,
      tabbedPane  , scrollPane ,
      image       , table      ,
      comboBox    , canvas     ,
      treeView    , label
   };

   ComponentInterface(const scv::Point &p1, const scv::Point &p2);
   virtual ~ComponentInterface(void);

   /*! Mouse Callback
   This function is called when mouse clicks on this component.
   \param evt Contains the event information.
   */
   virtual void onMouseClick(const scv::MouseEvent &evt) = 0;
   /*! Mouse Callback
   This function is called when mouse button is pressed on this component.
   \param evt Contains the event information.
   */
   virtual void onMouseHold(const scv::MouseEvent &evt) = 0;
   /*! Mouse Callback
   This function is called when the user moves your mouse over this component.
   \param evt Contains the event information.
   */
   virtual void onMouseOver(const scv::MouseEvent &evt) = 0;
   /*! Mouse Callback
   This function is called when the mouse button is released over this component.
   \param evt Contains the event information.
   */
   virtual void onMouseUp(const scv::MouseEvent &evt) = 0;
   /*! Mouse Callback
   This function is called when the mouse scroll wheel is rolled over this component.
   \param evt Contains the event information.
   */
   virtual void onMouseWheel(const scv::MouseEvent &evt) = 0;
   /*! Keyboard Callback
   This function is called when a key is pressed while this component is focused.
   \param evt Contains the event information.
   */
   virtual void onKeyPressed(const scv::KeyEvent &evt) = 0;
   /*! Keyboard Callback
   This function is called when a key is released while this component is focused.
   \param evt Contains the event information.
   */
   virtual void onKeyUp(const scv::KeyEvent &evt) = 0;
   /*! Resize Callback
   This function is called while the component is being resized.
   */
   virtual void onResizing(void) = 0;
   /*! Drag Callback
   This function is called while the component is being dragged.
   */
   virtual void onDragging(void) = 0;



   /*! Sets the new relative position of the component
   \param position The new position relative to your father
   */
   virtual void setRelativePosition(const Point &position);
   /*! Gets the relative position of the component
   */
   Point getRelativePosition(void) const;
   /*! Gets the absolute position of the component
   */
   Point getAbsolutePosition(void) const;
   /*! Gets the Width of the component.
   */
   virtual int getWidth(void) const;
   /*! Gets the Height of the component.
   */
   virtual int getHeight(void) const;
   /*! Gets a point that contains the Width and the Height of the component.
   */
   virtual Point getSize(void) const;
   /*! Sets a new Width to the component.
   */
   virtual void setWidth(const int width);
   /*! Sets a new Height to the component.
   */
   virtual void setHeight(const int height);
   /*! Shows if the mouse pointer is over the component.
   */
   bool isOvered(void) const;
   /*! Shows if the mouse pointer is pressed over the component.
   */
   bool isHolded(void) const;
   /*! Shows if the component is being dragged.
   */
   bool isDragging(void) const;
   /*! Shows if the component is being resized.
   */
   bool isResizing(void) const;
   /*! Shows if the component is focused.
   */
   bool isFocused(void) const;
   /*! Shows if the component is visible.
   */
   bool isVisible(void);
   /*! Sets that the component can be dragged.
   */
   virtual void setDraggable(bool state);
   /*! Sets that the component can be resized.
   */
   virtual void setResizable(bool state);
   /*! Sets that the component can be saw.
   */
   virtual void setVisible(bool state);
   /*! Register a Context Menu to the component.
   */
   void registerContextMenu(ContextMenu *contextMenu);
   /*! Shows if the point specified by the event is inside the component.
   */
   bool isInside(const MouseEvent &evt) const;
   /*! Shows if the component callbacks is actives.
   */
   bool isCallbacksActive(void);
   /*! Sets if the component will receive callbacks.
   */
   void setCallbacksActive(bool state);
   //! Translate function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void setPanelTranslate(const Point &translate);
   //! Translate function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   Point getPanelTranslate(void);
   //! Scissor function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void setPanelScissor(const Scissor::ScissorInfo &scissor);
   //! Scissor function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   const Scissor::ScissorInfo &getPanelScissor(void);
   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void processMouse(const scv::MouseEvent &evt);
   //! Key function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void processKey(const scv::KeyEvent &evt);
   /*! Display function of the component.
    * This should only be re-implemented if you're creating a new type of component.
    */
   virtual void display(void) = 0;
   /*! Gets the type of the component.
   */
   typeComponent getType(void);

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

} // namespace scv

#endif // __SCV_COMPONENT_INTERFACE_H__
