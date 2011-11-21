#include "stdafx.h"
#include "Application.h"

#include "MenuBar.h"
#include "Properties.h"
#include "Pallete.h"


MainTabbedPane::MainTabbedPane(void) : scv::TabbedPane(scv::Point(), scv::Point()) {
}

MainTabbedPane::~MainTabbedPane(void) {
}

void MainTabbedPane::onTabChange(void) {
   if (getCurrTab() != 2) {
      ObjectEditor::getInstance()->setComponent(NULL);
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

Application::Application(void) : Kernel() {
   currGroup = NULL;

   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(true);
   setFramesPerSecond(60);

   setWindowTitle("SCV Designer - Laboratório de Computação Aplicada (LaCA)");
}

Application::~Application(void) {
}

void Application::init(void) {
   static const int s_defaultGap = 10;
   static const int s_defaultRightPanelWidth = 250;
   
   _componentSelector = new ComponentSelector();
   _componentSelector->setVisible(false);
   scv::InternalFrameHolder::getInstance()->registerFrame(_componentSelector);

   _mainPanel = new scv::Panel(scv::Point(0 + s_defaultGap, 0 + s_defaultGap), scv::Point(s_defaultWindowWidth - s_defaultGap, s_defaultWindowHeight - s_defaultGap));
   addComponent(_mainPanel);

   //Menu
   ///////////////////////////////////////////////////////////
   MenuBar *menuBar = new MenuBar(s_defaultWindowWidth);
   _mainPanel->addChild(menuBar);

   ///////////////////////////////////////////////////////////
   
   //Palette
   ///////////////////////////////////////////////////////////
   scv::Panel *panelPalette = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultRightPanelWidth, 0));
   _mainPanel->addChild(panelPalette);
   
   scv::GroupLayout *paletteLayout = new scv::GroupLayout(panelPalette);
   panelPalette->setLayout(paletteLayout);

   PanelPalleteComponents *containers = new PanelPalleteComponents("SCV Containers", scv::Point(), scv::Point(s_defaultRightPanelWidth, 0));   
   panelPalette->addChild(containers);
   containers->addComponent("Image");
   containers->addComponent("Panel");
   containers->addComponent("ScrollComponent");
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
   _hPanelWrapper = new GroupPanelWrapper(GroupPanel::HORIZONTAL);
   _vPanelWrapper = new GroupPanelWrapper(GroupPanel::VERTICAL);

   scv::ScrollComponent *hScrollDesign = new scv::ScrollComponent(scv::Point(0, 0), scv::Point(0, 0), _hPanelWrapper);
   scv::ScrollComponent *vScrollDesign = new scv::ScrollComponent(scv::Point(0, 0), scv::Point(0, 0), _vPanelWrapper);

   scv::TabbedPane *tabbedDesign = new scv::TabbedPane(scv::Point(), scv::Point());
   tabbedDesign->addChild(hScrollDesign, "Group Layout: Horizontal");
   tabbedDesign->addChild(vScrollDesign, "Group Layout: Vertical");

   _designPreview = new scv::Panel(scv::Point(), scv::Point());

   _mainTabbedPane = new MainTabbedPane();   
   _mainTabbedPane->addChild(_designPreview, "Design Preview");
   _mainTabbedPane->addChild(tabbedDesign, "Group Layout");
   _mainTabbedPane->addChild(ObjectEditor::getInstance(), "Object Editor");

   _mainPanel->addChild(_mainTabbedPane);
   ///////////////////////////////////////////////////////////

   //Properties
   ///////////////////////////////////////////////////////////
   _properties = new Properties(s_defaultRightPanelWidth);
   _mainPanel->addChild(_properties);
   ///////////////////////////////////////////////////////////

   //GroupLayout
   ///////////////////////////////////////////////////////////
   scv::GroupLayout *layout = new scv::GroupLayout(_mainPanel);

   layout->setHorizontalGroup(layout->createParallelGroup()
      ->addComponent(menuBar)
      ->addGroup(layout->createSequentialGroup()->setAutoCreateGaps(true)
         ->addComponent(_mainTabbedPane)
         ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
            ->addComponent(panelPalette)
            ->addComponent(_properties)
         )
      )
   );

   layout->setVerticalGroup(
      layout->createSequentialGroup()->setAutoCreateGaps(true)->setAutoGapsSize(5)
      ->addComponent(menuBar)
      ->addGroup(
         layout->createParallelGroup()
            ->addComponent(_mainTabbedPane)
            ->addGroup(layout->createSequentialGroup()->setAutoCreateGaps(true)
               ->addComponent(panelPalette)
               ->addComponent(_properties)
            )
      )
   );
   ///////////////////////////////////////////////////////////

   _mainPanel->setLayout(layout);
}

void Application::onMouseClick(const scv::MouseEvent &evt) {   
}
void Application::onMouseHold(const scv::MouseEvent &evt) {
   if (CodeGenerator::getInstance()->hasComponent(getFocusedComponent())) {
      _properties->setComponent(getFocusedComponent());
   }
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
}
void Application::onMouseUp(const scv::MouseEvent &evt) {
   if (CodeGenerator::getInstance()->hasComponent(getFocusedComponent())) {
      _properties->setComponent(getFocusedComponent());
   }
}
void Application::onMouseWheel(const scv::MouseEvent &evt) {
}

void Application::onKeyPressed(const scv::KeyEvent &evt) {
}
void Application::onKeyUp(const scv::KeyEvent &evt) {
}

void Application::onSizeChange(void) {
   _mainPanel->setSize(getWidth() - 20, getHeight() - 20);
}
void Application::onPositionChange(void) {
}

void Application::onDisplay(void) {
   ObjectEditor::getInstance()->update();
}

void Application::addComponentFromPalette(std::string component) {
   ObjectEditor::getInstance()->setComponent(CodeGenerator::getInstance()->addComponent(component));
   _mainTabbedPane->setCurrTab(2);
}

std::string Application::getLayoutCode(const std::string &panelName) const {
   std::string output;

   output += "   scv::GroupLayout *layout = new scv::GroupLayout(" + panelName + ");\n";
   output += "   " + panelName + "->setLayout(layout);\n";
   output += "\n";
   output += "   layout->setHorizontalGroup(\n";
   output += "   " + _hPanelWrapper->getGroupCode();
   output += "   );\n";
   output += "   layout->setVerticalGroup(\n";
   output += "   " + _vPanelWrapper->getGroupCode();
   output += "   );\n";

   return output;
}

void Application::openComponentSelector(GroupPanel *group) {
   _componentSelector->setVisible(true);
}
