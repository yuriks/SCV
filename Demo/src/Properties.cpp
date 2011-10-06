#include "stdafx.h"
#include "Properties.h"

Properties::Properties(int width) : scv::Panel(scv::Point(0, 0), scv::Point(width, 0)) {
   _currComponent = NULL;

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
}

void Properties::onValueChange(const std::string &title, const std::string &str) {

}

void Properties::onValueChange(const std::string &title, bool state) {

}

void Properties::addChild(std::string title, PropertieOption::Type type) {
   scv::Component::addChild(new PropertieOption(this, title, type));
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

PanelProperties::PanelProperties(void) : Properties(200) {

}

PanelProperties::~PanelProperties(void) {
}

void PanelProperties::setComponent(scv::Component *component) {
   
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
