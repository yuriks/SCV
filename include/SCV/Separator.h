#ifndef __SCV_SEPARATOR_H__
#define __SCV_SEPARATOR_H__

#include "MatrixTemplate.h"
#include "Component.h"
#include "ComponentTexture.h"

namespace scv {

class Separator : public Component {
public:
   enum Orientation { HORIZONTAL, VERTICAL };
      
   Separator(const scv::Point &p1, Separator::Orientation align, unsigned int size);

   inline Separator::Orientation getAlign(void) const;
   
   virtual void display(void);

protected:
   void createTexture(void);
   ComponentTexture* _cTexture;

   Separator::Orientation _align;   
};

///////////////////////////////////////////////////////////

Separator::Orientation Separator::getAlign(void) const {
   return _align;
}

} // namespace scv

#endif // __SCV_SEPARATOR_H__
