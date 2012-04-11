#include "stdafx.h"
#include "Spinner.h"
#include "Kernel.h"
#include "util.h"
#include "MenuHolder.h"

namespace scv {

scv::TextFilter Spinner::s_filter;

Spinner::Spinner(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue) :
      scv::Panel(p, Point(p.x + width, p.y + s_spinnerSizeY)), Counter(minValue, maxValue, startValue<minValue?minValue:startValue>maxValue?maxValue:startValue, stepValue) {

   setWidth((width < s_minSize) ? s_minSize : width);

   _editable = true;
   _isHResizable = true;
   _isVResizable = false;

   s_filter.denyAll();
   s_filter.allowNumbers();
   s_filter.allowThese(std::string(".-"));

   _layout = new GroupLayout(this);
   setLayout(_layout);

   _textField = new TextFieldSpinner(this, getWidth() - s_spinnerSizeX - 6, toString(startValue));
   addChild(_textField);

   _layout->setHorizontalGroup(GroupLayout::createSequentialGroup()
      ->addComponent(_textField)
      ->addGap(s_spinnerSizeX)
   );

   _textField ->setFilter(s_filter);
   _textField->setMinimumSize(Point(scv::FontTahoma::getInstance()->getStringLength(toString(maxValue)) + 4, getHeight()));
   
   _upPress   = false;
   _downPress = false;
   _upOver    = false;
   _downOver  = false;

   setMinimumSize(Point(s_minSize, s_spinnerSizeY));
   setPreferredSize(Point(_preferredSize.x, s_spinnerSizeY));
   setMaximumSize(Point(_maximumSize.x, s_spinnerSizeY));
   
   _lastTime = _incrementTime = 0;
   _type = SPINNER;

   createTexture();
}
     
Spinner::~Spinner(void) {
   if (_layout != NULL) {
      delete _layout;
   }
}

void Spinner::onValueChange(void) {
}

void Spinner::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point relPosition = getRelativePosition();
   Point currPosition = getAbsolutePosition();

   if (!isFocused() && kernel->getFocusedComponent() != _textField) {
      _textField->setString(toString(getValue()));
   }

   Panel::display();

   _cTexture->enable();
      scheme->applyDefaultModulate();
      // border
      _cTexture->display(currPosition.x + _textField->getWidth() + 1, currPosition.y + 1, 0, s_spinnerSizeX, getHeight() - 2);

      scheme->applyColor(ColorScheme::MAINCOMPONENTS);
      // middle
      _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + 2, 2, s_spinnerSizeX - 2, getHeight() / 2 - 3);
      _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + getHeight() / 2 + 1, 2, s_spinnerSizeX - 2, getHeight() / 2 - 3);

      // middle 2
      if (_upPress) {
         scheme->applyColor(ColorScheme::HOLDCOMPONENTS);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + 3, 6, s_spinnerSizeX - 4, getHeight() / 2 - 5);

         // spin control
         if (_whileUp.isRunning() && _upOver) {
            _incrementTime = _whileUp.getMilliseconds() - _lastTime;
            if ((_whileUp.getMilliseconds() > 600 && _incrementTime > 100) || (_whileUp.getMilliseconds() > 2000 && _incrementTime > 30) || (_whileUp.getMilliseconds() > 4000 && _incrementTime > 10)) {
               IncrementStep();
               _lastTime = _whileUp.getMilliseconds();
               _incrementTime = 0;
            }
         }
      } else if (_upOver) {
         scheme->applyColor(ColorScheme::OVERCOMPONENTS);
         _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + 2, 5, s_spinnerSizeX - 2, getHeight() / 2 - 3);
      } else {
         scheme->applyColor(ColorScheme::MAINCOMPONENTS);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + 3, 1, s_spinnerSizeX - 4, getHeight() / 2 - 5);
      }

      if (_downPress) {
         scheme->applyColor(ColorScheme::HOLDCOMPONENTS);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + getHeight() / 2 + 2, 6, s_spinnerSizeX - 4, getHeight() / 2 - 5);

         // spin control
         if (_whileDown.isRunning() && _downOver) {
            _incrementTime = _whileDown.getMilliseconds() - _lastTime;
            if ((_whileDown.getMilliseconds() > 600 && _incrementTime > 100) || (_whileDown.getMilliseconds() > 2000 && _incrementTime > 30) || (_whileDown.getMilliseconds() > 4000 && _incrementTime > 10)) {
               DecrementStep();
               _lastTime = _whileDown.getMilliseconds();
               _incrementTime = 0;
            }
         }
      } else if (_downOver) {
         scheme->applyColor(ColorScheme::OVERCOMPONENTS);
         _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + getHeight() / 2 + 1, 5, s_spinnerSizeX - 2, getHeight() / 2 - 3);
      } else {
         scheme->applyColor(ColorScheme::MAINCOMPONENTS);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + getHeight() / 2 + 2, 1, s_spinnerSizeX - 4, getHeight() / 2 - 5);
      }

      scheme->applyColor(ColorScheme::FONT);
      // top pin
      _cTexture->display(currPosition.x + _textField->getWidth() + 6, currPosition.y + 4 , 3);

      // bot spin
      _cTexture->display(currPosition.x + _textField->getWidth() + 6, currPosition.y + 13, 4);


   _cTexture->disable();
}


