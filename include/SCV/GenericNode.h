#ifndef _SCV_GENERIC_NODE_H_
#define _SCV_GENERIC_NODE_H_

/*!
\file       GenericNode.h
\brief      Implementation of GenericNode.
\author     SCV Team
*/

namespace scv {

struct GenericNode
{
   GenericNode(const std::string& label, int userData = 0);
   ~GenericNode();

   std::string label;
   int userData;
   std::vector<GenericNode*> children;
   bool open;
};

}

#endif