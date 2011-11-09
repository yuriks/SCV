#include "stdafx.h"
#include "SequentialGroupPanel.h"

SequetialGroupPanel::SequetialGroupPanel(GroupType type) : GroupPanel(type) {
   switch (type) {
   case HORIZONTAL:
      _verticalGroup = _layout->createParallelGroup();
      _horizontalGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true);
      break;
   case VERTICAL:
      _verticalGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true);
      _horizontalGroup = _layout->createParallelGroup();
      break;
   }  

   _layout->setVerticalGroup(_verticalGroup);
   _layout->setHorizontalGroup(_horizontalGroup);
}

SequetialGroupPanel::~SequetialGroupPanel(void) {

}

void SequetialGroupPanel::applyColor(void) {
   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.7f, 0.7f, 0.3f, 0.3f));
}

std::string SequetialGroupPanel::getCode(void) {
   std::string code = "->addGroup(createSequentialGroup()\n";

   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if (dynamic_cast<GroupPanel*>(*iter)) {
         code += static_cast<GroupPanel*>(*iter)->getCode();
      } else {
         code += "->addComponent(code)\n";
      }
   }
   code += ")";
   return code;
}
