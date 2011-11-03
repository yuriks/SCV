#include "stdafx.h"
#include "Application.h"

#include "MenuBar.h"
#include "Properties.h"
#include "Pallete.h"

Application::Application(void) : Kernel() {
   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(true);
}

Application::~Application(void) {
}

void Application::init(void) {
   static const int s_defaultGap = 10;
   static const int s_defaultRightPanelWidth = 250;


   scv::Panel *mainPanel = new scv::Panel(scv::Point(0 + s_defaultGap, 0 + s_defaultGap), scv::Point(s_defaultWindowWidth - s_defaultGap, s_defaultWindowHeight - s_defaultGap));
   addComponent(mainPanel);

   //Menu
   ///////////////////////////////////////////////////////////
   MenuBar *menuBar = new MenuBar(s_defaultWindowWidth);
   mainPanel->addChild(menuBar);

   ///////////////////////////////////////////////////////////
   

   //Palette
   ///////////////////////////////////////////////////////////
   scv::Panel *panelPalette = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultRightPanelWidth, 0)); //26
   mainPanel->addChild(panelPalette);
   
   scv::GroupLayout *paletteLayout = new scv::GroupLayout(panelPalette);
   panelPalette->setLayout(paletteLayout);

   PanelPalleteComponents *containers = new PanelPalleteComponents("SCV Containers", scv::Point(), scv::Point(s_defaultRightPanelWidth, 0));   
   panelPalette->addChild(containers);
   containers->addComponent("Image");
   containers->addComponent("Panel");
   containers->addComponent("ScroolPane");
   containers->addComponent("TabbedPane");
   containers->adjustButtonsWidth();

   PanelPalleteComponents *controls = new PanelPalleteComponents("SCV Controls", scv::Point(), scv::Point(s_defaultRightPanelWidth, 0));
   panelPalette->addChild(controls);
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

   PanelPalleteComponents *windows = new PanelPalleteComponents("SCV Windows", scv::Point(), scv::Point(s_defaultRightPanelWidth, 0));
   panelPalette->addChild(windows);
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
   ///////////////////////////////////////////////////////////

   //Design
   ///////////////////////////////////////////////////////////
   scv::Panel *panelDesign = new scv::Panel(scv::Point(0, 0), scv::Point(800, 600));
   panelDesign->setResizable(true);
   scv::ScrollPane *scrollPaneDesign = new scv::ScrollPane(scv::Point(0, 0), scv::Point(0, 0), panelDesign);
   scrollPaneDesign->setPanel(panelDesign);
   mainPanel->addChild(scrollPaneDesign);
   ///////////////////////////////////////////////////////////

   //Properties
   ///////////////////////////////////////////////////////////
   _properties = new Properties(s_defaultRightPanelWidth);
   mainPanel->addChild(_properties);
   ///////////////////////////////////////////////////////////


   _managedComponents.push_back(panelDesign);
   /**/


   //GroupLayout
   ///////////////////////////////////////////////////////////
   scv::GroupLayout *layout = new scv::GroupLayout(mainPanel);

   layout->setHorizontalGroup(
      layout->createSequentialGroup()->setAutoCreateGaps(true)
         ->addComponent(scrollPaneDesign)
         ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
            ->addComponent(panelPalette)
            ->addComponent(_properties)
         )
   );

   layout->setVerticalGroup(
      layout->createSequentialGroup()->setAutoCreateGaps(true)->setAutoGapsSize(5)
      ->addComponent(menuBar)
      ->addGroup(
         layout->createParallelGroup()
            ->addComponent(scrollPaneDesign)
            ->addGroup(layout->createSequentialGroup()->setAutoCreateGaps(true)
               ->addComponent(panelPalette)
               ->addComponent(_properties)
            )
      )
   );
   ///////////////////////////////////////////////////////////

   mainPanel->setLayout(layout);
}

void Application::onMouseClick(const scv::MouseEvent &evt) {   
}
void Application::onMouseHold(const scv::MouseEvent &evt) {
   if (std::find(_managedComponents.begin(), _managedComponents.end(), getFocusedComponent()) ==  _managedComponents.end()) return;
   _properties->setComponent(getFocusedComponent());
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
}
void Application::onMouseUp(const scv::MouseEvent &evt) {
   if (std::find(_managedComponents.begin(), _managedComponents.end(), getFocusedComponent()) ==  _managedComponents.end()) return;
   _properties->setComponent(getFocusedComponent());
}
void Application::onMouseWheel(const scv::MouseEvent &evt) {
}

void Application::onKeyPressed(const scv::KeyEvent &evt) {
}
void Application::onKeyUp(const scv::KeyEvent &evt) {
}

void Application::onSizeChange(void) {
}
void Application::onPositionChange(void) {
}

void Application::addComponentFromPalette(std::string component) {
   std::cout << component << std::endl;

}

