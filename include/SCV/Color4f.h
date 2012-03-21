#ifndef __SCV_COLOR_4F_H__
#define __SCV_COLOR_4F_H__

namespace scv {

class ColorRGBA;

/*! Color class implementation.
 */

class Color4f {
public:
   explicit Color4f(void);
   Color4f(float r, float g, float b, float a = 1.f);
   Color4f(const ColorRGBA &rhs);

   Color4f operator+(float w) const;
   Color4f operator-(float w) const;
   Color4f& operator+=(float w);
   Color4f& operator-=(float w);

   inline float& operator[](int index);
   inline const float& operator[](int index) const;

   friend std::ostream& operator<<(std::ostream &stream, const Color4f& rhs);

   static Color4f fromByte(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
   {
      return Color4f(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
   }

private:
   float data[4];
};

float& Color4f::operator[](int index) {
   assert(index >= 0 && index < 4);
   return data[index];
}

const float& Color4f::operator[](int index) const  {
   assert(index >= 0 && index < 4);
   return data[index];
}

} // namespace scv

#endif // __SCV_COLOR_4F_H__