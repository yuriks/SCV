/*!
\file       GenericTree.h
\brief      Implementation of a GenericTree.
\author     SCV Team
*/

#ifndef _SCV_GENERIC_TREE_H_
#define _SCV_GENERIC_TREE_H_

#include "GenericNode.h"
#include "ComponentWithTexture.h"

namespace scv {

/*! class used to create a generic tree which can link each
 * node to an id (function, integer...)
 */

struct GenericNodeDisplay;

class GenericTree : public ComponentWithTexture
{
public:
   GenericTree(scv::Point p1, scv::Point p2, GenericNode* root);
   virtual ~GenericTree(void);

   GenericNode* getSelectedNode(void);
   GenericNode* getRootNode();
   void refreshDisplay();

   virtual void onItemSelected(void);

   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);

   virtual void display(void);

private:
   GenericNode* GenericTree::findSelected(GenericNode*, int, int espacos);
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

inline GenericNode* GenericTree::getSelectedNode(void) {
   return _nodeSelected;
}

/*! Returns the tree's root node. Edit and add children to this node to fill in the tree.
\note After changing the tree's contents, you must call \c refreshDisplay()
*/
inline GenericNode* GenericTree::getRootNode() {
   return _nodeRoot;
}

} //namespace scv

#endif