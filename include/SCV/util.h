/*!
\file       util.h
\brief      Implementation of useful functions.
\author     SCV Team
*/

#ifndef __SCV_UTIL_H__
#define __SCV_UTIL_H__

#include <sstream>

namespace scv {

/*! Transform a number value of generic type in a string
 * \ingroup util
 */
template<class T>
std::string toString(T rhs) {
   std::stringstream stream;
   stream << rhs;
   return stream.str();
}

/*! Transform a string to a number value of generic type
 * \ingroup util
 */
template<class T>
T fromString(const std::string &str) {
   std::istringstream stream (str);
   T classType;
   stream >> classType;
   return classType;
}


} // namespace scv

#endif // __SCV_UTIL_H__