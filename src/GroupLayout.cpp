#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) : minSize(-1, -1), preferredSize(-1, -1), maxSize(-1, -1) {
   _horizontalGroup = NULL;
   _verticalGroup   = NULL;

   _host = host;

   //_autoCreateContainerPadding = false;
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

   if (_horizontalGroup != NULL) {
      width = _host->getWidth();

      minSize.x = _horizontalGroup->calculateMinimumSize(Spring::HORIZONTAL);
      preferredSize.x = _horizontalGroup->calculatePreferredSize(Spring::HORIZONTAL);
      maxSize.x = _horizontalGroup->calculateMaximumSize(Spring::HORIZONTAL);

      if (width > preferredSize.x) {
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, width); 
      } else if (preferredSize.x > width) {
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, preferredSize.x - (preferredSize.x - width)); 
      } else {      
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, preferredSize.x);
      }   
   }
   
   if (_verticalGroup != NULL) {
      height = _host->getHeight();

      minSize.y = _verticalGroup->calculateMinimumSize(Spring::VERTICAL);
      preferredSize.y = _verticalGroup->calculatePreferredSize(Spring::VERTICAL);
      maxSize.y = _verticalGroup->calculateMaximumSize(Spring::VERTICAL);

      if (height > preferredSize.y) {
         _verticalGroup->setSize(Spring::VERTICAL, 0, height); 
      } else if (preferredSize.y > height) {
         _verticalGroup->setSize(Spring::VERTICAL, 0, preferredSize.y - (preferredSize.y - height));
      } else {      
         _verticalGroup->setSize(Spring::VERTICAL, 0, preferredSize.y);
      }
   }
}

int GroupLayout::getMinimumSize(Spring::Axis axis) {
   return (axis == Spring::HORIZONTAL) ? minSize.x : minSize.y;
}

int GroupLayout::getPreferredSize(Spring::Axis axis) {
   return (axis == Spring::HORIZONTAL) ? preferredSize.x : preferredSize.y;
}

int GroupLayout::getMaximumSize(Spring::Axis axis) {
   return (axis == Spring::HORIZONTAL) ? maxSize.x : maxSize.y;
}

} //namespace scv