#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <vector>

class Application : public scv::Kernel {
public:
   static const int s_defaultWindowWidth = 1050;
   static const int s_defaultWindowHeight = 800;

   Application(void);
   virtual ~Application(void);

   void init(void);

  
   virtual void onSizeChange();
   virtual void onDisplay();

   void generateCode();
   void clearRecursive(scv::Component*);
   void clearInterface();

   scv::Panel *_mainPanel;
};

#endif //__APPLICATION_H__