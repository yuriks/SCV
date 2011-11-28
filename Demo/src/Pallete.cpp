#include "stdafx.h"
#include "Pallete.h"

#include "PalleteComponents.h"

#include "Application.h"

Pallete::Pallete(void) : scv::Panel(scv::Point(0, 0), scv::Point(static_cast<Application *>(scv::Kernel::getInstance())->s_defaultRightPanelWidth, 0)) {
   scv::GroupLayout *paletteLayout = new scv::GroupLayout(this);
   setLayout(paletteLayout);

   PalleteComponents *containers = new PalleteComponents("SCV Containers", scv::Point(), scv::Point(getWidth(), 0));   
   addChild(containers);
   containers->addComponent("Image");
   containers->addComponent("Panel");
   containers->addComponent("TabbedPane");
   containers->addComponent("ScrollComponent");
   containers->adjustButtonsWidth();

   PalleteComponents *controls = new PalleteComponents("SCV Controls", scv::Point(), scv::Point(getWidth(), 0));
   addChild(controls);
   controls->addComponent("Button");
   controls->addComponent("ToggleButton");
   controls->addComponent("ProgressBar");
   controls->addComponent("Slider");
   controls->addComponent("Spinner");
   controls->addComponent("ComboBox");
   controls->addComponent("MenuBar");
   controls->addComponent("CheckBox");
   controls->addComponent("RadioButton");
   controls->addComponent("Label");
   controls->addComponent("TextBox");
   controls->addComponent("TextField");
   controls->addComponent("Canvas");
   controls->addComponent("ColorPicker");
   controls->addComponent("Separator");
   controls->addComponent("Table");
   controls->adjustButtonsWidth();

   PalleteComponents *windows = new PalleteComponents("SCV Windows", scv::Point(), scv::Point(getWidth(), 0));
   addChild(windows);
   windows->addComponent("InternalFrame");
   windows->adjustButtonsWidth();

   paletteLayout->setHorizontalGroup(
      paletteLayout->createParallelGroup()
         ->addComponent(containers, containers->getWidth(), containers->getWidth(), -1)
         ->addComponent(controls, controls->getWidth(), controls->getWidth(), -1)
         ->addComponent(windows, windows->getWidth(), windows->getWidth(), -1)
   );

   paletteLayout->setVerticalGroup(
      paletteLayout->createSequentialGroup()->setAutoCreateGaps(true)
         ->addComponent(containers, containers->getHeight(), containers->getHeight(), containers->getHeight())
         ->addComponent(controls, controls->getHeight(), controls->getHeight(), controls->getHeight())
         ->addComponent(windows, windows->getHeight(), windows->getHeight(), windows->getHeight())
   );
}

Pallete::~Pallete(void) {
}
