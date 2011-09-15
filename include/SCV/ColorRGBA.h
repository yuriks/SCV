/*!
\file       ColorRGBA.h
\brief      Implementation of a color class.
\author     SCV Team
*/

#ifndef __SCV_COLOR_RGBA_H__
#define __SCV_COLOR_RGBA_H__

namespace scv {

/*! Color RGBA class implementation.
 */

class ColorRGBA {
public:
   //! Explicit Constructor
   explicit ColorRGBA(void);
   /*! Constructor
   \param r Red channel
   \param g Green channel
   \param b Blue channel
   \param a Opacity channel
   */
   ColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
   //! Copy Constructor
   ColorRGBA(const ColorRGBA& rhs);

   //! Operator "Basic assignment"
   ColorRGBA& operator=(const ColorRGBA& rhs);
   //! Operator "Unary plus"
   ColorRGBA operator+(unsigned char w) const;
   //! Operator "Unary minus"
   ColorRGBA operator-(unsigned char w) const;
   //! Operator "Not equal to"
   bool operator != (const ColorRGBA& rhs);
   //! Operator "Equal to"
   bool operator == (const ColorRGBA& rhs);
   //! Operator "Array subscript"
   inline unsigned char& operator[](int index);
   //! Operator "Array subscript"
   inline const unsigned char& operator[](int index) const;
   //! Operator "Stream insertion"
   friend std::ostream& operator<<(std::ostream& stream, const ColorRGBA& rhs);

   /*! Converts the current color RGB to a new vector in HLS format.
   \param hls The new HLS vector returned by reference
   */
   void toHSL(float hls[]);

   /*! Convert HLS Color to RGB Color
   \param h Hue [0.0 -> 360.0]
   \param l Luminosity [0.0 -> 1.0]
   \param s Saturation [0.0 -> 1.0]
   */
   static ColorRGBA toRGB(double h, double l, double s);

private:
   static double cRGB(double q1, double q2, double hue);
   unsigned char rgba[4];
};

unsigned char& ColorRGBA::operator[](int index) {
   assert(index >= 0 && index < 4);
   return rgba[index];
}

const unsigned char& ColorRGBA::operator[](int index) const {
   assert(index >= 0 && index < 4);
   return rgba[index];
}

} // namespace scv

#endif // __SCV_COLOR_RGBA_H__
