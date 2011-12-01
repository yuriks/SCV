#include "stdafx.h"
#include "Application.h"

#include "MenuBar.h"

#include "Properties.h"
#include "SpecializedProperties.h"
#include "PropertiesManager.h"

#include "Pallete.h"

#include "GroupObjectWrapper.h"

#include "DesignPreview.h"


MainTabbedPane::MainTabbedPane(void) : scv::TabbedPane(scv::Point(), scv::Point()) {
}

MainTabbedPane::~MainTabbedPane(void) {
}

void MainTabbedPane::onTabChange(void) {
   if (getCurrTabIndex() == 0) {
      (static_cast<Application *>(Application::getInstance()))->createPreview();
   }
   
   if (getCurrTabIndex() != 2) {
      PropertiesManager::getCurr()->setVisible(false);
   } else {
      PropertiesManager::getCurr()->setVisible(true);
   }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

Application::Application(void) : Kernel() {
   currGroup = NULL;

   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(true);
   setFramesPerSecond(60);

   setWindowTitle("SCV Designer");
}

Application::~Application(void) {
}

void Application::init(void) {   
   _componentSelector = new ComponentSelector();
   _componentSelector->setVisible(false, NULL);
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
   Pallete *panelPalette = Pallete::getInstance();
   _mainPanel->addChild(panelPalette);
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

   _mainTabbedPane = new MainTabbedPane();   
   _mainTabbedPane->addChild(DesignPreview::getInstance(), "Design Preview");
   _mainTabbedPane->addChild(tabbedDesign, "Group Layout");
   _mainTabbedPane->addChild(ObjectEditor::getInstance(), "Object Editor");

   _mainPanel->addChild(_mainTabbedPane);
   ///////////////////////////////////////////////////////////

   //Properties
   ///////////////////////////////////////////////////////////
   _mainPanel->addChild(Properties::getInstance());
   _mainPanel->addChild(CountersProperties::Singleton<CountersProperties>::getInstance());
   _mainPanel->addChild(StringsProperties::Singleton<StringsProperties>::getInstance());
   _mainPanel->addChild(StatesProperties::Singleton<StatesProperties>::getInstance());
   _mainPanel->addChild(InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance());
   _mainPanel->addChild(ImageProperties::Singleton<ImageProperties>::getInstance());
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
            ->addComponent(Properties::getInstance())
            ->addComponent(CountersProperties::Singleton<CountersProperties>::getInstance())
            ->addComponent(StringsProperties::Singleton<StringsProperties>::getInstance())
            ->addComponent(StatesProperties::Singleton<StatesProperties>::getInstance())
            ->addComponent(InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance())
            ->addComponent(ImageProperties::Singleton<ImageProperties>::getInstance())
         )
      )
   );

   layout->setVerticalGroup(
      layout->createSequentialGroup()->setAutoCreateGaps(true)->setAutoGapsSize(5)
      ->addComponent(menuBar)
      ->addGroup(
         layout->createParallelGroup()
            ->addComponent(_mainTabbedPane)
            ->addGroup(layout->createSequentialGroup()
               ->addComponent(panelPalette)->addGap(15)
               ->addComponent(Properties::getInstance())
               ->addComponent(CountersProperties::Singleton<CountersProperties>::getInstance())
               ->addComponent(StringsProperties::Singleton<StringsProperties>::getInstance())
               ->addComponent(StatesProperties::Singleton<StatesProperties>::getInstance())
               ->addComponent(InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance())
               ->addComponent(ImageProperties::Singleton<ImageProperties>::getInstance())
            )
      )
   );
   ///////////////////////////////////////////////////////////

   _mainPanel->setLayout(layout);
}

void Application::onMouseClick(const scv::MouseEvent &evt) {   
}

void Application::onMouseHold(const scv::MouseEvent &evt) {
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
}

void Application::onMouseUp(const scv::MouseEvent &evt) {
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
}

void Application::addComponentFromPalette(std::string component) {
   scv::Component *object = CodeGenerator::getInstance()->addComponent(component);
   ObjectEditor::getInstance()->setComponent(object);
}

std::string Application::getLayoutCode(const std::string &panelName) const {
   std::string output;

   output += "   scv::GroupLayout *layout = new scv::GroupLayout(" + panelName + ");\n";
   output += "   " + panelName + "->setLayout(layout);\n";
   output += "\n";
   output += "   layout->setHorizontalGroup(\n";
   output += _hPanelWrapper->getGroupCode();
   output += "   );\n";
   output += "   layout->setVerticalGroup(\n";
   output += _vPanelWrapper->getGroupCode();
   output += "   );\n";

   return output;
}

void Application::openComponentSelector(GroupPanel *group) {
   _componentSelector->setVisible(true, group);
}

void Application::createPreview() {
   DesignPreview::getInstance()->createPreview(_hPanelWrapper, _vPanelWrapper);   
}
