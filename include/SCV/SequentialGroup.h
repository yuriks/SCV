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

   virtual inline int combined(int a, int b);
protected:
   
private:
};

///////////////////////////////////////////////////////////
int SequentialGroup::combined(int a, int b) {
   return constrain(a) + constrain(b);
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_SEQUENTIAL_GROUP_H__