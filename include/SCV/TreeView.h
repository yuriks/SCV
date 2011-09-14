/*!
\file       TreeView.h
\brief      Implementation of a TreeView widget.
\author     SCV Team
*/

#ifndef __SCV_TREE_VIEW_H__
#define __SCV_TREE_VIEW_H__

#include "GTree.h"
#include "TreeModel.h"

namespace scv {

/*! A widget which display the content about folders and files of your system.
 * \ingroup widgets
 */
class TreeView : public ComponentWithTexture {
public:

   /*! Constructor:
    \param p1 The upper left corner of the component.
    \param p2 The lower right corner of the component.
    \param view Type of display(just folders or files and folders).
    * enum TW_types {
    *    TW_ONLY_FOLDERS,
    *    TW_FOLDERS_AND_FILES
    * };
    */
   TreeView(scv::Point p1, scv::Point p2, TW_types view = TW_ONLY_FOLDERS );
   /*! Default destructor.
   */
   ~TreeView();


   virtual void createTexture(void);
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   virtual void display(void);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onResizing(void);
   virtual void onDragging(void);

   //! Callback
   /*!
    * This function is called whenever you select a file/folder.
    * parameters: path and name of selected item.
    */
   virtual void itemSelect(void);

   /*! Return the last path used
    * to get the folders/execute file.
    */
   std::string getLastPath();

   /*! Return the type of the last path used
    * to get the folders/execute file.
    */
   TW_Content_Types getTypeLastPath();

private:

   static const int s_lineSpacing  = 16;
   static const int s_borderWidth  = 8;
   static const int s_borderHeight = 3;
   static const int s_imageSpace   = 26;

   void addInFolder();

   TW_types modeView;

   int  m_selectStart;
   int  m_selectEnd;

   GTree *tree;
   TreeModel *tModel;
   int m_firstLine;
   int m_nLines;
   int spaceBack;

   std::string lastPath;
   TW_Content_Types typeLastPath;

   std::vector<GInfoNode> m_nodes;

   bool useCallback;


};

} //namespace scv

#endif