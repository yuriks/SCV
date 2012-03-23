#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include "ManagedComponent.h"

class CodeGenerator : public Singleton<CodeGenerator> {
friend class Singleton<CodeGenerator>;
public:
   int count[23];

   std::string createAllocationCode(scv::Component *comp);
   std::string addChildren(scv::Component *child, std::string dad);
   
   void generateCode(void);
   std::string generateCodeMain(void);
   std::string generateCodeAppH(void);
   std::string generateCodeAppCpp(void);
   
   void setSCVFrame( scv::InternalFrame *frame);
   inline scv::InternalFrame *getSCVFrame(void) const;

protected:
   CodeGenerator(void);
   virtual ~CodeGenerator(void);

   int getComponentCount(scv::Component::Type type);   

   std::map<scv::Component::Type, int> _counter;
   scv::InternalFrame *_scvFrame;
};

///////////////////////////////////////////////////////////

scv::InternalFrame * CodeGenerator::getSCVFrame(void) const {
   return _scvFrame;
}

#endif //__CODE_GENERATOR_H__