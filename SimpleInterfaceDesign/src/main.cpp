
#include "stdafx.h"
//#include "SCV/SCV.h"

#include "InterfaceDesign.h"
#include "MenuDesign.h"

static const int screenWidth  = 1050;
static const int screenHeight = 860;

int main(int argc, char* argv[]) {
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();

   kernel->setWindowTitle("SCV Interface Designer v1.0");
   scv::Panel *mainPanel = new scv::Panel(scv::Point(0,0), scv::Point(screenWidth,screenHeight));
   kernel->addComponent(mainPanel);
   mainPanel->registerContextMenu(new InterfaceDesign(NULL));
   
   
   kernel->setWindowSize(screenWidth, screenHeight);
   kernel->lockWindowSize(false);
   //////////////////////////
   kernel->setFramesPerSecond(60);
   kernel->run();

   return 0;
}
