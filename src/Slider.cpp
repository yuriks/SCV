#include "stdafx.h"
#include "Slider.h"
#include "Kernel.h"
#include "Mathematic.h"

namespace scv {

Slider::Slider( const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue ) :
      ComponentWithTexture(p,Point(p.x+width,p.y+24)), Counter(minValue,maxValue,startValue<minValue?minValue:startValue>maxValue?maxValue:startValue,stepValue) {
   _isVResizable = false;
   _type = slider;

   createTexture();
}


Slider::Slider( const scv::Point &p , double minValue, double maxValue, double startValue, double stepValue ) :
      ComponentWithTexture(p,Point(p.x+100,p.y+24)), Counter(minValue,maxValue,startValue<minValue?minValue:startValue>maxValue?maxValue:startValue,stepValue) {
   _isVResizable = false;
   _type = slider;

   createTexture();
}

void Slider::onMouseClick(const scv::MouseEvent &evt) {/**/}
void Slider::onMouseHold(const scv::MouseEvent &evt) {/**/}
void Slider::onMouseOver(const scv::MouseEvent &evt) {/**/}
void Slider::onMouseUp(const scv::MouseEvent &evt) {/**/}
void Slider::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void Slider::onKeyUp(const scv::KeyEvent &evt) {/**/}
void Slider::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void Slider::onValueChange(void) {/**/}
void Slider::onSizeChange(void) {/**/}
void Slider::onPositionChange(void) {/**/}

void Slider::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
      scheme->applyDefaultModulate();
      // lines
      _cTexture->display(currPosition.x, currPosition.y + 6, 2, getWidth(), 4);
      _cTexture->display(currPosition.x, currPosition.y + 7, 1, getWidth(), 2);

      _cTexture->display(currPosition.x + 5, currPosition.y + getHeight() - 1, 2, 1, 4);
      _cTexture->display(currPosition.x + getWidth() -  5, currPosition.y + getHeight() - 1, 2, 1, 4);

      scheme->applyColor(ColorScheme::mainComponents);
      // pine
      _cTexture->display(currPosition.x + static_cast<int>(((getValue() - getMinValue()) / (getMaxValue() - getMinValue())) * (getWidth() - 9)), currPosition.y, 0);
   _cTexture->disable();

}


