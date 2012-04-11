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

   scv::TextBox *textBox0 = new scv::TextBox(scv::Point(642,0), scv::Point(1035, 256), "TextBox 0");
   addComponent(textBox0);

   scv::TextField *textField0 = new scv::TextField(scv::Point(643,260), 167, "TextField 0");
   addComponent(textField0);

   scv::Slider *slider0 = new scv::Slider(scv::Point(459,24), 100, 0.f, 100.f, 50.f, 1.f);
   addComponent(slider0);

   scv::Spinner *spinner0 = new scv::Spinner(scv::Point(34,9), 76, 0.f, 100.f, 50.f, 1.f);
   addComponent(spinner0);

   scv::Table *table0 = new scv::Table(scv::Point(30,540), 4, 4, 1, 50);
   addComponent(table0);

   scv::ProgressBar *progressBar0 = new scv::ProgressBar(scv::Point(298,183), scv::Point(398, 207), 0);
   addComponent(progressBar0);

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
