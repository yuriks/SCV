#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include "ManagedComponent.h"

class CodeGenerator : public Singleton<CodeGenerator> {
friend class Singleton<CodeGenerator>;
public:
   ///////////////////////////////////////////////////////////
   typedef std::list<ManagedComponent *> ManagedList;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void addComponent(scv::Component *comp);
   void addManagedComponent(scv::Component *object, const std::string &type, const std::string &aString = "");

   void deleteComponent(ManagedComponent *managed);   
   void deleteComponents();
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   bool hasComponent(scv::Component *object) const;
   bool hasComponent(const std::string &name) const;
   ///////////////////////////////////////////////////////////

   int count[23];

   ///////////////////////////////////////////////////////////
   ManagedComponent *getManagedComponent(scv::Component *object) const;
   ManagedComponent *getManagedComponent(const std::string &name) const;

   ManagedList getManagedComponents(void) const;

   void modifyNameManagedComponent(scv::Component * obj, std::string newName);
   ///////////////////////////////////////////////////////////

   std::string createAllocationCode(scv::Component *comp);
   std::string addChildren(scv::Component *child, std::string dad);

   ///////////////////////////////////////////////////////////
   void generateCode(void);
   std::string generateCodeMain(void);
   std::string generateCodeAppH(void);
   std::string generateCodeAppCpp(void);
   ///////////////////////////////////////////////////////////
   
   void setSCVFrame( scv::InternalFrame *frame);
   inline scv::InternalFrame *getSCVFrame(void) const;

protected:
   ///////////////////////////////////////////////////////////
   CodeGenerator(void);
   virtual ~CodeGenerator(void);
   ///////////////////////////////////////////////////////////

   int getComponentCount(scv::Component::Type type);   

   ManagedList _managed;
   std::map<scv::Component::Type, int> _counter;
   scv::InternalFrame *_scvFrame;
};

///////////////////////////////////////////////////////////

scv::InternalFrame * CodeGenerator::getSCVFrame(void) const {
   return _scvFrame;
}

///////////////////////////////////////////////////////////

#endif //__CODE_GENERATOR_H__