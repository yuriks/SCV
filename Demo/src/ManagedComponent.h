#ifndef __MANAGED_COMPONENT_H__
#define __MANAGED_COMPONENT_H__

class ManagedComponent {
public:
   ///////////////////////////////////////////////////////////
   ManagedComponent(scv::Component *object, const std::string &name);
   virtual ~ManagedComponent(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline std::string getName(void) const;
   inline scv::Component *getComponent(void) const;
   ///////////////////////////////////////////////////////////

protected:
   std::string _name;
   scv::Component *_object;
private:
};

///////////////////////////////////////////////////////////

std::string ManagedComponent::getName(void) const {
   return _name;
}

scv::Component * ManagedComponent::getComponent(void) const {
   return _object;
}

///////////////////////////////////////////////////////////

#endif //__MANAGED_COMPONENT_H__