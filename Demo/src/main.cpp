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

   /*
   GroupPanelWrapper *wrapper = new GroupPanelWrapper();   
   kernel->addComponent(wrapper);
   /**/

   
   scv::Panel *panel1 = new scv::Panel(scv::Point(10,10), scv::Point(1280 - 10, 720 - 10));
   kernel->addComponent(panel1);

   scv::GroupLayout *layout = new scv::GroupLayout(panel1);
   panel1->setLayout(layout);

   

   scv::Panel *panel2 = new scv::Panel(scv::Point(), scv::Point(200,200));
   scv::Panel *panel3 = new scv::Panel(scv::Point(), scv::Point(200,200));
   scv::Panel *panel4 = new scv::Panel(scv::Point(), scv::Point(200,200));
   scv::Panel *panel5 = new scv::Panel(scv::Point(), scv::Point(200,200));
   panel1->addChild(panel2);
   panel1->addChild(panel3);
   panel1->addChild(panel4);
   panel1->addChild(panel5);

   layout->setHorizontalGroup(layout->createSequentialGroup()->addGap(15)->addGroup(layout->createParallelGroup()->addComponent(panel2)->addComponent(panel3)));
   layout->setVerticalGroup(layout->createSequentialGroup()->addGap(15)->addGroup(
      layout->createSequentialGroup()->setAutoCreateGaps(true)->addComponent(panel2)->addComponent(panel3)->addComponent(panel4)->addComponent(panel5))
      
      );

   //layout->setVerticalGroup(layout->createSequentialGroup()->addGap(15)->addGroup(layout->createSequentialGroup()->setAutoCreateGaps(true)->addComponent(panel2)->addComponent(panel3)));
   /**/

   kernel->run();
   return 0;
}
