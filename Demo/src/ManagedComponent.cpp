#include "stdafx.h"
#include "ManagedComponent.h"

#include "CodeGenerator.h"

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ManagedComponent::ManagedComponent(scv::Component *object, const std::string &name, const std::string &typeName) {
   _object = object;
   _className = name;
   _typeName = typeName;

   _customClass = false;

   _parent = NULL;
}

ManagedComponent::~ManagedComponent(void) {
   setParent(NULL);

   List::iterator iter = _children.begin();
   while (iter != _children.end()) {
      ManagedComponent *pItem = (*iter);
      iter = _children.erase(iter);
      delete pItem;
   }
}

void ManagedComponent::setParent(ManagedComponent *parent) {
   if (_parent != NULL) _parent->removeChild(this);

   _parent = parent;

   if (_parent != NULL) _parent->addChild(this);
}

void ManagedComponent::addChild(ManagedComponent *object) {
   if (object != NULL) {
      object->setParent(NULL);

      object->_parent = this;
      _children.push_back(object);
   }   
}

void ManagedComponent::removeChild(ManagedComponent *object) {
   if (std::find(_children.begin(), _children.end(), object) != _children.end()) {
      object->_parent = NULL;
      _children.remove(object);
   }
}

ManagedComponent *ManagedComponent::getChild(scv::Component *object) {
   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if ((*iter)->getComponent() == object) {
         return (*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(object);
         if (managed != NULL) return managed;
      }
   }
   return NULL;
}

ManagedComponent * ManagedComponent::getChild(const std::string &name) {
   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if ((*iter)->getClassName() == name) {
         return (*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(name);
         if (managed != NULL) return managed;
      }
   }
   return NULL;
}

std::string ManagedComponent::getDeclarationCode(void) {
   std::string output;

   if (getCustomClass()) {   
      output += "class " + getClassName() + " : public scv::" + getDerivedTypeName() + " {\n";
      output += "public:\n";
      output += "   " + getClassName() + "(void);\n";
      output += "   virtual ~" + getClassName() + "(void);\n";
      output += "\n";
      output += "   ///////////////////////////////////////////////////////////\n";
      output += "   virtual void onMouseClick(const scv::MouseEvent &evt);\n";
      output += "   virtual void onMouseHold (const scv::MouseEvent &evt);\n";
      output += "   virtual void onMouseOver (const scv::MouseEvent &evt);\n";
      output += "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n";
      output += "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n";
      output += "\n";
      output += "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n";
      output += "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n";
      output += "\n";
      output += "   virtual void onSizeChange(void);\n";
      output += "   virtual void onPositionChange(void);\n";
      output += getCustomDeclarationCode();
      output += "   ///////////////////////////////////////////////////////////\n";
      output += "};\n";
   }

   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      output += (*iter)->getDeclarationCode();
   }

   return output;
}

std::string ManagedComponent::getImplementationCode(void) {
   std::string output;

   std::string customCallbacks;

   if (getCustomClass()) {
      output += "///////////////////////////////////////////////////////////\n";
      output += getClassName() + "::" + getClassName() + "(void) : " + getDefaultClassInitialization() + " {\n";
      output += "}\n";
      output += getClassName() + "::~" + getClassName() + "(void) {\n";
      output += "}\n";
      output += "\n";
      output += "void " + getClassName() + "::onMouseClick(const scv::MouseEvent &evt) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onMouseHold(const scv::MouseEvent &evt) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onMouseOver(const scv::MouseEvent &evt) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onMouseUp(const scv::MouseEvent &evt) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onMouseWheel(const scv::MouseEvent &evt) {\n";
      output += "}\n";
      output += "\n";
      output += "void " + getClassName() + "::onKeyPressed(const scv::KeyEvent &evt) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onKeyUp(const scv::KeyEvent &evt) {\n";
      output += "}\n";
      output += "\n";
      output += "void " + getClassName() + "::onSizeChange(void) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onPositionChange(void) {\n";
      output += "}\n";
      output += getCustomImplementationCode();
      output += "///////////////////////////////////////////////////////////\n";
      output += "\n";
   }
   
   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      output += (*iter)->getImplementationCode();
   }

   return output;
}

std::string ManagedComponent::getAllocationCode(void) {
   static const std::string s_defaultTab("   ");

   std::string output;

   if (getCustomClass()) {
      output += s_defaultTab + getClassName() + " *" + getPointerName() + " = new " + getClassName() + "();\n";
   } else {
      output += s_defaultTab + "scv::" + getDerivedTypeName() + " *" + getPointerName() + " = new " + getDefaultClassInitialization() + ";\n";
   }

   if (getParent() == NULL) {
      output += s_defaultTab + "_mainPanel->addComponent(" + getPointerName() + ");\n";
   }

   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      output += (*iter)->getAllocationCode();
      output += s_defaultTab + getPointerName() + "->addChild(" + (*iter)->getPointerName() + ");\n";
   }

   return output;
}

