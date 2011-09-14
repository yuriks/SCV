#include "stdafx.h"
#include "Spinner.h"
#include "Kernel.h"
#include "util.h"
#include "MenuHolder.h"

namespace scv {

Spinner::Spinner(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue) :
      ComponentWithTexture(p, Point(p.x + s_spinnerSizeX, p.y + s_spinnerSizeY)), Counter(minValue,maxValue,startValue<minValue?minValue:startValue>maxValue?maxValue:startValue,stepValue) {
   _isHResizable = _isVResizable = false;

   _filter.denyAll();
   _filter.allowNumbers();
   _filter.allowThese(std::string(".-"));

   _textField = new TextFieldSpinner(this, p, ((width < s_minSize) ? s_minSize : width) - s_spinnerSizeX - 1, toString(startValue));
   _textField ->setFilter(_filter);

   _UpPress   = false;
   _DownPress = false;
   _UpOver      = false;
   _DownOver    = false;

   _whileUp   = new Timer();
   _whileDown = new Timer();

   _minSize.x = 200;
   _minSize.y = getHeight();

   _lastTime = _incrementTime = 0;
   _type = spinner;
}


Spinner::Spinner(const scv::Point &p , double minValue, double maxValue, double startValue, double stepValue) :
      ComponentWithTexture(p, Point(p.x + s_spinnerSizeX, p.y + s_spinnerSizeY)), Counter(minValue,maxValue,startValue<minValue?minValue:startValue>maxValue?maxValue:startValue,stepValue) {
   _isHResizable = _isVResizable = false;

   _filter.denyAll();
   _filter.allowNumbers();
   _filter.allowThese(std::string(".-"));

   _textField = new TextFieldSpinner(this, p, 100 - s_spinnerSizeX - 1, toString(startValue));
   _textField ->setFilter(_filter);

   _UpPress   = false;
   _DownPress = false;
   _UpOver      = false;
   _DownOver    = false;

   _whileUp   = new Timer();
   _whileDown = new Timer();

   _lastTime = _incrementTime = 0;
   _type = spinner;
}

void Spinner::onMouseClick(const scv::MouseEvent &evt) {/*none*/}
void Spinner::onMouseHold(const scv::MouseEvent &evt) {/*none*/}
void Spinner::onMouseOver(const scv::MouseEvent &evt) {/*none*/}
void Spinner::onMouseUp(const scv::MouseEvent &evt) {/*none*/}
void Spinner::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void Spinner::onKeyPressed(const scv::KeyEvent &evt) {/*none*/}
void Spinner::onKeyUp(const scv::KeyEvent &evt) {/*none*/}
void Spinner::onValueChange(void) {/**/}
void Spinner::onResizing(void) {/**/}
void Spinner::onDragging(void) {/**/}


void Spinner::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point relPosition = getRelativePosition();
   Point currPosition = getAbsolutePosition();

   _textField->setPanelTranslate(currPosition - relPosition);

   _textField->display();

   _cTexture->enable();
      scheme->applyDefaultModulate();
      // border
      _cTexture->display(currPosition.x + _textField->getWidth() + 1, currPosition.y + 1, 0, s_spinnerSizeX, getHeight() - 2);

      scheme->applyColor(ColorScheme::mainComponents);
      // middle
      _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + 2, 2, s_spinnerSizeX - 2, getHeight() / 2 - 3);
      _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + getHeight() / 2 + 1, 2, s_spinnerSizeX - 2, getHeight() / 2 - 3);

      // middle 2
      if (_UpPress) {
         scheme->applyColor(ColorScheme::holdComponents);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + 3, 6, s_spinnerSizeX - 4, getHeight() / 2 - 5);

         // spin control
         if (_whileUp->isRunning() && _UpOver) {
            _incrementTime = _whileUp->getMilliseconds() - _lastTime;
            if ((_whileUp->getMilliseconds() > 600 && _incrementTime > 100) || (_whileUp->getMilliseconds() > 2000 && _incrementTime > 30) || (_whileUp->getMilliseconds() > 4000 && _incrementTime > 10)) {
               IncrementStep();
               _lastTime = _whileUp->getMilliseconds();
               _incrementTime = 0;
            }
         }
      } else if (_UpOver) {
         scheme->applyColor(ColorScheme::overComponents);
         _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + 2, 5, s_spinnerSizeX - 2, getHeight() / 2 - 3);
      } else {
         scheme->applyColor(ColorScheme::mainComponents);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + 3, 1, s_spinnerSizeX - 4, getHeight() / 2 - 5);
      }

      if (_DownPress) {
         scheme->applyColor(ColorScheme::holdComponents);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + getHeight() / 2 + 2, 6, s_spinnerSizeX - 4, getHeight() / 2 - 5);

         // spin control
         if (_whileDown->isRunning() && _DownOver) {
            _incrementTime = _whileDown->getMilliseconds() - _lastTime;
            if ((_whileDown->getMilliseconds() > 600 && _incrementTime > 100) || (_whileDown->getMilliseconds() > 2000 && _incrementTime > 30) || (_whileDown->getMilliseconds() > 4000 && _incrementTime > 10)) {
               DecrementStep();
               _lastTime = _whileDown->getMilliseconds();
               _incrementTime = 0;
            }
         }
      } else if (_DownOver) {
         scheme->applyColor(ColorScheme::overComponents);
         _cTexture->display(currPosition.x + _textField->getWidth() + 2, currPosition.y + getHeight() / 2 + 1, 5, s_spinnerSizeX - 2, getHeight() / 2 - 3);
      } else {
         scheme->applyColor(ColorScheme::mainComponents);
         _cTexture->display(currPosition.x + _textField->getWidth() + 3, currPosition.y + getHeight() / 2 + 2, 1, s_spinnerSizeX - 4, getHeight() / 2 - 5);
      }

      scheme->applyColor(ColorScheme::font);
      // top pin
      _cTexture->display(currPosition.x + _textField->getWidth() + 6, currPosition.y + 4 , 3);

      // bot spin
      _cTexture->display(currPosition.x + _textField->getWidth() + 6, currPosition.y + 13, 4);


   _cTexture->disable();
}


