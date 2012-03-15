#include "GenericNode.h"

namespace scv {

GenericNode::GenericNode(const std::string& label)
   : label(label), userData(0), open(false)
{
}

GenericNode::GenericNode(const std::string& label, int userData)
   : label(label), userData(userData), open(false)
{
}

GenericNode::~GenericNode()
{
   /* TODO MEMORY LEAKS */
}

}