#include "stdafx.h"
#include "PropertieOption.h"

#include "Properties.h"

PropertieOption::PropertieOption(Properties *host, std::string title, Type type) : scv::Panel(scv::Point(0,0), scv::Point(100, 50)) {
   _host = host;
   _type = type;

   addChild(new scv::Label(scv::Point(0,0), title));

   switch (_type) {
   case EDITABLE_TEXTFIELD:
      addChild(new PropertieTextField(this));
      break;
   case TEXTFIELD:
      addChild(new PropertieTextField(this));
      break;
   case EDITABLE_CHECKBOX:
      addChild(new PropertieCheckBox(this));
      break;
   }

}

PropertieOption::~PropertieOption(void) {
}

void PropertieOption::onValueChange(const std::string &str) {
   _host->onValueChange(static_cast<scv::Label*>(*_children.begin())->getString(), str);
}

void PropertieOption::onValueChange(bool state) {
   _host->onValueChange(static_cast<scv::Label*>(*_children.begin())->getString(), state);
}

PropertieOption::PropertieCheckBox::PropertieCheckBox(PropertieOption *host) : scv::CheckBox(scv::Point(0, 0), true, "") {
   _host = host;
}

PropertieOption::PropertieCheckBox::~PropertieCheckBox(void) {
}

void PropertieOption::PropertieCheckBox::onValueChange(void) {
   _host->onValueChange(getState());
}

PropertieOption::PropertieTextField::PropertieTextField(PropertieOption *host) : scv::TextField(scv::Point(0,0), 100, "") {
   _host = host;
}

PropertieOption::PropertieTextField::~PropertieTextField(void) {
}

void PropertieOption::PropertieTextField::onKeyUp(const scv::KeyEvent &evt) {
   _host->onValueChange(getString());
}
