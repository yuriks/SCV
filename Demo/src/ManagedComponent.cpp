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
      output += "};\n\n";
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
      output += getClassName() + "::" + getClassName() + "(void) : " + getDefaultClassInitialization() + "{\n";
      output += "}\n";
      output += getClassName() + "::~" + getClassName() + "(void) {\n";
      output += "}\n\n";
   }
   
   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      output += (*iter)->getImplementationCode();
   }

   return output;
}

std::string ManagedComponent::getAllocationCode(void) {
   std::string output;

   if (getCustomClass()) {
      output += getClassName() + " *" + getPointerName() + " = new " + getClassName() + "();";
   } else {
      output += "scv::" + getDerivedTypeName() + " *" + getPointerName() + " = new " + getDefaultClassInitialization() + ";";
   }

   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      output += (*iter)->getImplementationCode();
      output += getPointerName() + "->addChild(" + (*iter)->getPointerName() + ");";
   }

   return output;
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

