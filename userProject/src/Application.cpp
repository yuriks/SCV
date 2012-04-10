#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(708, 481);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV v4.0 - FreeForm Interface Designer");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(708, 481));

   addComponent(_mainPanel);

   scv::InternalFrame *internalFrame0 = new scv::InternalFrame(425, 408, "internal frame 0");
   internalFrame0->setRelativePosition(scv::Point(0,0));
   addComponent(internalFrame0);

   scv::InternalFrame *internalFrame1 = new scv::InternalFrame(245, 447, "internal frame 1");
   internalFrame1->setRelativePosition(scv::Point(424,1));
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
