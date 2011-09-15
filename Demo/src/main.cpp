#include "stdafx.h"

#include "InterfaceDesign.h"

int main(int argc, char* argv[]) {
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   scheme->loadScheme(ColorScheme::osx);
   kernel->setWindowSize(1280, 720);
   
   kernel->registerContextMenu(new InterfaceDesign(NULL));
   //////////////////////////
   kernel->run();
   return 0;
}
