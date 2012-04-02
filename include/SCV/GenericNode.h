#ifndef _SCV_GENERIC_NODE_H_
#define _SCV_GENERIC_NODE_H_

#include <string>
#include <vector>

/*!
\file       GenericNode.h
\brief      
\author     SCV Team
*/

namespace scv {

 /*! class used to create each node of the genericTree.
 */

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
