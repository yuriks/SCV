#include "stdafx.h"
#include "ManagedComponent.h"

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ManagedComponent::ManagedComponent(scv::Component *object, const std::string &name) {
   _object = object;
   _name = name;
}

ManagedComponent::~ManagedComponent(void) {
}
