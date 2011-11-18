#ifndef __MANAGED_COMPONENT_H__
#define __MANAGED_COMPONENT_H__

class ManagedComponent {
public:
   ///////////////////////////////////////////////////////////
   ManagedComponent(void);
   virtual ~ManagedComponent(void);
   ///////////////////////////////////////////////////////////

   std::string getName(void) const;
   scv::Component *getComponent(void) const;

protected:
   
private:
};

#endif //__MANAGED_COMPONENT_H__