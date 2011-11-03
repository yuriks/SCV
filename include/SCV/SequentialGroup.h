#ifndef __SCV_SEQUENTIAL_GROUP_H__
#define __SCV_SEQUENTIAL_GROUP_H__

#include "Group.h"

namespace scv {

class SequentialGroup : public Group {
public:
   ///////////////////////////////////////////////////////////
   SequentialGroup(void);
   virtual ~SequentialGroup(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual SequentialGroup *addGroup(Group *group);

   virtual SequentialGroup *addComponent(Component *component);
   virtual SequentialGroup *addComponent(Component *component, int min, int pref, int max);

   virtual SequentialGroup *addGap(int size);
   virtual SequentialGroup *addGap(int min, int pref, int max);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setValidSize(Spring::Axis axis, int origin, int size);
   ///////////////////////////////////////////////////////////

   virtual inline int combined(int a, int b);

   ///////////////////////////////////////////////////////////
   SequentialGroup *setAutoCreateGaps(bool autoCreatePadding);
   bool getAutoCreateGap(void) const;

   inline SequentialGroup *setAutoGapsSize(int autoGapSize);
   inline int getAutoGapsSize(void) const;
   ///////////////////////////////////////////////////////////

protected:
   ///////////////////////////////////////////////////////////
   class SpringDelta {
   public:
      int _index, _delta;
      SpringDelta(int index, int delta) {
         _index = index;
         _delta = delta;
      }
      bool operator<(const SpringDelta &rhs) const { return _delta < rhs._delta; }   
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   typedef std::deque<SpringDelta> SpringDeltaDeque;
   ///////////////////////////////////////////////////////////

   virtual void setValidSizeNotPreferred(Spring::Axis axis, int origin, int size);
   virtual SpringDeltaDeque buildResizableList(Spring::Axis axis, bool useMin);

   ///////////////////////////////////////////////////////////
   void autoCreatePadding(void);

   bool _autoCreatePadding;

   int _autoGapSize;
   const static int s_defaultGap = 10;
   ///////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////
int SequentialGroup::combined(int a, int b) {
   return constrain(a) + constrain(b);
}

SequentialGroup * SequentialGroup::setAutoGapsSize(int autoGapSize) {
   _autoGapSize = autoGapSize;
   return this;
}

int SequentialGroup::getAutoGapsSize(void) const {
   return _autoGapSize;
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_SEQUENTIAL_GROUP_H__