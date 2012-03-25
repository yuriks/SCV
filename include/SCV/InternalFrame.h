/*!
\file       InternalFrame.h
\brief      Implementation of a InternalFrame.
\author     SCV Team
*/

#ifndef __SCV_WINDOW_H__
#define __SCV_WINDOW_H__

#include "Label.h"

#include "Component.h"
#include "ComponentTexture.h"
#include "Panel.h"

#include "Timer.h"

namespace scv {

class InternalFrameHolder;

class InternalFrame : public Component {
friend class WindowHolder;
public:
   InternalFrame(GLsizei width, GLsizei height, const std::string &title);

   virtual void onOpen(void);
   virtual void onClose(void);

   virtual void setVisible(bool state);

   inline void setPanel(scv::Panel *panel);
   inline scv::Panel *getPanel(void) const;

   inline void setTitle(const std::string &title);
   inline std::string getTitle(void) const;

   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

   void display(void);

protected:
   void createTexture(void);
   ComponentTexture* _cTexture;

   bool isOnTopBar(const scv::Point &p);
   bool isOnCloseButton(const scv::Point &p);
   void configPanel(void);

   static const int s_borderTop, s_borderWidth;
   static const int s_closeWidth, s_closeHeight;

   std::string _title;

   bool _overClose, _clickClose;
   bool _refreshPosition, _rolluped;
   scv::Panel *_panel;
};

///////////////////////////////////////////////////////////

void InternalFrame::setPanel(scv::Panel *panel) {
   if (_panel != NULL) {
      removeChild(getPanel());
   }
   
   if (panel != NULL) {
      _panel = panel;
      addChild(_panel);
   }
}


Panel *InternalFrame::getPanel(void) const {
   return _panel;
}

void InternalFrame::setTitle(const std::string &title) {
   _title = title;
}

std::string InternalFrame::getTitle(void) const {
   return _title;
}

} // namespace scv

#endif // __SCV_WINDOW_H__
