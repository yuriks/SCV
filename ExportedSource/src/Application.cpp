#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(1050, 800);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV Interface Designer v1.1");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1050, 800));

   addComponent(_mainPanel);

   scv::TabbedPane *tabbedPane0 = new scv::TabbedPane(scv::Point(130,97), scv::Point(998, 757));
   addComponent(tabbedPane0);
      scv::Panel *panel0 = new scv::Panel(scv::Point(0,22), scv::Point(868, 660));
      panel0->setParent(tabbedPane0);
      scv::Image *image0 = new scv::Image(scv::Point(15,29), scv::Point(518, 603), "C:/Users/Tiago/Pictures/crash-bandicoot.jpg");
      image0->setParent(panel0);
      scv::Button *button0 = new scv::Button(scv::Point(55,22), scv::Point(376, 62), "[CRASH DANDO JOINHA]");
      button0->setParent(image0);


      scv::Panel *panel1 = new scv::Panel(scv::Point(540,32), scv::Point(854, 604));
      panel1->setParent(panel0);
      scv::TabbedPane *tabbedPane1 = new scv::TabbedPane(scv::Point(28,44), scv::Point(299, 534));
      tabbedPane1->setParent(panel1);
      scv::Panel *panel2 = new scv::Panel(scv::Point(0,22), scv::Point(271, 490));
      panel2->setParent(tabbedPane1);
      scv::TextBox *textBox0 = new scv::TextBox(scv::Point(71,144), scv::Point(237, 212), "   IS JUST LEGENDARY");
      textBox0->setParent(panel2);






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
   _mainPanel->setSize(getWidth(), getHeight());
}
void Application::onPositionChange(void) {
}
