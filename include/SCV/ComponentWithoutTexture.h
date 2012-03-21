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