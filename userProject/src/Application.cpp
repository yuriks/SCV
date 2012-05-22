#include "Application.h"
#include "Widget.h"

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

   Panel0 *panel0 = new Panel0(scv::Point(377,173), scv::Point(897, 597));
   addComponent(panel0);

   Panel1 *panel1 = new Panel1(scv::Point(91,38), scv::Point(461, 388));
   panel1->setParent(panel0);

   Button0 *button0 = new Button0(scv::Point(36,40), scv::Point(89, 64), "");
   button0->setParent(panel1);

   Label0 *label0 = new Label0(scv::Point(113,114), scv::Point(189, 127), "");
   label0->setParent(panel1);

   Canvas0 *canvas0 = new Canvas0(scv::Point(12,95), scv::Point(212, 295));
   canvas0->setParent(panel1);

   MenuBar0 *menuBar0 = new MenuBar0(370);
   menuBar0->setParent(panel1);

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
