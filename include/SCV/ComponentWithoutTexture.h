#ifndef __SCV_COMPONENT_WITHOUT_TEXTURE_H__
#define __SCV_COMPONENT_WITHOUT_TEXTURE_H__

///////////////////////////////////////////////////////////
#include "Component.h"
///////////////////////////////////////////////////////////

namespace scv {

class ComponentWithoutTexture : public Component {
public:
   ///////////////////////////////////////////////////////////
   ComponentWithoutTexture(const scv::Point &p1, const scv::Point &p2);
   virtual ~ComponentWithoutTexture(void);
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

   virtual void onResizing(void);
   virtual void onDragging(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void render(void);
   virtual void update(void);
   ///////////////////////////////////////////////////////////
   
   void display(void);

protected:
private:
};

} // namespace scv


#endif // __SCV_COMPONENT_WITHOUT_TEXTURE_H__