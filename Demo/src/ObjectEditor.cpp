#include "stdafx.h"
#include "ObjectEditor.h"

ObjectEditor::ObjectEditor(void) : scv::ScrollComponent(scv::Point(), scv::Point()) {
}

ObjectEditor::~ObjectEditor(void) {
}

void ObjectEditor::refreshContainerPosition(void) {
   scv::ScrollComponent::refreshContainerPosition();
   if (getComponent() != NULL) {
      int width = getComponent()->getWidth();
      int height = getComponent()->getHeight();      

      if (width < getWidth() && !getComponent()->isResizing()) {
         width = getAbsolutePosition().x + (getSize().x - getComponent()->getSize().x - s_border) / 2;
      } else {
         width = getComponent()->getRelativePosition().x;
      }

      if (height < getHeight() && !getComponent()->isResizing()) {
         height = getAbsolutePosition().y + (getSize().y - getComponent()->getSize().y - s_border) / 2;
      } else {
         height = getComponent()->getRelativePosition().y;
      }

      getComponent()->setRelativePosition(scv::Point(width, height));
   }
}

void ObjectEditor::setComponent(scv::Component *object) {
   _registeredComponent = object;
}