std::string ManagedComponent::getCustomDeclarationCode(void) {
   std::string output;

   if (getDerivedTypeName() == "ColorPicker") {
      output += "   virtual void onColorChange(void);\n";
   } else if (getDerivedTypeName() == "ProgressBar") {
      output += "   virtual void onValueChange(void);\n";
   } else if (getDerivedTypeName() == "Slider") {
      output += "   virtual void onValueChange(void);\n";
   } else if (getDerivedTypeName() == "Spinner") {
      output += "   virtual void onValueChange(void);\n";
   } else if (getDerivedTypeName() == "CheckBox") {
      output += "   virtual void onValueChange(void);\n";
   } else if (getDerivedTypeName() == "RadioButton") {
      output += "   virtual void onValueChange(void);\n";
   } else if (getDerivedTypeName() == "ToggleButton") {
      output += "   virtual void onValueChange(void);\n";
   } else if (getDerivedTypeName() == "TextField") {
      output += "   virtual void onStringChange(void);\n";
   } else if (getDerivedTypeName() == "TextBox") {
      output += "   virtual void onStringChange(void);\n";
   } else if (getDerivedTypeName() == "InternalFrame") {
      output += "   virtual void onOpen(void);\n";
      output += "   virtual void onClose(void);\n";
   } else if (getDerivedTypeName() == "TabbedPane") {
      output += "   virtual void onTabChange(void);\n";      
   } else if (getDerivedTypeName() == "ComboBox") {
      output += "   virtual void onSelectionChanged(std::string address, int id);\n";
   } else if (getDerivedTypeName() == "Canvas") {
      output += "   virtual void render(void);\n";
      output += "   virtual void update(void);\n";
   } else if (getDerivedTypeName() == "SystemTreeView") {
      output += "   virtual void onItemSelect(void);\n";
   } else if (getDerivedTypeName() == "Label") {
      output += "   virtual void onStringChange(void);\n";
   }

   return (output.empty()) ? output : "\n" + output;
}

std::string ManagedComponent::getCustomImplementationCode(void) {
   std::string output;

   if (getDerivedTypeName() == "ColorPicker") {
      output += "void " + getClassName() + "::onColorChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "ProgressBar") {
      output += "void " + getClassName() + "::onValueChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "Slider") {
      output += "void " + getClassName() + "::onValueChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "Spinner") {
      output += "void " + getClassName() + "::onValueChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "CheckBox") {
      output += "void " + getClassName() + "::onValueChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "RadioButton") {
      output += "void " + getClassName() + "::onValueChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "ToggleButton") {
      output += "void " + getClassName() + "::onValueChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "TextField") {
      output += "void " + getClassName() + "::onStringChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "TextBox") {
      output += "void " + getClassName() + "::onStringChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "InternalFrame") {
      output += "void " + getClassName() + "::onOpen(void) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::onClose(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "TabbedPane") {
      output += "void " + getClassName() + "::onTabChange(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "ComboBox") {
      output += "void " + getClassName() + "::onSelectionChanged(std::string address, int id) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "Canvas") {
      output += "void " + getClassName() + "::render(void) {\n";
      output += "}\n";
      output += "void " + getClassName() + "::update(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "SystemTreeView") {
      output += "void " + getClassName() + "::onItemSelect(void) {\n";
      output += "}\n";
   } else if (getDerivedTypeName() == "Label") {
      output += "void " + getClassName() + "::onStringChange(void) {\n";
      output += "}\n";
   }

   return (output.empty()) ? output : "\n" + output;
}

