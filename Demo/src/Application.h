#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Properties.h"
#include "GroupPanelWrapper.h"

class Application : public scv::Kernel {
public:
   ///////////////////////////////////////////////////////////
   Application(void);
   virtual ~Application(void);
   ///////////////////////////////////////////////////////////

   void init(void);

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
   ///////////////////////////////////////////////////////////

   void addComponentFromPalette(std::string component);

   void getCode(void) const;

protected:
   static const int s_defaultWindowWidth = 1280;
   static const int s_defaultWindowHeight = 720;

   scv::Panel *_mainPanel;
   scv::Panel *_designPreview;
   Properties *_properties;

   std::list<scv::Component*> _managedComponents;

   GroupPanelWrapper *_hPanelWrapper, *_vPanelWrapper;
private:
};

#endif //__APPLICATION_H__