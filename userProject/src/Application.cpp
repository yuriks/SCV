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

   scv::ToggleButton *toggleButton0 = new scv::ToggleButton(scv::Point(93,79), scv::Point(181, 103), 0, "");
   addComponent(toggleButton0);

   scv::ToggleButton *toggleButton1 = new scv::ToggleButton(scv::Point(194,76), scv::Point(280, 100), 0, "asd");
   addComponent(toggleButton1);

   scv::Spinner *spinner0 = new scv::Spinner(scv::Point(327,112), 35, 0.f, 100.f, 50.f, 1.f);
   addComponent(spinner0);

   scv::GenericTree *genericTree0 = new scv::GenericTree(scv::Point(515,90), scv::Point(715, 290), new scv::GenericNode("Root") );
   addComponent(genericTree0);

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
