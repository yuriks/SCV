#include "stdafx.h"
#include "ColorPicker.h"
#include "Kernel.h"
#include "util.h"

namespace scv {

ColorPicker::ColorPicker(const scv::Point &p1) : MatrixTemplate<ColorRGBA>(360, 102, ColorRGBA(0,255,0,255)), Panel(p1, Point(p1.x + 360, p1.y + 155)) {
   _isHResizable = _isVResizable = false;

   _currentColor = ColorRGBA(0,0,0,255);

   _pickerWaitingColor = false;

   _cpTexture = NULL;

   _rgbs[0] = new Spinner(Point(20 ,106),50,0,255,0,1);
   _rgbs[1] = new Spinner(Point(90 ,106),50,0,255,0,1);
   _rgbs[2] = new Spinner(Point(160,106),50,0,255,0,1);
   _rgbs[3] = new Spinner(Point(230,106),50,0,100,100,5);
   _btPicker = new EyeDropper(this, Point(285,106), Point(285+69,126), "EyeDropper");

   _saturation = 100;
   Panel::addChild(_rgbs[0]);
   Panel::addChild(_rgbs[1]);
   Panel::addChild(_rgbs[2]);
   Panel::addChild(_rgbs[3]);
   Panel::addChild(_btPicker);

   Panel::addChild(new Label(Point(  8, 109), "R:"));
   Panel::addChild(new Label(Point( 78, 109), "G:"));
   Panel::addChild(new Label(Point(148, 109), "B:"));
   Panel::addChild(new Label(Point(218, 109), "S:"));

   // initial color
   _currentColorPosition = Point(0, MatrixTemplate<ColorRGBA>::getHeight() - 1);

   _type = colorPicker;

   refreshColor();

   createTexture();
}

ColorPicker::~ColorPicker() {
   delete _btPicker;
}

void ColorPicker::onMouseClick(const scv::MouseEvent &evt) {/**/}
void ColorPicker::onMouseHold(const scv::MouseEvent &evt) {/**/}
void ColorPicker::onMouseOver(const scv::MouseEvent &evt) {/**/}
void ColorPicker::onMouseUp(const scv::MouseEvent &evt) {/**/}
void ColorPicker::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void ColorPicker::onKeyUp(const scv::KeyEvent &evt) {/**/}
void ColorPicker::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void ColorPicker::onColorChange(void) {/**/}
void ColorPicker::onSizeChange(void) {/**/}
void ColorPicker::onPositionChange(void) {/**/}

void ColorPicker::display(void) {
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cpTexture == NULL || _isVisible == false) return;

   Panel::display();

   Point currPosition = getAbsolutePosition();

   refreshColor();

   _cpTexture->enable();
   scheme->applyDefaultModulate();

      // colorful area
      _cpTexture->display(currPosition.x, currPosition.y,0, MatrixTemplate<ColorRGBA>::getWidth(), MatrixTemplate<ColorRGBA>::getHeight());

      // selected color
      glColor3f(_currentColor[0]/255.f, _currentColor[1]/255.f, _currentColor[2]/255.f);
      _cpTexture->display(currPosition.x + 5, currPosition.y + 130, 1, MatrixTemplate<ColorRGBA>::getWidth() - 11, 20);

   _cpTexture->disable();
}

void ColorPicker::createTexture(void) {   
   Panel::createTexture();

   createColors();

   if ((_cpTexture = kernel->getWidgetTexture(Kernel::colorPicker)) != NULL) return;

   _cpTexture = new ComponentTexture(MatrixTemplate<ColorRGBA>::getWidth(), MatrixTemplate<ColorRGBA>::getHeight() + 1);
   kernel->setWidgetTexture(Kernel::colorPicker, _cpTexture);

   _cpTexture->setTextureEnvMode(GL_MODULATE);
   _cpTexture->addTexture(Point(0,0), *this);

   _cpTexture->addTexture(Point(0,MatrixTemplate<ColorRGBA>::getHeight()), MatrixTemplate<ColorRGBA>(1, 1, ColorRGBA(255,255,255,255)));

   _cpTexture->createTexture();
}

Point ColorPicker::foundHSL(void) {
   _currentPickerColor = ColorRGBA((unsigned char)_rgbs[0]->getValue(), (unsigned char)_rgbs[1]->getValue(), (unsigned char)_rgbs[2]->getValue());
   float hls[3];
   ColorRGBA colorHLS = _currentPickerColor;
   colorHLS.toHSL(hls);
   _saturation = hls[2] * 100.f;
   _rgbs[3]->setValue(_saturation);
   return Point((int)(hls[0]*360),(int)(100.f-hls[1]*99.f-1.f));
}

