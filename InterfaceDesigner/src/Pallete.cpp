#include <SCV/SCV.h>
#include "GroupPanelWrapper.h"
#include "Pallete.h"

#include "PalleteComponents.h"

#include "Application.h"

Pallete::Pallete(void) : scv::Panel(scv::Point(0, 0), scv::Point(Application::s_defaultRightPanelWidth, 0)) {
}

Pallete::~Pallete(void) {
}

void Pallete::setGroupPanelsWraper(GroupPanelWrapper* h, GroupPanelWrapper* v)
{
       _title = new scv::Label(scv::Point(0, 0), "Palette");
   addChild(_title);

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

    _hGP = h;
    _vGP = v;

   PalleteDeleteComponents *deleteAllPanel = new PalleteDeleteComponents("SCV Delete", scv::Point(), scv::Point(getWidth(), 0));
   addChild(deleteAllPanel);
   deleteAllPanel->addComponent("Clean All Interface", _hGP, _vGP);
   deleteAllPanel->adjustButtonsWidth();

   paletteLayout->setHorizontalGroup(
      paletteLayout->createParallelGroup()
         ->addGroup(scv::GroupLayout::createSequentialGroup()
            ->addGap(15, 15, -1)
            ->addComponent(_title)
            ->addGap(15, 15, -1)
         )
         ->addComponent(containers, containers->getWidth(), containers->getWidth(), -1)
         ->addComponent(controls, controls->getWidth(), controls->getWidth(), -1)
         ->addComponent(windows, windows->getWidth(), windows->getWidth(), -1)
         ->addComponent(deleteAllPanel, deleteAllPanel->getWidth(), deleteAllPanel->getWidth(), -1)
   );

   paletteLayout->setVerticalGroup(
      paletteLayout->createSequentialGroup()
         ->addGap(5)
         ->addComponent(_title)->addGap(8)
         ->addComponent(deleteAllPanel, deleteAllPanel->getHeight(), deleteAllPanel->getHeight(), deleteAllPanel->getHeight())->addGap(10)
         ->addComponent(containers, containers->getHeight(), containers->getHeight(), containers->getHeight())->addGap(10)
         ->addComponent(controls, controls->getHeight(), controls->getHeight(), controls->getHeight())->addGap(10)
         ->addComponent(windows, windows->getHeight(), windows->getHeight(), windows->getHeight())
   );
}

void Pallete::display(void) {
   static scv::Kernel *kernel = scv::Kernel::getInstance();
   static scv::Scissor *scissor = scv::Scissor::getInstance();
   static scv::ColorScheme *scheme = scv::ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   scv::Point currPosition = getAbsolutePosition();

   scissor->pushScissor(getScissor());

   _cTexture->enable();
   scv::ColorScheme::getInstance()->applyColor(scv::ColorScheme::MENUBAR);

   // middle
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);

   // corners
   _cTexture->display(currPosition.x, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + getWidth() - 1, currPosition.y + 1, 0, 1, getHeight() - 2);
   _cTexture->display(currPosition.x + 1, currPosition.y, 0, getWidth() - 2, 1);
   _cTexture->display(currPosition.x + 1, currPosition.y + getHeight() - 1, 0, getWidth() - 2, 1);

   _cTexture->disable();

   if (_layout != NULL) {
      _layout->layoutContainer();
   }

   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }

   scissor->popScissor();
}
