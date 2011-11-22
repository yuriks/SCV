#include "stdafx.h"
#include "CodeGenerator.h"

#include "Application.h"

CodeGenerator::CodeGenerator(void) {
}

CodeGenerator::~CodeGenerator(void) {
}

scv::Component *CodeGenerator::addComponent(const std::string &type) {
   scv::Component *object = NULL;

   if (type == "Panel") {
      object = new scv::Panel(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "ColorPicker") {
      object = new scv::ColorPicker(scv::Point(0, 0));
   } else if (type == "ProgressBar") {
      object = new scv::ProgressBar(scv::Point(0, 0),  0);
   } else if (type == "Slider") {
      object = new scv::Slider(scv::Point(0, 0), 0.f, 100.f, 50.f, 1.f);
   } else if (type == "Spinner") {
      object = new scv::Spinner(scv::Point(0, 0), 200, 0.f, 100.f, 50.f, 1.f);
   } else if (type == "Button") {
      object = new scv::Button(scv::Point(0, 0), "SCV Button");
   } else if (type == "CheckBox") {
      object = new scv::CheckBox(scv::Point(0, 0), false, "SCV CheckBox");
   } else if (type == "RadioButton") {
      object = new scv::RadioButton(scv::Point(0, 0), false, "SCV RadioButton");
   } else if (type == "ToggleButton") {
      object = new scv::ToggleButton(scv::Point(0, 0), false, "SCV ToogleButton");
   } else if (type == "TextField") {
      object = new scv::TextField(scv::Point(0, 0), 200, "SCV TextField");
   } else if (type == "TextBox") {
      object = new scv::TextBox(scv::Point(0, 0), scv::Point(200, 200), "SCV TextBox");
   } else if (type == "Separator") {
      object = new scv::Separator(scv::Point(0, 0), scv::Separator::HORIZONTAL, 100);
   } else if (type == "InternalFrame") {
      object = new scv::InternalFrame(200, 200, "SCV InternalFrame");
   } else if (type == "MenuBar") {
      object = new scv::MenuBar(200);
   } else if (type == "TabbedPane") {
      object = new scv::TabbedPane(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "ScrollComponent") {
      object = new scv::ScrollComponent(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "Image") {
      object = new scv::Image(scv::Point(0, 0), "default_image.png");
   } else if (type == "Table") {
      object = new scv::Table(scv::Point(0, 0));
   } else if (type == "ComboBox") {
      object = new scv::ComboBox(scv::Point(0,0), 200);
   } else if (type == "Canvas") {
      object = new scv::Canvas(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "SystemTreeView") {
      object = new scv::SystemTreeView(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "Label") {
      object = new scv::Label(scv::Point(0, 0), "SCV Label");
   }

   _managed.push_back(new ManagedComponent(object, type + scv::toString(getComponentCount(object->getType())), type));   
   return object;
}

void CodeGenerator::deleteComponent(ManagedComponent *managed) {
   if (std::find(_managed.begin(), _managed.end(), managed) != _managed.end()) {
      _managed.remove(managed);
   }
   delete managed;
}

bool CodeGenerator::hasComponent(scv::Component *object) const {
   return getManagedComponent(object) ? true : false;
}

bool CodeGenerator::hasComponent(const std::string &name) const {
   return getManagedComponent(name) ? true : false;
}

ManagedComponent *CodeGenerator::getManagedComponent(scv::Component *object) const {
   for (ManagedList::const_iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == object) {
         return(*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(object);
         if (managed != NULL) return managed;
      }
   }
   return NULL;
}

ManagedComponent *CodeGenerator::getManagedComponent(const std::string &name) const {
   for (ManagedList::const_iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getClassName() == name) {
         return(*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(name);
         if (managed != NULL) return managed;
      }
   }
   return NULL; 
}

CodeGenerator::ManagedList CodeGenerator::getManagedComponents(void) const {
   return _managed;
}

void CodeGenerator::generateCode(void) {
   std::string mainDotCpp;

   std::string applicationDotH;   
   applicationDotH += "#ifndef __APPLICATION_H__\n";
   applicationDotH += "#define __APPLICATION_H__\n";
   applicationDotH += "\n";
   applicationDotH += "class Application : public scv::Kernel {\n";
   applicationDotH += "public:\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   Application(void);\n";
   applicationDotH += "   virtual ~Application(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "   void init(void);\n";
   applicationDotH += "\n";
   applicationDotH += "   //SCVCallbacks\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   virtual void onMouseClick(const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseHold (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseOver (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n";
   applicationDotH += "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onSizeChange(void);\n";
   applicationDotH += "   virtual void onPositionChange(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "protected:\n";
   applicationDotH += "   static const int s_defaultWindowWidth = 1280;\n";
   applicationDotH += "   static const int s_defaultWindowHeight = 720;\n";
   applicationDotH += "   scv::Panel *_mainPanel;\n";
   applicationDotH += "private:\n";
   applicationDotH += "};\n";
   applicationDotH += "\n";
   applicationDotH += "#endif //__APPLICATION_H__\n";

   std::string applicationDotCpp;
   applicationDotCpp += "#include \"Application.h\"\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::Application(void) : Kernel() {\n";
   applicationDotCpp += "   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);\n";
   applicationDotCpp += "   lockWindowSize(true);\n";
   applicationDotCpp += "   setFramesPerSecond(60);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   setWindowTitle(\"SCV Designer - Laboratório de Computação Aplicada (LaCA)\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(10, 10), scv::Point(0, 0));\n";
   applicationDotCpp += static_cast<Application *>(Application::getInstance())->getLayoutCode("_mainPanel");
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onMouseClick(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseHold(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseOver(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseUp(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseWheel(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onKeyPressed(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onKeyUp(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onSizeChange(void) {\n";
   applicationDotCpp += "   _mainPanel->setSize(getWidth() - 20, getHeight() - 20);\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onPositionChange(void) {\n";
   applicationDotCpp += "}\n";   
   
   std::ofstream outputFile;

   outputFile = std::ofstream("../Application.h");
   outputFile << applicationDotH;
   outputFile.close();

   outputFile = std::ofstream("../Application.cpp");
   outputFile << applicationDotCpp;
   outputFile.close();

   std::string widgetDotH, widgetDotCpp;
   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      widgetDotH += (*iter)->getDeclarationCode();
      widgetDotCpp += (*iter)->getImplementationCode();
      mainDotCpp += (*iter)->getAllocationCode();
   }
  
   outputFile = std::ofstream("../Widget.h");
   outputFile << widgetDotH;
   outputFile.close();
   
   outputFile = std::ofstream("../Widget.cpp");
   outputFile << widgetDotCpp;
   outputFile.close();

   outputFile = std::ofstream("../Main.cpp");
   outputFile << mainDotCpp;
   outputFile.close();
}


int CodeGenerator::getComponentCount(scv::Component::Type type) {
   return _counter[type]++;
}

