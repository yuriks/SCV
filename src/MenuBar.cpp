#include "stdafx.h"
#include "MenuBar.h"
#include "Kernel.h"
#include "MenuHolder.h"
#include "StaticLabel.h"

namespace scv {

const int MenuBar::s_menuHeight   = 22;
const int MenuBar::s_menuSpacing  = 18;
const int MenuBar::s_borderWidth  = 8;
const int MenuBar::s_borderHeight = 5;

MenuBar::MenuBar(int width) : Panel(Point(0, 0),Point(width, s_menuHeight)) {
   _isVResizable = false;
   _active = false;
   _index.push_back(s_borderWidth);
   _currSelectedMenu = -1;
   _currecOverMenu = -1;
   _type = MENUBAR;

   createTexture();
}

void MenuBar::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();

   if (!_receivingCallbacks) {
      Component::processMouse(evt);
   } else {
      Panel::processMouse(evt);
   }

   if(!_receivingCallbacks) return;

   Point currPosition = getAbsolutePosition();
   Point relativeMouse = evt.getPosition();

   // open menu
   if (isInside(evt.getPosition())) {
      if (kernel->requestMouseUse(this)) {
         if (isFocused()) {
            if (evt.getState() == MouseEvent::CLICK && evt.getButton() == MouseEvent::LEFT) {
               for (int i = 0; i < _menus.size(); i++) {
                  if (relativeMouse.x > _index[i] + currPosition.x && relativeMouse.x < _index[i+1] + currPosition.x
                        && relativeMouse.y > s_borderHeight/2-1 + currPosition.y && relativeMouse.y < currPosition.y + getHeight() - 2) {
                     menu->closeAllMenus();
                     _active = !_active;
                     _menus[i]->_status = !_menus[i]->_status;
                     if (_active) {
                        _currSelectedMenu = i;
                        return;
                     } else {
                        _currSelectedMenu = -1;
                        menu->closeAllMenus();
                        _active = false;
                        return;
                     }
                  }
               }
            }
         }

         // select menu ifActive
         if (_active) {
            for (int i = 0; i < _menus.size(); i++) {
               if (relativeMouse.x > _index[i] + currPosition.x && relativeMouse.x < _index[i+1] + currPosition.x
                     && relativeMouse.y > s_borderHeight/2-1 + currPosition.y && relativeMouse.y < currPosition.y + getHeight() - 2) {
                  menu->closeAllMenus();
                  _currSelectedMenu = i;
                  _menus[i]->_status = true;
                  break;
               }
            }
         }

         // over menu
         _currecOverMenu = -1;
         for (int i = 0; i < _menus.size(); i++) {
            if (relativeMouse.x > _index[i] + currPosition.x && relativeMouse.x < _index[i+1] + currPosition.x
                  && relativeMouse.y > s_borderHeight/2-1 + currPosition.y && relativeMouse.y < currPosition.y + getHeight() - 2) {
               _currecOverMenu = i;
               break;
            }
         }
      }
   } else {
      _currecOverMenu = -1;
   }

   for (int i = 0; i < _menus.size() ; i++) {
   	if (_menus[i]->getStatus()) return;
   }
   _active = false;
   _currSelectedMenu = -1;
}

void MenuBar::processKey(const scv::KeyEvent &evt) {
   static MenuHolder *menu = MenuHolder::getInstance();

   if (evt.getState() == KeyEvent::UP || _currSelectedMenu == -1) return;
   if(!_receivingCallbacks) return;

   ContextMenu * cMenu = _menus[_currSelectedMenu];

   while (cMenu->hasSubMenuActive())
      cMenu = cMenu->_list[cMenu->_currSelectedMenu];

   if (evt.getKeyString() == "Left" && !cMenu->_recentlyChange) {
      if (_currSelectedMenu == 0) _currSelectedMenu = _menus.size() - 1;
      else _currSelectedMenu--;
      menu->closeAllMenus();
      _menus[_currSelectedMenu]->_status = true;
      _menus[_currSelectedMenu]->_currSelectedMenu = 0;
   } else if (evt.getKeyString() == "Right" && ((cMenu->_currSelectedMenu != -1 && !cMenu->_list[cMenu->_currSelectedMenu]->hasSubMenus() && !cMenu->_recentlyChange) ||
         cMenu->_currSelectedMenu == -1)) {
      _currSelectedMenu = (_currSelectedMenu + 1) % _menus.size();
      menu->closeAllMenus();
      _menus[_currSelectedMenu]->_status = true;
      _menus[_currSelectedMenu]->_currSelectedMenu = 0;
   }
}

