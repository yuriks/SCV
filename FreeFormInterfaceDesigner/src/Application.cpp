#include "stdafx.h"
#include "Application.h"
#include "InterfaceDesign.h"
#include "CodeGenerator.h"

Application::Application(void) : Kernel() {

   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV v4.1 - FreeForm Interface Designer");
}

Application::~Application(void) {
}

void Application::init(void) {   
   _mainPanel = new scv::Panel(scv::Point(0,0), scv::Point(s_defaultWindowWidth, s_defaultWindowHeight));
   addComponent(_mainPanel);
   _mainPanel->registerContextMenu(new InterfaceDesign(NULL));
}

void Application::onSizeChange() {
   _mainPanel->setSize(getWidth(), getHeight());
}

void Application::onDisplay() {
}

void Application::generateCode()
{
   CodeGenerator::getInstance()->generateCode();
}

void Application::clearRecursive(scv::Component* comp)
{
   while(comp->_children.size() > 0)
   {
      scv::Component* obj = comp->_children.back();
      clearRecursive(obj);
      removeComponent(obj);
   }
}

void Application::clearInterface()
{
   while(_objects.size() > 1)
   {
      scv::Component* obj = _objects.back();
      clearRecursive(obj);
      removeComponent(obj);
   }
}