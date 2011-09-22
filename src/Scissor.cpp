#include "stdafx.h"
#include "Scissor.h"
#include "Kernel.h"
#include "Mathematic.h"

namespace scv {

Scissor::Scissor(void) {/**/}

Scissor::~Scissor(void) {/**/}

Scissor::Info::Info(void) {
   mx = my = 0;
   mwidth = -1;
   mheight = -1;
}

Scissor::Info::Info(GLint x, GLint y, GLsizei width, GLsizei height) {
   mx = x; my = y;
   mwidth = width; mheight = height;
}

void Scissor::pushScissor(const Info &scissor) {
   if (!scissor.isValid()) return;

   _scissorStack.push_front(scissor);

   if (_scissorStack.size() >=2 ) {
      Point scissor11 = Point(_scissorStack[0].mx,_scissorStack[0].my);
      Point scissor12 = Point(_scissorStack[0].mx + _scissorStack[0].mwidth,_scissorStack[0].my + _scissorStack[0].mheight);
      Point scissor21 = Point(_scissorStack[1].mx,_scissorStack[1].my);
      Point scissor22 = Point(_scissorStack[1].mx + _scissorStack[1].mwidth,_scissorStack[1].my + _scissorStack[1].mheight);

      math::intersectSquare(scissor11, scissor12, scissor21, scissor22);

      _scissorStack[0].mx = scissor11.x;
      _scissorStack[0].my = scissor11.y;
      _scissorStack[0].mwidth = scissor12.x - scissor11.x;
      _scissorStack[0].mheight = scissor12.y - scissor11.y;
   }

   glEnable(GL_SCISSOR_TEST);
   glScissor(_scissorStack[0].mx, _scissorStack[0].my, _scissorStack[0].mwidth, _scissorStack[0].mheight);
}

void Scissor::popScissor(void) {
   if (_scissorStack.size() >= 1) _scissorStack.pop_front();

   if (_scissorStack.size()) {
      glScissor(_scissorStack[0].mx, _scissorStack[0].my, _scissorStack[0].mwidth, _scissorStack[0].mheight);
   } else {
       glDisable(GL_SCISSOR_TEST);
   }
}

const Scissor::Info& Scissor::currentScissor(void) const {
   static const Info scissorInf;
   return _scissorStack.size() ? _scissorStack[0] : scissorInf;
}


bool Scissor::Info::isInside(const Point &p) const {
   return ((mheight == -1 || mwidth == -1) || (p.x >= mx && p.x <= mx + mwidth && p.y >= my && p.y <= my + mheight))? true : false;
}

} // namespace scv
