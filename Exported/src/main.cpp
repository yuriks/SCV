#include <SCV/SCV.h>
#include "Application.h"
#include "Widget.h"

int main(int argc, char* argv[]) {
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);

   kernel->init();

   kernel->run();
   return 0;
}
