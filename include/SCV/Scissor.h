#ifndef __SCV_SCISSOR_H__
#define __SCV_SCISSOR_H__

#include "Singleton.h"
#include "Point.h"

namespace scv {

class Scissor : public Singleton<Scissor> {
friend class Singleton<Scissor>;
public:
   class  Info {
   public:
      ///////////////////////////////////////////////////////////
      Info(void);
      Info(GLint x, GLint y, GLsizei width, GLsizei height);
      //[<number>,<number>,<number>,<number>]
      Info(const std::string &str);
      ///////////////////////////////////////////////////////////

      bool isInside(const Point &p) const;
      inline bool isValid(void) const {
         return (height == -1 || height == -1) ? false : true;
      }

      inline Point getPosition(void) {
         return Point(x, y);
      }

      inline void operator+=(const Point &p) {
         x += p.x; y += p.y;
      }

      friend std::ostream& operator<<(std::ostream& stream, const Info& rhs) {
          return (stream << rhs.x << "," << rhs.y << "," << rhs.width << "," << rhs.height);
      }

      GLint x, y;
      GLsizei width, height;
   };

   void pushScissor(const Info &scissor);
   void popScissor(void);
   const Info& currentScissor(void) const;

private:
   Scissor(void);
   ~Scissor(void);

   std::deque<Info> _scissorStack;
};

} // namespace scv

#endif // __SCV_SCISSOR_H__