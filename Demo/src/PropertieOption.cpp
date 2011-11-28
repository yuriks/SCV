#include "stdafx.h"
#include "PropertieOption.h"

#include "Properties.h"

PropertieOption::PropertieOption(Properties *host, std::string title, Type type) {
   _host = host;
   _type = type;
   _target = NULL;

   _label = new scv::Label(scv::Point(0,0), title);
   static_cast<scv::Panel *>(host)->addChild(_label);   

   switch (_type) {
   case EDITABLE_TEXTFIELD:
      _target = new PropertieTextField(this, true);
      break;
   case TEXTFIELD:
      _target = new PropertieTextField(this, false);
      break;      
   case EDITABLE_CHECKBOX:
      _target = new PropertieCheckBox(this);
      break;
   }   
   static_cast<scv::Panel*>(host)->addChild(_target);
}

PropertieOption::~PropertieOption(void) {
}

void PropertieOption::setValue(const std::string &str) {
   if (_type == EDITABLE_TEXTFIELD || _type == TEXTFIELD) {
      static_cast<scv::TextField *>(_target)->setString(str);
   }
}

void PropertieOption::setValue(bool state) {
   if (_type == EDITABLE_CHECKBOX) {
      static_cast<scv::CheckBox *>(_target)->setState(state);
   }
}

void PropertieOption::onValueChange(const std::string &str) {
   _host->onValueChange(_label->getString(), str);
}

void PropertieOption::onValueChange(bool state) {
   _host->onValueChange(_label->getString(), state);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

PropertieOption::PropertieCheckBox::PropertieCheckBox(PropertieOption *host) : scv::CheckBox(scv::Point(0, 0), true, "") {
   _host = host;
}

PropertieOption::PropertieCheckBox::~PropertieCheckBox(void) {
}

void PropertieOption::PropertieCheckBox::onValueChange(void) {
   _host->onValueChange(getState());
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

PropertieOption::PropertieTextField::PropertieTextField(PropertieOption *host, bool editable) : scv::TextField(scv::Point(0,0), 100, "") {
   _host = host;

   scv::TextFilter filter;
   filter.denyAll();
   filter.allowNumbers();
   filter.allowThese(",");

   setFilter(filter);

   setEditable(editable);
}

PropertieOption::PropertieTextField::~PropertieTextField(void) {
}

void PropertieOption::PropertieTextField::onKeyPressed(const scv::KeyEvent &evt) {
   if (evt.getKeyString() == "Enter") {
      _host->onValueChange(getString());
   }
}
