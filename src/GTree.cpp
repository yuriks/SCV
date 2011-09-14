#include <iostream>
#include <string>
#include "GTree.h"


namespace scv {

void GInfoNode::setName(std::string nname)
{
   name = nname;
}

void GInfoNode::setHaveChilds(bool t)
{
   ifHaveChilds = t;
}

void GInfoNode::setOpen(bool t)
{
   Open = t;
}

std::string GInfoNode::getName()
{
   return name;
}

bool GInfoNode::haveChilds()
{
   return ifHaveChilds;
}

bool GInfoNode::isOpen()
{
   return Open;
}

TW_Content_Types GInfoNode::getType()
{
   return type;
}

void GInfoNode::setType(TW_Content_Types t)
{
   type = t;
}

bool get;
GNode::GNode(std::string nname)
{
   first = NULL;
   next = NULL;
   name = nname;
   HaveFolders = false;
   type = T_FOLDER;
}

GNode::GNode(std::string nname, bool t, TW_Content_Types te)
{
   first = NULL;
   next = NULL;
   name = nname;
   HaveFolders = t;
   type = te;
}

GNode::~GNode()
{
   name.clear();
   GNode* aux2 = NULL;
   for(GNode* aux = first; aux != NULL ; aux = aux->next)
   {
      if(aux2 != NULL)
         delete aux2;
      aux2 = aux;
   }
   delete aux2;

}


void GNode::addNode(std::string nname)
{
   GNode* aux;
   GNode* aux2 = first;
   if(first == NULL)
   {
      first = new GNode(nname);
   }else{
      for(aux = first; aux != NULL ; aux = aux->next)
      {
         aux2 = aux;
      }
      aux = new GNode(nname);
      aux2->next = aux;
   }
}

void GNode::setType(TW_Content_Types t)
{
   type = t;
}

void GNode::addNode(std::string nname, bool t, TW_Content_Types type)
{
   GNode* aux;
   GNode* aux2 = first;
   if(first == NULL)
   {
      first = new GNode(nname, t, type);
   }else{
      for(aux = first; aux != NULL ; aux = aux->next)
      {
         aux2 = aux;
      }
      aux = new GNode(nname, t, type);
      aux2->next = aux;
   }
}



std::string GNode::searchAndPath(GNode* selected, const std::string& path)
{
   std::string ret = "";
   GNode* aux;
   for(aux = first; aux != NULL && !get ; aux = aux->next)
   {
      if(aux == selected)
      {
         get = true;
         return (path+aux->name+"/");
      }
      if(aux->first != NULL)
         ret = aux->searchAndPath(selected,path+aux->name+"/");
   }
   return ret;
}

void GNode::printLine()
{
   GNode* aux;
   for(aux = first; aux != NULL ; aux = aux->next)
   {
      std::cout << aux->name << std::endl;
      aux->printLine();
   }
}

void GNode::removeAllChilds()
{
   GNode *aux2 = NULL;
   for(GNode *aux = first; aux != NULL ; aux = aux->next)
   {
      if(aux2 != NULL)
         delete aux2;
      aux2 = aux;
   }
   first = NULL;
   delete aux2;
}

void GNode::getChildNames(std::vector<GInfoNode> &vx, const std::string& path)
{
   bool result = false;
   GInfoNode GNodeAux;
   for(GNode* aux = first ; aux != NULL ; aux = aux->next)
   {
      if(!result) {result = true;}
      GNodeAux.setName(path+aux->name);
      GNodeAux.setType(aux->getType());
      GNodeAux.setHaveChilds(aux->ifHaveFolders());
      if(aux->first != NULL){
         GNodeAux.setOpen(true);
      }else {GNodeAux.setOpen(false);}
      vx.push_back(GNodeAux);
      aux->getChildNames(vx, path+"   ");
   }
}

GNode* GNode::findSelected(int *h)
{
   GNode*aux = NULL;

   for(GNode* p = first; p != NULL; p = p->next)
   {
      if( *h == 0 )
      {
         return p;
      }
      *h = *h - 1;
      aux = p->findSelected(h);
      if(aux != NULL)
      {
         return aux;
      }
   }
   return NULL;
}

bool GNode::ifHaveFolders()
{
   return HaveFolders;
}

void GNode::setHaveFolders(bool set)
{
   HaveFolders = set;
}

TW_Content_Types GNode::getType()
{
   return type;
}

GTree::GTree()
{
   init = NULL;
   selected = NULL;
}

GTree::~GTree()
{
   selected = NULL;
   if(init != NULL){
      delete init;
   }
}

void GTree::imprimir()
{
   std::cout << init->name << std::endl;
   init->printLine();
}

void GTree::addInPath(std::vector<GInfoNode> &vx)
{
   int a = vx.size();
   for(int i = 0; i < a; i++)
      selected->addNode(vx[i].getName(), vx[i].haveChilds(), vx[i].getType());
}

std::string GTree::getPathOfSelected(std::string name, std::string path)
{
   get = false;
   if(init->first == NULL){
      return  path;
   }
   std::string ret = "";
   for(GNode* aux = init->first; aux != NULL && !get ; aux = aux->next)
   {
      if(aux == selected)
      {
         return (path+aux->name+"/");
      }
      if(aux->first != NULL)
         ret = aux->searchAndPath(selected, aux->name+"/");

   }
   if(get){
      return ret;
   }
   else{
      return "";
   }
}

void GTree::findSelected(int *h)
{
   GNode* aux = NULL;

   for(GNode* p = init->first; p != NULL; p = p->next)
   {
      if( *h == 0 )
      {
         selected = p;
         return;
      }
      *h = *h - 1;
      aux = p->findSelected(h);
      if(aux != NULL)
      {
         selected = aux;
         return;
      }
   }
   selected = NULL;
}

std::string GNode::getname()
{
   return name;
}

}
