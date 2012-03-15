#ifndef __SCV_POINT_H__
#define __SCV_POINT_H__

#include "stdafx.h"

namespace scv {

class Point {
public:
   ///////////////////////////////////////////////////////////
   Point(void);
   Point(int x, int y);
   //[<number>,<number>]
   Point(const std::string &str);

   virtual ~Point(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline Point operator*(int w) const;
   inline Point operator/(int w) const;
   inline Point operator+(int w) const;
   inline Point operator-(int w) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline Point operator+(const Point& rhs) const;
   inline Point operator-(const Point& rhs) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline void operator+=(int w);
   inline void operator-=(int w);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline void operator+=(const Point& rhs);
   inline void operator-=(const Point& rhs);
   inline bool operator!=(const Point& rhs) const;
   inline bool operator==(const Point& rhs) const;
   inline bool operator>=(const Point& rhs) const;
   inline bool operator<=(const Point& rhs) const;
   inline bool operator>(const Point& rhs) const;
   inline bool operator<(const Point& rhs) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   friend std::ostream& operator<<(std::ostream& lhs, const Point& rhs);
   ///////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////
   inline Point & translateX(int w);
   inline Point & translateY(int w);
   ///////////////////////////////////////////////////////////
   
   const Point inverse(void) const;

   ///////////////////////////////////////////////////////////
   int x, y;
   ///////////////////////////////////////////////////////////
};



Point Point::operator*(int w) const {
   return Point(x * w, y * w);
}

Point Point::operator/(int w) const {
   return Point(x / w, y / w);
}

Point Point::operator+(int w) const {
   return Point(x + w, y + w);
}

Point Point::operator+(const Point& rhs) const {
   return Point(x + rhs.x, y + rhs.y);
}

Point Point::operator-(int w) const {
   return Point(x - w, y - w);
}


Point Point::operator-(const Point &rhs) const {
   return Point(x - rhs.x, y - rhs.y);
}

void Point::operator+=(int w) {
   x += w;
   y += w;
}

void Point::operator+=(const Point &rhs) {
   x += rhs.x;
   y += rhs.y;
}

void Point::operator-=(int w) {
   x -= w;
   y -= w;
}

void Point::operator-=(const Point &rhs) {
   x -= rhs.x;
   y -= rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
   return (x != rhs.x || y != rhs.y);
}

bool Point::operator==(const Point &rhs) const {
   return (x == rhs.x && y == rhs.y);
}

bool Point::operator>=(const Point &rhs) const {
   return (x >= rhs.x && y >= rhs.y);
}

bool Point::operator<=(const Point &rhs) const {
   return (x <= rhs.x && y <= rhs.y);
}

bool Point::operator>(const Point &rhs) const {
   return (x > rhs.x && y > rhs.y);
}

bool Point::operator<(const Point &rhs) const {
   return (x < rhs.x && y < rhs.y);
}

Point &Point::translateX(int w)  {
   x += w;
   return *this;
}

Point &Point::translateY(int w)  {
   y += w;
   return *this;
}

} // namespace scv


#endif // __SCV_POINT_H__