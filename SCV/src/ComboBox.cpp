#include "stdafx.h"
#include "ComboBox.h"
#include "Kernel.h"
#include "MenuHolder.h"
#include "data.h"
#include "StaticLabel.h"

#include "ComboBoxMenuStyle.h"

namespace scv {

ComboBox::ComboBoxMenu::ComboBoxMenu(scv::ComboBox *host) : ContextMenu("ComboBoxMenu") {
   _host = host;
   setMenuStyle(ComboBoxMenuStyle::getInstance());
}

void ComboBox::ComboBoxMenu::onMenuAccessed(const std::deque<std::string> &address) {
   _host->select(address[1]);
   _host->_active = false;
}

void ComboBox::ComboBoxMenu::onStatusChange(void) {
   if (getStatus() == false) {
      _host->_active = true;
   }
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

ComboBox::ComboBox(const scv::Point &p1, const scv::Point &p2) : Button(p1, p2, std::string()), _comboBoxMenu(0) {
   _comboBoxMenu = new ComboBoxMenu(this);
   MenuHolder::getInstance()->registerMenu(_comboBoxMenu);
   _active = false;
   _type = COMBOBOX;

   createTexture();
}

ComboBox::ComboBox(const scv::Point &p1, unsigned int width) : Button(p1, Point(p1.x + width, p1.y + 20), std::string()), _comboBoxMenu(0) {
   _comboBoxMenu = new ComboBoxMenu(this);
   MenuHolder::getInstance()->registerMenu(_comboBoxMenu);
   _active = false;
   _type = COMBOBOX;

   createTexture();
}

ComboBox::~ComboBox(void) {
   if (_comboBoxMenu != NULL) {
      MenuHolder::getInstance()->unregisterMenu(_comboBoxMenu);
      delete _comboBoxMenu;
   }
}

void ComboBox::onSelectionChanged(std::string address, int id) {
}

void ComboBox::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   
   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   if (isDragging()) _comboBoxMenu->setPosition(currPosition + Point(0, getHeight()));

   _cTexture->enable();

   ColorScheme::getInstance()->applyColor(ColorScheme::TEXTFIELD);
   _cTexture->display(currPosition.x, currPosition.y, 1, getWidth(), getHeight());
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);

   ColorScheme::getInstance()->applyColor(ColorScheme::MAINCOMPONENTS);
   _cTexture->display(currPosition.x + getWidth() - 17, currPosition.y + getHeight() - 2, 2, 15, - 16);

   ColorScheme::getInstance()->applyColor(ColorScheme::TEXTFIELD);
   if (isHolded()) {
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 4, getWidth() - 2, getHeight() - 2);
   } else if (isOvered()) {
      _cTexture->display(currPosition.x + 1 , currPosition.y + 1, 3, getWidth() - 2, getHeight() - 2);
   }

   _cTexture->disable();

   Scissor::getInstance()->pushScissor(Scissor::Info(currPosition.x + 3, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() - 22, getHeight()));

   StaticLabel::display(currPosition.x + 4, currPosition.y + getHeight() / 2 - 6, Label::getString());

   Scissor::getInstance()->popScissor();
}

void ComboBox::setItems(const std::vector<std::string>& items) {
   _comboBoxMenu->setItems(items);
   _values = items;
}

void ComboBox::popupMenu(void) {
   static MenuHolder* holder = MenuHolder::getInstance();
   holder->activeMenu(_comboBoxMenu, getAbsolutePosition() + Point(0, getHeight()));
}

void ComboBox::popMenu(void) {
   _comboBoxMenu->setStatus(false);
}

void ComboBox::select(const std::string& value) {
   setString(value);

   _currentValue = std::find(_values.begin(), _values.end(), value) - _values.begin();

   onSelectionChanged(value, _currentValue);
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
      }else if (evt.getState() == MouseEvent::CLICK && evt.getButton() == MouseEvent::RIGHT) {
         _active = false;
      }
   }else if (evt.getState() == MouseEvent::CLICK){
      _active = false;
   }
}

void ComboBox::createTexture(void) {
   static Kernel *kernel = Kernel::getInstance();

   if ((_cTexture = kernel->getWidgetTexture(COMBOBOX)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(15, 17);
   kernel->setWidgetTexture(COMBOBOX, _cTexture);

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
   _comboBoxMenu->addItem(str);
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