#include "stdafx.h"
#include "ComponentWithTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithTexture::ComponentWithTexture(const scv::Point &p1, const scv::Point &p2) :
      SCVComponent(p1, p2) {
   _cTexture = NULL;
}
ComponentWithTexture::~ComponentWithTexture(void) {}

void ComponentWithTexture::processMouse(const scv::MouseEvent &evt) {
   SCVComponent::processMouse(evt);
}

void ComponentWithTexture::processKey(const scv::KeyEvent &evt) {
   SCVComponent::processKey(evt);
}

void ComponentWithTexture::setRelativePosition(const Point &position) {
   SCVComponent::setRelativePosition(position);
}

int ComponentWithTexture::getWidth(void) const {
   return SCVComponent::getWidth();
}

int ComponentWithTexture::getHeight(void) const {
   return SCVComponent::getHeight();
}

void ComponentWithTexture::setWidth(const int width) {
   SCVComponent::setWidth(width);
}

void ComponentWithTexture::setHeight(const int height) {
   SCVComponent::setHeight(height);
}

void ComponentWithTexture::setDraggable(bool state) {
   SCVComponent::setDraggable(state);
}

void ComponentWithTexture::setResizable(bool state) {
   SCVComponent::setResizable(state);
}

void ComponentWithTexture::setVisible(bool state) {
   SCVComponent::setVisible(state);
}

Point ComponentWithTexture::getSize(void) const {
   return SCVComponent::getSize();
}


} // namespace scv
