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

class GenericTree : public ComponentWithTexture
{
public:

   ///////////////////////////////////////////////////////////
   GenericTree(scv::Point p1,scv::Point p2);
   GenericTree(scv::Point p1, scv::Point p2, std::string rootNodeName);
   GenericTree(scv::Point p1, scv::Point p2, GenericNode* root);
   virtual ~GenericTree(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline std::string getNameNodeSelected(void);
   inline int getIDNodeSelected(void);
   inline GenericNode* getNodeSelected(void);
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

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   virtual void onItemSelect(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void display(void);
   ///////////////////////////////////////////////////////////

private:
   GenericNode* GenericTree::findSelected(GenericNode*, int, std::string);
   virtual void createTexture(void);   

   static const int s_lineSpacing  = 16;
   static const int s_borderWidth  = 8;
   static const int s_borderHeight = 3;
   static const int s_imageSpace   = 26;
      
   int  m_selectStart, m_selectEnd;
   int m_firstLine, m_nLines, spaceBack;

   GenericNode* _nodeSelected;
   GenericNode* _nodeRoot;
   int _jumpOnFindSelected;
   std::vector<std::string> _nodesDisplay;
   
   bool useCallback;
};

///////////////////////////////////////////////////////////
std::string GenericTree::getNameNodeSelected(void) {
   return _nodeSelected->getName();
}

int GenericTree::getIDNodeSelected(void) {
   return _nodeSelected->getNodeFunction();
}

GenericNode* GenericTree::getNodeSelected(void) {
   return _nodeSelected;
}
///////////////////////////////////////////////////////////
} //namespace scv

#endif