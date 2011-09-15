/*!
\file       Point.h
\brief      Implementation of a Integer Point.
\author     SCV Team
*/

#ifndef __SCV_POINT_H__
#define __SCV_POINT_H__

namespace scv {

/*! A Integer Point to define the component positions and a lot more things.
 * \ingroup util
 */

class Point {
public:
   //! Default Constructor
   Point(void);
   /*! Constructor
   \param x Value grows horizontally
   \param y Value grows vertically
   */
   Point(int x, int y);
   //! Operator "Multiplication"
   Point operator*(int w) const;
   //! Operator "Division"
   Point operator/(int w) const;
   //! Operator "Unary plus"
   Point operator+(int w) const;
   //! Operator "Unary minus"
   Point operator-(int w) const;
   //! Operator "Addition"
   Point operator+(const Point& rhs) const;
   //! Operator "Subtraction"
   Point operator-(const Point& rhs) const;
   //! Operator "Addition assignment"
   void operator+=(int w);
   //! Operator "Subtraction assignment"
   void operator-=(int w);
   //! Operator "Addition assignment"
   void operator+=(const Point& rhs);
   //! Operator "Subtraction assignment"
   void operator-=(const Point& rhs);
   //! Operator "Not equal to"
   bool operator!=(const Point& rhs) const;
   //! Operator "Equal to"
   bool operator==(const Point& rhs) const;
   //! Operator "Greater than or equal to"
   bool operator>=(const Point& rhs) const;
   //! Operator "Less than or equal to"
   bool operator<=(const Point& rhs) const;
   //! Operator "Greater than"
   bool operator>(const Point& rhs) const;
   //! Operator "Less than"
   bool operator<(const Point& rhs) const;

   friend std::ostream& operator<<(std::ostream& lhs, const Point& rhs);
   //! Translates the point in the horizontal direction
   Point & translateX(int w);
   //! Translates the point in the vertical direction
   Point & translateY(int w);
   //! Convert the origin of Y-coordinates
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