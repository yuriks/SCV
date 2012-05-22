#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(1050, 800);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV v4.1 - FreeForm Interface Designer");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1050, 800));

   addComponent(_mainPanel);

   Panel0 *panel0 = new Panel0(scv::Point(229,109), scv::Point(429, 309));
   addComponent(panel0);

   MenuBar0 *menuBar0 = new MenuBar0(200);
   menuBar0->setParent(panel0);
   menuBar0->addMenu(new scv::ContextMenu("menu0"));
   menuBar0->addMenu(new scv::ContextMenu("menu1"));
   menuBar0->addMenu(new scv::ContextMenu("menu2"));

   MenuBar1 *menuBar1 = new MenuBar1(1050);
   addComponent(menuBar1);
   menuBar1->addMenu(new scv::ContextMenu("menu0"));
   menuBar1->addMenu(new scv::ContextMenu("menu1"));
   menuBar1->addMenu(new scv::ContextMenu("menu2"));
   menuBar1->addMenu(new scv::ContextMenu("menu3"));
   menuBar1->addMenu(new scv::ContextMenu("menu4"));
   menuBar1->addMenu(new scv::ContextMenu("menu5"));

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
