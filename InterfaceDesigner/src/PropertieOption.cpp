#include <SCV/SCV.h>
#include "PropertieOption.h"

#include "Properties.h"

PropertieOption::PropertieOption(Properties *host, std::string title, Type type) {
   _host = host;
   _type = type;
   _target = NULL;

   _label = new scv::Label(scv::Point(0,0), title);
   host->addChild(_label);   

   switch (_type) {
   case EDITABLE_NUMERAL_TEXTFIELD:
      _target = new PropertieTextField(this, true, true);
      break;
   case EDITABLE_TEXTFIELD:
      _target = new PropertieTextField(this, true, false);
      break;
   case NUMERAL_TEXTFIELD:
      _target = new PropertieTextField(this, false, true);
      break;
   case TEXTFIELD:
      _target = new PropertieTextField(this, false, false);
      break;
   case EDITABLE_CHECKBOX:
      _target = new PropertieCheckBox(this);
      break;
   }   
   host->addChild(_target);
}

PropertieOption::~PropertieOption(void) {
}

void PropertieOption::setValue(const std::string &str) {
   if (_type == EDITABLE_NUMERAL_TEXTFIELD || _type == EDITABLE_TEXTFIELD) {
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

PropertieOption::PropertieTextField::PropertieTextField(PropertieOption *host, bool editable, bool allowOnlyNumbers) : scv::TextField(scv::Point(0,0), 100, "") {
   _host = host;

   scv::TextFilter filter;
   if (allowOnlyNumbers) {
      filter.allowNumbers();
      filter.allowThese(",");
   } else {
      filter.allowAll();
   }
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
