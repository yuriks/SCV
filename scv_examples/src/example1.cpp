#include "SCV.h"

void example1_main() {
   scv::Kernel *kernel = scv::Kernel::getInstance();
   kernel->setWindowSize(200, 100);

   scv::Label* label = new scv::Label(scv::Point(50, 50), "Hello World!");
   kernel->addComponent(label);

   kernel->setFramesPerSecond(60);
   kernel->run();
}