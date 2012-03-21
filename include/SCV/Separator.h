#ifndef __SCV_SEPARATOR_H__
#define __SCV_SEPARATOR_H__

#include "MatrixTemplate.h"
#include "ComponentWithTexture.h"

namespace scv {

class Separator : public ComponentWithTexture {
public:
   enum Orientation { HORIZONTAL, VERTICAL };
      
   Separator(const scv::Point &p1, Separator::Orientation align, unsigned int size);

   inline Separator::Orientation getAlign(void) const;
   
   virtual void display(void);

protected:
   void createTexture(void);

   Separator::Orientation _align;   
};

///////////////////////////////////////////////////////////

Separator::Orientation Separator::getAlign(void) const {
   return _align;
}

} // namespace scv

#endif // __SCV_SEPARATOR_H__
