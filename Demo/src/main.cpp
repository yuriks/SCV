#include "stdafx.h"

#include "Application.h"
#include "Properties.h"
#include "GapSpring.h"

/*
void example1() {
   scv::Kernel *kernel = scv::Kernel::getInstance();
   kernel->setWindowSize(1280, 720);
   scv::Panel *panel = new scv::Panel(scv::Point(0, 0), scv::Point(330, 75));
   panel->setResizable(true);
   panel->setDraggable(true);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

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
      ->addComponent(label)->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addComponent(textField)
         ->addGroup(layout->createSequentialGroup()
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(caseCheckBox)
               ->addComponent(wholeCheckBox))->addGap(10, 10, 10)
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(wrapCheckBox)
               ->addComponent(backCheckBox))))->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addComponent(findButton)
         ->addComponent(cancelButton))
      );

   layout->setVerticalGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addComponent(label)
         ->addComponent(textField)
         ->addComponent(findButton))->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addGroup(layout->createSequentialGroup()
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(caseCheckBox)
               ->addComponent(wrapCheckBox))->addGap(10, 10, 10)
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(wholeCheckBox)
               ->addComponent(backCheckBox)))
         ->addComponent(cancelButton))->addGap(10, 10, 10)
      );


   kernel->addComponent(panel);
   panel->setRelativePosition(scv::Point(10, 10));
}

void example2() {
   scv::Kernel *kernel = scv::Kernel::getInstance();
   kernel->setWindowSize(1280, 720);
   scv::Panel *panel = new scv::Panel(scv::Point(0, 0), scv::Point(330, 75));
   panel->setResizable(true);
   panel->setDraggable(true);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

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
      ->addComponent(label)->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(textField)
      ->addGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(caseCheckBox)
      ->addComponent(wholeCheckBox))->addGap(10, 10, 10)
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(wrapCheckBox)
      ->addComponent(backCheckBox))))->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(findButton)
      ->addComponent(cancelButton))
      );

   layout->setVerticalGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
      ->addComponent(label)
      ->addComponent(textField)
      ->addComponent(findButton))->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
      ->addGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
      ->addComponent(caseCheckBox)
      ->addComponent(wrapCheckBox))->addGap(10, 10, 10)
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(wholeCheckBox)
      ->addComponent(backCheckBox)))
      ->addComponent(cancelButton))->addGap(10, 10, 10)
      );


   kernel->addComponent(panel);
   panel->setRelativePosition(scv::Point(10, 95));
}

void example3() {
   scv::Kernel *kernel = scv::Kernel::getInstance();
   kernel->setWindowSize(1280, 720);
   scv::Panel *panel = new scv::Panel(scv::Point(0, 0), scv::Point(330, 75));
   panel->setResizable(true);
   panel->setDraggable(true);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

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
      ->addComponent(label)->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(textField)
      ->addGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(caseCheckBox)
      ->addComponent(wholeCheckBox))->addGap(10, 10, 10)
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(wrapCheckBox)
      ->addComponent(backCheckBox))))->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(findButton)
      ->addComponent(cancelButton))
      );

   layout->setVerticalGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(label)
      ->addComponent(textField)
      ->addComponent(findButton))->addGap(10, 10, 10)
      //--
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(caseCheckBox)
      ->addComponent(wrapCheckBox))->addGap(10, 10, 10)
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, true)
      ->addComponent(wholeCheckBox)
      ->addComponent(backCheckBox)))
      ->addComponent(cancelButton))->addGap(10, 10, 10)
      );


   kernel->addComponent(panel);
   panel->setRelativePosition(scv::Point(10, 180));
}
/**/

int main(int argc, char* argv[]) {
   scv::Kernel::setInstance(new Application());
   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());

   scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   
   scheme->loadScheme(scv::ColorScheme::OSX);
   scheme->setColor(scv::ColorScheme::FONT, scv::Color4f(1,1,1));
   
   kernel->init();
   
   kernel->run();
   return 0;
}
