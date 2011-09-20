/*!
\file       Panel.h
\brief      Implementation of a Panel widget.
\author     SCV Team
*/


#ifndef __SCV_PANEL_INTERFACE_H__
#define __SCV_PANEL_INTERFACE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ComponentWithTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! Used to group children widgets together. They allow to have a better control on the layout of the widgets.
 * \ingroup widgets
 */

class Panel : public ComponentWithTexture {
public:

   /*! Constructor
   \param p1 The upper left corner of the component.
   \param p2 The bottom right corner of the component.
   */
   Panel(const scv::Point &p1, const scv::Point &p2);
   /*! Constructor
   \param p1 The upper left corner of the component.
   \param width Width of the component.
   \param height Height of the component.
   */
   Panel(const scv::Point &p1, unsigned int width, unsigned int height);
   //! Default Constructor
   Panel();

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);

   /*! Adds a new component to the panel.
   \param component Reference to the instance of the component.
   */
   virtual void addComponent(SCVObject::Ptr& object);
   /*! Sets a new position to the component relative to your father.
   \param position The new position of the component.
   */
   virtual void setRelativePosition(const Point &position);
   /*! Translate the panel by the specified amount.
   \param translate Amount to translate.
   */
   void setPanelTranslate(const Point &translate);

   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);


   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   //! Key function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processKey(const scv::KeyEvent &evt);
   virtual void display(void);
   //! Scissor function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void setPanelScissor(const Scissor::ScissorInfo &scissor);


protected:

   void refresh(bool cScissor, bool cTranslate);
   virtual void createTexture(void);
};

} // namespace scv

#endif // __SCV_PANEL_INTERFACE_H__
