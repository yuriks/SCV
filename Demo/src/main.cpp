#include "stdafx.h"

//#include "InterfaceDesign.h"


int main(int argc, char* argv[]) {
   
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();
   
   scheme->loadScheme(ColorScheme::osx);
   kernel->setWindowSize(1280, 720);
   
   
   scv::Panel *panel = new scv::Panel(scv::Point(10,10), scv::Point(220,220));
   kernel->addComponent(panel);

   panel->addChild(new scv::Panel(scv::Point(10,10), scv::Point(220,220)));

   //kernel->removeComponent(panel);
   //delete panel;

   //kernel->registerContextMenu(new InterfaceDesign(NULL));
   //////////////////////////
   kernel->run();
   

   return 0;
}
