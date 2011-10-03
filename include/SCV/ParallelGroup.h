#ifndef __SCV_PARALLEL_GROUP_H__
#define __SCV_PARALLEL_GROUP_H__

//http://javasourcecode.org/html/open-source/jdk/jdk-6u23/javax/swing/GroupLayout.ParallelGroup.html

#include "Group.h"

namespace scv {

class ParallelGroup : public Group {
public:
   ///////////////////////////////////////////////////////////
   ParallelGroup(void);
   virtual ~ParallelGroup(void);
   ///////////////////////////////////////////////////////////

   virtual inline int combined(int a, int b);
protected:
   
private:
};

///////////////////////////////////////////////////////////
int ParallelGroup::combined(int a, int b) {
   return std::max(a, b);
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_PARALLEL_GROUP_H__