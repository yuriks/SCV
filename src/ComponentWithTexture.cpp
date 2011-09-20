#include "stdafx.h"
#include "ComponentWithTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithTexture::ComponentWithTexture(const scv::Point &p1, const scv::Point &p2) :
      SCVObject(p1, p2) {
   _cTexture = NULL;

}
ComponentWithTexture::~ComponentWithTexture(void) {
   /*
   if (_cTexture != NULL)
      delete _cTexture;
   /**/
}

void ComponentWithTexture::processMouse(const scv::MouseEvent &evt) {
   SCVObject::processMouse(evt);
}

void ComponentWithTexture::processKey(const scv::KeyEvent &evt) {
   SCVObject::processKey(evt);
}


void ComponentWithTexture::setRelativePosition(const Point &position) {
   SCVObject::setRelativePosition(position);
}

int ComponentWithTexture::getWidth(void) const {
   return SCVObject::getWidth();
}

int ComponentWithTexture::getHeight(void) const {
   return SCVObject::getHeight();
}

void ComponentWithTexture::setWidth(const int width) {
   SCVObject::setWidth(width);
}

void ComponentWithTexture::setHeight(const int height) {
   SCVObject::setHeight(height);
}

void ComponentWithTexture::setDraggable(bool state) {
   SCVObject::setDraggable(state);
}

void ComponentWithTexture::setResizable(bool state) {
   SCVObject::setResizable(state);
}

void ComponentWithTexture::setVisible(bool state) {
   SCVObject::setVisible(state);
}


} // namespace scv
