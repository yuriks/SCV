#ifndef __SCV_SEPARATOR_H__
#define __SCV_SEPARATOR_H__

#include "MatrixTemplate.h"
#include "ComponentWithTexture.h"

namespace scv {

class Separator : public ComponentWithTexture {
public:
   ///////////////////////////////////////////////////////////
   enum Orientation { HORIZONTAL, VERTICAL };
   ///////////////////////////////////////////////////////////
      
   ///////////////////////////////////////////////////////////
   Separator(const scv::Point &p1, Separator::Orientation align, unsigned int size);
   virtual ~Separator(void);
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline Separator::Orientation getAlign(void) const;
   ///////////////////////////////////////////////////////////
   
   virtual void display(void);

protected:
   void createTexture(void);

   Separator::Orientation _align;   
};

///////////////////////////////////////////////////////////

Separator::Orientation Separator::getAlign(void) const {
   return _align;
}

///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_SEPARATOR_H__
