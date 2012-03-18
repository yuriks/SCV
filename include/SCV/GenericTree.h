/*!
\file       GenericTree.h
\brief      Implementation of a GenericTree.
\author     SCV Team
*/

#ifndef _SCV_GENERIC_TREE_H_
#define _SCV_GENERIC_TREE_H_

#include "GenericNode.h"
#include "ComponentWithTexture.h"
#include "GenericNodeDisplay.h"

namespace scv {

/*! class used to create a generic tree which can link each
 * node to an id (function, integer...)
 */

class GenericTree : public ComponentWithTexture
{
public:

   ///////////////////////////////////////////////////////////
   GenericTree(scv::Point p1, scv::Point p2, GenericNode* root);
   virtual ~GenericTree(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   GenericNode* getSelectedNode(void);
   GenericNode* getRootNode();
   ///////////////////////////////////////////////////////////

   virtual void onItemSelected(void);

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void display(void);
   ///////////////////////////////////////////////////////////

private:
   GenericNode* GenericTree::findSelected(GenericNode*, int, std::string, int espacos);
   virtual void createTexture(void);   

   static const int s_lineSpacing  = 12;
   static const int s_borderWidth  = 4;
   static const int s_borderHeight = 3;
   static const int s_imageSpace   = 26;
      
   int  m_selectStart, m_selectEnd;
   int m_firstLine, m_nLines, spaceBack;

   GenericNode* _nodeSelected;
   GenericNode* _nodeRoot;
   int _jumpOnFindSelected;
   std::vector<GenericNodeDisplay> _nodesDisplay;
};

///////////////////////////////////////////////////////////
inline GenericNode* GenericTree::getSelectedNode(void) {
   return _nodeSelected;
}

inline GenericNode* GenericTree::getRootNode() {
   return _nodeRoot;
}
///////////////////////////////////////////////////////////
} //namespace scv

#endif