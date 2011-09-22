#include "stdafx.h"
#include "ComponentWithTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithTexture::ComponentWithTexture(const scv::Point &p1, const scv::Point &p2) :
      Component(p1, p2) {
   _cTexture = NULL;
}
ComponentWithTexture::~ComponentWithTexture(void) {}

void ComponentWithTexture::onMouseClick(const scv::MouseEvent &evt) {}

void ComponentWithTexture::onMouseHold(const scv::MouseEvent &evt) {}

void ComponentWithTexture::onMouseOver(const scv::MouseEvent &evt) {}

void ComponentWithTexture::onMouseUp(const scv::MouseEvent &evt) {}

void ComponentWithTexture::onMouseWheel(const scv::MouseEvent &evt) {}

void ComponentWithTexture::onKeyPressed(const scv::KeyEvent &evt) {}

void ComponentWithTexture::onKeyUp(const scv::KeyEvent &evt) {}

void ComponentWithTexture::onResizing(void) {}

void ComponentWithTexture::onDragging(void) {}

void ComponentWithTexture::processMouse(const scv::MouseEvent &evt) {
   Component::processMouse(evt);
}

void ComponentWithTexture::processKey(const scv::KeyEvent &evt) {
   Component::processKey(evt);
}

void ComponentWithTexture::setRelativePosition(const Point &position) {
   Component::setRelativePosition(position);
}

int ComponentWithTexture::getWidth(void) const {
   return Component::getWidth();
}

int ComponentWithTexture::getHeight(void) const {
   return Component::getHeight();
}

void ComponentWithTexture::setWidth(const int width) {
   Component::setWidth(width);
}

void ComponentWithTexture::setHeight(const int height) {
   Component::setHeight(height);
}

void ComponentWithTexture::setDraggable(bool state) {
   Component::setDraggable(state);
}

void ComponentWithTexture::setResizable(bool state) {
   Component::setResizable(state);
}

void ComponentWithTexture::setVisible(bool state) {
   Component::setVisible(state);
}

Point ComponentWithTexture::getSize(void) const {
   return Component::getSize();
}

void ComponentWithTexture::addChild(Component *object) {
   Component::addChild(object);
}

void ComponentWithTexture::removeChild(Component *object) {
   Component::removeChild(object);
}



} // namespace scv
