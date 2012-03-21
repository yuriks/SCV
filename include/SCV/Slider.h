#ifndef __SCV_SLIDER_H__
#define __SCV_SLIDER_H__

#include "ComponentWithTexture.h"
#include "Counter.h"

namespace scv {

class Slider : public ComponentWithTexture, public Counter {
public:
   Slider(const scv::Point &p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);
   Slider(const scv::Point &p,                     double minValue, double maxValue, double startValue, double stepValue);
   virtual ~Slider() {}

   virtual void onValueChange(void);

   virtual void display(void);

protected:
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

   void createTexture(void);
};

} // namespace scv

#endif // __SCV_SLIDER_H__