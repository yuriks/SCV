#ifndef __SCV_PARALLEL_GROUP_H__
#define __SCV_PARALLEL_GROUP_H__

//http://download.oracle.com/javase/6/docs/api/javax/swing/GroupLayout.ParallelGroup.html

#include "Group.h"

namespace scv {

class ParallelGroup : public Group {
public:
   ParallelGroup(void);
   virtual ~ParallelGroup(void);
protected:
   
private:
};

} //namespace scv

#endif //__SCV_PARALLEL_GROUP_H__