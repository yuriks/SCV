#include "stdafx.h"
#include "Color4f.h"

#include "ColorRGBA.h"

namespace scv {

Color4f::Color4f(void) {
   std::memset(data, 0, sizeof(float) * 4);
}

Color4f::Color4f(float r, float g, float b, float a /*= 1.f*/) {
   data[0] = r;
   data[1] = g;
   data[2] = b;
   data[3] = a;
}

Color4f::Color4f(const ColorRGBA &rhs) {
   data[0] = rhs[0] / 255.f;
   data[1] = rhs[1] / 255.f;
   data[2] = rhs[2] / 255.f;
   data[3] = rhs[3] / 255.f;
}

scv::Color4f Color4f::operator+(float w) const {
   return Color4f(data[0] + w, data[1] + w,
      data[2] + w, data[3] + w);
}

scv::Color4f Color4f::operator-(float w) const {
   return Color4f(data[0] - w, data[1] - w,
      data[2] - w, data[3] - w);
}

Color4f& Color4f::operator+=(float w) {
   data[0] += w;
   data[1] += w;
   data[2] += w;
   data[3] += w;
   return *this;
}

Color4f& Color4f::operator-=(float w) {
   data[0] -= w;
   data[1] -= w;
   data[2] -= w;
   data[3] -= w;
   return *this;
}

std::ostream& operator<<(std::ostream &stream, const Color4f& rhs) {
   return stream << "R:" << rhs[0] << " G:" << rhs[1] << " B:" << rhs[2] << " A:" << rhs[3];
}

} // namespace scv