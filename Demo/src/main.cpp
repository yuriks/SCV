#include "stdafx.h"

#include "Application.h"
#include "Properties.h"
#include "GapSpring.h"


#include "GroupPanelWrapper.h"
#include "SequentialGroupPanel.h"
#include "ParallelGroupPanel.h"

int main(int argc, char* argv[]) {
   scv::Kernel::setInstance(new Application());
   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());
      
   kernel->init();

   scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   //scheme->loadScheme(scv::ColorScheme::OSX);
   //scheme->setColor(scv::ColorScheme::FONT, scv::Color4f(1,1,1));

   kernel->run();
   return 0;
}
