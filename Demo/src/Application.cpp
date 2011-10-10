#include "stdafx.h"
#include "Application.h"

#include "Properties.h"
#include "Pallete.h"

Application::Application(void) : Kernel() {  
}

Application::~Application(void) {
}

void Application::init(void) {
   setWindowSize(s_defaultWindowWidht, s_defaultWindowHeight);

   static const int s_defaultBorderGap = 10;
   static const int s_defaultRightBarSize = 300;


   scv::Panel *panelRightBar = new scv::Panel(scv::Point(s_defaultWindowWidht - s_defaultRightBarSize + s_defaultBorderGap, s_defaultBorderGap), scv::Point(s_defaultWindowWidht - s_defaultBorderGap, s_defaultWindowHeight - s_defaultBorderGap));
   addComponent(panelRightBar);

   //Palette
   ///////////////////////////////////////////////////////////
   scv::Panel *panelPalette = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultRightBarSize - s_defaultBorderGap - 25, 0));
   scv::ScrollPane *scrollPanePalette = new scv::ScrollPane(scv::Point(0, 0), scv::Point(s_defaultRightBarSize - s_defaultBorderGap - 10, 345), panelPalette);
   panelRightBar->addChild(scrollPanePalette);

   int y = 0;
   PanelPalleteComponents *containers = new PanelPalleteComponents("SCV Containers", scv::Point(0,0), scv::Point(panelPalette->getWidth(), 0));   
   panelPalette->addChild(containers);
   containers->addComponent("Image");
   containers->addComponent("Panel");
   containers->addComponent("ScroolPane");
   containers->addComponent("TabbedPane");
   containers->adjustButtonsWidth();

   y = containers->getRelativePosition().y + containers->getHeight() + 15;
   PanelPalleteComponents *controls = new PanelPalleteComponents("SCV Controls", scv::Point(0, y), scv::Point(panelPalette->getWidth(), y));
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

   y = controls->getRelativePosition().y + controls->getHeight() + 15;
   PanelPalleteComponents *windows = new PanelPalleteComponents("SCV Windows", scv::Point(0, y), scv::Point(panelPalette->getWidth(), y));
   panelPalette->addChild(windows);
   windows->addComponent("InternalFrame");
   windows->adjustButtonsWidth();

   y = windows->getRelativePosition().y + windows->getHeight();
   panelPalette->setHeight(y);

   ///////////////////////////////////////////////////////////

   //Design
   ///////////////////////////////////////////////////////////
   scv::Panel *panelDesign = new scv::Panel(scv::Point(0, 0), scv::Point(800, 600));
   panelDesign->setResizable(true);
   scv::ScrollPane *scrollPaneDesign = new scv::ScrollPane(scv::Point(s_defaultBorderGap, s_defaultBorderGap), scv::Point(s_defaultWindowWidht - s_defaultRightBarSize, s_defaultWindowHeight - s_defaultBorderGap), panelDesign);
   scrollPaneDesign->setPanel(panelDesign);
   addComponent(scrollPaneDesign);
   ///////////////////////////////////////////////////////////

   _properties = new Properties(200);
   panelDesign->addChild(_properties);
   /**/
}

void Application::onMouseClick(const scv::MouseEvent &evt) {   
}
void Application::onMouseHold(const scv::MouseEvent &evt) {
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
}
void Application::onMouseUp(const scv::MouseEvent &evt) {
   //std::cout << getFocusedComponent() << std::endl;
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

