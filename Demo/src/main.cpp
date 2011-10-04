#include "stdafx.h"

#include "InterfaceDesign.h"


int main(int argc, char* argv[]) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   static scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   
   scheme->loadScheme(scv::ColorScheme::osx);
   scheme->setColor(scv::ColorScheme::font, scv::Color4f(1,1,1));
   kernel->setWindowSize(1280, 720);

   
   scv::Panel *panel = new scv::Panel(scv::Point(40,40), scv::Point(1280 - 920, 720 - 40));
   panel->setResizable(true);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

   layout->setAutoCreateGaps(true);
   layout->setAutoCreateContainerGaps(true);

   /*
   scv::Label *label1 = new scv::Label(scv::Point(  0,   0), "First Row");
   scv::Label *label2 = new scv::Label(scv::Point(100, 100), "Second Row");

   scv::TextField *tf1 = new scv::TextField(scv::Point(), 100, "");
   scv::TextField *tf2 = new scv::TextField(scv::Point(), 100, "");

   panel->addChild(label1);
   panel->addChild(label2);

   panel->addChild(tf1);
   panel->addChild(tf2);
     
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
   
   scv::Label *label = new scv::Label(scv::Point(), "Find What:");
   panel->addChild(label);
   scv::TextField *textField = new scv::TextField(scv::Point(), 200, "");
   panel->addChild(textField);
   scv::CheckBox *caseCheckBox = new scv::CheckBox(scv::Point(), false, "Match Case");
   panel->addChild(caseCheckBox);
   scv::CheckBox *wrapCheckBox = new scv::CheckBox(scv::Point(), false, "Wrap Around");
   panel->addChild(wrapCheckBox);
   scv::CheckBox *wholeCheckBox = new scv::CheckBox(scv::Point(), false, "Whole Words");
   panel->addChild(wholeCheckBox);
   scv::CheckBox *backCheckBox = new scv::CheckBox(scv::Point(), false, "Search Backwards");
   panel->addChild(backCheckBox);
   scv::Button *findButton = new scv::Button(scv::Point(), "Find");
   panel->addChild(findButton);
   scv::Button *cancelButton = new scv::Button(scv::Point(), "Cancel");
   panel->addChild(cancelButton);

   layout->setHorizontalGroup(layout->createSequentialGroup()
      ->addComponent(label)
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
      ->addComponent(textField)
      ->addGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
      ->addComponent(caseCheckBox)
      ->addComponent(wholeCheckBox))
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
      ->addComponent(wrapCheckBox)
      ->addComponent(backCheckBox))))
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
      ->addComponent(findButton)
      ->addComponent(cancelButton))
      );

   layout->setVerticalGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::BASELINE)
      ->addComponent(label)
      ->addComponent(textField)
      ->addComponent(findButton))
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
      ->addGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::BASELINE)
      ->addComponent(caseCheckBox)
      ->addComponent(wrapCheckBox))
      ->addGroup(layout->createParallelGroup(scv::Spring::BASELINE)
      ->addComponent(wholeCheckBox)
      ->addComponent(backCheckBox)))
      ->addComponent(cancelButton))
      );
   

   kernel->addComponent(panel);
   ///////////////////////////////////////////////////////////

   kernel->run();
   return 0;
}