void MenuBar::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   Scissor::Info scissorInfo(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());
   scissor->pushScissor(scissorInfo);

   _cTexture->enable();

   // background
   scheme->applyColor(ColorScheme::MENUBAR);
   _cTexture->display(currPosition.x, currPosition.y , 0, getWidth(), getHeight());

   // line bottom
   glColor3f(0.f,0.f,0.f);
   _cTexture->display(currPosition.x, currPosition.y + getHeight() - 1, 4, getWidth(), 1);

   if (_currecOverMenu != -1 && _currSelectedMenu == -1) {

      int size = _index[_currecOverMenu+1]-_index[_currecOverMenu];

      scheme->applyColor(ColorScheme::OVERCOMPONENTS);

      //vertical
      _cTexture->display(currPosition.x + _index[_currecOverMenu] + size - 1, currPosition.y + s_borderHeight/2 + 2, 2, 1, s_menuSpacing - 4);
      _cTexture->display(currPosition.x + _index[_currecOverMenu]           , currPosition.y + s_borderHeight/2 + 2, 2, 1, s_menuSpacing - 4);
      //horizontal
      _cTexture->display(currPosition.x + _index[_currecOverMenu] + 2       , currPosition.y + s_borderHeight/2, 2, size - 4, 1);
      _cTexture->display(currPosition.x + _index[_currecOverMenu] + 2       , currPosition.y + s_menuHeight - 3, 2, size - 4, 1);

      // pixel border
      _cTexture->display(currPosition.x + _index[_currecOverMenu]           , currPosition.y + s_borderHeight / 2       , 3, 2, 2);
      _cTexture->display(currPosition.x + _index[_currecOverMenu]           , currPosition.y + s_menuHeight -2        , 3, 2, -2);
      _cTexture->display(currPosition.x + _index[_currecOverMenu] + size    , currPosition.y + s_borderHeight / 2, 3,-2,  2);
      _cTexture->display(currPosition.x + _index[_currecOverMenu] + size    , currPosition.y + s_menuHeight - 2, 3,-2, -2);

      // center select
      _cTexture->display(currPosition.x + _index[_currecOverMenu] + 2       , currPosition.y + s_borderHeight/2 + 2, 1, size - 4, s_menuSpacing - 4);
      scheme->applyDefaultModulate();
   } else if (_currSelectedMenu != -1) {
      int size = _index[_currSelectedMenu + 1] - _index[_currSelectedMenu];

      scheme->applyColor(ColorScheme::CONTEXTMENU);

      _cTexture->display(currPosition.x + _index[_currSelectedMenu] + 2, currPosition.y + s_borderHeight/2, 4, size - 4, 1);
      _cTexture->display(currPosition.x + _index[_currSelectedMenu] + 1, currPosition.y + s_borderHeight/2 + 1, 4, size - 2, 1);
      _cTexture->display(currPosition.x + _index[_currSelectedMenu]    , currPosition.y + s_borderHeight/2 + 2, 4, size, s_menuSpacing);

      scheme->applyDefaultModulate();
   }

   _cTexture->disable();

   for (int i = 0; i < _menus.size(); i++) {
      if (i == _currSelectedMenu) {
         StaticLabel::display(currPosition.x + s_borderWidth + _index[i], currPosition.y + s_borderHeight, _menus[i]->_label, scheme->getColor(ColorScheme::CONTEXTMENUFONT));
      } else {
         StaticLabel::display(currPosition.x + s_borderWidth + _index[i], currPosition.y + s_borderHeight, _menus[i]->_label);
      }
      _menus[i]->setPosition(Point(currPosition.x + _index[i], currPosition.y + getHeight() + 1));
      _menus[i]->display();
   }

   scissor->popScissor();
}



void MenuBar::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(Kernel::menuBar)) != NULL) return;

   _cTexture = new ComponentTexture(5, 2);
   kernel->setWidgetTexture(Kernel::menuBar, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // background
   MatrixTemplate<ColorRGBA> middle(1, 1, ColorRGBA(200,200,200,255));
   _cTexture->addTexture(Point(0,0), middle); // 0

   // over
   MatrixTemplate<ColorRGBA> overCenter(1,1, ColorRGBA(240,240,240,50));
   _cTexture->addTexture(Point(1,0), overCenter); // 1

   MatrixTemplate<ColorRGBA> overBorder(1,1, ColorRGBA(210,210,210,150));
   _cTexture->addTexture(Point(0,1), overBorder); // 2

   MatrixTemplate<ColorRGBA> pixelBorder(2,2, ColorRGBA(220,220,220,100));
   Texture2D::drawPoint(pixelBorder, Point(0, 0),ColorRGBA(0,0,0,0));
   _cTexture->addTexture(Point(2,0), pixelBorder); // 3

   // selected
   MatrixTemplate<ColorRGBA> selected(1,1, ColorRGBA(240,240,240,255));
   _cTexture->addTexture(Point(4,0), selected); // 4

   _cTexture->createTexture();
}


void MenuBar::onMouseClick(const scv::MouseEvent &evt) {/**/}
void MenuBar::onMouseHold(const scv::MouseEvent &evt) {/**/}
void MenuBar::onMouseOver(const scv::MouseEvent &evt) {/**/}
void MenuBar::onMouseUp(const scv::MouseEvent &evt) {/**/}
void MenuBar::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void MenuBar::onKeyUp(const scv::KeyEvent &evt) {/**/}
void MenuBar::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void MenuBar::onSizeChange(void) {/**/}
void MenuBar::onPositionChange(void) {/**/}


void MenuBar::addMenu(ContextMenu *menu) {
   static FontTahoma *font = FontTahoma::getInstance();
   static MenuHolder *menuH = MenuHolder::getInstance();
   menuH->registerMenu(menu);

   int position = (_index.back() + (s_borderWidth * 2) + font->getStringLength(menu->getString()));
   _index.push_back(position);
   _menus.push_back(menu);
}

} // namespace scv
