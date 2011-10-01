#include "stdafx.h"

#include "InterfaceDesign.h"


int main(int argc, char* argv[]) {
   
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();
   
   scheme->loadScheme(ColorScheme::osx);
   kernel->setWindowSize(1280, 720);
   
   scv::Panel *panel = new scv::Panel(scv::Point(0, 0), scv::Point(1280,720));
   panel->setDraggable(false);
   panel->setResizable(false);
   kernel->addComponent(panel);

   panel->registerContextMenu(new InterfaceDesign(NULL));
   //////////////////////////
   kernel->run();
   

   return 0;
}
