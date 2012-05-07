/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laboratório de Computação Aplicada
webpage: www.inf.ufsm.br/~pozzer/scv
email: pozzer@inf.ufsm.br
2007-2012

*/

#include "SCV/SCV.h"

void example1_main() {
   scv::Kernel *kernel = scv::Kernel::getInstance();
   kernel->setWindowSize(200, 100);

   scv::Label* label = new scv::Label(scv::Point(50, 50), "Hello World!");
   kernel->addComponent(label);

   kernel->setFramesPerSecond(60);
   kernel->run();
}
