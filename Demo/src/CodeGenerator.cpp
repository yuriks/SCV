#include <SCV/SCV.h>
#include "CodeGenerator.h"

#include "Application.h"

CodeGenerator::CodeGenerator(void) {
   _scvFrame = NULL;
}

CodeGenerator::~CodeGenerator(void) {
}

/*Adicionar novo componente através do Pallete*/
scv::Component *CodeGenerator::addComponent(const std::string &type) {
   scv::Component *object = NULL;
   std::string aditionalString = "";

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
      aditionalString = "_SCV_Button";
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
      object = new scv::Table(scv::Point(0, 0),4,4,1,15);
   } else if (type == "ComboBox") {
      object = new scv::ComboBox(scv::Point(0,0), 200);
   } else if (type == "Canvas") {
      object = new scv::Canvas(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "SystemTreeView") {
      object = new scv::SystemTreeView(scv::Point(0, 0), scv::Point(200, 200));
   } else if (type == "Label") {
      object = new scv::Label(scv::Point(0, 0), "SCV Label");
   }

   addManagedComponent(object, type, aditionalString);
   return object;
}

/*Adiciona novo componente criado no Pallete (A string adicional é para componentes especiais)*/
void CodeGenerator::addManagedComponent(scv::Component *object, const std::string &type, const std::string &aString) {
    _managed.push_back(new ManagedComponent(object, type + scv::toString(getComponentCount(object->getType())) + aString , type));
}

void CodeGenerator::deleteComponent(ManagedComponent *managed) {
   if (std::find(_managed.begin(), _managed.end(), managed) != _managed.end()) {
      _managed.remove(managed);
   }
   delete managed;
}

/**/
void CodeGenerator::deleteComponents()
{
    ManagedComponent* a;
    while(_managed.size() > 1)
    {
        a = _managed.back();
        if(a->getParent() != NULL){
            a->getParent()->removeChild(a);
        }else
        {
            _managed.pop_back();
        }
    }
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
   // main.cpp, Widget.cpp, Widget.h
   ///////////////////////////////////////////////////////////
   std::string mainDotCpp, allocationCode;
   mainDotCpp += "#include <SCV/SCV.h>\n";
   mainDotCpp += "#include \"Application.h\"\n";
   mainDotCpp += "#include \"Widget.h\"\n";
   mainDotCpp += "\n";
   mainDotCpp += "int main(int argc, char* argv[]) {\n";
   mainDotCpp += "   Application *kernel = new Application();\n";
   mainDotCpp += "   scv::Kernel::setInstance(kernel);\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->init();\n";
   mainDotCpp += "\n";

   std::string widgetDotH, widgetDotCpp;
   widgetDotH += "#ifndef __WIDGET_H__\n";
   widgetDotH += "#define __WIDGET_H__\n";
   widgetDotH += "\n";
   widgetDotH += "#include <SCV/SCV.h>\n";
   widgetDotH += "\n";

   widgetDotCpp += "#include \"Widget.h\"\n";
   widgetDotCpp += "\n";

   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == _scvFrame) continue;

      widgetDotH += (*iter)->getDeclarationCode();
      widgetDotCpp += (*iter)->getImplementationCode();
      allocationCode += (*iter)->getAllocationCode();
   }

   widgetDotH += "\n";
   widgetDotH += "#endif //__WIDGET_H__\n";

   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";
   ///////////////////////////////////////////////////////////

   // Application.h
   ///////////////////////////////////////////////////////////
   std::string applicationDotH;   
   applicationDotH += "#ifndef __APPLICATION_H__\n";
   applicationDotH += "#define __APPLICATION_H__\n";
   applicationDotH += "\n";
   applicationDotH += "#include <SCV/SCV.h>\n";
   applicationDotH += "#include \"Widget.h\"\n";
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
   ///////////////////////////////////////////////////////////

   // Application.cpp
   ///////////////////////////////////////////////////////////
   std::string applicationDotCpp;
   applicationDotCpp += "#include \"Application.h\"\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::Application(void) : Kernel() {\n";
   applicationDotCpp += "   setWindowSize(" + scv::toString(_scvFrame->getWidth()) + " - 20, " + scv::toString(_scvFrame->getHeight()) + " - 40);\n";
   applicationDotCpp += "   lockWindowSize(true);\n";
   applicationDotCpp += "   setFramesPerSecond(60);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   setWindowTitle(\"" + _scvFrame->getTitle() + "\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(2, 2), scv::Point(2, 2));\n";
   applicationDotCpp += allocationCode;
   applicationDotCpp += static_cast<Application *>(Application::getInstance())->getLayoutCode("_mainPanel") + "\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   addComponent(_mainPanel);\n";   
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
   applicationDotCpp += "   _mainPanel->setSize(getWidth() - 4, getHeight() - 4);\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onPositionChange(void) {\n";
   applicationDotCpp += "}\n";   
   ///////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////
   std::ofstream outputFile;

   outputFile = std::ofstream("../Application.h");
   outputFile << applicationDotH;
   outputFile.close();

   outputFile = std::ofstream("../Application.cpp");
   outputFile << applicationDotCpp;
   outputFile.close();

   outputFile = std::ofstream("../Widget.h");
   outputFile << widgetDotH;
   outputFile.close();
   
   outputFile = std::ofstream("../Widget.cpp");
   outputFile << widgetDotCpp;
   outputFile.close();

   outputFile = std::ofstream("../main.cpp");
   outputFile << mainDotCpp;
   outputFile.close();
   ///////////////////////////////////////////////////////////
}