void Spinner::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(SPINNER)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(16, 16);
   kernel->setWidgetTexture(SPINNER, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // border
   MatrixTemplate<ColorRGBA> oBorder(1, 1, ColorRGBA(171,173,179));
   _cTexture->addTexture(Point(0,0), oBorder);

   // in middle
   MatrixTemplate<ColorRGBA> inMiddle(1, 1, ColorRGBA(255,255,255));
   _cTexture->addTexture(Point(0,1), inMiddle);

   // out middle
   MatrixTemplate<ColorRGBA> outMiddle(1, 1, ColorRGBA(241,241,241));
   _cTexture->addTexture(Point(1,0), outMiddle);

   // top pin
   MatrixTemplate<ColorRGBA> tPin(5, 3, ColorRGBA(0,0,0,0));
   Texture2D::line(tPin, Point(2, 0), Point(2,0), ColorRGBA(140,140,140));
   Texture2D::line(tPin, Point(1, 1), Point(3,1), ColorRGBA(150,150,150));
   Texture2D::line(tPin, Point(0, 2), Point(4,2), ColorRGBA(170,170,170));
   _cTexture->addTexture(Point(2,0), tPin);

   // bot pin
   MatrixTemplate<ColorRGBA> bPin(5, 3, ColorRGBA(0,0,0,0));

   Texture2D::line(bPin, Point(2, 2), Point(2,2), ColorRGBA(140,140,140));
   Texture2D::line(bPin, Point(1, 1), Point(3,1), ColorRGBA(150,150,150));
   Texture2D::line(bPin, Point(0, 0), Point(4,0), ColorRGBA(170,170,170));
   _cTexture->addTexture(Point(7,0), bPin);

   MatrixTemplate<ColorRGBA> over(1, 1, ColorRGBA(240,240,240,240));
   _cTexture->addTexture(Point(12,0), over);

   MatrixTemplate<ColorRGBA> hold(1, 1, ColorRGBA(100,100,100,100));
   _cTexture->addTexture(Point(13,0), hold);

   _cTexture->createTexture();
}


