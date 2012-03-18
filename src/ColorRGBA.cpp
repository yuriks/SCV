#include "stdafx.h"
#include "ColorRGBA.h"

namespace scv {

//! Constructs a ColorRGBA initialized to fully transparent black.
ColorRGBA::ColorRGBA() {
   std::fill_n(&rgba[0], 4, 0);
}

ColorRGBA::ColorRGBA(
   unsigned char r, //!< Red channel
   unsigned char g, //!< Green channel
   unsigned char b, //!< Blue channel
   unsigned char a  //!< Alpha (opacity) channel
) {
   rgba[0] = r;
   rgba[1] = g;
   rgba[2] = b;
   rgba[3] = a;
}

ColorRGBA ColorRGBA::operator-(unsigned char w) const {
   return ColorRGBA(
      ((rgba[0] - w < 0)? 0 : rgba[0] - w),
      ((rgba[1] - w < 0)? 0 : rgba[1] - w),
      ((rgba[2] - w < 0)? 0 : rgba[2] - w),
      ((rgba[3] - w < 0)? 0 : rgba[3] - w)
      );
}

ColorRGBA ColorRGBA::operator+(unsigned char w) const {
   return ColorRGBA(
      ((rgba[0] + w > 255)? 255 : rgba[0] + w),
      ((rgba[1] + w > 255)? 255 : rgba[1] + w),
      ((rgba[2] + w > 255)? 255 : rgba[2] + w),
      ((rgba[3] + w > 255)? 255 : rgba[3] + w)
      );
}

std::ostream& operator<<(std::ostream& stream, const ColorRGBA& rhs) {
   return stream << " R: " << (int)rhs[0] << " G: " << (int)rhs[1]
                 << " B: " << (int)rhs[2] << " A: " << (int)rhs[3]
                 << std::endl;
}

bool ColorRGBA::operator != (const ColorRGBA& rhs) {
   return rgba[0] == rhs[0] &&
          rgba[1] == rhs[1] &&
          rgba[2] == rhs[2] &&
          rgba[3] == rhs[3];
}

bool ColorRGBA::operator == (const ColorRGBA& rhs) {
   return rgba[0] == rhs[0] &&
          rgba[1] == rhs[1] &&
          rgba[2] == rhs[2] &&
          rgba[3] == rhs[3];
}

/*! Converts the RGB color to HLS (Hue-Lightness-Saturation) format.
\param hls The output color vector. Indices 0 through 2 will have the hue, saturation and lightness, respectively.

%Example: \code
   ColorRGBA color;
   float hls_col[3];
   color.toHLS(hls_col);
   std::cout <<
      "Hue: "         << hls_col[0] <<
      " Lightness: "  << hls_col[1] <<
      " Saturation: " << hls_col[2] << std::endl;
\endcode
*/
void ColorRGBA::toHLS(float hls[]) {
   float max, min,dif;
   float r_dist, g_dist, b_dist;

   float r = rgba[0] / 255.f;
   float g = rgba[1] / 255.f;
   float b = rgba[2] / 255.f;

   max = std::max(r, std::max(g,b));
   min = std::min(r, std::min(g,b));
   dif = max-min;
   hls[1] = (max + min) / 2.f;

   if(std::abs(dif) < 0.00000001f) {
      hls[2] = 0.f;
      hls[0] = 0.f;
   } else {
      if(hls[1] <= .5f) {
         hls[2] = dif / (max + min);
      } else {
         hls[2] = dif / (2 - max - min);
      }
      r_dist = (max - r) / dif;
      g_dist = (max - g) / dif;
      b_dist = (max - b) / dif;
      if (r == max) {
         hls[0] = b_dist - g_dist;
      } else if (g==max) {
         hls[0] = 2 + r_dist - b_dist;
      } else if (b==max) {
         hls[0] = 4 + g_dist - r_dist;
      }
      hls[0] *= 60.0;
      if(hls[0] < 0.f) hls[0] += 360.f;
      hls[0] /= 360.f;
   }
}

/*! Converts a HLS color value to a ColorRGBA.
\param h Hue [0.0 -> 360.0]
\param l Lightness [0.0 -> 1.0]
\param s Saturation [0.0 -> 1.0]
*/
ColorRGBA ColorRGBA::toRGB(float h, float l, float s) {
   if (s == 0) {
      return ColorRGBA((int)(l * 255.f), (int)(l * 255.f), (int)(l * 255.f));
   } else {
      float p1, p2;

      if (l <= .5f) {
         p2 = l * (1 + s);
      } else {
         p2 = l + s - l * s;
      }

      p1 = 2.f * l - p2;

      return ColorRGBA(
         (int)(cRGB(p1, p2, h + 120.f) * 255.f),
         (int)(cRGB(p1, p2, h)         * 255.f),
         (int)(cRGB(p1, p2, h - 120.f) * 255.f)
         );
   }
}

float ColorRGBA::cRGB(float q1, float q2, float hue) {
   if(hue > 360.f) {
      hue -= 360.f;
   } else if(hue < 0.f) {
      hue += 360.f;
   }

   if(hue < 60.f) {
      return (q1 + (q2 - q1) * hue / 60.f);
   } else if (hue < 180.f) {
      return q2;
   } else if (hue < 240.f) {
      return (q1 + (q2 - q1) * (240.f - hue) / 60.f);
   } else return q1;
}

} // namespace scv

