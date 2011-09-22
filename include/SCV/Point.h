#ifndef __SCV_POINT_H__
#define __SCV_POINT_H__

namespace scv {

class Point {
public:
   Point(void);
   Point(int x, int y);

   Point operator*(int w) const;
   Point operator/(int w) const;
   Point operator+(int w) const;
   Point operator-(int w) const;

   Point operator+(const Point& rhs) const;
   Point operator-(const Point& rhs) const;

   void operator+=(int w);
   void operator-=(int w);

   void operator+=(const Point& rhs);
   void operator-=(const Point& rhs);
   bool operator!=(const Point& rhs) const;
   bool operator==(const Point& rhs) const;
   bool operator>=(const Point& rhs) const;
   bool operator<=(const Point& rhs) const;
   bool operator>(const Point& rhs) const;
   bool operator<(const Point& rhs) const;

   friend std::ostream& operator<<(std::ostream& lhs, const Point& rhs);
   
   Point & translateX(int w);
   Point & translateY(int w);
   
   const Point inverse(void) const;

   int x, y;
};

inline Point::Point(void)
   : x(0), y(0) {
}

inline Point::Point(int x, int y)
   : x(x), y(y) {
}

inline Point Point::operator*(int w) const {
   return Point(x * w, y * w);
}

inline Point Point::operator/(int w) const {
   return Point(x / w, y / w);
}

inline Point Point::operator+(int w) const {
   return Point(x + w, y + w);
}

inline Point Point::operator+(const Point& rhs) const {
   return Point(x + rhs.x, y + rhs.y);
}

inline Point Point::operator-(int w) const {
   return Point(x - w, y - w);
}


inline Point Point::operator-(const Point& rhs) const {
   return Point(x - rhs.x, y - rhs.y);
}

inline void Point::operator+=(int w) {
   x += w;
   y += w;
}

inline void Point::operator+=(const Point& rhs) {
   x += rhs.x;
   y += rhs.y;
}

inline void Point::operator-=(int w) {
   x -= w;
   y -= w;
}

inline void Point::operator-=(const Point& rhs) {
   x -= rhs.x;
   y -= rhs.y;
}

inline bool Point::operator!=(const Point& rhs) const {
   return (x != rhs.x || y != rhs.y);
}

inline bool Point::operator==(const Point& rhs) const {
   return (x == rhs.x && y == rhs.y);
}

inline bool Point::operator>=(const Point& rhs) const {
   return (x >= rhs.x && y >= rhs.y);
}

inline bool Point::operator<=(const Point& rhs) const {
   return (x <= rhs.x && y <= rhs.y);
}

inline bool Point::operator>(const Point& rhs) const {
   return (x > rhs.x && y > rhs.y);
}

inline bool Point::operator<(const Point& rhs) const {
   return (x < rhs.x && y < rhs.y);
}

inline Point & Point::translateX(int w)  {
   x += w;
   return *this;
}

inline Point & Point::translateY(int w)  {
   y += w;
   return *this;
}

} // namespace scv


#endif // __SCV_POINT_H__