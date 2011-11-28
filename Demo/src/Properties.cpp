#include "stdafx.h"
#include "Properties.h"

#include "Application.h"

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

Properties::Properties(void) : scv::Panel(scv::Point(0, 0), scv::Point(static_cast<Application *>(scv::Kernel::getInstance())->s_defaultRightPanelWidth, 0)) {
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

   addChild(s_MinimumSize, PropertieOption::EDITABLE_TEXTFIELD);
   addChild(s_PreferredSize, PropertieOption::EDITABLE_TEXTFIELD);
   addChild(s_MaximumSize, PropertieOption::EDITABLE_TEXTFIELD);

   addChild(s_Resizable, PropertieOption::EDITABLE_CHECKBOX);
   addChild(s_Visible, PropertieOption::EDITABLE_CHECKBOX);

   addChild(s_CallbacksStatus, PropertieOption::EDITABLE_CHECKBOX);
}

Properties::~Properties(void) {
   delete _layout;
}


void Properties::setComponent(scv::Component *component) {   
   if (component == NULL) return;
   
   _currComponent = component;
   _currComponent->setResizable(true);

   if (_currComponent->getSize() > _currComponent->getMinimumSize()) {
      setValue(s_PreferredSize, scv::toString(_currComponent->getSize()));
      setValue(s_MinimumSize, scv::toString(_currComponent->getSize()));      
   } else {
      setValue(s_MinimumSize, scv::toString(_currComponent->getMinimumSize()));
      setValue(s_PreferredSize, scv::toString(_currComponent->getPreferredSize()));
   }
   setValue(s_MaximumSize, scv::toString(_currComponent->getMaximumSize()));

   setValue(s_Resizable, _currComponent->isResizable());
   setValue(s_Visible, _currComponent->isVisible());

   setValue(s_CallbacksStatus, _currComponent->getCallbacksStatus());
}

void Properties::addChild(std::string title, PropertieOption::Type type) {
   PropertieOption *option = new PropertieOption(this, title, type);
   _propertieList.push_back(option);

   _hLeftGroup->addComponent(option->getLabel());
   _hRightGroup->addComponent(option->getTarget());
      
   _vGroup->addGroup(_layout->createParallelGroup(scv::Spring::LEADING, false)
      ->addComponent(option->getLabel())
      ->addComponent(option->getTarget())
   );
}

void Properties::setValue(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;

   for (PropertieList::iterator iter = _propertieList.begin(); iter != _propertieList.end(); ++iter) {
      if ((*iter)->getOption() == title) {
         (*iter)->setValue(str);
         break;
      }
   }
}

void Properties::setValue(const std::string &title, bool state) {   
   if (_currComponent == NULL) return;

   for (PropertieList::iterator iter = _propertieList.begin(); iter != _propertieList.end(); ++iter) {
      if ((*iter)->getOption() == title) {
         (*iter)->setValue(state);
         break;
      }
   }
}

void Properties::onValueChange(const std::string &title, const std::string &str) {
   if (_currComponent == NULL) return;

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
   if (_currComponent == NULL) return;

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
