#include "stdafx.h"

#include "Application.h"

int main(int argc, char* argv[]) {
   scv::Kernel::setInstance(new Application());
   scv::Kernel *kernel = scv::Kernel::getInstance();
   scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   
   scheme->loadScheme(scv::ColorScheme::osx);
   scheme->setColor(scv::ColorScheme::font, scv::Color4f(1,1,1));

   static const int s_defaultWindowWidht = 1280;
   static const int s_defaultWindowHeight = 720;
   
   kernel->setWindowSize(s_defaultWindowWidht, s_defaultWindowHeight);

   static const int s_defaultBorderGap = 10;
   static const int s_defaultRightBarSize = 300;


   scv::Panel *panelRightBar = new scv::Panel(scv::Point(s_defaultWindowWidht - s_defaultRightBarSize + s_defaultBorderGap, s_defaultBorderGap), scv::Point(s_defaultWindowWidht - s_defaultBorderGap, s_defaultWindowHeight - s_defaultBorderGap));
   kernel->addComponent(panelRightBar);
      
   //Palette
   ///////////////////////////////////////////////////////////
   scv::Panel *panelPalette = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultRightBarSize - s_defaultBorderGap - 26, 600));
   scv::ScrollPane *scrollPanePalette = new scv::ScrollPane(scv::Point(0, 0), scv::Point(s_defaultRightBarSize - s_defaultBorderGap - 10, 300), panelPalette);
   panelRightBar->addChild(scrollPanePalette);
   
   scv::Label *labelContainers = new scv::Label(scv::Point(10,10), "SCV Containers");
   panelPalette->addChild(labelContainers);
   panelPalette->addChild(new scv::Separator(scv::Point(0, labelContainers->getRelativePosition().y + labelContainers->getHeight() + 5), scv::Separator::horizontal, panelPalette->getWidth()));
   ///////////////////////////////////////////////////////////

   //Design
   ///////////////////////////////////////////////////////////
   scv::Panel *panelDesign = new scv::Panel(scv::Point(0, 0), scv::Point(800, 600));
   panelDesign->setResizable(true);
   scv::ScrollPane *scrollPaneDesign = new scv::ScrollPane(scv::Point(s_defaultBorderGap, s_defaultBorderGap), scv::Point(s_defaultWindowWidht - s_defaultRightBarSize, s_defaultWindowHeight - s_defaultBorderGap), panelDesign);
   scrollPaneDesign->setPanel(panelDesign);
   kernel->addComponent(scrollPaneDesign);
   ///////////////////////////////////////////////////////////

   /*   
   scv::Panel *panel = new scv::Panel(scv::Point(40,40), scv::Point(1280 - 920, 720 - 40));
   panel->setResizable(true);

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
         ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
            ->addComponent(findButton)
            ->addComponent(cancelButton))
      );

   layout->setVerticalGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addComponent(label)
         ->addComponent(textField)
         ->addComponent(findButton))
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addGroup(layout->createSequentialGroup()
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(caseCheckBox)
               ->addComponent(wrapCheckBox))
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(wholeCheckBox)
               ->addComponent(backCheckBox)))
         ->addComponent(cancelButton))
      );
   

   kernel->addComponent(panel);
   /**/

   kernel->run();
   return 0;
}
