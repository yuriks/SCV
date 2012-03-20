#include <SCV/SCV.h>

#include "Application.h"
#include "Properties.h"
#include <SCV/GapSpring.h>


#include "GroupPanelWrapper.h"
#include "SequentialGroupPanel.h"
#include "ParallelGroupPanel.h"

int main(int argc, char* argv[]) {
   scv::Kernel::setInstance(new Application());
   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());
      
   kernel->init();

   kernel->run();
   return 0;
}
