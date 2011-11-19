#include "stdafx.h"
#include "CodeGenerator.h"

#include "Application.h"

CodeGenerator::CodeGenerator(void) {
}

CodeGenerator::~CodeGenerator(void) {
}

int CodeGenerator::getComponentCount(scv::Component::ObjectType type) {
   return counter[type]++;
}

void CodeGenerator::addComponent(scv::Component *object) {
   std::cout << getComponentCount(object->getType()) << std::endl;

}

bool CodeGenerator::hasComponent(scv::Component *object) {
   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == object) return true;
   }
   return false;
}

ManagedComponent *CodeGenerator::getManagedComponent(scv::Component *object) {
   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == object) return(*iter);
   }
   return NULL;   
}

void CodeGenerator::generateCode(void) {

   std::string applicationDotH;   
   applicationDotH += 
   "\
   #ifndef __APPLICATION_H__\n\
   #define __APPLICATION_H__\n\
   \n\
   class Application : public scv::Kernel {\n\
   public:\n\
      ///////////////////////////////////////////////////////////\n\
      Application(void);\n\
      virtual ~Application(void);\n\
      ///////////////////////////////////////////////////////////\n\
   \n\
      void init(void);\n\
   \n\
      //SCVCallbacks\n\
      ///////////////////////////////////////////////////////////\n\
      virtual void onMouseClick(const scv::MouseEvent &evt);\n\
      virtual void onMouseHold (const scv::MouseEvent &evt);\n\
      virtual void onMouseOver (const scv::MouseEvent &evt);\n\
      virtual void onMouseUp   (const scv::MouseEvent &evt);\n\
      virtual void onMouseWheel(const scv::MouseEvent &evt);\n\
   \n\
      virtual void onKeyPressed(const scv::KeyEvent &evt);\n\
      virtual void onKeyUp     (const scv::KeyEvent &evt);\n\
   \n\
      virtual void onSizeChange(void);\n\
      virtual void onPositionChange(void);\n\
      ///////////////////////////////////////////////////////////\n\
   \n\
   protected:\n\
      static const int s_defaultWindowWidth = 1280;\n\
      static const int s_defaultWindowHeight = 720;\n\
      scv::Panel *_mainPanel;\n\
   private:\n\
   };\n\
   \n\
   #endif //__APPLICATION_H__\n\
   ";

   std::string applicationDotCpp;
   applicationDotCpp +=
   "\
   #include \"Application.h\"\n\
   \n\
   Application::Application(void) : Kernel() {\n\
      setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);\n\
      lockWindowSize(true);\n\
      setFramesPerSecond(60);\n\
   \n\
      setWindowTitle(\"SCV Designer - Laboratório de Computação Aplicada (LaCA)\");\n\
   }\n\
   \n\
   Application::~Application(void) {\n\
   }\n\
   \n\
   void Application::init(void) {\n\
      _mainPanel = new scv::Panel(scv::Point(10, 10), scv::Point(0, 0));\n\
   \n"
   + static_cast<Application *>(Application::getInstance())->getLayoutCode() +   
   "\
   }\n\
   \n\
   void Application::onMouseClick(const scv::MouseEvent &evt) {\n\
   }\n\
   void Application::onMouseHold(const scv::MouseEvent &evt) {\n\
   }\n\
   void Application::onMouseOver(const scv::MouseEvent &evt) {\n\
   }\n\
   void Application::onMouseUp(const scv::MouseEvent &evt) {\n\
   }\n\
   void Application::onMouseWheel(const scv::MouseEvent &evt) {\n\
   }\n\
   \n\
   void Application::onKeyPressed(const scv::KeyEvent &evt) {\n\
   }\n\
   void Application::onKeyUp(const scv::KeyEvent &evt) {\n\
   }\n\
   \n\
   void Application::onSizeChange(void) {\n\
      _mainPanel->setSize(getWidth() - 20, getHeight() - 20);\n\
   }\n\
   void Application::onPositionChange(void) {\n\
   }\n\
   ";

   std::ofstream outputFile;

   outputFile = std::ofstream("../Application.h");
   outputFile << applicationDotH;
   outputFile.close();

   outputFile = std::ofstream("../Application.cpp");
   outputFile << applicationDotCpp;
   outputFile.close();
}
