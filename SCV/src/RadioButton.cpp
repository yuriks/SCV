#include "stdafx.h"
#include "RadioButton.h"
#include "Kernel.h"
#include "StaticLabel.h"

namespace scv {

RadioButton::RadioButton(const scv::Point &p1, bool state, const std::string &str) : StateButton(state), Label(p1, Point(p1.x + 13 + FontTahoma::getInstance()->getStringLength(str) + 3,p1.y + 13), str) {
   _isHResizable = _isVResizable = false;
   _type = RADIOBUTTON;

   createTexture();
}

void RadioButton::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
      scheme->applyDefaultModulate();
      if (getState() == false) {
         _cTexture->display(currPosition, 0);
      } else {
         _cTexture->display(currPosition, 1);
      }
      if (isHolded()) {
         scheme->applyColor(ColorScheme::HOLDCOMPONENTS);
         _cTexture->display(currPosition, 2);
      } else if (isOvered()) {
         scheme->applyColor(ColorScheme::OVERCOMPONENTS);
         _cTexture->display(currPosition, 3);
      }
   _cTexture->disable();

   scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() + font->getStringLength(Label::getString()) + 3, getHeight()));

   StaticLabel::display(currPosition.x + 12 + 3, currPosition.y - 1, Label::getString());

   scissor->popScissor();
}

