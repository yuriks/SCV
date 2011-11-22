#ifndef __MANAGED_COMPONENT_H__
#define __MANAGED_COMPONENT_H__

class ManagedComponent {
public:
   typedef std::list<ManagedComponent *> List;

   ///////////////////////////////////////////////////////////
   ManagedComponent(scv::Component *object, const std::string &name, const std::string &typeName);
   virtual ~ManagedComponent(void);
   ///////////////////////////////////////////////////////////

   inline void setCustomClass(bool custom);
   inline bool getCustomClass(void) const;

   ///////////////////////////////////////////////////////////
   inline std::string getClassName(void) const;
   inline std::string getDerivedTypeName(void) const;
   inline std::string getPointerName(void) const;
   inline scv::Component *getComponent(void) const;   
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
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
   std::string getAllocationCode(void);

   std::string getDefaultClassInitialization(void);
   ///////////////////////////////////////////////////////////
   
protected:
   std::string _className, _typeName;
   scv::Component *_object;
   bool _customClass;

   ManagedComponent *_parent;
   List _children;
};

///////////////////////////////////////////////////////////

void ManagedComponent::setCustomClass(bool custom) {
   _customClass = custom;
}

bool ManagedComponent::getCustomClass(void) const {
   return _customClass;
}

std::string ManagedComponent::getClassName(void) const {
   return _className;
}

std::string ManagedComponent::getDerivedTypeName(void) const {
   return _typeName;
}

std::string ManagedComponent::getPointerName(void) const {
   std::string pointer(getClassName());
   std::transform(pointer.begin(), pointer.end(), pointer.begin(), ::tolower);
   return pointer;
}

scv::Component * ManagedComponent::getComponent(void) const {
   return _object;
}

ManagedComponent *ManagedComponent::getParent(void) const {
   return _parent;
}

///////////////////////////////////////////////////////////

#endif //__MANAGED_COMPONENT_H__