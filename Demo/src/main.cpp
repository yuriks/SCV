#include "stdafx.h"

#include "Application.h"
#include "Properties.h"
#include "GapSpring.h"

#include "SequentialGroupPanel.h"
#include "ParallelGroupPanel.h"

int main(int argc, char* argv[]) {
   /*
   scv::Kernel::setInstance(new Application());
   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());

   scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   
   scheme->loadScheme(scv::ColorScheme::OSX);
   scheme->setColor(scv::ColorScheme::FONT, scv::Color4f(1,1,1));
   
   kernel->init();
   
   kernel->run();
   /**/

   scv::Kernel *kernel = scv::Kernel::getInstance();
   kernel->setWindowSize(1280, 720);

   scv::Panel *mainPanel = new scv::Panel(scv::Point(10, 10), scv::Point(1280 - 10, 720 - 10));
   kernel->addComponent(mainPanel);


   SequetialGroupPanel *sequential = new SequetialGroupPanel(GroupPanel::HORIZONTAL);
   ParallelGroupPanel *parallel = new ParallelGroupPanel(GroupPanel::HORIZONTAL);

   mainPanel->addChild(sequential);

   sequential->addChild(new scv::Button(scv::Point(), "Button 1"));
   sequential->addChild(parallel);

   parallel->addChild(new scv::Button(scv::Point(), "Button 2"));

   sequential = new SequetialGroupPanel(GroupPanel::HORIZONTAL);
   parallel->addChild(sequential);

   sequential->addChild(new scv::Button(scv::Point(), "Button 3"));
   sequential->addChild(new scv::Button(scv::Point(), "Button 4"));

   kernel->run();
   return 0;
}
