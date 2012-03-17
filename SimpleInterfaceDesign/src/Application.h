#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <vector>

class Application : public scv::Kernel {
public:
   ///////////////////////////////////////////////////////////
   static const int s_defaultWindowWidth = 1050;
   static const int s_defaultWindowHeight = 800;
   ///////////////////////////////////////////////////////////

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

   virtual void onDisplay(void);

protected:
   scv::Panel *_mainPanel;
};

#endif //__APPLICATION_H__