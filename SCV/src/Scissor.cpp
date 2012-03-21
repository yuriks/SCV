#include "stdafx.h"
#include "Scissor.h"
#include "Kernel.h"
#include "Mathematic.h"

#include "util.h"

namespace scv {

Scissor::Info::Info(void) {
   x = y = 0;
   width = -1;
   height = -1;
}

Scissor::Info::Info(GLint x, GLint y, GLsizei width, GLsizei height) {
   this->x = x;
   this->y = y;
   this->width = width;
   this->height = height;
}

Scissor::Info::Info(const std::string &str) {
   std::istringstream iss(str);
   std::string word;

   getline( iss, word, ',' );
   x = fromString<int>(trim(word));   
   getline( iss, word, ',' );
   y = fromString<int>(trim(word));
   getline( iss, word, ',' );
   width = fromString<int>(trim(word));
   getline( iss, word, ',' );
   height = fromString<int>(trim(word));
}

void Scissor::pushScissor(const Info &scissor) {
   if (!scissor.isValid()) return;

   _scissorStack.push_front(scissor);

   if (_scissorStack.size() >=2 ) {
      Point scissor11 = Point(_scissorStack[0].x,_scissorStack[0].y);
      Point scissor12 = Point(_scissorStack[0].x + _scissorStack[0].width,_scissorStack[0].y + _scissorStack[0].height);
      Point scissor21 = Point(_scissorStack[1].x,_scissorStack[1].y);
      Point scissor22 = Point(_scissorStack[1].x + _scissorStack[1].width,_scissorStack[1].y + _scissorStack[1].height);

      math::intersectSquare(scissor11, scissor12, scissor21, scissor22);

      _scissorStack[0].x = scissor11.x;
      _scissorStack[0].y = scissor11.y;
      _scissorStack[0].width = scissor12.x - scissor11.x;
      _scissorStack[0].height = scissor12.y - scissor11.y;
   }

   glEnable(GL_SCISSOR_TEST);
   glScissor(_scissorStack[0].x, _scissorStack[0].y, _scissorStack[0].width, _scissorStack[0].height);
}

void Scissor::popScissor(void) {
   if (_scissorStack.size() >= 1) _scissorStack.pop_front();

   if (_scissorStack.size()) {
      glScissor(_scissorStack[0].x, _scissorStack[0].y, _scissorStack[0].width, _scissorStack[0].height);
   } else {
       glDisable(GL_SCISSOR_TEST);
   }
}

const Scissor::Info& Scissor::currentScissor(void) const {
   static const Info scissorInf;
   return _scissorStack.size() ? _scissorStack[0] : scissorInf;
}


bool Scissor::Info::isInside(const Point &p) const {
   return ((height == -1 || width == -1) || (p.x >= x && p.x <= x + width && p.y >= y && p.y <= y + height))? true : false;
}

} // namespace scv
