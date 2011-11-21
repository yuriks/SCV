#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include "ManagedComponent.h"

class CodeGenerator : public Singleton<CodeGenerator> {
friend class Singleton<CodeGenerator>;
public:
   ///////////////////////////////////////////////////////////
   scv::Component *addComponent(const std::string &type);
   ///////////////////////////////////////////////////////////

   bool hasComponent(scv::Component *object);

   ManagedComponent *getManagedComponent(scv::Component *object);

   void generateCode(void);

protected:
   ///////////////////////////////////////////////////////////
   CodeGenerator(void);
   virtual ~CodeGenerator(void);
   ///////////////////////////////////////////////////////////

   int getComponentCount(scv::Component::ObjectType type);

   typedef std::list<ManagedComponent *> ManagedList;
   ManagedList _managed;


   std::map<scv::Component::ObjectType, int> counter;
};

#endif //__CODE_GENERATOR_H__