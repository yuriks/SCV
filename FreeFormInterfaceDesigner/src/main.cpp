/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laboratório de Computação Aplicada
www.inf.ufsm.br/~pozzer/scv/
2007-2012 

*/


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