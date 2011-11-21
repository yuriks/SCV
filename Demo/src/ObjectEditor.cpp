#include "stdafx.h"
#include "ObjectEditor.h"

ObjectEditor::ObjectEditor(void) : scv::Panel(scv::Point(), scv::Point()) {
   _currObject = NULL;
}

ObjectEditor::~ObjectEditor(void) {
}

void ObjectEditor::setComponent(scv::Component *object) {
   if (_currObject != NULL) {
      removeChild(_currObject);
   }
   _currObject = object;
   addChild(_currObject);

   _currObject->setRelativePosition((getSize() - _currObject->getSize()) / 2);
}
