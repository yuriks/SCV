#ifndef __SCV_GROUP_H__
#define __SCV_GROUP_H__

//http://javasourcecode.org/html/open-source/jdk/jdk-6u23/javax/swing/GroupLayout.Group.html

#include "Spring.h"

#include "Component.h"

namespace scv {

class Group : public Spring {
public:
   ///////////////////////////////////////////////////////////
   typedef std::deque<Spring*> SpringsList;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   enum SizeType {
      MIN_SIZE, PREF_SIZE, MAX_SIZE
   };
   ///////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////
   Group(void);
   virtual ~Group(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual Group *addGroup(Group *group);

   virtual Group *addComponent(Component *component);
   virtual Group *addComponent(Component *component, int min, int pref, int max);

   virtual Group *addGap(int size);
   virtual Group *addGap(int min, int pref, int max);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual Group *addSpring(Spring *spring);
   ///////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////
   virtual int calculateMinimumSize(Spring::Axis axis);
   virtual int calculatePreferredSize(Spring::Axis axis);
   virtual int calculateMaximumSize(Spring::Axis axis);
   ///////////////////////////////////////////////////////////

   int calculateSize(Spring::Axis axis, SizeType type);

   int getSpringSize(Spring *spring, Spring::Axis axis, SizeType type);

   virtual int combined(int a, int b) = 0;

protected:
   inline Spring *getSpring(int index);

   SpringsList _springs;
private:
};

///////////////////////////////////////////////////////////
Spring * Group::getSpring(int index) {
   return _springs[index];
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_GROUP_H__