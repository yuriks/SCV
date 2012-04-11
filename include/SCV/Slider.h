/*!
\file       Slider.h
\brief      Implementation of a Slider.
\author     SCV Team
*/

#ifndef __SCV_SLIDER_H__
#define __SCV_SLIDER_H__

#include "Component.h"
#include "ComponentTexture.h"
#include "Counter.h"

namespace scv {

class Slider : public Component, public Counter {
public:
   Slider(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   Slider(const scv::Point &p,                     double minValue, double maxValue, double startValue, double stepValue);
   virtual ~Slider() {}

   virtual void onValueChange(void);
   
   inline virtual void setEditable(bool edit);
   inline virtual bool isEditable();


   virtual void display(void);

protected:
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

   bool _editable;

   void createTexture(void);
   ComponentTexture* _cTexture;
};

void Slider::setEditable(bool edit)
{
   _editable = edit;
}


bool Slider::isEditable()
{
   return _editable;
}



} // namespace scv

#endif // __SCV_SLIDER_H__