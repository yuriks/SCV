#include "SCV.h"
#include "Application.h"
#include "Widget.h"

int main(int argc, char* argv[]) {
   scv::Kernel::setInstance(new Application());
   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());

   kernel->init();

   kernel->run();
   return 0;
}
