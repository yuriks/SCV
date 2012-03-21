#ifndef __SCV_GROUP_H__
#define __SCV_GROUP_H__

#include "Spring.h"

#include "Component.h"

namespace scv {

class Group : public Spring {
public:
   typedef std::list<Spring*> SpringsList;

   enum SizeType {
      MIN_SIZE, PREF_SIZE, MAX_SIZE
   };
   
   virtual Group *addGroup(Group *group);

   virtual Group *addComponent(Component *component);
   virtual Group *addComponent(Component *component, int size);
   virtual Group *addComponent(Component *component, int min, int pref, int max);
   void removeComponent(scv::Component * object);

   virtual Group *addGap(int size);
   virtual Group *addGap(int min, int pref, int max);

   virtual Group *addSpring(Spring *spring);
   
   virtual int calculateMinimumSize(Spring::Axis axis);
   virtual int calculatePreferredSize(Spring::Axis axis);
   virtual int calculateMaximumSize(Spring::Axis axis);

   virtual void setSize(Spring::Axis axis, int origin, int size);
   virtual void setValidSize(Spring::Axis axis, int origin, int size) = 0;

   Group *enableAutoCreateContainerGaps(void);
   bool getAutoCreateContainerGaps(void) const;

   int calculateSize(Spring::Axis axis, SizeType type);

   int getSpringSize(Spring *spring, Spring::Axis axis, SizeType type);

   virtual int combined(int a, int b) = 0;

   inline Spring *getSpring(int index);

protected:
   SpringsList _springs;
   //bool _autoCreateContainerPadding;
private:
};

///////////////////////////////////////////////////////////

Spring * Group::getSpring(int index) {
   for (SpringsList::iterator iter = _springs.begin(); iter != _springs.end(); ++iter) {
      if (index == 0) return (*iter);
      index--;
   }
   return NULL;
}

} //namespace scv

#endif //__SCV_GROUP_H__