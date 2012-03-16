//#include "stdafx.h"

#include "InterfaceDesign.h"
#include "MenuDesign.h"
#include "SCV/ComboBox.h"
#include "SCV/SCV.h"

static const int screenWidth  = 1050;
static const int screenHeight = 860;

int main(int argc, char* argv[]) {
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   scheme->loadScheme(ColorScheme::osx);
   kernel->setWindowTitle("SCV Interface Designer v1.0");
   //kernel->registerContextMenu(new InterfaceDesign(NULL));
   kernel->getPanel()->registerContextMenu(new InterfaceDesign(kernel->getPanel()));
   kernel->setWindowSize(screenWidth, screenHeight);
   kernel->lockWindowSize(false);
   //////////////////////////
   kernel->setFramesPerSecond(60);
   kernel->run();
   return 0;
}
