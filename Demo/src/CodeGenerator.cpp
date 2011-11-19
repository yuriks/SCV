#include "stdafx.h"
#include "CodeGenerator.h"

std::map<scv::Component::ObjectType, int> ComponentCounter::counter;

std::string ComponentCounter::getName(scv::Component::ObjectType type) {
   return "none";
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

CodeGenerator::CodeGenerator(void) {
}

CodeGenerator::~CodeGenerator(void) {
}

void CodeGenerator::addComponent(scv::Component *object) {
   std::cout << ComponentCounter::getName(object->getType()) << std::endl;

}

bool CodeGenerator::hasComponent(scv::Component *object) {
   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == object) return true;
   }
   return false;
}
