#include "stdafx.h"
#include "GroupLayout.h"

namespace scv {

GroupLayout::GroupLayout(Panel *host) {
   _horizontalGroup = NULL;
   _verticalGroup   = NULL;

   _host = host;
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
   if (_horizontalGroup != NULL) {
      int width = _host->getWidth();
      int preferredSize = _horizontalGroup->calculatePreferredSize(Spring::HORIZONTAL);
      
      if (width > preferredSize) {
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, width); 
      } else if (preferredSize > width) {         
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, preferredSize - (preferredSize - width)); 
      } else {
         _horizontalGroup->setSize(Spring::HORIZONTAL, 0, preferredSize);
      }   
   }
   
   if (_verticalGroup != NULL) {
      int height = _host->getHeight();
      int preferredSize = _verticalGroup->calculatePreferredSize(Spring::VERTICAL);

      if (height > preferredSize) {
         _verticalGroup->setSize(Spring::VERTICAL, 0, height); 
      } else if (preferredSize > height) {
         _verticalGroup->setSize(Spring::VERTICAL, 0, preferredSize - (preferredSize - height));
      } else {      
         _verticalGroup->setSize(Spring::VERTICAL, 0, preferredSize);
      }
   }
}

int GroupLayout::getMinimumSize(Spring::Axis axis) {
   switch (axis) {
   case Spring::HORIZONTAL:
      if (_horizontalGroup != NULL) {
         return _horizontalGroup->calculateMinimumSize(Spring::HORIZONTAL);
      } else {
         return Spring::DEFAULT_SIZE;
      }
      break;
   case Spring::VERTICAL:
      if (_verticalGroup != NULL) {
         return _verticalGroup->calculateMinimumSize(Spring::VERTICAL);
      } else {
         return Spring::DEFAULT_SIZE;
      }
      break;
   default:
      return Spring::DEFAULT_SIZE;
      break;
   }
}

int GroupLayout::getPreferredSize(Spring::Axis axis) {
   switch (axis) {
   case Spring::HORIZONTAL:
      if (_horizontalGroup != NULL) {
         return _horizontalGroup->calculatePreferredSize(Spring::HORIZONTAL);
      } else {
         return Spring::DEFAULT_SIZE;
      }
      break;
   case Spring::VERTICAL:
      if (_verticalGroup != NULL) {
         return _verticalGroup->calculatePreferredSize(Spring::VERTICAL);
      } else {
         return Spring::DEFAULT_SIZE;
      }
      break;
   default:
      return Spring::DEFAULT_SIZE;
      break;
   }
}

int GroupLayout::getMaximumSize(Spring::Axis axis) {
   switch (axis) {
   case Spring::HORIZONTAL:
      if (_horizontalGroup != NULL) {
         return _horizontalGroup->calculateMaximumSize(Spring::HORIZONTAL);
      } else {
         return Spring::DEFAULT_SIZE;
      }
      break;
   case Spring::VERTICAL:
      if (_verticalGroup != NULL) {
         return _verticalGroup->calculateMaximumSize(Spring::VERTICAL);
      } else {
         return Spring::DEFAULT_SIZE;
      }
      break;
   default:
      return Spring::DEFAULT_SIZE;
      break;
   }
}

Group * GroupLayout::getHorizontalGroup(void) const {
   return _horizontalGroup;
}

Group * GroupLayout::getVerticalGroup(void) const {
   return _verticalGroup;
}

void GroupLayout::removeComponent(scv::Component *object) {
   if (getHorizontalGroup()) {
      getHorizontalGroup()->removeComponent(object);
   }
   
   if (getVerticalGroup()) {
      getVerticalGroup()->removeComponent(object);
   }
}

} //namespace scv