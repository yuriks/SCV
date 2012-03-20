#include <SCV/SCV.h>
#include "Application.h"

#include "MenuBar.h"

#include "Properties.h"
#include "SpecializedProperties.h"
#include "PropertiesManager.h"

#include "Pallete.h"

#include "GroupObjectWrapper.h"

#include "DesignPreview.h"

#include "CodeViewer.h"

///////////////////////////////////////////////////////////

CodeViewerTabbedPane::CodeViewerTabbedPane(std::vector<CodeViewer*> cv)
    : scv::TabbedPane(scv::Point(), scv::Point()) {
    _vCodeViewer = cv;
    _vCodeViewer[0]->setText(CodeGenerator::getInstance()->generateCodeMain());
    _vCodeViewer[1]->setText(CodeGenerator::getInstance()->generateCodeAppH());
}

CodeViewerTabbedPane::~CodeViewerTabbedPane(void) {
}

void CodeViewerTabbedPane::onTabChange(void) {
   if (getCurrTabIndex() == 2) {
       _vCodeViewer[2]->setText(CodeGenerator::getInstance()->generateCodeAppCpp());
   } else if (getCurrTabIndex() == 3) {
       _vCodeViewer[3]->setText(CodeGenerator::getInstance()->generateCodeWdgH());
   } else if (getCurrTabIndex() == 4) {
       _vCodeViewer[4]->setText(CodeGenerator::getInstance()->generateCodeWdgCpp());
   }
}

///////////////////////////////////////////////////////////

MainTabbedPane::MainTabbedPane(CodeViewerTabbedPane* cvt)
    : scv::TabbedPane(scv::Point(), scv::Point()) {
    _cvt = cvt;
}

MainTabbedPane::~MainTabbedPane(void) {
}

void MainTabbedPane::onTabChange(void) {
   if (getCurrTabIndex() == 0) {
      //Refresh on DesignPreview used on GroupPanel::addChild()
   }

   if (getCurrTabIndex() != 1) {
       _cvt->setCurrTabIndex(0);
   } else {
   
   }

   if (getCurrTabIndex() != 2) {
      PropertiesManager::getCurr()->setVisible(false);
   } else {
      PropertiesManager::getCurr()->setVisible(true);
   }
}

