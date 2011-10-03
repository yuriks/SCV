#ifndef __SCV_COMPONENT_SPRING_H__
#define __SCV_COMPONENT_SPRING_H__

#include "Spring.h"

#include "Component.h"

namespace scv {

class ComponentSpring : public Spring {
public:
   ///////////////////////////////////////////////////////////
   ComponentSpring(Component *component, int min, int pref, int max);
   virtual ~ComponentSpring(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int calculateMinimumSize(Axis axis);
   virtual int calculatePreferredSize(Axis axis);
   virtual int calculateMaximumSize(Axis axis);
   ///////////////////////////////////////////////////////////

   virtual int getSizeAlongAxis(Axis axis, Point size);

   inline void setComponent(Component *component);
   inline Component *getComponent(void) const;

protected:
   inline bool isVisible(void) const;

   Component *_component;
private:   
};

///////////////////////////////////////////////////////////
bool ComponentSpring::isVisible(void) const {
   return _component->isVisible();
}

void ComponentSpring::setComponent(Component *component) {
   _component = component;
}

Component *ComponentSpring::getComponent(void) const {
   return _component;
}

///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_COMPONENT_SPRING_H__