#include "stdafx.h"
#include "ComponentWithTexture.h"
#include "Kernel.h"

namespace scv {

ComponentWithTexture::ComponentWithTexture(const scv::Point &p1, const scv::Point &p2)
   : Component(p1, p2), _cTexture(0)
{
}

} // namespace scv
