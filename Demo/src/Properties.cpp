#include "stdafx.h"
#include "Properties.h"

const std::string Properties::s_Scissor = "Scissor";
const std::string Properties::s_ParentScissor = "Parent Scissor";
const std::string Properties::s_CallbacksStatus = "Callbacks Status";
const std::string Properties::s_Visible = "Visible";
const std::string Properties::s_Resizable = "Resizable";
const std::string Properties::s_Draggable = "Draggable";
const std::string Properties::s_MaximumSize = "Maximum Size";
const std::string Properties::s_PreferredSize = "Preferred Size";
const std::string Properties::s_MinimumSize = "Minimum Size";
const std::string Properties::s_Height = "Height";
const std::string Properties::s_Width = "Width";
const std::string Properties::s_AbsolutePosition = "Absolute Position";
const std::string Properties::s_RelativePosition = "Relative Position";

Properties::Properties(int width) : scv::Panel(scv::Point(0, 0), scv::Point(width, 0)) {
   _currComponent = NULL;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   _hGroup = _layout->createParallelGroup(scv::Group::CENTER);
   _vGroup = _layout->createSequentialGroup();
   _vGroup->addGap(5,5,5);
   
   _layout->setHorizontalGroup(_hGroup);
   _layout->setVerticalGroup(_vGroup);

   addChild(s_RelativePosition, PropertieOption::EDITABLE_TEXTFIELD);
   
   addChild(s_AbsolutePosition, PropertieOption::EDITABLE_TEXTFIELD);

   addChild(s_Width, PropertieOption::EDITABLE_TEXTFIELD);
   addChild(s_Height, PropertieOption::EDITABLE_TEXTFIELD);

   addChild(s_MinimumSize, PropertieOption::EDITABLE_TEXTFIELD);
   addChild(s_PreferredSize, PropertieOption::EDITABLE_TEXTFIELD);
   addChild(s_MaximumSize, PropertieOption::EDITABLE_TEXTFIELD);

   addChild(s_Draggable, PropertieOption::EDITABLE_CHECKBOX);
   addChild(s_Resizable, PropertieOption::EDITABLE_CHECKBOX);
   addChild(s_Visible, PropertieOption::EDITABLE_CHECKBOX);

   addChild(s_CallbacksStatus, PropertieOption::EDITABLE_CHECKBOX);

   addChild(s_ParentScissor, PropertieOption::TEXTFIELD);
   addChild(s_Scissor, PropertieOption::TEXTFIELD);
}

Properties::~Properties(void) {
   delete _layout;
}


void Properties::setComponent(scv::Component *component) {   
   if (component == NULL) return;
   
   _currComponent = component;

   setValue(s_RelativePosition, scv::toString(_currComponent->getRelativePosition()));
   setValue(s_AbsolutePosition, scv::toString(_currComponent->getAbsolutePosition()));

   setValue(s_Width, scv::toString(_currComponent->getWidth()));
   setValue(s_Height, scv::toString(_currComponent->getHeight()));

   setValue(s_MinimumSize, scv::toString(_currComponent->getMinimumSize()));
   setValue(s_PreferredSize, scv::toString(_currComponent->getPreferredSize()));
   setValue(s_MaximumSize, scv::toString(_currComponent->getMaximumSize()));

   setValue(s_Draggable, _currComponent->isDraggable());
   setValue(s_Resizable, _currComponent->isResizable());
   setValue(s_Visible, _currComponent->isVisible());

   setValue(s_CallbacksStatus, _currComponent->getCallbacksStatus());

   setValue(s_ParentScissor, scv::toString(_currComponent->getParentScissor()));
   setValue(s_Scissor, scv::toString(_currComponent->getScissor()));
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
   if (title == s_RelativePosition) {
      _currComponent->setRelativePosition(scv::Point(str));
   } else if (title == s_AbsolutePosition) {
      _currComponent->setAbsolutePosition(scv::Point(str));

   } else if (title == s_Width) {
      _currComponent->setWidth(scv::fromString<int>(str));
   } else if (title == s_Height) {
      _currComponent->setHeight(scv::fromString<int>(str));

   } else if (title == s_MinimumSize) {
      _currComponent->setMinimumSize(scv::Point(str));
   } else if (title == s_PreferredSize) {
      _currComponent->setPreferredSize(scv::Point(str));
   } else if (title == s_MaximumSize) {
      _currComponent->setMaximumSize(scv::Point(str));
   }

   setComponent(_currComponent);
}

void Properties::onValueChange(const std::string &title, bool state) {
   if (title == s_Draggable) {
      _currComponent->setDraggable(state);
   } else if (title == s_Resizable) {
      _currComponent->setResizable(state);
   } else if (title == s_Visible) {
      _currComponent->setVisible(state);
   } else if (title == s_CallbacksStatus) {
      _currComponent->setCallbacksStatus(state);
   }
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
