#ifndef __SCV_PARALLEL_GROUP_H__
#define __SCV_PARALLEL_GROUP_H__

#include "Group.h"

namespace scv {

class ParallelGroup : public Group {
public:
   ParallelGroup(Spring::Alignment alignment, bool resizable);

   virtual ParallelGroup *addGroup(Group *group);

   virtual ParallelGroup *addComponent(Component *component);
   virtual ParallelGroup *addComponent(Component *component, int size);
   virtual ParallelGroup *addComponent(Component *component, int min, int pref, int max);

   virtual ParallelGroup *addGap(int size);
   virtual ParallelGroup *addGap(int min, int pref, int max);

   virtual int calculateMinimumSize(Spring::Axis axis);
   virtual int calculateMaximumSize(Spring::Axis axis);

   virtual void setValidSize(Spring::Axis axis, int origin, int size);
   virtual void setChildSize(Spring *spring, Spring::Axis axis, int origin, int size);

   virtual inline bool isResizable(void) const;
   virtual inline int combined(int a, int b);
protected:
   Spring::Alignment _childAlignment;
   bool _resizable;
private:
};

///////////////////////////////////////////////////////////

bool ParallelGroup::isResizable(void) const {
   return _resizable;
}

int ParallelGroup::combined(int a, int b) {
   return std::max(a, b);
}

} //namespace scv

#endif //__SCV_PARALLEL_GROUP_H__