void ColorPicker::refreshColor(void) {
   _currentPickerColor = ColorRGBA((unsigned char)_rgbs[0]->getValue(), (unsigned char)_rgbs[1]->getValue(), (unsigned char)_rgbs[2]->getValue());
   if (_saturation != _rgbs[3]->getValue()) {
      _saturation = _rgbs[3]->getValue();
      createTexture();
      _currentColor = ColorRGBA(MatrixTemplate<ColorRGBA>::get(_currentColorPosition.y, _currentColorPosition.x));
      setSpinsColor();
      onColorChange();
   } else if (_currentPickerColor != _currentColor) {
      _currentColor = _currentPickerColor;
      onColorChange();
   }
}

void ColorPicker::setSpinsColor(void) {
   _rgbs[0]->setValue(_currentColor[0]);
   _rgbs[1]->setValue(_currentColor[1]);
   _rgbs[2]->setValue(_currentColor[2]);
   refreshColor();
}

void ColorPicker::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor * cursor = Cursor::getInstance();

   if (!_receivingCallbacks) {
      Component::processMouse(evt);
   } else {
      Panel::processMouse(evt);
   }

   if (!_receivingCallbacks) return;

   if (_pickerWaitingColor) {
      kernel->lockMouseUse(this);
      cursor->forceGlutCursor(GLUT_CURSOR_FULL_CROSSHAIR);
      glReadPixels(evt.getPosition().x, evt.getInversePosition().y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &_currentColor);
      setSpinsColor();
      onColorChange();
      if (evt.getState() == MouseEvent::CLICK && evt.getButton() == MouseEvent::LEFT) {
         _btPicker->setState(false);
         _pickerWaitingColor = false;
         _currentColorPosition = foundHSL();
         createTexture();
      }
   } else {
      if (isInside(evt.getPosition()) && kernel->requestMouseUse(this)) {
         if (isFocused()) {
            Point relativeMouse = evt.getPosition()-getAbsolutePosition();
            if (relativeMouse.x < MatrixTemplate<ColorRGBA>::getWidth() && relativeMouse.y < MatrixTemplate<ColorRGBA>::getHeight()) {
               cursor->setGlutCursor(GLUT_CURSOR_FULL_CROSSHAIR);
               if (evt.getState() == MouseEvent::CLICK && evt.getButton() == MouseEvent::LEFT) {
                  _isDragging = false;
                  _currentColorPosition = relativeMouse;
                  _currentColor =  ColorRGBA(MatrixTemplate<ColorRGBA>::get(_currentColorPosition.y,_currentColorPosition.x));
                  setSpinsColor();
                  onColorChange();
                  onMouseClick(evt);
               } else if (evt.getState() == MouseEvent::HOLD && evt.getButton() == MouseEvent::LEFT) {
                  kernel->lockMouseUse(this);
                  _isDragging = false;
                  _currentColorPosition = relativeMouse;
                  _currentColor =  ColorRGBA(MatrixTemplate<ColorRGBA>::get(_currentColorPosition.y,_currentColorPosition.x));
                  setSpinsColor();
                  onColorChange();
                  onMouseHold(evt);
               } else if (evt.getState() == MouseEvent::UP) {
                  kernel->unlockMouseUse(this);
               }
            }
         }
      } else if (evt.getState() == MouseEvent::UP) {
         kernel->unlockMouseUse(this);
      }
   }
}

void ColorPicker::createColors(void) {
   double S = _rgbs[3]->getValue() / 100.f;

   for (int L = 100; L > 0 ; L--) {
      for (int H = 0; H < 360 ; H++) {
         set((100 - L) + 1, H, ColorRGBA::toRGB((double)H, L / 100.0, S));
      }
   }

   for (int H = 0; H < 360 ; H++) {
      set(0, H, ColorRGBA(255,255,255,255));
      set(101, H, ColorRGBA(0,0,0,255));
   }
}

ColorRGBA ColorPicker::getColor(void) const {
   return _currentColor;
}

void ColorPicker::setColor(const ColorRGBA &color) {
   if (_currentColor == color) return;
   _currentColor = color;
   setSpinsColor();
   refreshColor();
   onColorChange();

}

int ColorPicker::getWidth(void) const {
   return Panel::getWidth();
}
int ColorPicker::getHeight(void) const {
   return Panel::getHeight();
}

void ColorPicker::setDraggable(bool state) {
   Component::setDraggable(state);
   /*
   for (int i = 0; i < 4; i++) _rgbs[i]->setDraggable(state);
   _btPicker->setDraggable(state);
   */
}

void ColorPicker::setResizable(bool state) {
   Component::setResizable(state);
   /*
   for (int i = 0; i < 4; i++) _rgbs[i]->setResizable(state);
   _btPicker->setResizable(state);
   */
}

} // namespace scv
