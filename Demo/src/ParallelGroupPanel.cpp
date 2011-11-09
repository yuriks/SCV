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

   _layout->setVerticalGroup(_verticalGroup);
   _layout->setHorizontalGroup(_horizontalGroup);
}

ParallelGroupPanel::~ParallelGroupPanel(void) {

}

void ParallelGroupPanel::applyColor(void) {
   scv::ColorScheme::getInstance()->applyColor(scv::Color4f(0.7f, 1.0f, 0.7f, 0.3f));
}
