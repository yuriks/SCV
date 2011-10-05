#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) {
   _horizontalGroup = NULL;
   _verticalGroup   = NULL;

   _host = host;

   _autoCreatePadding = false;
   _autoCreateContainerPadding = false;
}

GroupLayout::~GroupLayout(void) {

}

ParallelGroup *GroupLayout::createParallelGroup(void) {
   return createParallelGroup(Spring::LEADING);
}

ParallelGroup *GroupLayout::createParallelGroup(Spring::Alignment alignment) {
   return createParallelGroup(alignment, true);
}

ParallelGroup * GroupLayout::createParallelGroup(Spring::Alignment alignment, bool resizable) {
   return new ParallelGroup(alignment, resizable);
}

SequentialGroup *GroupLayout::createSequentialGroup(void) {
   return new SequentialGroup();
}

void GroupLayout::setHorizontalGroup(Group *group) {
   _horizontalGroup = group;
}

void GroupLayout::setVerticalGroup(Group *group) {
   _verticalGroup = group;
}

void GroupLayout::layoutContainer(void) {
   int width, height;
   int minSize, preferredSize, maxSize;

   if (_horizontalGroup != NULL) {
      width = _host->getWidth();

      minSize = _horizontalGroup->calculateMinimumSize(Spring::HORIZONTAL);
      preferredSize = _horizontalGroup->calculatePreferredSize(Spring::HORIZONTAL);
      maxSize = _horizontalGroup->calculateMaximumSize(Spring::HORIZONTAL);

      if (width > preferredSize) {
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, width); 
      } else if (preferredSize > width) {
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, preferredSize - (preferredSize - width)); 
      } else {      
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, preferredSize);
      }   
   }
   
   if (_verticalGroup != NULL) {
      height = _host->getHeight();

      minSize = _verticalGroup->calculateMinimumSize(Spring::VERTICAL);
      preferredSize = _verticalGroup->calculatePreferredSize(Spring::VERTICAL);
      maxSize = _verticalGroup->calculateMinimumSize(Spring::VERTICAL);

      if (height > preferredSize) {
         _verticalGroup->setSize(Spring::VERTICAL, 0, height); 
      } else if (preferredSize > height) {
         _verticalGroup->setSize(Spring::VERTICAL, 0, preferredSize - (preferredSize - height)); 
      } else {      
         _verticalGroup->setSize(Spring::VERTICAL, 0, preferredSize);
      }
   }
}

} //namespace scv