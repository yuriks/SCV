#include "stdafx.h"
#include "InterfaceDesign.h"
#include "MenuDesign.h"
#include "AbstractWindow.h"

InterfaceDesign::InterfaceDesign(scv::Panel *_panel, bool remove) : ContextMenu("InterfaceDesign") {

   m_panel = _panel;
   contButton = contFrame = contTeggleButton = contTextField = contTextBox = contRadioButton = contMenubar = contLabel = contCheckbox = 0;
   contProgressBar = 50;
   ContextMenu * panel = new ContextMenu("Add Panel");
   ContextMenu * component = new ContextMenu("Add Component");

   addMenu(panel);
   addMenu(component);
   if(remove)
      addMenu(new ContextMenu("Remove Component"));
   addMenu(new ContextMenu("Generate Code..."));

   ContextMenu * open = new ContextMenu("Open");
   addMenu(open);
   open->addMenu(new ContextMenu("text"));
   
   panel->addMenu(new ContextMenu("Image"));
   panel->addMenu(new ContextMenu("Internal Frame"));
   panel->addMenu(new ContextMenu("Panel"));
   panel->addMenu(new ContextMenu("Scroll Pane"));
   panel->addMenu(new ContextMenu("Tabbed Pane"));
   
   
   

   component->addMenu(new ContextMenu("Button"));
   component->addMenu(new ContextMenu("Canvas"));
   component->addMenu(new ContextMenu("CheckBox"));
   component->addMenu(new ContextMenu("Color Picker"));
   component->addMenu(new ContextMenu("ComboBox"));
   component->addMenu(new ContextMenu("Label"));
   component->addMenu(new ContextMenu("Menu Bar"));
   component->addMenu(new ContextMenu("Progress Bar"));
   component->addMenu(new ContextMenu("Radio Button"));

   ContextMenu * separator = new ContextMenu("Separator");
   separator->addMenu(new ContextMenu("Horizontal"));
   separator->addMenu(new ContextMenu("Vertical"));

   component->addMenu(separator);
   component->addMenu(new ContextMenu("Slider"));
   component->addMenu(new ContextMenu("Spinner"));
   component->addMenu(new ContextMenu("Table"));
   component->addMenu(new ContextMenu("TextBox"));
   component->addMenu(new ContextMenu("TextField"));
   component->addMenu(new ContextMenu("Toggle Button"));
   component->addMenu(new ContextMenu("Tree View"));

}


void InterfaceDesign::onMenuAccessed(const std::deque<std::string> &address) {

   if (address.size() == 0) {
      return;
   } else if (address.size() == 1) {

   } else  if (address.size() == 2) {
      if (address[1] == "Remove Component") {
		  scv::Kernel::getInstance()->removeComponent(m_panel);
      } else if (address[1] == "Generate Code...") {
         //scv::Kernel::getInstance()->generateCode();
      }
   } else if (address[2] == "Panel") {
      scv::Panel * newpanel;
      if (m_panel != NULL) {
         newpanel = new scv::Panel(getCurrPosition() - m_panel->getAbsolutePosition(), getCurrPosition() - m_panel->getAbsolutePosition() + 200);
      } else {
         newpanel = new scv::Panel(getCurrPosition(), getCurrPosition() + 200);
      }

      newpanel->registerContextMenu(new InterfaceDesign(newpanel, true));
      newpanel->setDraggable(true);
      newpanel->setResizable(true);
      //newpanel->setCallbacksStatus(false);

      if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newpanel);
      else m_panel->addChild(newpanel);
   } 
}

