#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include "ManagedComponent.h"

class ComponentCounter {
public:
   static std::string getName(scv::Component::ObjectType type);
   
protected:
   static std::map<scv::Component::ObjectType, int> counter;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class CodeGenerator : public Singleton<CodeGenerator> {
friend class Singleton<CodeGenerator>;
public:
   ///////////////////////////////////////////////////////////
   void addComponent(scv::Component *object);
   ///////////////////////////////////////////////////////////

   bool hasComponent(scv::Component *object);

protected:
   ///////////////////////////////////////////////////////////
   CodeGenerator(void);
   virtual ~CodeGenerator(void);
   ///////////////////////////////////////////////////////////

   typedef std::list<ManagedComponent *> ManagedList;
   ManagedList _managed;

};

#endif //__CODE_GENERATOR_H__