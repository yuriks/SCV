#include "stdafx.h"
#include "Point.h"
#include "Kernel.h"

namespace scv {

std::ostream& operator<<(std::ostream& lhs, const Point& rhs) {
   return (lhs << "X: " << rhs.x << " Y: " << rhs.y);
}

const Point Point::inverse(void) const {
   static Kernel *kernel = Kernel::getInstance();
   return Point(x, kernel->getHeight() - y);
}

} // namespace scv


