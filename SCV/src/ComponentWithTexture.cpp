#include "stdafx.h"
#include "ComponentWithTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithTexture::ComponentWithTexture(const scv::Point &p1, const scv::Point &p2) :
      Component(p1, p2) {
   _cTexture = NULL;
}
ComponentWithTexture::~ComponentWithTexture(void) {}

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

Point ComponentWithTexture::getMinimumSize(void) const {
   return Component::getMinimumSize();
}

Point ComponentWithTexture::getPreferredSize(void) const {
   return Component::getPreferredSize();
}

Point ComponentWithTexture::getMaximumSize(void) const {
   return Component::getMaximumSize();
}

void ComponentWithTexture::addChild(Component *object) {
   Component::addChild(object);
}

void ComponentWithTexture::removeChild(Component *object) {
   Component::removeChild(object);
}

} // namespace scv
