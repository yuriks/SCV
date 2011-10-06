#include "stdafx.h"
#include "Canvas.h"

namespace scv {

Canvas::Canvas(const scv::Point &p1, const scv::Point &p2) : ComponentWithoutTexture(p1, p2) {
   setType(Component::canvas);
}

Canvas::~Canvas(void) {}

void Canvas::onMouseClick(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseClick(evt);   
}

void Canvas::onMouseHold(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseHold(evt);
}

void Canvas::onMouseOver(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseOver(evt);
}

void Canvas::onMouseUp(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseUp(evt);
}

void Canvas::onMouseWheel(const scv::MouseEvent &evt) {
   ComponentWithoutTexture::onMouseWheel(evt);
}

void Canvas::onKeyPressed(const scv::KeyEvent &evt) {
   ComponentWithoutTexture::onKeyPressed(evt);
}

void Canvas::onKeyUp(const scv::KeyEvent &evt) {
   ComponentWithoutTexture::onKeyUp(evt);
}

void Canvas::onSizeChange(void) {
   ComponentWithoutTexture::onSizeChange();
}

void Canvas::onPositionChange(void) {
   ComponentWithoutTexture::onPositionChange();
}

void Canvas::render(void) {
   ComponentWithoutTexture::render();
}

void Canvas::update(void) {
   ComponentWithoutTexture::update();
}

} // namespace scv