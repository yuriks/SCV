#ifndef __SCV_SCISSOR_H__
#define __SCV_SCISSOR_H__

#include "Singleton.h"
#include "Point.h"

namespace scv {

class Scissor : public Singleton<Scissor> {
friend class Singleton<Scissor>;
public:
   class  ScissorInfo {
   public:
      ScissorInfo(void);
      ScissorInfo(GLint x, GLint y, GLsizei width, GLsizei height);

      bool isInside(const Point &p) const;
      inline bool isValid(void) const {
         return (mheight == -1 || mheight == -1) ? false : true;
      }

      inline Point getPosition(void) {
         return Point(mx, my);
      }

      inline void operator+=(const Point &p) {
         mx += p.x; my += p.y;
      }

      friend std::ostream& operator<<(std::ostream& stream, const ScissorInfo& rhs) {
          return (stream << "X: " << rhs.mx << " Y: " << rhs.my << " Width: " << rhs.mwidth << " Height: " << rhs.mheight);
      }

      GLint mx, my;
      GLsizei mwidth, mheight;
   };

   void pushScissor(const ScissorInfo &scissor);
   void popScissor(void);
   const ScissorInfo& currentScissor(void) const;

private:
   Scissor(void);
   ~Scissor(void);

   std::deque<ScissorInfo> _scissorStack;
};

} // namespace scv

#endif // __SCV_SCISSOR_H__