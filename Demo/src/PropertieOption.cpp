#include "stdafx.h"
#include "PropertieOption.h"

#include "Properties.h"

PropertieOption::PropertieOption(Properties *host, std::string title, Type type) : scv::Panel(scv::Point(0,0), scv::Point(100, 50)) {
   _host = host;
   _type = type;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   scv::Label *label = new scv::Label(scv::Point(0,0), title);
   addChild(label);

   switch (_type) {
   case EDITABLE_TEXTFIELD:
      addChild(new PropertieTextField(this, true));
      break;
   case TEXTFIELD:
      addChild(new PropertieTextField(this, false));
      break;
   case EDITABLE_CHECKBOX:
      addChild(new PropertieCheckBox(this));
      break;
   }

   _layout->setHorizontalGroup(_layout->createSequentialGroup()
      ->addComponent(label)
      ->addComponent(*++_children.begin())
   );
   _layout->setVerticalGroup(_layout->createParallelGroup()
      ->addComponent(label)
      ->addComponent(*++_children.begin())
   );
}

PropertieOption::~PropertieOption(void) {
   delete _layout;
}

const std::string & PropertieOption::getOption(void) const {
   return static_cast<scv::Label*>(*_children.begin())->getString();
}

void PropertieOption::setValue(const std::string &str) {
   scv::TextField *textField = static_cast<scv::TextField*>(*((_children.begin()++)++));
   textField->setString(str);
}

void PropertieOption::setValue(bool state) {
   scv::CheckBox *checkBox = static_cast<scv::CheckBox*>(*((_children.begin()++)++));
   checkBox->setState(state);
}

void PropertieOption::onValueChange(const std::string &str) {
   _host->onValueChange(static_cast<scv::Label*>(*_children.begin())->getString(), str);
}

void PropertieOption::onValueChange(bool state) {
   _host->onValueChange(static_cast<scv::Label*>(*_children.begin())->getString(), state);
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
