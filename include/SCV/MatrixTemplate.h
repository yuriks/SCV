/*!
\file       MatrixTemplate.h
\brief      Implementation of a Generic Matrix.
\author     SCV Team
*/

#ifndef __SCV_MATRIX_TEMPLATE_H__
#define __SCV_MATRIX_TEMPLATE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Point.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A generic object matrix with basic functions.
 * \ingroup util
 */
template <typename T>
class MatrixTemplate {
public:

   virtual ~MatrixTemplate(void) {}

   //! Default Constructor
   MatrixTemplate(void) : _width(0), _height(0) {
      //none
   }
   /*! Constructor
   \param width Width of the matrix.
   \param height Height of the matrix.
   */
   MatrixTemplate(unsigned int width, unsigned int height) : _width(width), _height(height) {
      _data.resize(_width * _height);
   }
   /*! Constructor
   \param width Width of the matrix.
   \param height Height of the matrix.
   \param rhs The initialization value of the matrix.
   */
   MatrixTemplate(unsigned int width, unsigned int height, const T& rhs) : _width(width), _height(height) {
      _data.resize(_width * _height, rhs);
   }
   //! Copy Constructor
   MatrixTemplate(const MatrixTemplate &rhs) : _width(rhs._width), _height(rhs._height) {
      _data = rhs._data;
   }
   //! Operator "Basic Assignment"
   MatrixTemplate& operator=(const MatrixTemplate &rhs) {
      if (this != &rhs) {
         _data = rhs._data;
         const_cast<unsigned int&>(_width) = rhs._width;
         const_cast<unsigned int&>(_height) = rhs._height;
      }
      return *this;
   }
   //! Operator "Function Call"
   inline T& operator()(unsigned int l, unsigned int c) {
      return _data[l * _width + c];
   }
   //! Operator "Equal To"
   bool operator==(const MatrixTemplate<T>& rhs) const {
      return(_data == rhs._data)? true : false;
   }
   //! Gets the width of the matrix.
   inline int getWidth(void) const {
      return _width;
   }
   //! Gets the height of the matrix.
   inline int getHeight(void) const {
      return _height;
   }
   /*! Gets one element of the matrix by reference.
   \param l Line
   \param c Column
   */
   inline T &get(unsigned int l, unsigned int c) {
      return _data[l * _width + c];
   }
   //! Gets the data vector of the matrix by reference;
   inline std::vector<T> &getData(void) {
      return _data;
   }
   //! Sets a new object to a specified position of the matrix.
   inline void set(const scv::Point &p, T rhs) {
      _data[p.y * _width + p.x] = rhs;
   }
   //! Sets a new object to a specified position of the matrix.
   inline void set(unsigned int l, unsigned int c, T rhs) {
      _data[l * _width + c] = rhs;
   }
   //! Gets a boolean that specifies if the input position of the matrix is valid.
   inline bool isValid(const scv::Point &p) {
      return (p.y >=0 && p.y < _height && p.x >= 0 && p.x < _width)? true : false;
   }
   //! Gets a boolean that specifies if the input position of the matrix is valid.
   inline bool isValid(unsigned int l, unsigned int c) {
      return (l < _height && c < _width)? true : false;
   }
   /*! Resize the matrix
   \param l New number of lines.
   \param c New number of columns.
   */
   inline void resize(unsigned int l, unsigned int c) {
      _data.resize(l * c);
      _width = c;
      _height = l;
   }

protected:
   unsigned int _width, _height;
   std::vector<T> _data;
};

} // namespace scv


#endif // __SCV_MATRIX_TEMPLATE_H__
