/*!
\file       ProgressBar.h
\brief      Implementation of a ProgressBar.
\author     SCV Team
*/

#ifndef __SCV_PROGRESSBAR_H__
#define __SCV_PROGRESSBAR_H__

#include "Label.h"
#include "Counter.h"

namespace scv {

class ProgressBar : public Label, public Counter {
public:
   ProgressBar(const scv::Point &p1, const scv::Point &p2, double startValue);
   ProgressBar(const scv::Point &p, unsigned int width, double startValue);
   ProgressBar(const scv::Point &p, double startValue);
   virtual ~ProgressBar(void) {}

   virtual void onValueChange(void);
   
   void setValue(double value);

   virtual void display(void);

protected:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_PROGRESSBAR_H__