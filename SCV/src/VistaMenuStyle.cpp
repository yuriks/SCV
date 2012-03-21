#include "VistaMenuStyle.h"

#include "StaticLabel.h"

#include "ContextMenu.h"
#include "ColorScheme.h"
#include "Kernel.h"

namespace scv {

VistaMenuStyle::VistaMenuStyle(void) {
   _menuSpacing  = 10;
   _borderHeight =  8;
   _borderWidth  =  8;
   _leftBorder   = 28;
   _menuHeight   = 22;

   createTexture();
}

void VistaMenuStyle::drawItem(const scv::ContextMenu *menu, int index) const {
   const ContextMenu::MenuList& menus = menu->getMenus();
   const Point& pos = menu->getCurrPosition();
   const int width = menu->getWidth();
   const int height = menu->getHeight();

   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   _cTexture->enable();
   {
      scheme->applyDefaultModulate();
      // shadow
      _cTexture->display(pos.x + 1, pos.y + 1, 2, width + 2, height + 2);

      // border
      _cTexture->display(pos.x - 1, pos.y - 1, 1, width + 2, height + 2);

      scheme->applyColor(ColorScheme::CONTEXTMENU);
      // center
      _cTexture->display(pos.x, pos.y, 0, width, height);

      scheme->applyDefaultModulate();
      // center line
      _cTexture->display(pos.x + _leftBorder, pos.y + 4, 1, 1, height - 8);

      if (index != -1) {
         scheme->applyColor(ColorScheme::OVERCOMPONENTS);
         //vertical
         _cTexture->display(pos.x + _borderWidth / 2, pos.y + index * _menuHeight + _borderHeight / 2 + 2, 4, 1, _menuHeight-4);
         _cTexture->display(pos.x + _borderWidth / 2 + width - _borderWidth - 1, pos.y + index * _menuHeight + _borderHeight / 2 + 2, 4, 1, _menuHeight-4);
         //horizontal
         _cTexture->display(pos.x + _borderWidth / 2 + 2, pos.y + index * _menuHeight + _borderHeight / 2, 4, width - _borderWidth-4, 1);
         _cTexture->display(pos.x + _borderWidth / 2 + 2, pos.y + index * _menuHeight + _borderHeight / 2 + _menuHeight - 1, 4, width - _borderWidth-4, 1);

         // pixel border
         _cTexture->display(pos.x + _borderWidth / 2, pos.y + index * _menuHeight + _borderHeight / 2, 5, 2, 2);
         _cTexture->display(pos.x + _borderWidth / 2, pos.y + index * _menuHeight + _borderHeight / 2 + _menuHeight, 5, 2, -2);
         _cTexture->display(pos.x + _borderWidth / 2 + width - _borderWidth, pos.y + index * _menuHeight + _borderHeight / 2, 5, -2, 2);
         _cTexture->display(pos.x + _borderWidth / 2 + width - _borderWidth, pos.y + index * _menuHeight + _borderHeight / 2 + _menuHeight, 5, -2, -2);

         // center select
         _cTexture->display(pos.x + _borderWidth / 2 + 2, pos.y + index * _menuHeight + _borderHeight / 2 + 2, 3, width - _borderWidth - 4, _menuHeight - 4);
         scheme->applyDefaultModulate();
      }

      // arrow
      for (int i = 0; i < menus.size(); i++) {
         if (menus[i]->hasSubMenus()) {
            _cTexture->display(pos.x + width - _borderWidth / 2 - 8, pos.y + i * _menuHeight + _menuHeight / 2, 6);
         }
      }
   }
   _cTexture->disable();

   for (int i = 0; i < menus.size(); i++) {
      StaticLabel::display(_leftBorder + pos.x + _borderHeight, pos.y + i * _menuHeight + _borderHeight, menus[i]->getString(), scheme->getColor(ColorScheme::CONTEXTMENUFONT));
   }
}

int VistaMenuStyle::calculateWidth(const scv::ContextMenu *menu) const {
   int width = 0;

   for (ContextMenu::MenuList::const_iterator i = menu->getMenus().begin(); i != menu->getMenus().end(); ++i) {
      const int str_width = FontTahoma::getInstance()->getStringLength((*i)->getString());
      if (str_width > width) width = str_width;
   }

   return width + _borderWidth * 5 + _leftBorder;
}

int VistaMenuStyle::calculateHeight(const scv::ContextMenu *menu) const {
   return menu->getMenus().size() * _menuHeight + _borderHeight;
}


void VistaMenuStyle::createTexture(void) {
   assert(_cTexture == 0);

   // create texture object
   _cTexture = new ComponentTexture(16, 8);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   MatrixTemplate<ColorRGBA> center(1, 1, ColorRGBA(240,240,240,255));
   _cTexture->addTexture(Point(0,0), center); // 0

   MatrixTemplate<ColorRGBA> border(1, 1, ColorRGBA(151,151,151,255));
   _cTexture->addTexture(Point(1,0), border); // 1

   MatrixTemplate<ColorRGBA> shadow(1, 1, ColorRGBA(0,0,0,255));
   _cTexture->addTexture(Point(2,0), shadow); // 2

   // over
   MatrixTemplate<ColorRGBA> overCenter(1,1, ColorRGBA(240,240,240,50));
   _cTexture->addTexture(Point(3,0), overCenter); // 3

   MatrixTemplate<ColorRGBA> overBorder(1,1, ColorRGBA(210,210,210,150));
   _cTexture->addTexture(Point(4,0), overBorder); // 4

   MatrixTemplate<ColorRGBA> pixelBorder(2,2, ColorRGBA(220,220,220,100));
   Texture2D::drawPoint(pixelBorder, Point(0, 0),ColorRGBA(0,0,0,0));
   _cTexture->addTexture(Point(5,0), pixelBorder); // 5

   // arrow
   MatrixTemplate<ColorRGBA> arrow(5, 7, ColorRGBA(0,0,0,0));
   Texture2D::rectFill(arrow,Point(0, 0),Point(4, 6),ColorRGBA(0,0,0,0));
   Texture2D::line(arrow, Point(0, 0),Point(0, 6),ColorRGBA(0,0,0,255));
   Texture2D::line(arrow, Point(1, 1),Point(1, 5),ColorRGBA(0,0,0,255));
   Texture2D::line(arrow, Point(2, 2),Point(2, 4),ColorRGBA(0,0,0,255));
   Texture2D::line(arrow, Point(3, 3),Point(3, 3),ColorRGBA(0,0,0,255));
   _cTexture->addTexture(Point(7,0), arrow); // 6

   _cTexture->createTexture();
}

} // namespace scv
