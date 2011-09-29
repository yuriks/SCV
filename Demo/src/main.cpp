#include "stdafx.h"

//#include "InterfaceDesign.h"


int main(int argc, char* argv[]) {
   
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();
   
   scheme->loadScheme(ColorScheme::osx);
   kernel->setWindowSize(1280, 720);
   
   
   scv::Panel *panel = new scv::Panel(scv::Point(100,100), scv::Point(220,220));
   panel->setDraggable(true);
   panel->setResizable(true);
   kernel->addComponent(panel);

   scv::Panel *cPanel = new scv::Panel(scv::Point(10,10), scv::Point(220,220));
   cPanel->setDraggable(true);
   cPanel->setResizable(true);
   panel->addChild(cPanel);
   /**/

   kernel->addComponent(new scv::ColorPicker(scv::Point(400,100)));
   kernel->addComponent(new scv::ColorPicker(scv::Point(0,0)));
   

   //kernel->removeComponent(panel);
   //delete panel;

   //kernel->registerContextMenu(new InterfaceDesign(NULL));
   //////////////////////////
   kernel->run();
   

   return 0;
}
