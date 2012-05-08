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

   scv::MenuBar *menuBar0 = new scv::MenuBar(1050);
   addComponent(menuBar0);

   scv::ProgressBar *progressBar0 = new scv::ProgressBar(scv::Point(4,43), scv::Point(297, 116), 0);
   addComponent(progressBar0);

   scv::CheckBox *checkBox0 = new scv::CheckBox(scv::Point(43,181), 1, "do nothing");
   addComponent(checkBox0);

   scv::ToggleButton *toggleButton0 = new scv::ToggleButton(scv::Point(180,138), scv::Point(386, 228), 1, "toggle button");
   addComponent(toggleButton0);

   scv::ColorPicker *colorPicker0 = new scv::ColorPicker(scv::Point(7,250));
   addComponent(colorPicker0);

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
