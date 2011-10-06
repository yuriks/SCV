#include "stdafx.h"
#include "Properties.h"

Properties::Properties(int width) : scv::Panel(scv::Point(0, 0), scv::Point(width, 0)) {
   _currComponent = NULL;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   _hGroup = _layout->createParallelGroup(scv::Group::CENTER);
   _vGroup = _layout->createSequentialGroup();
   _vGroup->addGap(5,5,5);
   
   _layout->setHorizontalGroup(_hGroup);
   _layout->setVerticalGroup(_vGroup);

   addChild("Relative Position", PropertieOption::EDITABLE_TEXTFIELD);
   
   addChild("Absolute Position", PropertieOption::EDITABLE_TEXTFIELD);

   addChild("Width", PropertieOption::EDITABLE_TEXTFIELD);
   addChild("Height", PropertieOption::EDITABLE_TEXTFIELD);

   addChild("Minimum Size", PropertieOption::EDITABLE_TEXTFIELD);
   addChild("Preferred Size", PropertieOption::EDITABLE_TEXTFIELD);
   addChild("Maximum Size", PropertieOption::EDITABLE_TEXTFIELD);

   addChild("Draggable", PropertieOption::EDITABLE_CHECKBOX);
   addChild("Resizable", PropertieOption::EDITABLE_CHECKBOX);
   addChild("Visible", PropertieOption::EDITABLE_CHECKBOX);

   addChild("Callbacks Status", PropertieOption::EDITABLE_CHECKBOX);

   addChild("Parent Scissor", PropertieOption::EDITABLE_TEXTFIELD);
   addChild("Scissor", PropertieOption::EDITABLE_TEXTFIELD);   
}

Properties::~Properties(void) {
   delete _layout;
}


void Properties::setComponent(scv::Component *component) {
   setValue("Relative Position", "Relative Position");
}

void Properties::addChild(std::string title, PropertieOption::Type type) {
   PropertieOption *option = new PropertieOption(this, title, type);
   scv::Component::addChild(option);

   _hGroup->addComponent(option);
   _vGroup->addComponent(option, 20, 20, 20);
   _vGroup->addGap(5,5,5);

   setHeight(_children.size() * 20 + (_children.size() + 1) * 5);
}

void Properties::setValue(const std::string &title, const std::string &str) {
   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      PropertieOption *option = static_cast<PropertieOption*>(*iter);
      if (option->getOption() == title) option->setValue(str);
   }
}

void Properties::setValue(const std::string &title, bool state) {
   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      PropertieOption *option = static_cast<PropertieOption*>(*iter);
      if (option->getOption() == title) option->setValue(state);
   }
}

void Properties::onValueChange(const std::string &title, const std::string &str) {
}

void Properties::onValueChange(const std::string &title, bool state) {
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

PanelProperties::PanelProperties(void) : Properties(200) {
}

PanelProperties::~PanelProperties(void) {
}

void PanelProperties::setComponent(scv::Component *component) {
   Properties::setComponent(component);
}

void PanelProperties::setValue(const std::string &title, const std::string &str) {
   Properties::setValue(title, str);
}

void PanelProperties::setValue(const std::string &title, bool state) {
   Properties::setValue(title, state);
}

void PanelProperties::onValueChange(const std::string &title, const std::string &str) {
   Properties::onValueChange(title, str);
}

void PanelProperties::onValueChange(const std::string &title, bool state) {
   Properties::onValueChange(title, state);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
