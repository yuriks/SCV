#ifndef __MANAGED_COMPONENT_H__
#define __MANAGED_COMPONENT_H__

class ManagedComponent {
public:
   typedef std::list<ManagedComponent *> List;

   ///////////////////////////////////////////////////////////
   ManagedComponent(scv::Component *object, const std::string &name);
   virtual ~ManagedComponent(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline std::string getName(void) const;
   inline scv::Component *getComponent(void) const;

   void setParent(ManagedComponent *parent);
   inline ManagedComponent *getParent(void) const;

   void addChild(ManagedComponent *object);
   void removeChild(ManagedComponent * object);

   ManagedComponent *getChild(scv::Component *object);
   ManagedComponent *getChild(const std::string &name);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   std::string getDeclarationCode(void);
   std::string getImplementationCode(void);
   ///////////////////////////////////////////////////////////

protected:
   std::string _name;
   scv::Component *_object;

   ManagedComponent *_parent;
   List _children;
};

///////////////////////////////////////////////////////////

std::string ManagedComponent::getName(void) const {
   return _name;
}

scv::Component * ManagedComponent::getComponent(void) const {
   return _object;
}

ManagedComponent *ManagedComponent::getParent(void) const {
   return _parent;
}

///////////////////////////////////////////////////////////

#endif //__MANAGED_COMPONENT_H__