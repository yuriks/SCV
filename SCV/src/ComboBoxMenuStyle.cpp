#include "ComboBoxMenuStyle.h"

#include "StaticLabel.h"

#include "ContextMenu.h"
#include "ColorScheme.h"
#include "Kernel.h"
#include "ComboBox.h"

namespace scv {

ComboBoxMenuStyle::ComboBoxMenuStyle(void) {
   _menuSpacing  =  0;
   _borderHeight =  0;
   _borderWidth  =  0;
   _horzMargin   =  4;
   _menuHeight   = 13;

   createTexture();
}

void ComboBoxMenuStyle::drawItem(const scv::ContextMenu *menu, int index) const {
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
      _cTexture->display(pos.x, pos.y, 1, width, height);

      scheme->applyColor(ColorScheme::CONTEXTMENU);
      // center
      _cTexture->display(pos.x + 1, pos.y + 1, 0, width - 2, height - 2);

      scheme->applyDefaultModulate();

      if (index != -1) {
         scheme->applyColor(ColorScheme::OVERCOMPONENTS);
         //vertical
         _cTexture->display(pos.x + 2,         pos.y + index * _menuHeight + 2 + 1, 4, 1, _menuHeight-2);
         _cTexture->display(pos.x + width - 3, pos.y + index * _menuHeight + 2 + 1, 4, 1, _menuHeight-2);
         //horizontal
         _cTexture->display(pos.x + 2, pos.y + index * _menuHeight + 2,                4, width-4, 1);
         _cTexture->display(pos.x + 2, pos.y + index * _menuHeight + _menuHeight + 1, 4, width-4, 1);

         // center select
         _cTexture->display(pos.x + 3, pos.y + index * _menuHeight + 3, 3, width - 5, _menuHeight - 1);
         scheme->applyDefaultModulate();
      }
   }
   _cTexture->disable();

   for (int i = 0; i < menus.size(); i++) {
      StaticLabel::display(pos.x + _horzMargin + 1, pos.y + i * _menuHeight + 1, menus[i]->getString(), scheme->getColor(ColorScheme::CONTEXTMENUFONT));
   }
}

int ComboBoxMenuStyle::calculateWidth(const scv::ContextMenu *menu) const {
   return static_cast<const ComboBox::ComboBoxMenu *>(menu)->_host->getWidth();
}

int ComboBoxMenuStyle::calculateHeight(const scv::ContextMenu *menu) const {
   return menu->getMenus().size() * _menuHeight + _borderHeight + 4;
}

void ComboBoxMenuStyle::createTexture(void) {
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

   _cTexture->createTexture();
}

} // namespace scv
