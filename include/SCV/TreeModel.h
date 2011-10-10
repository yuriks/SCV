#ifndef __SCV_TREE_MODEL_H__
#define __SCV_TREE_MODEL_H__

#include "GTree.h"

namespace scv {

enum TW_types {
   TW_ONLY_FOLDERS,
	TW_FOLDERS_AND_FILES
};

class TreeModel {
public:
   ///////////////////////////////////////////////////////////
   TreeModel(void);
   virtual ~TreeModel(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void getFolders(const char* dir, std::vector<GInfoNode> &m_nodes, TW_types view);
   void getNamesInTree(std::vector<GInfoNode> &m_nodes, GTree* tree);
   bool getIfHaveFolders(const char* dir, TW_types view);
   void getDirs(std::vector<std::string> &dirNames);
   ///////////////////////////////////////////////////////////
private:
   void getNFolders(std::vector<std::string> &dirNames);
};
}


#endif