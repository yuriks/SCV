#include "GenericNode.h"

namespace scv {

GenericNode::GenericNode(const std::string& label, int userData)
   : label(label), userData(userData), open(false)
{
}

GenericNode::~GenericNode()
{
   for (unsigned int i = 0; i < children.size(); ++i)
      delete children[i];
}

}