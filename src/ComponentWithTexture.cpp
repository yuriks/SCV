#include "stdafx.h"
#include "ComponentWithTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithTexture::ComponentWithTexture(const scv::Point &p1, const scv::Point &p2) :
      ComponentInterface(p1, p2) {
   Kernel::getInstance()->requestComponentLoad(this);
   _cTexture = NULL;
}
ComponentWithTexture::~ComponentWithTexture(void) {
   //delete _cTexture;
}

void ComponentWithTexture::processMouse(const scv::MouseEvent &evt) {
   ComponentInterface::processMouse(evt);
}

void ComponentWithTexture::processKey(const scv::KeyEvent &evt) {
   ComponentInterface::processKey(evt);
}

void ComponentWithTexture::createTexture(void) {/**/}

void ComponentWithTexture::setRelativePosition(const Point &position) {
   ComponentInterface::setRelativePosition(position);
}

int ComponentWithTexture::getWidth(void) const {
   return ComponentInterface::getWidth();
}

int ComponentWithTexture::getHeight(void) const {
   return ComponentInterface::getHeight();
}

void ComponentWithTexture::setWidth(const int width) {
   ComponentInterface::setWidth(width);
}

void ComponentWithTexture::setHeight(const int height) {
   ComponentInterface::setHeight(height);
}

void ComponentWithTexture::setDraggable(bool state) {
   ComponentInterface::setDraggable(state);
}

void ComponentWithTexture::setResizable(bool state) {
   ComponentInterface::setResizable(state);
}

void ComponentWithTexture::setVisible(bool state) {
   ComponentInterface::setVisible(state);
}


} // namespace scv
