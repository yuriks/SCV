#include "stdafx.h"
#include "SequentialGroup.h"
#include "GapSpring.h"

namespace scv {

SequentialGroup::SequentialGroup(void) : Group() {
   _autoCreatePadding = false;
   _autoGapSize = s_defaultGap;
}

SequentialGroup::~SequentialGroup(void) {

}

SequentialGroup *SequentialGroup::addGroup(Group *group) {
   autoCreatePadding();
   return (SequentialGroup*)Group::addGroup(group);
}

SequentialGroup *SequentialGroup::addComponent(Component *component) {
   return (SequentialGroup*)Group::addComponent(component);
}

SequentialGroup *SequentialGroup::addComponent(Component *component, int min, int pref, int max) {
   autoCreatePadding();
   return (SequentialGroup*)Group::addComponent(component, min, pref, max);
}

SequentialGroup *SequentialGroup::addGap(int size) {
   return (SequentialGroup*)Group::addGap(size);
}

SequentialGroup *SequentialGroup::addGap(int min, int pref, int max) {
   autoCreatePadding();
   return (SequentialGroup*)Group::addGap(min, pref, max);
}

void SequentialGroup::setValidSize(Spring::Axis axis, int origin, int size) {
   int pref = getPreferredSize(axis);
   if (size == pref) {      
      //layout at preferred size
      for (SpringsList::iterator iter = _springs.begin(); iter != _springs.end(); ++iter) {
         int springPref = (*iter)->getPreferredSize(axis);
         (*iter)->setSize(axis, origin, springPref);
         origin += springPref;
      }
   } else if (_springs.size() == 1) {      
      Spring *spring = getSpring(0);
      spring->setSize(axis, origin, std::min(std::max(size, spring->getMinimumSize(axis)), spring->getMaximumSize(axis)));
   } else if (_springs.size() > 1) {
      setValidSizeNotPreferred(axis, origin, size);
   }
}

SequentialGroup *SequentialGroup::setAutoCreateGaps(bool autoCreatePadding) {
   _autoCreatePadding = autoCreatePadding;
   return this;
}

bool SequentialGroup::getAutoCreateGap(void) const {
   return _autoCreatePadding;
}

void SequentialGroup::autoCreatePadding(void) {
   //autoCreatePadding
   if (_autoCreatePadding && _springs.size() > 0) {
      Group::addSpring(new GapSpring(getAutoGapsSize(), getAutoGapsSize(), getAutoGapsSize()));
   }
}

void SequentialGroup::setValidSizeNotPreferred(Spring::Axis axis, int origin, int size) {
   int delta = size - getPreferredSize(axis);

   assert(delta != 0);

   bool useMin = (delta < 0);
   int springCount = _springs.size();
   if (useMin) {
      delta *= -1;
   }

   SpringDeltaDeque resizable = buildResizableList(axis, useMin);
   int resizableCount = resizable.size();

   if (resizableCount > 0) {
      int sDelta = delta / resizableCount;
      int slop = delta - sDelta * resizableCount;
      
      std::vector<int> sizes(springCount);
      int sign = useMin ? -1 : 1;

      for (int counter = 0; counter < resizableCount; ++counter) {
         SpringDelta springDelta = resizable[counter];
         if ((counter + 1) == resizableCount) {
            sDelta += slop;
         }
         springDelta._delta = std::min(sDelta, springDelta._delta);
         delta -= springDelta._delta;
         if (springDelta._delta != sDelta && (counter + 1) < resizableCount) {
            sDelta = delta / (resizableCount - counter - 1);
            slop = delta - sDelta * (resizableCount - counter  - 1);
         }
         sizes[springDelta._index] = sign * springDelta._delta;
      }

      for (int counter = 0; counter < springCount; ++counter) {
         Spring *spring = getSpring(counter);
         int sSize = spring->getPreferredSize(axis) + sizes[counter];
         spring->setSize(axis, origin, sSize);
         origin += sSize;
      }

   } else {      
      for (int counter = 0; counter < springCount; ++counter) {
         Spring *spring = getSpring(counter);
         int sSize;
         if (useMin) {
            sSize = spring->getMinimumSize(axis);
         } else {
            sSize = spring->getMaximumSize(axis);
         }
         spring->setSize(axis, origin, sSize);
         origin += sSize;
      }
   }

}

SequentialGroup::SpringDeltaDeque SequentialGroup::buildResizableList(Spring::Axis axis, bool useMin) {
   int size = _springs.size();

   SpringDeltaDeque sorted = SpringDeltaDeque();
   for (int counter = 0; counter < size; ++counter) {
      Spring *spring = getSpring(counter);
      int sDelta;
      if (useMin) {
         sDelta = spring->getPreferredSize(axis) - spring->getMinimumSize(axis);
      } else {
         sDelta = spring->getMaximumSize(axis) - spring->getPreferredSize(axis);
      }
      if (sDelta > 0) {
         sorted.push_back(SpringDelta(counter, sDelta));
      }
      std::sort(sorted.begin(), sorted.end());
   }
   return sorted;
}

} //namespace scv