#include "stdafx.h"
#include "Canvas.h"

namespace scv {

Canvas::Canvas(const scv::Point &p1, const scv::Point &p2) : ComponentWithoutTexture(p1, p2) {
   _type = canvas;
   // none
}

Canvas::Canvas(const scv::Point &p1, unsigned int width, unsigned int height) : ComponentWithoutTexture(p1, Point(p1.x+width,p1.y+height)) {
    _type = canvas;
   // none
}

void Canvas::onMouseClick(const scv::MouseEvent &evt) {/**/}
void Canvas::onMouseHold(const scv::MouseEvent &evt) {/**/}
void Canvas::onMouseOver(const scv::MouseEvent &evt) {/**/}
void Canvas::onMouseUp(const scv::MouseEvent &evt) {/**/}
void Canvas::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void Canvas::onKeyUp(const scv::KeyEvent &evt) {/**/}
void Canvas::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void Canvas::onResizing(void) {/**/}
void Canvas::onDragging(void) {/**/}
void Canvas::render(void) {/*none*/}
void Canvas::update(void) {/*none*/}

} // namespace scv