#include "VistaMenuStyle.h"

#include "ContextMenu.h"
#include "ColorScheme.h"
#include "Kernel.h"

#include <cassert>

namespace scv {

void VistaMenuStyle::drawMenu(const ContextMenu& menu, int selected_menu) const {
   const ContextMenu::MenuList& menus = menu.getMenus();
   const Point& pos = menu.getCurrPosition();
   const int width = menu.getWidth();
   const int height = menu.getHeight();

   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   _cTexture->enable();
   {
      scheme->applyDefaultModulate();
      // shadow
      _cTexture->display(pos.x + 1, pos.y + 1, 2, width + 2, height + 2);

      // border
      _cTexture->display(pos.x - 1, pos.y - 1, 1, width + 2, height + 2);

      scheme->applyColor(ColorScheme::contextMenu);
      // center
      _cTexture->display(pos.x, pos.y, 0, width, height);

      scheme->applyDefaultModulate();
      // center line
      _cTexture->display(pos.x + s_leftBorder, pos.y + 4, 1, 1, height - 8);

      if (selected_menu != -1) {
         scheme->applyColor(ColorScheme::overComponents);
         //vertical
         _cTexture->display(pos.x + s_borderWidth / 2, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2 + 2, 4, 1, s_menuHeight-4);
         _cTexture->display(pos.x + s_borderWidth / 2 + width - s_borderWidth - 1, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2 + 2, 4, 1, s_menuHeight-4);
         //horizontal
         _cTexture->display(pos.x + s_borderWidth / 2 + 2, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2, 4, width - s_borderWidth-4, 1);
         _cTexture->display(pos.x + s_borderWidth / 2 + 2, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2 + s_menuHeight - 1, 4, width - s_borderWidth-4, 1);

         // pixel border
         _cTexture->display(pos.x + s_borderWidth / 2, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2, 5, 2, 2);
         _cTexture->display(pos.x + s_borderWidth / 2, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2 + s_menuHeight, 5, 2, -2);
         _cTexture->display(pos.x + s_borderWidth / 2 + width - s_borderWidth, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2, 5, -2, 2);
         _cTexture->display(pos.x + s_borderWidth / 2 + width - s_borderWidth, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2 + s_menuHeight, 5, -2, -2);

         // center select
         _cTexture->display(pos.x + s_borderWidth / 2 + 2, pos.y + selected_menu * s_menuHeight + s_borderHeight / 2 + 2, 3, width - s_borderWidth - 4, s_menuHeight - 4);
         scheme->applyDefaultModulate();
      }

      // arrow
      for (int i = 0; i < menus.size(); i++) {
         if (menus[i]->hasSubMenus()) {
            _cTexture->display(pos.x + width - s_borderWidth / 2 - 8, pos.y + i * s_menuHeight + s_menuHeight / 2, 6);
         }
      }
   }
   _cTexture->disable();

   for (int i = 0; i < menus.size(); i++) {
      Label::display(s_leftBorder + pos.x + s_borderHeight, pos.y + i * s_menuHeight + s_borderHeight, menus[i]->getString(), scheme->getColor(ColorScheme::contextMenuFont));

      /*
      if (kernel->getWidth() - (pos.x + width - s_borderWidth + 2) < menus[i]->getWidth()) {
         if (kernel->getHeight() < pos.y + selected_menu * s_menuHeight + menus[i]->getMenus().size() * s_menuHeight + s_borderHeight)
            menus[i]->setPosition(Point(pos.x - menus[i]->getWidth() + s_borderWidth, kernel->getHeight() - (menus[i]->getMenus().size() * s_menuHeight) - s_borderHeight));
         else
            menus[i]->setPosition(Point(pos.x - menus[i]->getWidth() + s_borderWidth, pos.y + i * s_menuHeight));
      } else {
         if (kernel->getHeight() < pos.y + selected_menu * s_menuHeight + menus[i]->_menus.size() * s_menuHeight + s_borderHeight)
            _menus[i]->setPosition(Point(pos.x + width - s_borderWidth + 2, kernel->getHeight()  - (_menus[i]->_menus.size() * s_menuHeight) - s_borderHeight));
         else
            _menus[i]->setPosition(Point(pos.x + width - s_borderWidth + 2, pos.y + i * s_menuHeight));
      }
      */
   }
}


bool VistaMenuStyle::isInsideMenuItem(const ContextMenu& menu, const Point& pos, int item) const {
   return (pos.x >= menu.getCurrPosition().x + 2 && pos.x <= menu.getCurrPosition().x + menu.getWidth() - 2 &&
      pos.y >= menu.getCurrPosition().y + item * s_menuHeight + s_borderHeight/2.f && pos.y <= menu.getCurrPosition().y + item * s_menuHeight + s_menuHeight + s_borderHeight/2.f - 1);
}

Point VistaMenuStyle::getSubmenuPos(const ContextMenu& menu, int menu_index) const {
   static Kernel *kernel = Kernel::getInstance();

   if (kernel->getWidth() - (menu.getCurrPosition().x + menu.getWidth() - s_borderWidth + 2) < menu.getMenus()[menu_index]->getWidth()) {
      if (kernel->getHeight() < menu.getCurrPosition().y + menu_index * s_menuHeight + menu.getMenus()[menu_index]->getMenus().size() * s_menuHeight + s_borderHeight)
         return Point(menu.getCurrPosition().x - menu.getMenus()[menu_index]->getWidth() + s_borderWidth, kernel->getHeight() - (menu.getMenus()[menu_index]->getMenus().size() * s_menuHeight) - s_borderHeight);
      else
         return Point(menu.getCurrPosition().x - menu.getMenus()[menu_index]->getWidth() + s_borderWidth, menu.getCurrPosition().y + menu_index * s_menuHeight);
   } else {
      if (kernel->getHeight() < menu.getCurrPosition().y + menu_index * s_menuHeight + menu.getMenus()[menu_index]->getMenus().size() * s_menuHeight + s_borderHeight)
         return Point(menu.getCurrPosition().x + menu.getWidth() - s_borderWidth + 2, kernel->getHeight() - (menu.getMenus()[menu_index]->getMenus().size() * s_menuHeight) - s_borderHeight);
      else
         return Point(menu.getCurrPosition().x + menu.getWidth() - s_borderWidth + 2, menu.getCurrPosition().y + menu_index * s_menuHeight);
   }
}


int VistaMenuStyle::calcWidth(const ContextMenu& menu) const {
   static const FontTahoma *font = FontTahoma::getInstance();

   int width = 0;

   for (ContextMenu::MenuList::const_iterator i = menu.getMenus().begin(); i != menu.getMenus().end(); ++i) {
      const int str_width = font->getStringLength((*i)->getString());
      if (str_width > width)
         width = str_width;
   }

   return width + s_borderWidth * 5 + s_leftBorder;
}

int VistaMenuStyle::calcHeight(const ContextMenu& menu) const {
   return menu.getMenus().size() * s_menuHeight + s_borderHeight;
}


VistaMenuStyle::VistaMenuStyle()
   : _cTexture(0) {
   createTexture();
}

void VistaMenuStyle::createTexture() {
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
