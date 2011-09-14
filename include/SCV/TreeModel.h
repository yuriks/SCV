/*!
\file       TreeModel.h
\brief      Implementation of a TreeModel, a internal class to assist the Treeview.
\author     SCV Team
*/


#ifndef __SCV_TREE_MODEL_H__
#define __SCV_TREE_MODEL_H__

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "GTree.h"

namespace scv {

enum TW_types {
   TW_ONLY_FOLDERS,
	TW_FOLDERS_AND_FILES
};

/*! A Internal Class which assist the TreeView to get the content of
 * files and folders of the system.
 *\ingroup internal
 */

class TreeModel {
public:
   TreeModel();
   ~TreeModel();

   void getFolders(const char* dir, std::vector<GInfoNode> &m_nodes, TW_types view);
   void getNamesInTree(std::vector<GInfoNode> &m_nodes, GTree* tree);
   bool getIfHaveFolders(const char* dir, TW_types view);
   void getDirs(std::vector<std::string> &dirNames);


private:
   void getNFolders(std::vector<std::string> &dirNames);
};
}


#endif