void Spinner::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();


   if(!_editable)
   {
      Component::processMouse(evt);
      return;
   }

   if(!_receivingCallbacks) {
      Component::processMouse(evt);
      return;
   } else {
      _textField->processMouse(evt);
   }

   if (isOnUpButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
      _upOver = true;
      if (evt.getButton() == MouseEvent::LEFT && evt.getState() == MouseEvent::CLICK) {
         kernel->requestComponentFocus(this);
         _upPress = true;
         if (getValue() == getMaxValue()) return;
         _whileUp.start();
         IncrementStep();
         onMouseClick(evt);
      }
      if (evt.getButton() == MouseEvent::RIGHT && evt.getState() == MouseEvent::CLICK) {
         Point evtPosition         = evt.getPosition();
         MenuHolder *menu = MenuHolder::getInstance();
         menu->activeMenu(_contextMenu, evtPosition);
      }
   } else {
      _upOver = false;
   }

   if (isOnDownButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
      _downOver = true;
      if (evt.getButton() == MouseEvent::LEFT && evt.getState() == MouseEvent::CLICK) {
         kernel->requestComponentFocus(this);
         _downPress = true;
         if (getValue() == getMinValue()) return;
         _whileDown.start();
         DecrementStep();
         onMouseClick(evt);
      }
      if (evt.getButton() == MouseEvent::RIGHT && evt.getState() == MouseEvent::CLICK) {
         Point evtPosition         = evt.getPosition();
         MenuHolder *menu = MenuHolder::getInstance();
         menu->activeMenu(_contextMenu, evtPosition);
      }
   } else {
      _downOver = false;
   }

   if (evt.getState() == MouseEvent::UP && evt.getButton() == MouseEvent::LEFT) {
      _upPress = false;
      _downPress = false;
      _downOver = _upOver = false;
      _whileDown.stop();
      _whileUp.stop();
      _lastTime = 0;
   }

   if (isFocused()) {
      if (isInside(evt.getPosition())  && kernel->requestMouseUse(this) && (evt.getPosition() < Point(getAbsolutePosition().x + getWidth(), getAbsolutePosition().y + 18)) &&
         evt.getState() == MouseEvent::CLICK) {
            _isDragging = false;
      } else if (evt.getState() == MouseEvent::HOLD && isDragging() == false) {
         onMouseHold(evt);
      }
   }
}

void Spinner::processKey(const scv::KeyEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Component::processKey(evt);

   if(!_receivingCallbacks || evt.state == KeyEvent::UP) return;

   if (evt.getKeyString() == "Up" && (isFocused() || kernel->getFocusedComponent() == _textField)) {
      if (evt.state == KeyEvent::DOWN) IncrementStep();
   } else if (evt.getKeyString() == "Down" && (isFocused() || kernel->getFocusedComponent() == _textField)) {
      if (evt.state == KeyEvent::DOWN) DecrementStep();
   } 
   if (isFocused() || kernel->getFocusedComponent() == _textField) {
      kernel->requestComponentFocus(_textField);
      _textField->processKey(evt);      
   }
}

bool Spinner::isOnUpButton(const Point &p) {
   return (p.y >= getAbsolutePosition().y+1 && p.y < getAbsolutePosition().y + s_spinnerSizeY/2.0 &&
      p.x >= getAbsolutePosition().x + _textField->getWidth() + 1 && p.x <= getAbsolutePosition().x + _textField->getWidth() + s_spinnerSizeX)? true : false;
}

bool Spinner::isOnDownButton(const Point &p) {
   return (p.y > getAbsolutePosition().y + s_spinnerSizeY/2.0 - 1 && p.y < getAbsolutePosition().y + getHeight()-1 &&
      p.x >= getAbsolutePosition().x + _textField->getWidth() + 1 && p.x <= getAbsolutePosition().x + _textField->getWidth() + s_spinnerSizeX)? true : false;
}

void Spinner::setValue(double value) {
   Counter::setValue(value);
   _textField->setString(toString(getValue()));
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

Spinner::TextFieldSpinner::TextFieldSpinner(Spinner *spinner, unsigned int width, const std::string &str) :
      TextField(scv::Point(), width, str) {
   _spinner = spinner;
   setResizable(false);
}

void Spinner::TextFieldSpinner::onStringChange(void) {
   bool point = false;
   bool minus = false;
   std::string str = _str;
   if (str.length() > 1) {
      for (int i = 0; i < str.length(); i++) {
         if (str[i] == '.') {
            if (point) str.erase(i,1);
            else point = true;
         } else if (str[i] == '-') {
            if (point) str.erase(i,1);
            else if (minus) str.erase(i,1);
            else minus = true;
         }
      }
      setString(str);
   }
   if (_str != "-" && _str != ".") {
      double t = 0;
      if (_str.length() > 0) {
         t = fromString<double>(getString());
      }
      if (_spinner->getValue() != t && _str.length() > 0) {
         if (t >= _spinner->getMinValue() && t <= _spinner->getMaxValue()) {
            _spinner->setValue(t);
            setString(toString(_spinner->getValue()));
         }         
      }
   }
}

} // namespace scv
