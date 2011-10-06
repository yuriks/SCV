#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class Application : public scv::Kernel {
public:
   ///////////////////////////////////////////////////////////
   Application(void);
   virtual ~Application(void);
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
   ///////////////////////////////////////////////////////////

   void addComponentFromPalette(std::string component);
protected:
   
private:
};

#endif //__APPLICATION_H__