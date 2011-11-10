#include "stdafx.h"
#include "ParallelGroupPanel.h"

ParallelGroupPanel::ParallelGroupPanel(GroupType type) : GroupPanel(type) {
   switch (type) {
   case HORIZONTAL:
      _verticalGroup = _layout->createSequentialGroup()->setAutoCreateGaps(true)->addGap(15);
      _horizontalGroup = _layout->createParallelGroup();
      break;
   case VERTICAL:
      _verticalGroup = _layout->createParallelGroup();
      _horizontalGroup = _layout->createSequentialGroup()->addGap(15);
      break;
   }

   _layout->setVerticalGroup(_verticalGroup);
   _layout->setHorizontalGroup(_horizontalGroup);  
   
}

ParallelGroupPanel::~ParallelGroupPanel(void) {

}

void ParallelGroupPanel::display(void) {
   GroupPanel::display();
   scv::Scissor::getInstance()->pushScissor(getScissor());
   scv::StaticLabel::display(getAbsolutePosition(), "ParallelGroupPanel");
   scv::Scissor::getInstance()->popScissor();
}

void ParallelGroupPanel::applyColor(void) {
   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.7f, 1.0f, 0.7f, 0.3f));
}

std::string ParallelGroupPanel::getCode(void) {
   std::string code = "->addGroup(createParallelGroup\n";

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
