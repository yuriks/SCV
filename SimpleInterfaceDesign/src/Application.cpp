#include "stdafx.h"
#include "Application.h"
#include "InterfaceDesign.h"

Application::Application(void) : Kernel() {

   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV Interface Designer v1.0");
}

Application::~Application(void) {
}

void Application::init(void) {   
   _mainPanel = new scv::Panel(scv::Point(0,0), scv::Point(s_defaultWindowWidth, s_defaultWindowHeight));
   addComponent(_mainPanel);
   _mainPanel->registerContextMenu(new InterfaceDesign(NULL));
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

void Application::onDisplay(void) {
}