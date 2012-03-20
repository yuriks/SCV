#include <SCV/SCV.h>
#include "Properties.h"

#include "Application.h"

const std::string Properties::s_MaximumSize   = "Maximum Size";
const std::string Properties::s_PreferredSize = "Preferred Size";
const std::string Properties::s_MinimumSize   = "Minimum Size";
const std::string Properties::s_CustomClass   = "Generate Custom Class";


Properties::Properties(void) : scv::Panel(scv::Point(0, 0), scv::Point(static_cast<Application *>(scv::Kernel::getInstance())->s_defaultRightPanelWidth, 0)) {
   setVisible(false);

   _currComponent = NULL;

   _layout = new scv::GroupLayout(this);
   setLayout(_layout);

   scv::Separator *separator = new scv::Separator(scv::Point(), scv::Separator::HORIZONTAL, getWidth());

   _hLeftGroup = _layout->createParallelGroup();
   _hRightGroup = _layout->createParallelGroup();
   _hGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true)
      ->addGap(0)->addGroup(_hLeftGroup)->addGroup(_hRightGroup)->addGap(0);
   _vGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true)->addGap(0)->setAutoGapsSize(5);
   
   _layout->setHorizontalGroup(_hGroup);
   _layout->setVerticalGroup(_vGroup);

   addChild(s_CustomClass, PropertieOption::EDITABLE_CHECKBOX);
   /**/
   Panel::addChild(separator);
   _vGroup->addComponent(separator);   
   /**/
   addChild(s_MinimumSize, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_PreferredSize, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
   addChild(s_MaximumSize, PropertieOption::EDITABLE_NUMERAL_TEXTFIELD);
}

Properties::~Properties(void) {
   delete _layout;
}


void Properties::setComponent(scv::Component *component) {
   if (component == NULL) return;
   
   _currComponent = component;
   _currComponent->setResizable(false);
   _currComponent->setCallbacksStatus(false);

   setValue(s_MinimumSize, scv::toString(_currComponent->getMinimumSize()));
   setValue(s_PreferredSize, scv::toString(_currComponent->getPreferredSize()));
   setValue(s_MaximumSize, scv::toString(_currComponent->getMaximumSize()));
   /**/
   setValue(s_CustomClass, CodeGenerator::getInstance()->getManagedComponent(component)->getCustomClass());
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

   if (title == s_MinimumSize) {
      if (scv::Point(str) > _currComponent->getPreferredSize()) {
         _currComponent->setPreferredSize(scv::Point(str));
         _currComponent->setSize(scv::Point(str).x, scv::Point(str).y);
      }
      _currComponent->setMinimumSize(scv::Point(str));
   } else if (title == s_PreferredSize) {
      _currComponent->setPreferredSize(scv::Point(str));
      _currComponent->setSize(scv::Point(str).x, scv::Point(str).y);
   } else if (title == s_MaximumSize) {
      _currComponent->setMaximumSize(scv::Point(str));
   }

   setComponent(_currComponent);
}

void Properties::onValueChange(const std::string &title, bool state) {
   if (_currComponent == NULL) return;

   if (title == s_CustomClass) {
      CodeGenerator::getInstance()->getManagedComponent(_currComponent)->setCustomClass(state);
   }
}
