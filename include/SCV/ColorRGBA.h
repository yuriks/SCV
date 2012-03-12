/*!
\file       ColorRGBA.h
\brief      Implementation of a color class.
\author     SCV Team
*/

#ifndef __SCV_COLOR_RGBA_H__
#define __SCV_COLOR_RGBA_H__

namespace scv {

/*! Color class that represents colors as a quadruple of bytes: RGB with alpha.
 */

class ColorRGBA {
public:
   ColorRGBA();
   ColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

   ColorRGBA operator+(unsigned char w) const;
   ColorRGBA operator-(unsigned char w) const;
   bool operator != (const ColorRGBA& rhs);
   bool operator == (const ColorRGBA& rhs);
   inline unsigned char& operator[](int index);
   inline const unsigned char& operator[](int index) const;
   friend std::ostream& operator<<(std::ostream& stream, const ColorRGBA& rhs);

   void toHLS(float hls[]);

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
