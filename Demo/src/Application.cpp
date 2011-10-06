#include "stdafx.h"
#include "Application.h"

Application::Application(void) : Kernel() {

}

Application::~Application(void) {

}

void Application::onMouseClick(const scv::MouseEvent &evt) {
   std::cout << "onMouseClick" << std::endl;
}
void Application::onMouseHold(const scv::MouseEvent &evt) {
   std::cout << "onMouseHold" << std::endl;
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
   std::cout << "onMouseOver" << std::endl;
}
void Application::onMouseUp(const scv::MouseEvent &evt) {
   std::cout << "onMouseUp" << std::endl;
}
void Application::onMouseWheel(const scv::MouseEvent &evt) {
   std::cout << "onMouseWheel" << std::endl;
}

void Application::onKeyPressed(const scv::KeyEvent &evt) {
   std::cout << "onKeyPressed" << std::endl;
}
void Application::onKeyUp(const scv::KeyEvent &evt) {
   std::cout << "onKeyUp" << std::endl;
}

void Application::onSizeChange(void) {
   std::cout << "onSizeChange" << std::endl;
}
void Application::onPositionChange(void) {
   std::cout << "onPositionChange" << std::endl;
}