std::string ManagedComponent::getDefaultClassInitialization(void) {
   std::string initialization;

   if (getDerivedTypeName() == "Panel") {
      initialization += "scv::Panel(scv::Point(0, 0), scv::Point(0, 0))";
   } else if (getDerivedTypeName() == "ColorPicker") {
      initialization += "scv::ColorPicker(scv::Point(0, 0))";
   } else if (getDerivedTypeName() == "ProgressBar") {
      initialization += "scv::ProgressBar(scv::Point(0, 0),  0)";
   } else if (getDerivedTypeName() == "Slider") {
      scv::Slider *object = static_cast<scv::Slider *>(getComponent());
      initialization += "scv::Slider(scv::Point(0, 0), " + scv::toString(object->getMinValue()) + ".f , " + scv::toString(object->getMaxValue()) + ".f, " + scv::toString(object->getStartValue()) + ".f, " + scv::toString(object->getStepValue()) + ".f)";
   } else if (getDerivedTypeName() == "Spinner") {
      scv::Spinner *object = static_cast<scv::Spinner *>(getComponent());
      initialization += "scv::Spinner(scv::Point(0, 0), 0, " +  scv::toString(object->getMinValue()) + ".f, " + scv::toString(object->getMaxValue()) + ".f, " + scv::toString(object->getStartValue()) + ".f, " + scv::toString(object->getStepValue()) + ".f)";
   } else if (getDerivedTypeName() == "Button") {
      scv::Button *object = static_cast<scv::Button *>(getComponent());
      initialization += "scv::Button(scv::Point(0, 0), \"" + object->getString() + "\")";
   } else if (getDerivedTypeName() == "CheckBox") {
      scv::CheckBox *object = static_cast<scv::CheckBox *>(getComponent());
      initialization += "scv::CheckBox(scv::Point(0, 0), " + scv::toString(object->getState()) + ", \"" + object->getString() + "\")";
   } else if (getDerivedTypeName() == "RadioButton") {
      scv::RadioButton *object = static_cast<scv::RadioButton *>(getComponent());
      initialization += "scv::RadioButton(scv::Point(0, 0), " + scv::toString(object->getState()) + ", \"" + object->getString() + "\")";
   } else if (getDerivedTypeName() == "ToggleButton") {
      scv::ToggleButton *object = static_cast<scv::ToggleButton *>(getComponent());
      initialization += "scv::ToggleButton(scv::Point(0, 0)," + scv::toString(object->getState()) + ", \"" + object->getString() + "\")";
   } else if (getDerivedTypeName() == "TextField") {
      scv::TextField *object = static_cast<scv::TextField *>(getComponent());
      initialization += "scv::TextField(scv::Point(0, 0), " + scv::toString(object->getWidth()) + ", \"" + object->getString() + "\")";
   } else if (getDerivedTypeName() == "TextBox") {
      scv::TextBox *object = static_cast<scv::TextBox *>(getComponent());
      initialization += "scv::TextBox(scv::Point(0, 0), scv::Point(200, 200), \"" + object->getString() + "\")";
   } else if (getDerivedTypeName() == "Separator") {
      scv::Separator *object = static_cast<scv::Separator *>(getComponent());
      if (object->getAlign() == scv::Separator::HORIZONTAL) {
         initialization += "scv::Separator(scv::Point(0, 0), scv::Separator::HORIZONTAL, 100)";
      } else {
         initialization += "scv::Separator(scv::Point(0, 0), scv::Separator::VERTICAL, 100)";
      }      
   } else if (getDerivedTypeName() == "InternalFrame") {
      scv::InternalFrame *object = static_cast<scv::InternalFrame *>(getComponent());
      initialization += "scv::InternalFrame(" + scv::toString(object->getWidth()) + ", " + scv::toString(object->getHeight()) + ", \"" + object->getTitle() + "\")";
   } else if (getDerivedTypeName() == "MenuBar") {
      initialization += "scv::MenuBar(200)";
   } else if (getDerivedTypeName() == "TabbedPane") {
      initialization += "scv::TabbedPane(scv::Point(0, 0), scv::Point(200, 200))";
   } else if (getDerivedTypeName() == "ScrollComponent") {
      initialization += "scv::ScrollComponent(scv::Point(0, 0), scv::Point(200, 200))";
   } else if (getDerivedTypeName() == "Image") {
      scv::Image *object = static_cast<scv::Image *>(getComponent());
      initialization += "scv::Image(scv::Point(0, 0), \"" + object->getPath() + "\")";
   } else if (getDerivedTypeName() == "Table") {
      initialization += "scv::Table(scv::Point(0, 0))";
   } else if (getDerivedTypeName() == "ComboBox") {
      initialization += "scv::ComboBox(scv::Point(0,0), 200)";
   } else if (getDerivedTypeName() == "Canvas") {
      initialization += "scv::Canvas(scv::Point(0, 0), scv::Point(200, 200))";
   } else if (getDerivedTypeName() == "SystemTreeView") {
      initialization += "scv::SystemTreeView(scv::Point(0, 0), scv::Point(200, 200))";
   } else if (getDerivedTypeName() == "Label") {
      scv::Label *object = static_cast<scv::Label *>(getComponent());
      initialization += "scv::Label(scv::Point(0, 0), \"" + object->getString() + "\")";
   }

   return initialization;
}

