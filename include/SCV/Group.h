#ifndef __SCV_GROUP_H__
#define __SCV_GROUP_H__

//http://download.oracle.com/javase/6/docs/api/javax/swing/GroupLayout.Group.html

#include "Component.h"

namespace scv {

class Group {
public:
   ///////////////////////////////////////////////////////////
   Group(void);
   virtual ~Group(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual Group *addComponent(Component *component);
   virtual Group *addGap(int size);
   virtual Group *addGroup(Group *group);
   ///////////////////////////////////////////////////////////

protected:
   
private:
};

} //namespace scv

#endif //__SCV_GROUP_H__