//////////////////////////////////////////////////////////

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
   
   _hPanelWrapper = new GroupPanelWrapper(GroupPanel::HORIZONTAL);
   _vPanelWrapper = new GroupPanelWrapper(GroupPanel::VERTICAL);

   //Palette
   ///////////////////////////////////////////////////////////
   Pallete *panelPalette = Pallete::getInstance();
   panelPalette->setGroupPanelsWraper(_hPanelWrapper, _vPanelWrapper);
   _mainPanel->addChild(panelPalette);
   ///////////////////////////////////////////////////////////

   //Design 
   ///////////////////////////////////////////////////////////
   scv::ScrollComponent *hScrollDesign = new scv::ScrollComponent(scv::Point(0, 0), scv::Point(0, 0), _hPanelWrapper);
   scv::ScrollComponent *vScrollDesign = new scv::ScrollComponent(scv::Point(0, 0), scv::Point(0, 0), _vPanelWrapper);

   scv::TabbedPane *tabbedDesign = new scv::TabbedPane(scv::Point(), scv::Point());
   tabbedDesign->addChild(hScrollDesign, "Group Layout: Horizontal");
   tabbedDesign->addChild(vScrollDesign, "Group Layout: Vertical");

   _mainCodeViewer = new CodeViewer();
   _AppHCodeViewer = new CodeViewer();
   _AppCppCodeViewer = new CodeViewer();
   _WdgHCodeViewer = new CodeViewer();
   _WdgCppCodeViewer = new CodeViewer();
   std::vector<CodeViewer*> cv;
   cv.push_back(_mainCodeViewer);
   cv.push_back(_AppHCodeViewer);
   cv.push_back(_AppCppCodeViewer);
   cv.push_back(_WdgHCodeViewer);
   cv.push_back(_WdgCppCodeViewer);
   _codeViewerTabbedPane = new CodeViewerTabbedPane(cv);
   _codeViewerTabbedPane->addChild(_mainCodeViewer, "main.cpp");
   _codeViewerTabbedPane->addChild(_AppHCodeViewer, "Aplication.h");
   _codeViewerTabbedPane->addChild(_AppCppCodeViewer, "Aplication.cpp");
   _codeViewerTabbedPane->addChild(_WdgHCodeViewer, "Widget.h");
   _codeViewerTabbedPane->addChild(_WdgCppCodeViewer, "Widget.cpp");


   _mainTabbedPane = new MainTabbedPane(_codeViewerTabbedPane);   
   _mainTabbedPane->addChild(tabbedDesign, "Group Layout");
   _mainTabbedPane->addChild(_codeViewerTabbedPane, "Code Viewer");
   _mainTabbedPane->addChild(ObjectEditor::getInstance(), "Object Editor");

   _mainPanel->addChild(_mainTabbedPane);

   _designPreviewTabbedPane = new scv::TabbedPane(scv::Point(), scv::Point());
   _designPreviewTabbedPane->addChild(DesignPreview::getInstance(), "Design Preview");

   _mainPanel->addChild(_designPreviewTabbedPane);
   //////////////////////////////////////////////////////////

   //Properties
   ///////////////////////////////////////////////////////////
   _mainPanel->addChild(Properties::getInstance());
   _mainPanel->addChild(CountersProperties::Singleton<CountersProperties>::getInstance());
   _mainPanel->addChild(StringsProperties::Singleton<StringsProperties>::getInstance());
   _mainPanel->addChild(StatesProperties::Singleton<StatesProperties>::getInstance());
   _mainPanel->addChild(InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance());
   _mainPanel->addChild(ImageProperties::Singleton<ImageProperties>::getInstance());
   _mainPanel->addChild(FrameProperties::Singleton<FrameProperties>::getInstance());
   ///////////////////////////////////////////////////////////

   //GroupLayout
   ///////////////////////////////////////////////////////////
   scv::GroupLayout *layout = new scv::GroupLayout(_mainPanel);

   layout->setHorizontalGroup(layout->createParallelGroup()
      ->addComponent(menuBar)
      ->addGroup(layout->createSequentialGroup()->setAutoCreateGaps(true)
      ->addGroup(layout->createParallelGroup()
         ->addComponent(_mainTabbedPane)
         ->addComponent(_designPreviewTabbedPane)
         )
         ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
            ->addComponent(panelPalette)
            ->addComponent(Properties::getInstance())
            ->addComponent(CountersProperties::Singleton<CountersProperties>::getInstance())
            ->addComponent(StringsProperties::Singleton<StringsProperties>::getInstance())
            ->addComponent(StatesProperties::Singleton<StatesProperties>::getInstance())
            ->addComponent(InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance())
            ->addComponent(ImageProperties::Singleton<ImageProperties>::getInstance())
            ->addComponent(FrameProperties::Singleton<FrameProperties>::getInstance())
         )
      )
   );

   layout->setVerticalGroup(
      layout->createSequentialGroup()->setAutoCreateGaps(true)->setAutoGapsSize(5)
      ->addComponent(menuBar)
      ->addGroup(
         layout->createParallelGroup()
         ->addGroup(layout->createSequentialGroup()
            ->addComponent(_mainTabbedPane)
            ->addComponent(_designPreviewTabbedPane)
            )
            ->addGroup(layout->createSequentialGroup()
               ->addComponent(panelPalette)->addGap(15)
               ->addComponent(Properties::getInstance())
               ->addComponent(CountersProperties::Singleton<CountersProperties>::getInstance())
               ->addComponent(StringsProperties::Singleton<StringsProperties>::getInstance())
               ->addComponent(StatesProperties::Singleton<StatesProperties>::getInstance())
               ->addComponent(InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance())
               ->addComponent(ImageProperties::Singleton<ImageProperties>::getInstance())
               ->addComponent(FrameProperties::Singleton<FrameProperties>::getInstance())
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
