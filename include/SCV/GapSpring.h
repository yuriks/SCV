#ifndef __SCV_GAP_SPRING_H__
#define __SCV_GAP_SPRING_H__

#include "Spring.h"

namespace scv {

class GapSpring : public Spring {
public:
   ///////////////////////////////////////////////////////////
   GapSpring(int min, int pref, int max);
   virtual ~GapSpring(void);
   ///////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////
   virtual int calculateMinimumSize(Spring::Axis axis);
   virtual int calculatePreferredSize(Spring::Axis axis);
   virtual int calculateMaximumSize(Spring::Axis axis);
   ///////////////////////////////////////////////////////////

protected:
   
private:
};

} //namespace scv

#endif //__SCV_GAP_SPRING_H__