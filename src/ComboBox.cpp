#include "stdafx.h"
#include "ComboBox.h"
#include "Kernel.h"
#include "MenuHolder.h"
#include "data.h"
#include "StaticLabel.h"

#include "ComboBoxMenuStyle.h"

namespace scv {

ComboBox::ComboBoxMenu::ComboBoxMenu(ComboBox& combo) : ContextMenu(""), combo(combo) {
   setMenuStyle(ComboBoxMenuStyle::getInstance());
}

void ComboBox::ComboBoxMenu::onMenuAccessed(const std::deque<std::string> &address) {
   combo.select(address[1]);
   combo._active = false;
}

void ComboBox::ComboBoxMenu::setItems(const std::vector<std::string>& items) {
   removeAllMenus();
   for (std::vector<std::string>::const_iterator i = items.begin(); i != items.end(); ++i) {
      addMenu(new ContextMenu(*i));
   }
}

void ComboBox::ComboBoxMenu::addItem(const std::string item) {
   addMenu(new ContextMenu(item));
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ComboBox::ComboBox(const scv::Point &p1, const scv::Point &p2) : Button(p1, p2, ""), menu(0) {
   menu = new ComboBoxMenu(*this);
   MenuHolder::getInstance()->registerMenu(menu);
   _isHResizable = true;
   _isVResizable = false;
   _type = COMBOBOX;

   _active = false;

   createTexture();
}

ComboBox::ComboBox(const scv::Point &p1, unsigned int width) : Button(p1, Point(p1.x + width, p1.y + 20), ""), menu(0) {
   menu = new ComboBoxMenu(*this);
   MenuHolder::getInstance()->registerMenu(menu);
   _isHResizable = true;
   _isVResizable = false;
   _type = COMBOBOX;

   _active = false;

   createTexture();
}

ComboBox::ComboBox(const scv::Point &p, unsigned int width, std::vector <std::string> items, unsigned int defaultIndex)
   : Button(p, Point(p.x + width, p.y + 20), ""), menu(0) {

   menu = new ComboBoxMenu(*this);
   MenuHolder::getInstance()->registerMenu(menu);

   _isHResizable = true;
   _isVResizable = false;
   _type = COMBOBOX;
   setItems(items);
   if (defaultIndex >= 0 && defaultIndex < items.size())
      select(items[defaultIndex]);
   _currentValue = defaultIndex;

   _active = false;

   createTexture();
}


void ComboBox::onMouseClick(const scv::MouseEvent &evt) {
}
void ComboBox::onMouseHold(const scv::MouseEvent &evt) {
}
void ComboBox::onMouseOver(const scv::MouseEvent &evt) {
}
void ComboBox::onMouseUp(const scv::MouseEvent &evt) {
}
void ComboBox::onMouseWheel(const scv::MouseEvent &evt) {
}

void ComboBox::onKeyPressed(const scv::KeyEvent &evt) {
}
void ComboBox::onKeyUp(const scv::KeyEvent &evt) {
}

void ComboBox::onSizeChange(void) {
}
void ComboBox::onPositionChange(void) {
}

void ComboBox::onSelectionChanged(std::string address, int id) {
}

void ComboBox::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   if (isDragging())
      menu->setPosition(currPosition + Point(0, getHeight()));

   _cTexture->enable();

      scheme->applyColor(ColorScheme::TEXTFIELD);
      _cTexture->display(currPosition.x, currPosition.y, 1, getWidth(), getHeight());
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);
      _cTexture->display(currPosition.x + getWidth() - 17, currPosition.y + getHeight() - 2, 2, 15, - 16);

      if (isHolded())
         _cTexture->display(currPosition.x + 1, currPosition.y + 1, 4, getWidth() - 2, getHeight() - 2);
      else if (isOvered())
         _cTexture->display(currPosition.x + 1 , currPosition.y + 1, 3, getWidth() - 2, getHeight() - 2);

   _cTexture->disable();

   scissor->pushScissor(Scissor::Info(currPosition.x + 3, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() - 22, getHeight()));

   StaticLabel::display(currPosition.x + 4, currPosition.y + getHeight() / 2 - 6, Label::getString());

   scissor->popScissor();
}

void ComboBox::setItems(const std::vector<std::string>& items) {
   menu->setItems(items);
   _values = items;
}

void ComboBox::popupMenu(void) {
   static MenuHolder* holder = MenuHolder::getInstance();
   holder->activeMenu(menu, getAbsolutePosition() + Point(0, getHeight()));
}

void ComboBox::select(const std::string& value) {

   setString(value);

   int i=0;
   for (; i < _values.size(); i++) {
      if (value==_values[i])
         break;
   }
   if (i < _values.size())
      _currentValue = i;

   onSelectionChanged(value, i);

}

void ComboBox::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Component::processMouse(evt);

   //if (!_receivingCallbacks) return;

   if (isInside(evt.getPosition())) {
      if (evt.getState() == MouseEvent::CLICK && evt.getButton() == MouseEvent::LEFT && isFocused()) {
         if (_active) {
            _active = false;
         } else {
            popupMenu();
            _active = true;
         }
      }
      if (evt.getState() == MouseEvent::CLICK && evt.getButton() == MouseEvent::RIGHT)
         _active = false;
   }
}

void ComboBox::createTexture(void) {
   static Kernel *kernel = Kernel::getInstance();

   if ((_cTexture = kernel->getWidgetTexture(Kernel::COMBOBOX)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(15, 17);
   kernel->setWidgetTexture(Kernel::COMBOBOX, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // middle
   _cTexture->addTexture(Point(0, 0), MatrixTemplate<ColorRGBA>(1, 1, ColorRGBA(255,255,255,255)));

   // lines
   _cTexture->addTexture(Point(1, 0), MatrixTemplate<ColorRGBA>(1, 1, ColorRGBA(100,100,100,255)));

   // button
   _cTexture->addTexture(Point(0, 1), 15, 16, data::ScrollPaneVerticalButton);

   // selects
   _cTexture->addTexture(Point(2, 0), ColorRGBA(220, 220, 220, 100));
   _cTexture->addTexture(Point(3, 0), ColorRGBA(120, 120, 120, 100));

   // generate texture
   _cTexture->createTexture();
}

void ComboBox::addItem(const std::string& str) {
   menu->addItem(str);
   _values.push_back(str);
}

std::string ComboBox::getValue(void) {
   return _values[_currentValue];
}

void ComboBox::setIndex(int offset) {
   if (offset >= 0 && offset < _values.size())
      select(_values[offset]);
}

int ComboBox::getIndex(void) {
   return _currentValue;
}
} // namespace scv