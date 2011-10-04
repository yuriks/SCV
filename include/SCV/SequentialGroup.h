#ifndef __SCV_SEQUENTIAL_GROUP_H__
#define __SCV_SEQUENTIAL_GROUP_H__

//http://javasourcecode.org/html/open-source/jdk/jdk-6u23/javax/swing/GroupLayout.SequentialGroup.html

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
protected:
   ///////////////////////////////////////////////////////////
   class SpringDelta {
   public:
      int _index, _delta;
      SpringDelta(int index, int delta) {
         _index = index;
         _delta = delta;
      }
      inline int compareTo(SpringDelta o) {
         return _delta - o._delta;
      }
      bool operator<(const SpringDelta &rhs) const { return _delta < rhs._delta; }
   
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   typedef std::deque<SpringDelta> SpringDeltaDeque;
   ///////////////////////////////////////////////////////////

   virtual void setValidSizeNotPreferred(Spring::Axis axis, int origin, int size);
   virtual SpringDeltaDeque buildResizableList(Spring::Axis axis, bool useMin);
private:
};

///////////////////////////////////////////////////////////
int SequentialGroup::combined(int a, int b) {
   return constrain(a) + constrain(b);
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_SEQUENTIAL_GROUP_H__