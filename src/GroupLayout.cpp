#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) {
   _host = host;

   _autoCreatePadding = false;
   _autoCreateContainerPadding = false;

   setHorizontalGroup(createParallelGroup(Spring::LEADING, true));
   setVerticalGroup(createParallelGroup(Spring::LEADING, true));
}

GroupLayout::~GroupLayout(void) {

}

ParallelGroup *GroupLayout::createParallelGroup(void) {
   return createParallelGroup(Spring::LEADING);
}

ParallelGroup *GroupLayout::createParallelGroup(Spring::Alignment alignment) {
   return createParallelGroup(alignment, true);
}

ParallelGroup *GroupLayout::createParallelGroup(Spring::Alignment alignment, bool resizable) {
   /*
   if (alignment == Spring::Alignment.BASELINE) {
      return new BaselineGroup(resizable);
   }
   /**/
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

   //HorizontalGroup
   ///////////////////////////////////////////////////////////   
   width = _host->getWidth();
   
   minSize = _horizontalGroup->calculateMinimumSize(Spring::HORIZONTAL);
   preferredSize = _horizontalGroup->calculatePreferredSize(Spring::HORIZONTAL);
   maxSize = _horizontalGroup->calculateMaximumSize(Spring::HORIZONTAL);

   int x = 0;
   if (width > preferredSize) {
      _horizontalGroup->setSize(Spring::HORIZONTAL, x, width); 
   } else if (preferredSize > width) {
      _horizontalGroup->setSize(Spring::HORIZONTAL, x, preferredSize - (preferredSize - width)); 
   } else {      
      _horizontalGroup->setSize(Spring::HORIZONTAL, x, preferredSize);
   }
   
   ///////////////////////////////////////////////////////////

   
   //VerticalGroup
   ///////////////////////////////////////////////////////////
   height = _host->getHeight();

   minSize = _verticalGroup->calculateMinimumSize(Spring::VERTICAL);
   preferredSize = _verticalGroup->calculatePreferredSize(Spring::VERTICAL);
   maxSize = _verticalGroup->calculateMinimumSize(Spring::VERTICAL);
   
   int y = 0;
   if (height > preferredSize) {
      _verticalGroup->setSize(Spring::VERTICAL, x, height); 
   } else if (preferredSize > height) {
      _verticalGroup->setSize(Spring::VERTICAL, x, preferredSize - (preferredSize - height)); 
   } else {      
      _verticalGroup->setSize(Spring::VERTICAL, x, preferredSize);
   }
   ///////////////////////////////////////////////////////////
   /**/
}

} //namespace scv