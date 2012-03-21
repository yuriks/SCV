#ifndef __SCV_COMPONENT_WITH_TEXTURE_H__
#define __SCV_COMPONENT_WITH_TEXTURE_H__

#include "Component.h"
#include "ComponentTexture.h"

namespace scv {

class ComponentWithTexture : public Component {
public:
   ComponentWithTexture(const scv::Point &p1, const scv::Point &p2);

protected:
   virtual void createTexture(void) = 0;
   ComponentTexture *_cTexture;
};

} // namespace scv

#endif // __SCV_COMPONENT_WITH_TEXTURE_H__
