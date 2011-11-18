#ifndef __SCV_WINDOW_H__
#define __SCV_WINDOW_H__

#include "Label.h"

#include "ComponentWithTexture.h"
#include "Panel.h"

#include "Timer.h"

namespace scv {

class InternalFrameHolder;

class InternalFrame : public ComponentWithTexture {
friend class WindowHolder;
public:
   ///////////////////////////////////////////////////////////
   InternalFrame(GLsizei width, GLsizei height, const std::string &title);
   virtual ~InternalFrame(void);
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

   virtual void onOpen(void);
   virtual void onClose(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setVisible(bool state);
   ///////////////////////////////////////////////////////////

   inline Panel *getPanel(void) const;

   ///////////////////////////////////////////////////////////
   inline void setTitle(const std::string &title);
   inline std::string getTitle(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   void display(void);

protected:
   void createTexture(void);

private:
   ///////////////////////////////////////////////////////////
   bool isOnTopBar(const scv::Point &p);
   bool isOnCloseButton(const scv::Point &p);
   void configPanel(void);
   ///////////////////////////////////////////////////////////

   static const int s_borderTop, s_borderWidth;
   static const int s_closeWidth, s_closeHeight;

   std::string _title;

   bool _overClose, _clickClose;
   bool _refreshPosition, _rolluped;
   Panel *_panel;
};

///////////////////////////////////////////////////////////

Panel *InternalFrame::getPanel(void) const {
   return _panel;
}

void InternalFrame::setTitle(const std::string &title) {
   _title = title;
}

std::string InternalFrame::getTitle(void) const {
   return _title;
}

///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_WINDOW_H__
