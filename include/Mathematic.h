/*!
\file       Mathematic.h
\brief      Basic operations of mathematics.
\author     SCV Team
*/

#ifndef __SCV_MATHEMATICS_H__
#define __SCV_MATHEMATICS_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Point.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! Mathematic functions
 * \ingroup util
 */

namespace math {

/*!
Product of all positive integers less than or equal to n.
\return Result. If n is negative returns -1.
*/

inline int factorial(int n) {
   if (n < 0) return -1;
   int f = 1;
   for (int i = 2; i <= n; i++) f *= i;
   return f;
}

/*!
Combination is a way of selecting several things out of a larger group,
where (unlike permutations) order does not matter.
\param n Set 'S' of n elements.
\param k Number of k-combinations.
*/
inline int combination(int n, int k) {
   return factorial(n) / (factorial(k) * factorial(n - k));
}

//! Number of k-permutations of n
inline int permutation(int n, int k) {
   return factorial(n) / factorial(n - k);
}

/*!
\verbatim
      P11__________
      |            |
      |       P21__|_______
      |       |    |       |
      |_______|____|       |
              |            |
              |____________|

      p12 = width and height from p11 square.
      p22 = width and height from p21 square.
\endverbatim
*/

/*!
Widths are positive and should grow to right and down.
\return Return true if intersection area not exist.
*/
inline bool isInside(scv::Point p11, scv::Point p12, scv::Point p21, scv::Point p22) {
   if (p12.x <= 0 || p12.y <= 0 || p22.x <= 0 || p22.y <= 0) return true;

   int tx1 = p11.x;
   int ty1 = p11.y;
   int rx1 = p21.x;
   int ry1 = p21.y;
   int tx2 = tx1 + p12.x;
   int ty2 = ty1 + p12.y;
   int rx2 = rx1 + p22.x;
   int ry2 = ry1 + p22.y;

   if (tx1 < rx1) tx1 = rx1;
   if (ty1 < ry1) ty1 = ry1;
   if (tx2 > rx2) tx2 = rx2;
   if (ty2 > ry2) ty2 = ry2;
   if (tx2 < tx1) tx1 = tx2;
   if (ty2 < ty1) ty1 = ty2;

   if (std::abs(tx1 - tx2) * std::abs(ty1 - ty2)) return true;
   return false;
}

//! Return the nearest value from 'p'.
inline double nearestValue(double p, double p1, double p2) {
   if (std::abs(p - p1) < std::abs(p2 - p)) return p1;
   return p2;
}

/*!
\verbatim
      P11__________
      |            |
      |       P21__|_______
      |       |    |       |
      |_______|____P12     |
              |            |
              |____________P22
\endverbatim
*/

//! return New square points by reference.
inline void intersectSquare(scv::Point &p11, scv::Point &p12, scv::Point &p21, scv::Point &p22) {
   if (p11.x < p21.x) p11.x = p21.x;
   if (p11.y < p21.y) p11.y = p21.y;
   if (p12.x > p22.x) p12.x = p22.x;
   if (p12.y > p22.y) p12.y = p22.y;
   if (p12.x < p11.x) p11.x = p12.x;
   if (p12.y < p11.y) p11.y = p12.y;
}

} // namespace math
} // namespace scv

#endif // __SCV_MATHEMATICS_H__