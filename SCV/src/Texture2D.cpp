#include "stdafx.h"
#include "Texture2D.h"


namespace scv {

void Texture2D::drawPoint(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p, const ColorRGBA& color) {
   if (!matrix.isValid(p)) return;
   matrix.set(p, color);
}

void Texture2D::rect(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& color) {
   if (!matrix.isValid(p1) || !matrix.isValid(p2)) return;
   line(matrix, Point(p1.x, p1.y), Point(p2.x, p1.y), color);
   line(matrix, Point(p1.x, p1.y), Point(p1.x, p2.y), color);
   line(matrix, Point(p2.x, p1.y), Point(p2.x, p2.y), color);
   line(matrix, Point(p1.x, p2.y), Point(p2.x, p2.y), color);
}

void Texture2D::rect(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& color, int thickness) {
   if (!matrix.isValid(p1) || !matrix.isValid(p2)) return;
   line(matrix, Point(p1.x, p1.y), Point(p2.x, p1.y), color);
   line(matrix, Point(p1.x, p1.y), Point(p1.x, p2.y), color);
   line(matrix, Point(p2.x, p1.y), Point(p2.x, p2.y), color);
   line(matrix, Point(p1.x, p2.y), Point(p2.x, p2.y), color);

   if (thickness > 1)
      rect(matrix, p1 + 1, p2 - 1, color, thickness - 1);
}

void Texture2D::rectFill(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& color) {
   if (!matrix.isValid(p1) || !matrix.isValid(p2)) return;
   for (int i = p1.y; i <= p2.y; i++) {
      line(matrix, Point(p1.x, i), Point(p2.x, i), color);
   }
}

void Texture2D::rectFill(MatrixTemplate<ColorRGBA>& matrix, const scv::Point &p1, const scv::Point &p2, const ColorRGBA& colorBorder, const ColorRGBA& colorFill) {
   if (!matrix.isValid(p1) || !matrix.isValid(p2)) return;
   rectFill(matrix, p1, p2, colorFill);
   line(matrix, Point(p1.x, p1.y), Point(p2.x, p1.y), colorBorder);
   line(matrix, Point(p1.x, p1.y), Point(p1.x, p2.y), colorBorder);
   line(matrix, Point(p2.x, p1.y), Point(p2.x, p2.y), colorBorder);
   line(matrix, Point(p1.x, p2.y), Point(p2.x, p2.y), colorBorder);
}

void Texture2D::line(MatrixTemplate<ColorRGBA>& matrix, Point p1, Point p2, const ColorRGBA& color) {
   if (!matrix.isValid(p1) || !matrix.isValid(p2)) return;

   bool steep = abs(p2.y - p1.y) > abs(p2.x - p1.x);
   if (steep) {
      std::swap(p1.x, p1.y);
      std::swap(p2.x, p2.y);
   }

   if (p1.x > p2.x) {
      std::swap(p1.x, p2.x);
      std::swap(p1.y, p2.y);
   }

   int deltax = p2.x - p1.x;
   int deltay = abs(p2.y - p1.y);

   int ystep;
   if (p1.y < p2.y) ystep = 1;
   else ystep = -1;

   int error = deltax / 2;
   int y = p1.y;

   if (steep) {
      for (int x = p1.x; x <= p2.x; x++) {
         drawPoint(matrix, Point(y, x), color);
         error -= deltay;
         if (error < 0) {
            y= y + ystep;
            error = error + deltax;
         }
      }
   } else {
      for (int x = p1.x; x <= p2.x; x++) {
         drawPoint(matrix, Point(x, y), color);
         error -= deltay;
         if (error < 0) {
            y= y + ystep;
            error = error + deltax;
         }
      }
   }
}

} // namespace scv