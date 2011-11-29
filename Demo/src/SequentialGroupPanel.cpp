#include "stdafx.h"
#include "SequentialGroupPanel.h"

#include "CodeGenerator.h"

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

   _layout->setVerticalGroup(_layout->createSequentialGroup()->addGap(15)->addGroup(_verticalGroup)->addGap(15));
   _layout->setHorizontalGroup(_layout->createSequentialGroup()->addGap(15)->addGroup(_horizontalGroup)->addGap(15));
}

SequetialGroupPanel::~SequetialGroupPanel(void) {

}

void SequetialGroupPanel::display(void) {
   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.7f, 1.0f, 0.7f, 1.0f));
   GroupPanel::display();
   scv::Scissor::getInstance()->pushScissor(getScissor());
   scv::StaticLabel::display(getAbsolutePosition() + 2, "SequetialGroupPanel");
   scv::Scissor::getInstance()->popScissor();
}
