#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(1050, 800);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV v4.0 - FreeForm Interface Designer");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1050, 800));

   addComponent(_mainPanel);

   scv::Button *button0 = new scv::Button(scv::Point(211,184), scv::Point(264, 208), "");
   addComponent(button0);

   scv::InternalFrame *internalFrame0 = new scv::InternalFrame(200,195, "internal frame 0");
   internalFrame0->setRelativePosition(scv::Point(483,183));
   addComponent(internalFrame0);

   scv::InternalFrame *internalFrame1 = new scv::InternalFrame(200,200, "internal frame 1");
   internalFrame1->setRelativePosition(scv::Point(263,183));
   addComponent(internalFrame1);

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
