#include "stdafx.h"
#include "ParallelGroupPanel.h"

ParallelGroupPanel::ParallelGroupPanel(GroupType type) : GroupPanel(type) {
   switch (type) {
   case HORIZONTAL:
      _verticalGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true);
      _horizontalGroup = _layout->createParallelGroup();
      break;
   case VERTICAL:
      _verticalGroup = _layout->createParallelGroup();
      _horizontalGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true);
      break;
   }

   _layout->setVerticalGroup(_layout->createSequentialGroup()->addGap(15)->addGroup(_verticalGroup)->addGap(15));
   _layout->setHorizontalGroup(_layout->createSequentialGroup()->addGap(15)->addGroup(_horizontalGroup)->addGap(15));
}

ParallelGroupPanel::~ParallelGroupPanel(void) {

}

void ParallelGroupPanel::display(void) {
   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(1.0f, 0.7f, 0.7f, 1.0f));
   GroupPanel::display();
   scv::Scissor::getInstance()->pushScissor(getScissor());
   scv::StaticLabel::display(getAbsolutePosition() + 2, "ParallelGroupPanel");
   scv::Scissor::getInstance()->popScissor();
}

std::string ParallelGroupPanel::getCode(const std::string &tab) {
   std::string currTab = s_defaultTab + tab;
   std::string code = currTab + "->addGroup(scv::GroupLayout::createParallelGroup()\n";

   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if (dynamic_cast<GroupPanel*>(*iter)) {
         code += static_cast<GroupPanel*>(*iter)->getCode(currTab);
      } else {
         code += currTab + s_defaultTab + "->addComponent(code)\n";
      }
   }
   code += currTab + ")\n";
   return code;
}
