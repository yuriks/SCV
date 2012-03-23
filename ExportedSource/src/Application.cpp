/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laboratório de Computação Aplicada
www.inf.ufsm.br/~pozzer/scv/
2007-2012 

*/

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

   scv::Button *button0 = new scv::Button(scv::Point(131,110), scv::Point(222, 167), "dfgdfg");
   addComponent(button0);

   scv::Panel *panel0 = new scv::Panel(scv::Point(351,81), scv::Point(551, 281));
   addComponent(panel0);

   scv::Panel *panel1 = new scv::Panel(scv::Point(606,97), scv::Point(806, 297));
   addComponent(panel1);

   scv::Button *button1 = new scv::Button(scv::Point(368,412), scv::Point(419, 436), "ghfghfh");
   addComponent(button1);

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
