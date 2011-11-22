#ifndef __SCV_TREE_VIEW_H__
#define __SCV_TREE_VIEW_H__

#include "GTree.h"
#include "TreeModel.h"

namespace scv {

class SystemTreeView : public ComponentWithTexture {
public:
   /*
   enum TW_types {
      TW_ONLY_FOLDERS, TW_FOLDERS_AND_FILES
   };
    */
   ///////////////////////////////////////////////////////////
   SystemTreeView(scv::Point p1, scv::Point p2, TW_types view = TW_ONLY_FOLDERS );
   virtual ~SystemTreeView(void);
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
   inline const std::string &getLastPath(void);
   inline TW_Content_Types getTypeLastPath(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

private:
   int getSpaces(const std::string &name);
   void addInFolder(void);
   virtual void createTexture(void);   

   static const int s_lineSpacing  = 16;
   static const int s_borderWidth  = 8;
   static const int s_borderHeight = 3;
   static const int s_imageSpace   = 26;
      

   TW_types modeView;

   int  m_selectStart, m_selectEnd;

   GTree *tree;
   TreeModel *tModel;
   int m_firstLine, m_nLines, spaceBack;

   std::string lastPath;
   TW_Content_Types typeLastPath;

   std::vector<GInfoNode> m_nodes;

   bool useCallback;
};

///////////////////////////////////////////////////////////
const std::string &SystemTreeView::getLastPath(void) {
   return lastPath;
}

TW_Content_Types SystemTreeView::getTypeLastPath(void) {
   return typeLastPath;
}
///////////////////////////////////////////////////////////
} //namespace scv

#endif