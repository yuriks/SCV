#include "stdafx.h"
#include "ComponentWithoutTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithoutTexture::ComponentWithoutTexture(const scv::Point &p1, const scv::Point &p2) : Component(p1, p2) {}

ComponentWithoutTexture::~ComponentWithoutTexture(void) {}

void ComponentWithoutTexture::onMouseClick(const scv::MouseEvent &evt) {}

void ComponentWithoutTexture::onMouseHold(const scv::MouseEvent &evt) {}

void ComponentWithoutTexture::onMouseOver(const scv::MouseEvent &evt) {}

void ComponentWithoutTexture::onMouseUp(const scv::MouseEvent &evt) {}

void ComponentWithoutTexture::onMouseWheel(const scv::MouseEvent &evt) {}

void ComponentWithoutTexture::onKeyPressed(const scv::KeyEvent &evt) {}

void ComponentWithoutTexture::onKeyUp(const scv::KeyEvent &evt) {}

void ComponentWithoutTexture::onSizeChange(void) {}

void ComponentWithoutTexture::onPositionChange(void) {}

void ComponentWithoutTexture::render(void) {}

void ComponentWithoutTexture::update(void) {}

void ComponentWithoutTexture::display(void) {
   static Scissor *scissor = Scissor::getInstance();

   update();

   if (_isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, getWidth(), getHeight(), 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glViewport(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());

   scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight()));
   glPushAttrib(GL_ALL_ATTRIB_BITS);

   glClearColor(1.f, 1.f, 1.f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glDisable(GL_TEXTURE_2D);

   render();

   glPopAttrib();

   scissor->popScissor();

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);

   if (glUseProgram) glUseProgram(0);

   kernel->applyDefaultTransformMatrix();
}

} // namespace scv