void RadioButton::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(RADIOBUTTON)) != NULL) return;

   ColorRGBA colorOver(170,220,255,60);
   ColorRGBA colorClick(colorOver[0] - 100, colorOver[1] - 80, colorOver[2] - 40, colorOver[3]);

   ColorRGBA BackgroundColor(112,112,112,0);

   // create texture object
   _cTexture = new ComponentTexture(64, 16);
   kernel->setWidgetTexture(RADIOBUTTON, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);

   // !selected
   MatrixTemplate<ColorRGBA> nSelected(12, 12, ColorRGBA(0,0,0,0));

   // line 0
   Texture2D::drawPoint(nSelected, Point( 3, 0),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(nSelected, Point( 4, 0),ColorRGBA(166,167,167,255));
   Texture2D::drawPoint(nSelected, Point( 5, 0),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(nSelected, Point( 6, 0),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(nSelected, Point( 7, 0),ColorRGBA(166,167,167,255));
   Texture2D::drawPoint(nSelected, Point( 8, 0),ColorRGBA(159,160,160,100));

   // line 1
   Texture2D::drawPoint(nSelected, Point( 2, 1),ColorRGBA(160,161,161,255));
   Texture2D::drawPoint(nSelected, Point( 3, 1),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(nSelected, Point( 4, 1),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(nSelected, Point( 5, 1),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(nSelected, Point( 6, 1),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(nSelected, Point( 7, 1),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(nSelected, Point( 8, 1),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(nSelected, Point( 9, 1),ColorRGBA(160,161,161,255));

   // line 2
   Texture2D::drawPoint(nSelected, Point( 1, 2),ColorRGBA(159,160,160,255));
   Texture2D::drawPoint(nSelected, Point( 2, 2),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(nSelected, Point( 3, 2),ColorRGBA(237,237,238,255));
   Texture2D::drawPoint(nSelected, Point( 4, 2),ColorRGBA(198,201,205,255));
   Texture2D::drawPoint(nSelected, Point( 5, 2),ColorRGBA(181,186,191,255));
   Texture2D::drawPoint(nSelected, Point( 6, 2),ColorRGBA(181,186,191,255));
   Texture2D::drawPoint(nSelected, Point( 7, 2),ColorRGBA(200,203,206,255));
   Texture2D::drawPoint(nSelected, Point( 8, 2),ColorRGBA(237,238,238,255));
   Texture2D::drawPoint(nSelected, Point( 9, 2),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(nSelected, Point( 10, 2),ColorRGBA(159,160,160,255));

   // line 3
   Texture2D::drawPoint(nSelected, Point( 0, 3),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(nSelected, Point( 1, 3),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(nSelected, Point( 2, 3),ColorRGBA(233,234,235,255));
   Texture2D::drawPoint(nSelected, Point( 3, 3),ColorRGBA(179,184,189,255));
   Texture2D::drawPoint(nSelected, Point( 4, 3),ColorRGBA(189,194,199,255));
   Texture2D::drawPoint(nSelected, Point( 5, 3),ColorRGBA(200,205,210,255));
   Texture2D::drawPoint(nSelected, Point( 6, 3),ColorRGBA(201,206,211,255));
   Texture2D::drawPoint(nSelected, Point( 7, 3),ColorRGBA(197,200,204,255));
   Texture2D::drawPoint(nSelected, Point( 8, 3),ColorRGBA(190,193,197,255));
   Texture2D::drawPoint(nSelected, Point( 9, 3),ColorRGBA(235,236,236,255));
   Texture2D::drawPoint(nSelected, Point( 10, 3),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(nSelected, Point( 11, 3),ColorRGBA(159,160,160,100));

   // line 4
   Texture2D::drawPoint(nSelected, Point( 0, 4),ColorRGBA(165,165,165,255));
   Texture2D::drawPoint(nSelected, Point( 1, 4),ColorRGBA(220,220,220,255));
   Texture2D::drawPoint(nSelected, Point( 2, 4),ColorRGBA(197,200,204,255));
   Texture2D::drawPoint(nSelected, Point( 3, 4),ColorRGBA(190,195,201,255));
   Texture2D::drawPoint(nSelected, Point( 4, 4),ColorRGBA(203,207,213,255));
   Texture2D::drawPoint(nSelected, Point( 5, 4),ColorRGBA(206,210,215,255));
   Texture2D::drawPoint(nSelected, Point( 6, 4),ColorRGBA(213,216,220,255));
   Texture2D::drawPoint(nSelected, Point( 7, 4),ColorRGBA(220,222,224,255));
   Texture2D::drawPoint(nSelected, Point( 8, 4),ColorRGBA(211,212,215,255));
   Texture2D::drawPoint(nSelected, Point( 9, 4),ColorRGBA(212,213,213,255));
   Texture2D::drawPoint(nSelected, Point( 10, 4),ColorRGBA(220,220,220,255));
   Texture2D::drawPoint(nSelected, Point( 11, 4),ColorRGBA(165,165,165,255));

   // line 5
   Texture2D::drawPoint(nSelected, Point( 0, 5),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(nSelected, Point( 1, 5),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(nSelected, Point( 2, 5),ColorRGBA(180,185,189,255));
   Texture2D::drawPoint(nSelected, Point( 3, 5),ColorRGBA(205,209,214,255));
   Texture2D::drawPoint(nSelected, Point( 4, 5),ColorRGBA(211,214,218,255));
   Texture2D::drawPoint(nSelected, Point( 5, 5),ColorRGBA(219,221,223,255));
   Texture2D::drawPoint(nSelected, Point( 6, 5),ColorRGBA(228,228,229,255));
   Texture2D::drawPoint(nSelected, Point( 7, 5),ColorRGBA(233,233,233,255));
   Texture2D::drawPoint(nSelected, Point( 8, 5),ColorRGBA(232,232,233,255));
   Texture2D::drawPoint(nSelected, Point( 9, 5),ColorRGBA(208,209,210,255));
   Texture2D::drawPoint(nSelected, Point( 10, 5),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(nSelected, Point( 11, 5),ColorRGBA(145,146,146,255));

   // line 6
   Texture2D::drawPoint(nSelected, Point( 0, 6),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(nSelected, Point( 1, 6),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(nSelected, Point( 2, 6),ColorRGBA(187,190,194,255));
   Texture2D::drawPoint(nSelected, Point( 3, 6),ColorRGBA(215,218,221,255));
   Texture2D::drawPoint(nSelected, Point( 4, 6),ColorRGBA(224,225,227,255));
   Texture2D::drawPoint(nSelected, Point( 5, 6),ColorRGBA(233,233,233,255));
   Texture2D::drawPoint(nSelected, Point( 6, 6),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(nSelected, Point( 7, 6),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(nSelected, Point( 8, 6),ColorRGBA(239,239,240,255));
   Texture2D::drawPoint(nSelected, Point( 9, 6),ColorRGBA(219,220,220,255));
   Texture2D::drawPoint(nSelected, Point( 10, 6),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(nSelected, Point( 11, 6),ColorRGBA(146,147,147,255));

   // line 7
   Texture2D::drawPoint(nSelected, Point( 0, 7),ColorRGBA(164,165,165,255));
   Texture2D::drawPoint(nSelected, Point( 1, 7),ColorRGBA(221,221,221,255));
   Texture2D::drawPoint(nSelected, Point( 2, 7),ColorRGBA(207,209,211,255));
   Texture2D::drawPoint(nSelected, Point( 3, 7),ColorRGBA(213,214,216,255));
   Texture2D::drawPoint(nSelected, Point( 4, 7),ColorRGBA(233,233,233,255));
   Texture2D::drawPoint(nSelected, Point( 5, 7),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(nSelected, Point( 6, 7),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(nSelected, Point( 7, 7),ColorRGBA(245,245,245,255));
   Texture2D::drawPoint(nSelected, Point( 8, 7),ColorRGBA(238,238,238,255));
   Texture2D::drawPoint(nSelected, Point( 9, 7),ColorRGBA(232,232,232,255));
   Texture2D::drawPoint(nSelected, Point( 10, 7),ColorRGBA(221,221,221,255));
   Texture2D::drawPoint(nSelected, Point( 11, 7),ColorRGBA(164,165,165,255));

   // line 8
   Texture2D::drawPoint(nSelected, Point( 0, 8),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(nSelected, Point( 1, 8),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(nSelected, Point( 2, 8),ColorRGBA(236,236,237,255));
   Texture2D::drawPoint(nSelected, Point( 3, 8),ColorRGBA(205,206,207,255));
   Texture2D::drawPoint(nSelected, Point( 4, 8),ColorRGBA(225,226,226,255));
   Texture2D::drawPoint(nSelected, Point( 5, 8),ColorRGBA(240,240,240,255));
   Texture2D::drawPoint(nSelected, Point( 6, 8),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(nSelected, Point( 7, 8),ColorRGBA(241,241,241,255));
   Texture2D::drawPoint(nSelected, Point( 8, 8),ColorRGBA(235,235,235,255));
   Texture2D::drawPoint(nSelected, Point( 9, 8),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(nSelected, Point( 10, 8),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(nSelected, Point( 11, 8),ColorRGBA(159,160,160,100));

   // line 9
   Texture2D::drawPoint(nSelected, Point( 1, 9),ColorRGBA(159,160,160,255));
   Texture2D::drawPoint(nSelected, Point( 2, 9),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(nSelected, Point( 3, 9),ColorRGBA(240,240,241,255));
   Texture2D::drawPoint(nSelected, Point( 4, 9),ColorRGBA(226,227,227,255));
   Texture2D::drawPoint(nSelected, Point( 5, 9),ColorRGBA(228,228,229,255));
   Texture2D::drawPoint(nSelected, Point( 6, 9),ColorRGBA(233,234,234,255));
   Texture2D::drawPoint(nSelected, Point( 7, 9),ColorRGBA(238,238,239,255));
   Texture2D::drawPoint(nSelected, Point( 8, 9),ColorRGBA(243,243,243,255));
   Texture2D::drawPoint(nSelected, Point( 9, 9),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(nSelected, Point( 10, 9),ColorRGBA(159,160,160,255));

   // line 10
   Texture2D::drawPoint(nSelected, Point( 2, 10),ColorRGBA(159,160,160,255));
   Texture2D::drawPoint(nSelected, Point( 3, 10),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(nSelected, Point( 4, 10),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(nSelected, Point( 5, 10),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(nSelected, Point( 6, 10),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(nSelected, Point( 7, 10),ColorRGBA(220,220,220,255));
   Texture2D::drawPoint(nSelected, Point( 8, 10),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(nSelected, Point( 9, 10),ColorRGBA(159,160,160,255));

   // line 11
   Texture2D::drawPoint(nSelected, Point( 3, 11),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(nSelected, Point( 4, 11),ColorRGBA(166,167,167,255));
   Texture2D::drawPoint(nSelected, Point( 5, 11),ColorRGBA(142,143,143,255));
   Texture2D::drawPoint(nSelected, Point( 6, 11),ColorRGBA(142,143,143,255));
   Texture2D::drawPoint(nSelected, Point( 7, 11),ColorRGBA(165,165,165,255));
   Texture2D::drawPoint(nSelected, Point( 8, 11),ColorRGBA(159,160,160,100));

   _cTexture->addTexture(Point(0,0), nSelected);


   // selected
   MatrixTemplate<ColorRGBA> selected(12, 12, ColorRGBA(0,0,0,0));

   // line 0
   Texture2D::drawPoint(selected, Point( 3, 0),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(selected, Point( 4, 0),ColorRGBA(166,167,167,255));
   Texture2D::drawPoint(selected, Point( 5, 0),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(selected, Point( 6, 0),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(selected, Point( 7, 0),ColorRGBA(166,167,167,255));
   Texture2D::drawPoint(selected, Point( 8, 0),ColorRGBA(159,160,160,100));

   // line 1
   Texture2D::drawPoint(selected, Point( 2, 1),ColorRGBA(160,161,161,255));
   Texture2D::drawPoint(selected, Point( 3, 1),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(selected, Point( 4, 1),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(selected, Point( 5, 1),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(selected, Point( 6, 1),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(selected, Point( 7, 1),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(selected, Point( 8, 1),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(selected, Point( 9, 1),ColorRGBA(160,161,161,255));

   // line 2
   Texture2D::drawPoint(selected, Point( 1, 2),ColorRGBA(159,160,160,255));
   Texture2D::drawPoint(selected, Point( 2, 2),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(selected, Point( 3, 2),ColorRGBA(237,237,238,255));
   Texture2D::drawPoint(selected, Point( 4, 2),ColorRGBA(186,191,197,255));
   Texture2D::drawPoint(selected, Point( 5, 2),ColorRGBA(133,147,159,255));
   Texture2D::drawPoint(selected, Point( 6, 2),ColorRGBA(133,147,159,255));
   Texture2D::drawPoint(selected, Point( 7, 2),ColorRGBA(188,193,197,255));
   Texture2D::drawPoint(selected, Point( 8, 2),ColorRGBA(237,238,238,255));
   Texture2D::drawPoint(selected, Point( 9, 2),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(selected, Point( 10, 2),ColorRGBA(159,160,160,255));

   // line 3
   Texture2D::drawPoint(selected, Point( 0, 3),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(selected, Point( 1, 3),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(selected, Point( 2, 3),ColorRGBA(233,234,235,255));
   Texture2D::drawPoint(selected, Point( 3, 3),ColorRGBA(137,151,162,255));
   Texture2D::drawPoint(selected, Point( 4, 3),ColorRGBA(39,71,96,255));
   Texture2D::drawPoint(selected, Point( 5, 3),ColorRGBA(72,99,120,255));
   Texture2D::drawPoint(selected, Point( 6, 3),ColorRGBA(54,81,102,255));
   Texture2D::drawPoint(selected, Point( 7, 3),ColorRGBA(32,64,88,255));
   Texture2D::drawPoint(selected, Point( 8, 3),ColorRGBA(142,154,164,255));
   Texture2D::drawPoint(selected, Point( 9, 3),ColorRGBA(235,236,236,255));
   Texture2D::drawPoint(selected, Point( 10, 3),ColorRGBA(185,186,186,255));
   Texture2D::drawPoint(selected, Point( 11, 3),ColorRGBA(159,160,160,100));

   // line 4
   Texture2D::drawPoint(selected, Point( 0, 4),ColorRGBA(165,165,165,255));
   Texture2D::drawPoint(selected, Point( 1, 4),ColorRGBA(220,220,220,255));
   Texture2D::drawPoint(selected, Point( 2, 4),ColorRGBA(185,190,196,255));
   Texture2D::drawPoint(selected, Point( 3, 4),ColorRGBA(36,68,93,255));
   Texture2D::drawPoint(selected, Point( 4, 4),ColorRGBA(145,178,198,255));
   Texture2D::drawPoint(selected, Point( 5, 4),ColorRGBA(199,235,253,255));
   Texture2D::drawPoint(selected, Point( 6, 4),ColorRGBA(105,194,212,255));
   Texture2D::drawPoint(selected, Point( 7, 4),ColorRGBA(20,64,92,255));
   Texture2D::drawPoint(selected, Point( 8, 4),ColorRGBA(30,63,87,255));
   Texture2D::drawPoint(selected, Point( 9, 4),ColorRGBA(201,204,205,255));
   Texture2D::drawPoint(selected, Point( 10, 4),ColorRGBA(220,220,220,255));
   Texture2D::drawPoint(selected, Point( 11, 4),ColorRGBA(165,165,165,255));

   // line 5
   Texture2D::drawPoint(selected, Point( 0, 5),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(selected, Point( 1, 5),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(selected, Point( 2, 5),ColorRGBA(125,141,152,255));
   Texture2D::drawPoint(selected, Point( 3, 5),ColorRGBA(48,75,95,255));
   Texture2D::drawPoint(selected, Point( 4, 5),ColorRGBA(144,213,229,255));
   Texture2D::drawPoint(selected, Point( 5, 5),ColorRGBA(93,206,221,255));
   Texture2D::drawPoint(selected, Point( 6, 5),ColorRGBA(40,162,209,255));
   Texture2D::drawPoint(selected, Point( 7, 5),ColorRGBA(23,138,199,255));
   Texture2D::drawPoint(selected, Point( 8, 5),ColorRGBA(24,51,72,255));
   Texture2D::drawPoint(selected, Point( 9, 5),ColorRGBA(143,156,166,255));
   Texture2D::drawPoint(selected, Point( 10, 5),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(selected, Point( 11, 5),ColorRGBA(145,146,146,255));

   // line 6
   Texture2D::drawPoint(selected, Point( 0, 6),ColorRGBA(145,146,146,255));
   Texture2D::drawPoint(selected, Point( 1, 6),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(selected, Point( 2, 6),ColorRGBA(130,144,156,255));
   Texture2D::drawPoint(selected, Point( 3, 6),ColorRGBA(24,51,71,255));
   Texture2D::drawPoint(selected, Point( 4, 6),ColorRGBA(34,143,198,255));
   Texture2D::drawPoint(selected, Point( 5, 6),ColorRGBA(32,157,209,255));
   Texture2D::drawPoint(selected, Point( 6, 6),ColorRGBA(24,152,209,255));
   Texture2D::drawPoint(selected, Point( 7, 6),ColorRGBA(14,132,198,255));
   Texture2D::drawPoint(selected, Point( 8, 6),ColorRGBA(24,51,72,255));
   Texture2D::drawPoint(selected, Point( 9, 6),ColorRGBA(151,163,172,255));
   Texture2D::drawPoint(selected, Point( 10, 6),ColorRGBA(239,239,239,255));
   Texture2D::drawPoint(selected, Point( 11, 6),ColorRGBA(146,147,147,255));

   // line 7
   Texture2D::drawPoint(selected, Point( 0, 7),ColorRGBA(164,165,165,255));
   Texture2D::drawPoint(selected, Point( 1, 7),ColorRGBA(221,221,221,255));
   Texture2D::drawPoint(selected, Point( 2, 7),ColorRGBA(192,197,201,255));
   Texture2D::drawPoint(selected, Point( 3, 7),ColorRGBA(30,63,87,255));
   Texture2D::drawPoint(selected, Point( 4, 7),ColorRGBA(15,63,93,255));
   Texture2D::drawPoint(selected, Point( 5, 7),ColorRGBA(15,131,199,255));
   Texture2D::drawPoint(selected, Point( 6, 7),ColorRGBA(11,130,199,255));
   Texture2D::drawPoint(selected, Point( 7, 7),ColorRGBA(12,61,93,255));
   Texture2D::drawPoint(selected, Point( 8, 7),ColorRGBA(31,63,88,255));
   Texture2D::drawPoint(selected, Point( 9, 7),ColorRGBA(217,220,222,255));
   Texture2D::drawPoint(selected, Point( 10, 7),ColorRGBA(221,221,221,255));
   Texture2D::drawPoint(selected, Point( 11, 7),ColorRGBA(164,165,165,255));

   // line 8
   Texture2D::drawPoint(selected, Point( 0, 8),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(selected, Point( 1, 8),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(selected, Point( 2, 8),ColorRGBA(236,236,237,255));
   Texture2D::drawPoint(selected, Point( 3, 8),ColorRGBA(153,163,171,255));
   Texture2D::drawPoint(selected, Point( 4, 8),ColorRGBA(29,62,87,255));
   Texture2D::drawPoint(selected, Point( 5, 8),ColorRGBA(24,53,74,255));
   Texture2D::drawPoint(selected, Point( 6, 8),ColorRGBA(25,52,74,255));
   Texture2D::drawPoint(selected, Point( 7, 8),ColorRGBA(30,62,87,255));
   Texture2D::drawPoint(selected, Point( 8, 8),ColorRGBA(174,184,191,255));
   Texture2D::drawPoint(selected, Point( 9, 8),ColorRGBA(242,242,242,255));
   Texture2D::drawPoint(selected, Point( 10, 8),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(selected, Point( 11, 8),ColorRGBA(159,160,160,100));

   // line 9
   Texture2D::drawPoint(selected, Point( 1, 9),ColorRGBA(159,160,160,255));
   Texture2D::drawPoint(selected, Point( 2, 9),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(selected, Point( 3, 9),ColorRGBA(240,240,241,255));
   Texture2D::drawPoint(selected, Point( 4, 9),ColorRGBA(209,213,215,255));
   Texture2D::drawPoint(selected, Point( 5, 9),ColorRGBA(166,176,185,255));
   Texture2D::drawPoint(selected, Point( 6, 9),ColorRGBA(169,180,188,255));
   Texture2D::drawPoint(selected, Point( 7, 9),ColorRGBA(220,223,226,255));
   Texture2D::drawPoint(selected, Point( 8, 9),ColorRGBA(243,243,243,255));
   Texture2D::drawPoint(selected, Point( 9, 9),ColorRGBA(195,195,195,255));
   Texture2D::drawPoint(selected, Point( 10, 9),ColorRGBA(159,160,160,255));

   // line 10
   Texture2D::drawPoint(selected, Point( 2, 10),ColorRGBA(159,160,160,255));
   Texture2D::drawPoint(selected, Point( 3, 10),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(selected, Point( 4, 10),ColorRGBA(219,219,219,255));
   Texture2D::drawPoint(selected, Point( 5, 10),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(selected, Point( 6, 10),ColorRGBA(244,244,244,255));
   Texture2D::drawPoint(selected, Point( 7, 10),ColorRGBA(220,220,220,255));
   Texture2D::drawPoint(selected, Point( 8, 10),ColorRGBA(186,187,187,255));
   Texture2D::drawPoint(selected, Point( 9, 10),ColorRGBA(159,160,160,255));

   // line 11
   Texture2D::drawPoint(selected, Point( 3, 11),ColorRGBA(159,160,160,100));
   Texture2D::drawPoint(selected, Point( 4, 11),ColorRGBA(166,167,167,255));
   Texture2D::drawPoint(selected, Point( 5, 11),ColorRGBA(142,143,143,255));
   Texture2D::drawPoint(selected, Point( 6, 11),ColorRGBA(142,143,143,255));
   Texture2D::drawPoint(selected, Point( 7, 11),ColorRGBA(165,165,165,255));
   Texture2D::drawPoint(selected, Point( 8, 11),ColorRGBA(159,160,160,100));

   _cTexture->addTexture(Point(12,0), selected);

   // hold
   MatrixTemplate<ColorRGBA> over(12, 12, ColorRGBA(0,0,0,0));
   Texture2D::rectFill(over, Point(1,1), Point(10, 10), colorClick);
   Texture2D::drawPoint(over,Point(10,1) ,BackgroundColor);
   Texture2D::drawPoint(over,Point(1,10) ,BackgroundColor);
   Texture2D::drawPoint(over,Point(10,10),BackgroundColor);
   Texture2D::drawPoint(over,Point(1,1)  ,BackgroundColor);
   _cTexture->addTexture(Point(24,0), over);

   // over
   MatrixTemplate<ColorRGBA> hold(12, 12, ColorRGBA(0,0,0,0));
   Texture2D::rectFill(hold, Point(1,1), Point(10, 10), colorOver);
   Texture2D::drawPoint(hold,Point(10,1) ,BackgroundColor);
   Texture2D::drawPoint(hold,Point(1,10) ,BackgroundColor);
   Texture2D::drawPoint(hold,Point(10,10),BackgroundColor);
   Texture2D::drawPoint(hold,Point(1,1)  ,BackgroundColor);
   _cTexture->addTexture(Point(36,0), hold);

   _cTexture->createTexture();
}

void RadioButton::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Component::processMouse(evt);

   if(!_receivingCallbacks) return;

   if (isInside(evt.getPosition())) {
      if (evt.getState() == MouseEvent::CLICK && isFocused())
         setState(!getState());
   }
}

void RadioButton::setString(const std::string& str) {
   static FontTahoma *font = FontTahoma::getInstance();
   Label::setString(str);
   setWidth(font->getStringLength(str) + 15);
}

} // namespace scv