void Spinner::createTexture(void) {
   static Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(Kernel::spinner)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(16, 16);
   kernel->setWidgetTexture(Kernel::spinner, _cTexture);

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
//    Texture2D::line(tPin, Point(2, 0), Point(2,0), ColorRGBA( 77,86,120));
//    Texture2D::line(tPin, Point(1, 1), Point(3,1), ColorRGBA( 95,110,165));
//    Texture2D::line(tPin, Point(0, 2), Point(4,2), ColorRGBA(112,133,209));
   _cTexture->addTexture(Point(2,0), tPin);

   // bot pin
   MatrixTemplate<ColorRGBA> bPin(5, 3, ColorRGBA(0,0,0,0));

   Texture2D::line(bPin, Point(2, 2), Point(2,2), ColorRGBA(140,140,140));
   Texture2D::line(bPin, Point(1, 1), Point(3,1), ColorRGBA(150,150,150));
   Texture2D::line(bPin, Point(0, 0), Point(4,0), ColorRGBA(170,170,170));
//    Texture2D::line(bPin, Point(2, 2), Point(2,2), ColorRGBA( 77,86,120));
//    Texture2D::line(bPin, Point(1, 1), Point(3,1), ColorRGBA( 95,110,165));
//    Texture2D::line(bPin, Point(0, 0), Point(4,0), ColorRGBA(112,133,209));
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

   if(!_receivingCallbacks) {
      ComponentInterface::processMouse(evt);
      return;
   } else {
      _textField->processMouse(evt);
   }

   if (isOnUpButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
      _UpOver = true;
      if (evt.getButton() == MouseEvent::left && evt.getState() == MouseEvent::click) {
         kernel->requestComponentFocus(this);
         _UpPress = true;
         if (getValue() == getMaxValue()) return;
         _whileUp->start();
         IncrementStep();
         onMouseClick(evt);
      }
      if (evt.getButton() == MouseEvent::right && evt.getState() == MouseEvent::click) {
         Point evtPosition         = evt.getPosition();
         MenuHolder *menu = MenuHolder::getInstance();
         menu->activeMenu(_contextMenu, evtPosition);
      }
   } else {
      _UpOver = false;
   }

   if (isOnDownButton(evt.getPosition()) && kernel->requestMouseUse(this)) {
      _DownOver = true;
      if (evt.getButton() == MouseEvent::left && evt.getState() == MouseEvent::click) {
         kernel->requestComponentFocus(this);
         _DownPress = true;
         if (getValue() == getMinValue()) return;
         _whileDown->start();
         DecrementStep();
         onMouseClick(evt);
      }
      if (evt.getButton() == MouseEvent::right && evt.getState() == MouseEvent::click) {
         Point evtPosition         = evt.getPosition();
         MenuHolder *menu = MenuHolder::getInstance();
         menu->activeMenu(_contextMenu, evtPosition);
      }
   } else {
      _DownOver = false;
   }

   if (evt.getState() == MouseEvent::up && evt.getButton() == MouseEvent::left) {
      _UpPress = false;
      _DownPress = false;
      _DownOver = _UpOver = false;
      _whileDown->stop();
      _whileUp->stop();
      _lastTime = 0;
   }

   if (isFocused()) {
      if (isInside(evt)  && kernel->requestMouseUse(this) && (evt.getPosition() < Point(getAbsolutePosition().x + getWidth(), getAbsolutePosition().y + 18)) &&
         evt.getState() == MouseEvent::click) {
            _isDragging = false;
      } else if (evt.getState() == MouseEvent::hold && isDragging() == false) {
         onMouseHold(evt);
      }
   }
}

void Spinner::processKey(const scv::KeyEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   ComponentInterface::processKey(evt);

   if(!_receivingCallbacks || evt.getState() == KeyEvent::up) return;

   if (evt.getKeyString() == "Up" && (isFocused() || kernel->getFocusedComponent() == _textField)) {
      if (evt.getState() == KeyEvent::down) IncrementStep();
   } else if (evt.getKeyString() == "Down" && (isFocused() || kernel->getFocusedComponent() == _textField)) {
      if (evt.getState() == KeyEvent::down) DecrementStep();
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

int Spinner::getWidth(void) const {
   return _textField->getWidth() + s_spinnerSizeX + 1;
}

int Spinner::getHeight(void) const {
   return ComponentInterface::getHeight();
}

void Spinner::setDraggable(bool state) {
   ComponentInterface::setDraggable(state);
   _textField->setDraggable(state);
}

void Spinner::setResizable(bool state) {
   ComponentInterface::setResizable(state);
   _textField->setResizable(state);
}


Spinner::TextFieldSpinner::TextFieldSpinner(Spinner *spinner, const scv::Point &p, unsigned int width, const std::string &str) :
      TextField(p, width, str) {
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
         _spinner->setValue(t);
         setString(toString(_spinner->getValue()));
      }
   }
}
} // namespace scv
