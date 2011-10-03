#ifndef __SCV_SEQUENTIAL_GROUP_H__
#define __SCV_SEQUENTIAL_GROUP_H__

//http://download.oracle.com/javase/6/docs/api/javax/swing/GroupLayout.SequentialGroup.html

#include "Group.h"

namespace scv {

class SequentialGroup : public Group {
public:
   SequentialGroup(void);
   virtual ~SequentialGroup(void);
protected:
   
private:
};

} //namespace scv

#endif //__SCV_SEQUENTIAL_GROUP_H__