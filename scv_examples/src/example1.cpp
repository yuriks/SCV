#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Label.h>

void example1_main() {
   scv::Kernel* kernel = scv::Kernel::getInstance();
   scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

   scheme->loadScheme(scv::ColorScheme::clean);
   kernel->setWindowSize(200, 100);

   scv::Label* label = new scv::Label(scv::Point(50, 50), "Hello World!");
   kernel->addComponent(label);

   kernel->setFramesPerSecond(60);
   kernel->run();
}