std::string CodeGenerator::generateCodeMain(void)
{
    ///////////////////////////////////////////////////////////
   std::string mainDotCpp;
   mainDotCpp += "#include <SCV/SCV.h>\n";
   mainDotCpp += "#include \"Application.h\"\n";
   mainDotCpp += "#include \"Widget.h\"\n";
   mainDotCpp += "\n";
   mainDotCpp += "int main(int argc, char* argv[]) {\n";
   mainDotCpp += "   scv::Kernel::setInstance(new Application());\n";
   mainDotCpp += "   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->init();\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";
   ///////////////////////////////////////////////////////////

   return mainDotCpp;
}
std::string CodeGenerator::generateCodeAppH(void)
{
   // Application.h
   ///////////////////////////////////////////////////////////
   std::string applicationDotH;   
   applicationDotH += "#ifndef __APPLICATION_H__\n";
   applicationDotH += "#define __APPLICATION_H__\n";
   applicationDotH += "\n";
   applicationDotH += "#include \"SCV.h\"\n";
   applicationDotH += "#include \"Widget.h\"\n";
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
   ///////////////////////////////////////////////////////////

   return applicationDotH;

}

std::string CodeGenerator::generateCodeAppCpp(void)
{
   ///////////////////////////////////////////////////////////
   std::string allocationCode;
   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == _scvFrame) continue;
      allocationCode += (*iter)->getAllocationCode();
   }
   ///////////////////////////////////////////////////////////

   // Application.cpp
   ///////////////////////////////////////////////////////////
   std::string applicationDotCpp;
   applicationDotCpp += "#include \"Application.h\"\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::Application(void) : Kernel() {\n";
   applicationDotCpp += "   setWindowSize(" + scv::toString(_scvFrame->getWidth()) + " - 20, " + scv::toString(_scvFrame->getHeight()) + " - 40);\n";
   applicationDotCpp += "   lockWindowSize(true);\n";
   applicationDotCpp += "   setFramesPerSecond(60);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   setWindowTitle(\"" + _scvFrame->getTitle() + "\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(2, 2), scv::Point(2, 2));\n";
   applicationDotCpp += allocationCode;
   applicationDotCpp += static_cast<Application *>(Application::getInstance())->getLayoutCode("_mainPanel") + "\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   addComponent(_mainPanel);\n";   
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
   applicationDotCpp += "   _mainPanel->setSize(getWidth() - 4, getHeight() - 4);\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onPositionChange(void) {\n";
   applicationDotCpp += "}\n";   
   ///////////////////////////////////////////////////////////

   return applicationDotCpp;
}

std::string CodeGenerator::generateCodeWdgH(void)
{
   std::string widgetDotH;
   widgetDotH += "#ifndef __WIDGET_H__\n";
   widgetDotH += "#define __WIDGET_H__\n";
   widgetDotH += "\n";
   widgetDotH += "#include <SVC/SCV.h>\n";
   widgetDotH += "\n";


   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == _scvFrame) continue;
      widgetDotH += (*iter)->getDeclarationCode();
   }

   widgetDotH += "\n";
   widgetDotH += "#endif //__WIDGET_H__\n";
   ///////////////////////////////////////////////////////////

   return widgetDotH;
}

std::string CodeGenerator::generateCodeWdgCpp(void)
{
   ///////////////////////////////////////////////////////////
   std::string widgetDotCpp;
   widgetDotCpp += "#include \"Widget.h\"\n";
   widgetDotCpp += "\n";

   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == _scvFrame) continue;
      widgetDotCpp += (*iter)->getImplementationCode();
   }
   ///////////////////////////////////////////////////////////
   return widgetDotCpp;
}

int CodeGenerator::getComponentCount(scv::Component::Type type) {
   return _counter[type]++;
}

std::string SpacesToUnderlines(std::string s)
{
    for(int i = 0 ; i < s.length() ; i++)
    {
        if(s[i] == ' ')
        {
            s[i] = '_';
        }
    }
    return s;
}

void CodeGenerator::modifyNameManagedComponent(scv::Component *obj, std::string newName)
{
    ManagedComponent *a = getManagedComponent(obj);
    a->setClassName(a->getClassName().substr(0,a->getClassName().find('_')+1) + SpacesToUnderlines(newName));
}

void CodeGenerator::setSCVFrame(scv::InternalFrame *frame) {
   if (_scvFrame == NULL) {
      _scvFrame = frame;
      addManagedComponent(frame, "InternalFrame");
   }
}

