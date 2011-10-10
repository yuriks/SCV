#include "stdafx.h"
#include "Point.h"
#include "Kernel.h"

#include "util.h"

namespace scv {

Point::Point(void) : x(0), y(0) {
}

Point::Point(int x, int y) : x(x), y(y) {
}

Point::Point(const std::string &str) {
   size_t found = str.find(",");
   x = fromString<int>(str.substr(0, found));
   y = fromString<int>(str.substr(found + 1, str.size() - 1));
}

Point::~Point(void) {
}

std::ostream& operator<<(std::ostream& lhs, const Point& rhs) {
   return (lhs << rhs.x << "," << rhs.y);
}

const Point Point::inverse(void) const {
   return Point(x, Kernel::getInstance()->getHeight() - y);
}

} // namespace scv


