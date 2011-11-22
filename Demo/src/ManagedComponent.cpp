#include "stdafx.h"
#include "ManagedComponent.h"

#include "CodeGenerator.h"

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ManagedComponent::ManagedComponent(scv::Component *object, const std::string &name) {
   _object = object;
   _name = name;

   _parent = NULL;
}

ManagedComponent::~ManagedComponent(void) {
   setParent(NULL);

   List::iterator iter = _children.begin();
   while (iter != _children.end()) {
      ManagedComponent *pItem = (*iter);
      iter = _children.erase(iter);
      delete pItem;
   }
}

void ManagedComponent::setParent(ManagedComponent *parent) {
   if (_parent != NULL) _parent->removeChild(this);

   _parent = parent;

   if (_parent != NULL) _parent->addChild(this);
}

void ManagedComponent::addChild(ManagedComponent *object) {
   if (object != NULL) {
      object->setParent(NULL);

      object->_parent = this;
      _children.push_back(object);
   }   
}

void ManagedComponent::removeChild(ManagedComponent *object) {
   if (std::find(_children.begin(), _children.end(), object) != _children.end()) {
      object->_parent = NULL;
      _children.remove(object);
   }
}

ManagedComponent *ManagedComponent::getChild(scv::Component *object) {
   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if ((*iter)->getComponent() == object) {
         return (*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(object);
         if (managed != NULL) return managed;
      }
   }
   return NULL;
}

ManagedComponent * ManagedComponent::getChild(const std::string &name) {
   for (List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      if ((*iter)->getName() == name) {
         return (*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(name);
         if (managed != NULL) return managed;
      }
   }
   return NULL;
}

std::string ManagedComponent::getDeclarationCode(void) {
   throw std::exception("The method or operation is not implemented.");
}

std::string ManagedComponent::getImplementationCode(void) {
   throw std::exception("The method or operation is not implemented.");
}
