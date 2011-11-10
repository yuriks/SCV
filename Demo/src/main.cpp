#include "stdafx.h"

#include "Application.h"
#include "Properties.h"
#include "GapSpring.h"


#include "GroupPanelWrapper.h"
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

   scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   scheme->loadScheme(scv::ColorScheme::OSX);
   scheme->setColor(scv::ColorScheme::FONT, scv::Color4f(1,1,1));

   scv::Component *object1 = new scv::Button(scv::Point(), "Button 1");
   scv::Component *object2 = new scv::Button(scv::Point(), "Button 2");
   scv::Component *object3 = new scv::Button(scv::Point(), "Button 3");
   scv::Component *object4 = new scv::Button(scv::Point(), "Button 4");

   GroupPanel *group;

   /*
   GroupPanel *hGroup = GroupPanelWrapper::createHorizontalSequentialGroupPanel();
   hGroup->addChild(object1);

   group = GroupPanelWrapper::createHorizontalParallelGroupPanel();
   group->addChild(object2);
   group->addChild(object3);

   hGroup->addChild(group);

   GroupPanelWrapper *p = new GroupPanelWrapper();
   p->setResizable(true);
   hGroup->addChild(p);
   /**/

   /*
   GroupPanel *vGroup = GroupPanelWrapper::createVerticalSequentialGroupPanel();
   vGroup->addChild(object1);

   group = GroupPanelWrapper::createVerticalParallelGroupPanel();
   group->addChild(object2);
   group->addChild(object3);

   vGroup->addChild(group);
   vGroup->addChild(object4);
   /**/

   
   GroupPanelWrapper *wrapper = new GroupPanelWrapper();   
   //wrapper->setVerticalGroup(vGroup);
   //wrapper->setHorizontalGroup(hGroup);
   //kernel->addComponent(wrapper);

   std::cout << wrapper->getHorizontalGroupCode() << std::endl;
   std::cout << wrapper->getVerticalGroupCode() << std::endl;
   
   scv::Panel *panel = new scv::Panel(scv::Point(10, 10), scv::Point(1280 - 10, 720 - 10));
   kernel->addComponent(panel);

   scv::Panel *panel2 = GroupPanelWrapper::createVerticalSequentialGroupPanel();
   panel->addChild(panel2);
   scv::Panel *panel3 = GroupPanelWrapper::createVerticalSequentialGroupPanel();
   panel->addChild(panel3);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

   layout->setHorizontalGroup(layout->createSequentialGroup()->addComponent(panel2)->addComponent(panel3));
   layout->setVerticalGroup(layout->createParallelGroup()->addComponent(panel2)->addComponent(panel3));

   kernel->run();
   return 0;
}