void Slider::createTexture(void) {
   if ((_cTexture = kernel->getWidgetTexture(Kernel::slider)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(16, 32);
   kernel->setWidgetTexture(Kernel::slider, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // left up
   MatrixTemplate<ColorRGBA> pine(10, 18, ColorRGBA(0,0,0,0));

   // line 0
   Texture2D::drawPoint(pine, Point( 0, 0),ColorRGBA(203,203,203,100));
   Texture2D::drawPoint(pine, Point( 1, 0),ColorRGBA(144,144,144,255));
   Texture2D::drawPoint(pine, Point( 2, 0),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 3, 0),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 4, 0),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 5, 0),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 6, 0),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 7, 0),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 8, 0),ColorRGBA(144,144,144,255));
   Texture2D::drawPoint(pine, Point( 9, 0),ColorRGBA(203,203,203,100));

   // line 1
   Texture2D::drawPoint(pine, Point( 0, 1),ColorRGBA(144,144,144,255));
   Texture2D::drawPoint(pine, Point( 1, 1),ColorRGBA(221,221,221,255));
   Texture2D::drawPoint(pine, Point( 2, 1),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 3, 1),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 4, 1),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 5, 1),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 6, 1),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 7, 1),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 8, 1),ColorRGBA(221,221,221,255));
   Texture2D::drawPoint(pine, Point( 9, 1),ColorRGBA(137,137,137,255));

   // line 2
   Texture2D::drawPoint(pine, Point( 0, 2),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 2),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 2, 2),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(pine, Point( 3, 2),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(pine, Point( 4, 2),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(pine, Point( 5, 2),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(pine, Point( 6, 2),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(pine, Point( 7, 2),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(pine, Point( 8, 2),ColorRGBA(252,252,252,255));
   Texture2D::drawPoint(pine, Point( 9, 2),ColorRGBA(112,112,112,255));

   // line 3
   Texture2D::drawPoint(pine, Point( 0, 3),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 3),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 2, 3),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(pine, Point( 3, 3),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(pine, Point( 4, 3),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(pine, Point( 5, 3),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(pine, Point( 6, 3),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(pine, Point( 7, 3),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(pine, Point( 8, 3),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 9, 3),ColorRGBA(112,112,112,255));

   // line 4
   Texture2D::drawPoint(pine, Point( 0, 4),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 4),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 2, 4),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(pine, Point( 3, 4),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(pine, Point( 4, 4),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(pine, Point( 5, 4),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(pine, Point( 6, 4),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(pine, Point( 7, 4),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(pine, Point( 8, 4),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 9, 4),ColorRGBA(112,112,112,255));

   // line 5
   Texture2D::drawPoint(pine, Point( 0, 5),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 5),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 2, 5),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(pine, Point( 3, 5),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(pine, Point( 4, 5),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(pine, Point( 5, 5),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(pine, Point( 6, 5),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(pine, Point( 7, 5),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(pine, Point( 8, 5),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 9, 5),ColorRGBA(112,112,112,255));

   // line 6
   Texture2D::drawPoint(pine, Point( 0, 6),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 6),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 2, 6),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(pine, Point( 3, 6),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(pine, Point( 4, 6),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(pine, Point( 5, 6),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(pine, Point( 6, 6),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(pine, Point( 7, 6),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(pine, Point( 8, 6),ColorRGBA(251,251,251,255));
   Texture2D::drawPoint(pine, Point( 9, 6),ColorRGBA(112,112,112,255));

   // line 7
   Texture2D::drawPoint(pine, Point( 0, 7),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 7),ColorRGBA(250,250,250,255));
   Texture2D::drawPoint(pine, Point( 2, 7),ColorRGBA(236,236,236,255));
   Texture2D::drawPoint(pine, Point( 3, 7),ColorRGBA(236,236,236,255));
   Texture2D::drawPoint(pine, Point( 4, 7),ColorRGBA(236,236,236,255));
   Texture2D::drawPoint(pine, Point( 5, 7),ColorRGBA(236,236,236,255));
   Texture2D::drawPoint(pine, Point( 6, 7),ColorRGBA(236,236,236,255));
   Texture2D::drawPoint(pine, Point( 7, 7),ColorRGBA(236,236,236,255));
   Texture2D::drawPoint(pine, Point( 8, 7),ColorRGBA(250,250,250,255));
   Texture2D::drawPoint(pine, Point( 9, 7),ColorRGBA(112,112,112,255));

   // line 8
   Texture2D::drawPoint(pine, Point( 0, 8),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 8),ColorRGBA(250,250,250,255));
   Texture2D::drawPoint(pine, Point( 2, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(pine, Point( 3, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(pine, Point( 4, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(pine, Point( 5, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(pine, Point( 6, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(pine, Point( 7, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(pine, Point( 8, 8),ColorRGBA(250,250,250,255));
   Texture2D::drawPoint(pine, Point( 9, 8),ColorRGBA(112,112,112,255));

   // line 9
   Texture2D::drawPoint(pine, Point( 0, 9),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 9),ColorRGBA(246,246,246,255));
   Texture2D::drawPoint(pine, Point( 2, 9),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(pine, Point( 3, 9),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(pine, Point( 4, 9),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(pine, Point( 5, 9),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(pine, Point( 6, 9),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(pine, Point( 7, 9),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(pine, Point( 8, 9),ColorRGBA(246,246,246,255));
   Texture2D::drawPoint(pine, Point( 9, 9),ColorRGBA(112,112,112,255));

   // line 10
   Texture2D::drawPoint(pine, Point( 0, 10),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 10),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(pine, Point( 2, 10),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 3, 10),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 4, 10),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 5, 10),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 6, 10),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 7, 10),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 8, 10),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(pine, Point( 9, 10),ColorRGBA(112,112,112,255));

   // line 11
   Texture2D::drawPoint(pine, Point( 0, 11),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 11),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(pine, Point( 2, 11),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 3, 11),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 4, 11),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 5, 11),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 6, 11),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 7, 11),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 8, 11),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(pine, Point( 9, 11),ColorRGBA(112,112,112,255));

   // line 12
   Texture2D::drawPoint(pine, Point( 0, 12),ColorRGBA(112,112,112,255));
   Texture2D::drawPoint(pine, Point( 1, 12),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(pine, Point( 2, 12),ColorRGBA(218,218,218,255));
   Texture2D::drawPoint(pine, Point( 3, 12),ColorRGBA(214,214,214,255));
   Texture2D::drawPoint(pine, Point( 4, 12),ColorRGBA(214,214,214,255));
   Texture2D::drawPoint(pine, Point( 5, 12),ColorRGBA(214,214,214,255));
   Texture2D::drawPoint(pine, Point( 6, 12),ColorRGBA(214,214,214,255));
   Texture2D::drawPoint(pine, Point( 7, 12),ColorRGBA(218,218,218,255));
   Texture2D::drawPoint(pine, Point( 8, 12),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(pine, Point( 9, 12),ColorRGBA(112,112,112,255));

   // line 13
   Texture2D::drawPoint(pine, Point( 0, 13),ColorRGBA(171,171,171,150));
   Texture2D::drawPoint(pine, Point( 1, 13),ColorRGBA(182,182,182,255));
   Texture2D::drawPoint(pine, Point( 2, 13),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(pine, Point( 3, 13),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 4, 13),ColorRGBA(212,212,212,255));
   Texture2D::drawPoint(pine, Point( 5, 13),ColorRGBA(212,212,212,255));
   Texture2D::drawPoint(pine, Point( 6, 13),ColorRGBA(217,217,217,255));
   Texture2D::drawPoint(pine, Point( 7, 13),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(pine, Point( 8, 13),ColorRGBA(182,182,182,255));
   Texture2D::drawPoint(pine, Point( 9, 13),ColorRGBA(117,117,117,255));

   // line 14
   Texture2D::drawPoint(pine, Point( 1, 14),ColorRGBA(161,161,161,255));
   Texture2D::drawPoint(pine, Point( 2, 14),ColorRGBA(180,180,180,255));
   Texture2D::drawPoint(pine, Point( 3, 14),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(pine, Point( 4, 14),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 5, 14),ColorRGBA(215,215,215,255));
   Texture2D::drawPoint(pine, Point( 6, 14),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(pine, Point( 7, 14),ColorRGBA(180,180,180,255));
   Texture2D::drawPoint(pine, Point( 8, 14),ColorRGBA(106,106,106,255));
   Texture2D::drawPoint(pine, Point( 9, 14),ColorRGBA(158,158,158,150));

   // line 15
   Texture2D::drawPoint(pine, Point( 2, 15),ColorRGBA(156,156,156,255));
   Texture2D::drawPoint(pine, Point( 3, 15),ColorRGBA(180,180,180,255));
   Texture2D::drawPoint(pine, Point( 4, 15),ColorRGBA(243,243,243,255));
   Texture2D::drawPoint(pine, Point( 5, 15),ColorRGBA(243,243,243,255));
   Texture2D::drawPoint(pine, Point( 6, 15),ColorRGBA(180,180,180,255));
   Texture2D::drawPoint(pine, Point( 7, 15),ColorRGBA(107,107,107,255));
   Texture2D::drawPoint(pine, Point( 8, 15),ColorRGBA(153,153,153,150));

   // line 16
   Texture2D::drawPoint(pine, Point( 3, 16),ColorRGBA(156,156,156,255));
   Texture2D::drawPoint(pine, Point( 4, 16),ColorRGBA(178,178,178,255));
   Texture2D::drawPoint(pine, Point( 5, 16),ColorRGBA(180,180,180,255));
   Texture2D::drawPoint(pine, Point( 6, 16),ColorRGBA(109,109,109,255));
   Texture2D::drawPoint(pine, Point( 7, 16),ColorRGBA(153,153,153,150));

   // line 17
   Texture2D::drawPoint(pine, Point( 4, 17),ColorRGBA(164,164,164,255));
   Texture2D::drawPoint(pine, Point( 5, 17),ColorRGBA(143,143,143,255));
   Texture2D::drawPoint(pine, Point( 6, 17),ColorRGBA(169,169,169,150));

   _cTexture->addTexture(Point(0,0), pine);

   MatrixTemplate<ColorRGBA> iBorder(1, 1, ColorRGBA(231,234,234,255));
   _cTexture->addTexture(Point(0,19), iBorder);

   MatrixTemplate<ColorRGBA> oBorder(1, 1, ColorRGBA(176,176,176,255));
   _cTexture->addTexture(Point(0,20), oBorder);

   _cTexture->createTexture();
}

void Slider::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();

   Component::processMouse(evt);

   if(!_receivingCallbacks) return;

   if (isFocused()) {
      
      if (isInside(evt.getPosition()) && evt.getState() == MouseEvent::CLICK) {
         _isDragging = false;
         double value = (static_cast<double>(evt.getPosition().x-(getAbsolutePosition().x+4))/(getWidth()-8)) * (static_cast<double>(getMaxValue()-getMinValue()));
         setValue(math::nearestValue(value, getMinValue() + getStep() * (int)((value-getMinValue())/getStep()), getMinValue() + getStep() * (1+(int)((value-getMinValue())/getStep()))));
      } else if (evt.getState() == MouseEvent::HOLD && isDragging() == false) {
         onMouseHold(evt);
         double value = (static_cast<double>(evt.getPosition().x-(getAbsolutePosition().x+4))/(getWidth()-8)) * (static_cast<double>(getMaxValue()-getMinValue()));
         setValue(math::nearestValue(value, getMinValue() + getStep() * (int)((value-getMinValue())/getStep()), std::min(getMaxValue(), getMinValue() + getStep() * (1+(int)((value-getMinValue())/getStep())))));
         cursor->requestDefaultCursor();
      }     
   }

}

void Slider::processKey(const scv::KeyEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Component::processKey(evt);

   if(!_receivingCallbacks) return;

   if (isFocused() && evt.getState() == KeyEvent::DOWN) {
      if (evt.getKeyString() == "Left") DecrementStep();
      else if (evt.getKeyString() == "Right") IncrementStep();
   }
}

} // namespace scv