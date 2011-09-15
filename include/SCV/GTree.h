/*!
\file       GTree.h
\brief      Implementation of GInfoNode, GNode and GTree.
\author     SCV Team
*/


#ifndef __SCV_G_TREE_H__
#define __SCV_G_TREE_H__


namespace scv {

enum TW_Content_Types {
   T_FOLDER = 0,
   T_FILE = 1
};


/*! class used to get the content of GTree to display on screen.
 * (used with a vector)
 *\ingroup internal
 */

class GInfoNode {
public:

   std::string      getName();
   void             setName(std::string nname);
   void             setHaveChilds(bool t);
   void             setOpen(bool t);
   void             setType(TW_Content_Types t);
   bool             haveChilds();
   bool             isOpen();
   TW_Content_Types getType();

private:
   bool ifHaveChilds;
   bool Open;
   TW_Content_Types type;
   std::string name;
};

/*! Used to store the content of the files/folders.
 *\ingroup internal
 */

class GNode {
public:
   GNode(std::string nname);
   GNode(std::string nname, bool i, TW_Content_Types type);
   ~GNode();
   GNode *first;
   GNode *next;
   std::string name;

   GNode* findSelected(int* h);

   void addNode(std::string nname, bool t, TW_Content_Types type);
   void addNode(std::string nname);
   std::string searchAndPath(GNode* selected, const std::string& path);
   void printLine();
   void removeAllChilds();
   void getChildNames(std::vector<GInfoNode> &vx, const std::string& path);
   bool ifHaveFolders();
   void setHaveFolders(bool);
   TW_Content_Types getType();
   void setType(TW_Content_Types type);
   std::string getname();

private:
   bool HaveFolders;
   TW_Content_Types type;
};


/*! a main class to get and store the content of files
 * on GNodes and folders, have the main functions of the
 * struct.
 *\ingroup internal
 */

class GTree {
public:
   GTree();
   ~GTree();
   GNode* init;
   GNode* selected;

   void imprimir();
   void addInPath(std::vector<GInfoNode> &vx);
   std::string getPathOfSelected(std::string name, std::string path);
   void findSelected(int *h);

private:

};

}

#endif