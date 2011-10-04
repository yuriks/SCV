#include "stdafx.h"

#include "InterfaceDesign.h"


int main(int argc, char* argv[]) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   static scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   
   scheme->loadScheme(scv::ColorScheme::osx);
   scheme->setColor(scv::ColorScheme::font, scv::Color4f(1,1,1));
   kernel->setWindowSize(1280, 720);

   ///////////////////////////////////////////////////////////
   scv::Panel *panel = new scv::Panel(scv::Point(40,40), scv::Point(1280 - 920, 720 - 40));
   panel->setResizable(true);

   scv::Label *label1 = new scv::Label(scv::Point(  0,   0), "First Row");
   scv::Label *label2 = new scv::Label(scv::Point(100, 100), "Second Row");

   scv::TextField *tf1 = new scv::TextField(scv::Point(), 100, "");
   scv::TextField *tf2 = new scv::TextField(scv::Point(), 100, "");

   panel->addChild(label1);
   panel->addChild(label2);

   panel->addChild(tf1);
   panel->addChild(tf2);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

   layout->setAutoCreateGaps(true);

   layout->setAutoCreateContainerGaps(true);

   /*
   layout->setHorizontalGroup(layout->createParallelGroup(scv::Spring::CENTER)->addComponent(tf1, 30, 30, 30)->addComponent(tf2, 50, 50, 50));

   layout->setVerticalGroup(layout->createSequentialGroup()->addComponent(tf1, 15, 15, 15)->addComponent(tf2, 15, 15, 15));
   /**/


   //createSequentialGroup
   //createParallelGroup
   
   scv::SequentialGroup *hGroup = layout->createSequentialGroup();
   hGroup->addGroup(layout->createParallelGroup()->
      addComponent(label1)->addComponent(label2));
   hGroup->addGroup(layout->createParallelGroup()->
      addComponent(tf1)->addComponent(tf2));
   layout->setHorizontalGroup(hGroup);

   
   scv::SequentialGroup *vGroup = layout->createSequentialGroup();
   vGroup->addGroup(layout->createParallelGroup(scv::Spring::BASELINE)->
      addComponent(label1)->addComponent(tf1));
   vGroup->addGroup(layout->createParallelGroup(scv::Spring::BASELINE)->
      addComponent(label2)->addComponent(tf2));
   layout->setVerticalGroup(vGroup);
   /**/
      

   kernel->addComponent(panel);
   ///////////////////////////////////////////////////////////

   kernel->run();
   return 0;
}
