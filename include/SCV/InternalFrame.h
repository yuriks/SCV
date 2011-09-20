/*!
\file       InternalFrame.h
\brief      Implementation of a InternalFrame widget.
\author     SCV Team
*/

#ifndef __SCV_WINDOW_H__
#define __SCV_WINDOW_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Label.h"

#include "ComponentWithTexture.h"
#include "Panel.h"

#include "Timer.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class InternalFrameHolder;
/*!
 * A widget which create a simple window
 * and you can add other widgets inside it.
 */
class InternalFrame : public ComponentWithTexture {
   friend class WindowHolder;
public:

   InternalFrame(GLsizei width, GLsizei height, const std::string &title);
   virtual ~InternalFrame(void);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);

   /*! Callback
   This function is called when the component is closed.
   */
   virtual void onClose(void);
   /*! Return a pointer to panel.
   */
   Panel * getPanel(void);
   /*! Sets the name of the internal frame.
   */
   void setTitle(const std::string &title);
   /*! Gets the name of the internal frame.
   */
   std::string getTitle(void);
   /*! Sets a new position to the component relative to your father.
   \param position The new position of the component.
   */
   void setRelativePosition(const Point &position);
   /*! Adds a new component to the internal frame.
   \param component Reference to the instance of the component.
   */
   void addComponent(SCVObject::Ptr& object);
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
   void display(void);

protected:

   void createTexture(void);

private:

   bool isOnTopBar(const Point &p);
   bool isOnCloseButton(const Point &p);

   static const int s_borderTop, s_borderWidth;
   static const int s_closeWidth, s_closeHeight;

   std::string _title;

   bool _overClose, _clickClose;
   bool _refreshPosition, _rolluped;
   Panel *_panel;

};

} // namespace scv

#endif // __SCV_WINDOW_H__
