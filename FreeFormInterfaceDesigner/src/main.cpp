#include "stdafx.h"
#include "Application.h"

#include "InterfaceDesign.h"
#include "MenuDesign.h"

int main(int argc, char* argv[]) {
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);

   kernel->init();

   kernel->run();
   return 0;
}