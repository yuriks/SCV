#include "stdafx.h"
#include "SpecializedProperties.h"
#include "CodeGenerator.h"

const std::string CountersProperties::s_stepValue  = "Step Value";
const std::string CountersProperties::s_startValue = "Start Value";
const std::string CountersProperties::s_maxVlaue   = "Maximum Value";
const std::string CountersProperties::s_minValue   = "Minimum Value";

// scv::Slider, scv::Spinner
CountersProperties::CountersProperties(void) : Properties () {
   addChild(s_minValue, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_maxVlaue, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_startValue, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_stepValue, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
}

CountersProperties::~CountersProperties(void) {
}

void CountersProperties::setComponent(scv::Component *component) {
   Properties::setComponent(component);
   if (_currComponent == NULL) return;

   if (dynamic_cast<scv::Slider *>(_currComponent)) {
      scv::Slider *object = static_cast<scv::Slider *>(_currComponent);
      setValue(s_minValue, scv::toString(object->getMinValue()));
      setValue(s_maxVlaue, scv::toString(object->getMaxValue()));
      setValue(s_startValue, scv::toString(object->getStartValue()));
      setValue(s_stepValue, scv::toString(object->getStepValue()));
   } else if (dynamic_cast<scv::Spinner *>(_currComponent)) {
      scv::Spinner *object = static_cast<scv::Spinner *>(_currComponent);
      setValue(s_minValue, scv::toString(object->getMinValue()));
      setValue(s_maxVlaue, scv::toString(object->getMaxValue()));
      setValue(s_startValue, scv::toString(object->getStartValue()));
      setValue(s_stepValue, scv::toString(object->getStepValue()));
   }   
}

void CountersProperties::onValueChange(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;

   if (dynamic_cast<scv::Slider *>(_currComponent)) {
      scv::Slider *object = static_cast<scv::Slider *>(_currComponent);
      if (title == s_minValue) {
         object->setMinValue(scv::fromString<double>(str));
      } else if (title == s_maxVlaue) {
         object->setMaxValue(scv::fromString<double>(str));
      } else if (title == s_startValue) {
         /**/
      } else if (title == s_stepValue) {
         object->setStepValue(scv::fromString<double>(str));
      }
   } else if (dynamic_cast<scv::Spinner *>(_currComponent)) {
      scv::Spinner *object = static_cast<scv::Spinner *>(_currComponent);
      if (title == s_minValue) {
         object->setMinValue(scv::fromString<double>(str));
      } else if (title == s_maxVlaue) {
         object->setMaxValue(scv::fromString<double>(str));
      } else if (title == s_startValue) {
         /**/
      } else if (title == s_stepValue) {
         object->setStepValue(scv::fromString<double>(str));
      }
   }
   Properties::onValueChange(title, str);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

const std::string StringsProperties::s_string = "Label";

// scv::Button, scv::Label, scv::TextField, scv::TextBox
StringsProperties::StringsProperties(void) : Properties () {
   addChild(s_string, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
}

StringsProperties::~StringsProperties(void) {
}


void StringsProperties::setComponent(scv::Component *component) {
   Properties::setComponent(component);
   if (_currComponent == NULL) return;

   if (dynamic_cast<scv::Button *>(_currComponent)) {
      scv::Button *object = static_cast<scv::Button *>(_currComponent);
      setValue(s_string, object->getString());
   } else if (dynamic_cast<scv::Label *>(_currComponent)) {
      scv::Label *object = static_cast<scv::Label *>(_currComponent);
      setValue(s_string, object->getString());
   } else if (dynamic_cast<scv::TextField *>(_currComponent)) {
      scv::TextField *object = static_cast<scv::TextField *>(_currComponent);
      setValue(s_string, object->getString());
   } else if (dynamic_cast<scv::TextBox *>(_currComponent)) {
      scv::TextBox *object = static_cast<scv::TextBox *>(_currComponent);
      setValue(s_string, object->getString());
   }   
}

/*Switch the value of initial string of a component */
void StringsProperties::onValueChange(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;
   
   if (title == s_string) {
      /*Switch Label of Button*/
      if (dynamic_cast<scv::Button *>(_currComponent)) {
         scv::Button *object = static_cast<scv::Button *>(_currComponent);
         object->setString(str);
         CodeGenerator::getInstance()->modifyNameManagedComponent(object, str);
      /*Switch Label*/
      } else if (dynamic_cast<scv::Label *>(_currComponent)) {
         scv::Label *object = static_cast<scv::Label *>(_currComponent);
         object->setString(str);
      /*Switch Text*/
      } else if (dynamic_cast<scv::TextField *>(_currComponent)) {
         scv::TextField *object = static_cast<scv::TextField *>(_currComponent);
         object->setString(str);
      /*Switch Text*/
      } else if (dynamic_cast<scv::TextBox *>(_currComponent)) {
         scv::TextBox *object = static_cast<scv::TextBox *>(_currComponent);
         object->setString(str);
      }
   }
   Properties::onValueChange(title, str);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

const std::string StatesProperties::s_string = "Label";
const std::string StatesProperties::s_state = "State";

// scv::CheckBox, scv::RadioButton, scv::ToggleButton
StatesProperties::StatesProperties(void) : Properties () {
   addChild(s_state, PropertieOption::EDITABLE_CHECKBOX);
   addChild(s_string, PropertieOption::EDITABLE_TEXTFIELD);
}

StatesProperties::~StatesProperties(void) {
}

void StatesProperties::setComponent(scv::Component *component) {
   Properties::setComponent(component);
   if (_currComponent == NULL) return;

   if (dynamic_cast<scv::CheckBox *>(_currComponent)) {
      scv::CheckBox *object = static_cast<scv::CheckBox *>(_currComponent);
      setValue(s_state, object->getState());
      setValue(s_string, object->getString());
   } else if (dynamic_cast<scv::RadioButton *>(_currComponent)) {
      scv::RadioButton *object = static_cast<scv::RadioButton *>(_currComponent);
      setValue(s_state, object->getState());
      setValue(s_string, object->getString());
   } else if (dynamic_cast<scv::ToggleButton *>(_currComponent)) {
      scv::ToggleButton *object = static_cast<scv::ToggleButton *>(_currComponent);
      setValue(s_state, object->getState());
      setValue(s_string, object->getString());
   }   
}

void StatesProperties::onValueChange(const std::string &title, const std::string &str) {
   Properties::onValueChange(title, str);
   if (_currComponent == NULL) return;

   if (title == s_string) {
      if (dynamic_cast<scv::CheckBox *>(_currComponent)) {
         scv::CheckBox *object = static_cast<scv::CheckBox *>(_currComponent);
         object->setString(str);
      } else if (dynamic_cast<scv::RadioButton *>(_currComponent)) {
         scv::RadioButton *object = static_cast<scv::RadioButton *>(_currComponent);
         object->setString(str);
      } else if (dynamic_cast<scv::ToggleButton *>(_currComponent)) {
         scv::ToggleButton *object = static_cast<scv::ToggleButton *>(_currComponent);
         object->setString(str);
      }
   }   
}

void StatesProperties::onValueChange(const std::string &title, bool state) {
   if (_currComponent == NULL) return;

   if (title == s_state) {
      if (dynamic_cast<scv::CheckBox *>(_currComponent)) {
         scv::CheckBox *object = static_cast<scv::CheckBox *>(_currComponent);
         object->setState(state);
      } else if (dynamic_cast<scv::RadioButton *>(_currComponent)) {
         scv::RadioButton *object = static_cast<scv::RadioButton *>(_currComponent);
         object->setState(state);
      } else if (dynamic_cast<scv::ToggleButton *>(_currComponent)) {
         scv::ToggleButton *object = static_cast<scv::ToggleButton *>(_currComponent);
         object->setState(state);
      }
   }
   Properties::onValueChange(title, state);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

const std::string InternalFrameProperties::s_title  = "Title";
const std::string InternalFrameProperties::s_height = "Height";
const std::string InternalFrameProperties::s_width  = "Width";

InternalFrameProperties::InternalFrameProperties(void) : Properties () {
   addChild(s_width, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_height, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_title, PropertieOption::EDITABLE_TEXTFIELD);
}

InternalFrameProperties::~InternalFrameProperties(void) {
}

void InternalFrameProperties::setComponent(scv::Component *component) {
   Properties::setComponent(component);
   if (_currComponent == NULL) return;

   scv::InternalFrame *object = static_cast<scv::InternalFrame *>(_currComponent);
   setValue(s_title, object->getTitle());
   setValue(s_height, scv::toString(object->getHeight()));
   setValue(s_width, scv::toString(object->getWidth()));
}

void InternalFrameProperties::onValueChange(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;

   scv::InternalFrame *object = static_cast<scv::InternalFrame *>(_currComponent);
   if (title == s_title) {
      object->setTitle(str);
   } else if (title == s_height) {
      object->setHeight(scv::fromString<int>(str));
   } else if (title == s_width) {
      object->setWidth(scv::fromString<int>(str));
   }

   Properties::onValueChange(title, str);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

const std::string ImageProperties::s_path = "Path";

ImageProperties::ImageProperties(void) : Properties () {
   addChild(s_path, PropertieOption::EDITABLE_TEXTFIELD);
}

ImageProperties::~ImageProperties(void) {
}

void ImageProperties::setComponent(scv::Component *component) {
   Properties::setComponent(component);
   if (_currComponent == NULL) return;

   scv::Image *object = static_cast<scv::Image *>(_currComponent);
   setValue(s_path, object->getPath());
}

void ImageProperties::onValueChange(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;

   scv::Image *object = static_cast<scv::Image *>(_currComponent);
   object->loadImage(str);

   Properties::onValueChange(title, str);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

const std::string FrameProperties::s_title  = "Title";
const std::string FrameProperties::s_height = "Height";
const std::string FrameProperties::s_width  = "Width";

FrameProperties::FrameProperties(void) : Properties() {
   removeAllChild();
   delete _layout;

   setVisible(false);

   _currComponent = NULL;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   _hLeftGroup = _layout->createParallelGroup();
   _hRightGroup = _layout->createParallelGroup();
   _hGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true)
      ->addGap(0)->addGroup(_hLeftGroup)->addGroup(_hRightGroup)->addGap(0);
   _vGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true)->addGap(0)->setAutoGapsSize(5);

   _layout->setHorizontalGroup(_hGroup);
   _layout->setVerticalGroup(_vGroup);

   addChild(s_width, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_height, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_title, PropertieOption::EDITABLE_TEXTFIELD);
}

FrameProperties::~FrameProperties(void) {
}

void FrameProperties::setComponent(scv::Component *component) {
   if (component == NULL) return;

   _currComponent = component;
   _currComponent->setResizable(false);
   _currComponent->setCallbacksStatus(false);

   scv::InternalFrame *object = static_cast<scv::InternalFrame *>(_currComponent);
   setValue(s_title, object->getTitle());
   setValue(s_height, scv::toString(object->getHeight()));
   setValue(s_width, scv::toString(object->getWidth()));
}

void FrameProperties::onValueChange(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;

   scv::InternalFrame *object = static_cast<scv::InternalFrame *>(_currComponent);
   if (title == s_title) {
      object->setTitle(str);
   } else if (title == s_height) {
      object->setHeight(scv::fromString<int>(str));
   } else if (title == s_width) {
      object->setWidth(scv::fromString<int>(str));
   }
}
