#include "stdafx.h"
#include "GTree.h"
#include "TreeModel.h"
#include "ComponentWithTexture.h"
#include "SystemTreeView.h"
#include "data.h"
#include "Image.h"
#include "ContextMenu.h"
#include "Kernel.h"
#include "StaticLabel.h"

namespace scv{

SystemTreeView::SystemTreeView(scv::Point p1,scv::Point p2 ,TW_types view) : ComponentWithTexture(p1, p2) {
   _type = TREEVIEW;
   tree = new GTree();
   tree->init = new GNode("INIT");

#ifdef _WIN32
   std::vector<std::string> dirNames;
   tModel->getDirs(dirNames);

   for(int i = 0; i < dirNames.size(); ++i) {
      tree->init->addNode(dirNames[i]);
   }   

   tree->init->setType(T_FOLDER);

   for(GNode* aux = tree->init->first ; aux != NULL ; aux = aux->next) {
      aux->setType(T_FOLDER);
      aux->setHaveFolders(tModel->getIfHaveFolders(aux->name.c_str(), view));
      aux->name.pop_back();
   }
#else
   tree->init->addNode("/");
   tree->init->first->setHaveFolders(tModel->getNFolders(tree->init->first->name.c_str()));
   tree->init->first->setType(T_FOLDER);
   tree->init->first->name.pop_back();
#endif
   tree->selected = tree->init->first;

   spaceBack = 0;
   m_firstLine = 0;
   m_nLines = 20;

   m_nodes.clear();
   tModel->getNamesInTree(m_nodes, tree);
   modeView = view;
   useCallback = false;

   createTexture();
}


SystemTreeView::~SystemTreeView(void) {
   delete tree;
   delete tModel;
}

void SystemTreeView::onMouseClick(const scv::MouseEvent &evt) {
}
void SystemTreeView::onMouseHold(const scv::MouseEvent &evt) {
}
void SystemTreeView::onMouseOver(const scv::MouseEvent &evt) {
}
void SystemTreeView::onMouseUp(const scv::MouseEvent &evt) {
}
void SystemTreeView::onMouseWheel(const scv::MouseEvent &evt) {
}

void SystemTreeView::onKeyPressed(const scv::KeyEvent &evt) {
}
void SystemTreeView::onKeyUp(const scv::KeyEvent &evt) {
}

void SystemTreeView::onSizeChange(void) {
}
void SystemTreeView::onPositionChange(void) {
}

void SystemTreeView::onItemSelect(void) {
}

void SystemTreeView::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (!_receivingCallbacks) {
      Component::processMouse(evt);
      return;
   } else {
      ComponentWithTexture::processMouse(evt);
   }

   scv::Point p = getAbsolutePosition();
   if(evt.getState() == MouseEvent::UP && isFocused()) {
      int y = (int)(((evt.getPosition().y - (p.y +  1))/s_lineSpacing) + m_firstLine);

      tree->findSelected(&(y));

      if(tree->selected != NULL) {
         lastPath.clear();
         lastPath = tree->getPathOfSelected(tree->selected->name, "");
         typeLastPath = tree->selected->getType();
         if(tree->selected->first == NULL) {
            addInFolder();
         } else {
            tree->selected->removeAllChilds();
         }
         useCallback = true;
         m_nodes.clear();
         tModel->getNamesInTree(m_nodes, tree);
         lastPath.pop_back();
      }

   }

   if (isFocused()) {
      if (evt.getState() == MouseEvent::WHEELDOWN) {
         if(spaceBack < 0) m_firstLine++;
         return;
      }
      if (evt.getState() == MouseEvent::WHELLUP) {
         if(m_firstLine > 0) { m_firstLine--; }
         return;
      }
   }
}

void SystemTreeView::processKey(const scv::KeyEvent &evt) {
}

void SystemTreeView::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();

   _cTexture->enable();
   scheme->applyColor(ColorScheme::TEXTFIELD);
   _cTexture->display(currPosition.x, currPosition.y, 1, getWidth(), getHeight());
   _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);
   _cTexture->disable();

   scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y) + 1, getWidth(), getHeight() - 4));
   
   /*Use Callback*/
   if(useCallback) {
      onItemSelect();
      useCallback = false;
   }

   /*draw the tree*/
   int i;
   int breakPrint = getHeight()/s_lineSpacing;
   for (i = 0; (i+m_firstLine) < m_nodes.size() && breakPrint > -2; i++) {
      if (m_nodes[i + m_firstLine].getType() == T_FOLDER){
         StaticLabel::display(scv::Point((currPosition.x  + s_borderWidth / 2)+s_imageSpace, currPosition.y + ((i) * s_lineSpacing)),
            m_nodes[i + m_firstLine].getName(), scheme->getColor(ColorScheme::TEXT));
      } else {
         StaticLabel::display(scv::Point((currPosition.x  + s_borderWidth / 2)+10, currPosition.y + ((i) * s_lineSpacing)),
            m_nodes[i + m_firstLine].getName(), scheme->getColor(ColorScheme::TEXT));
      }

      int nspaces = getSpaces(m_nodes[i+m_firstLine].getName());
      nspaces*=15;
      int a = (int)m_nodes.size();
      if (m_nodes[i+m_firstLine].getType() == T_FILE) {
         //_cTexture->display((currPosition.x  + s_borderWidth / 2) + nspaces , currPosition.y + ((i) * s_lineSpacing), 2, 8, 16 );
      } else if (m_nodes[i+m_firstLine].getType() == T_FOLDER) {
         _cTexture->enable();
         scheme->applyDefaultModulate();
         if(m_nodes[i+m_firstLine].isOpen()) {
            _cTexture->display((currPosition.x  + s_borderWidth / 2) + 8 + nspaces , currPosition.y + ((i) * s_lineSpacing), 4, 16, 16 );
         } else {
            _cTexture->display((currPosition.x  + s_borderWidth / 2) + 8 + nspaces , currPosition.y + ((i) * s_lineSpacing), 5, 16, 16 );
         }
         if(m_nodes[i+m_firstLine].haveChilds() && m_nodes[i+m_firstLine].isOpen()) {
            _cTexture->display((currPosition.x  + s_borderWidth / 2) + nspaces , currPosition.y + ((i) * s_lineSpacing), 2, 8, 16 );
         } else if(m_nodes[i+m_firstLine].haveChilds()) {
            _cTexture->display((currPosition.x  + s_borderWidth / 2) + nspaces , currPosition.y + ((i) * s_lineSpacing), 3, 8, 16 );
         }
         _cTexture->disable();
      }
      breakPrint--;
   }

   spaceBack = (getHeight()-(i * s_lineSpacing));
   int spBack = spaceBack/s_lineSpacing;

   while(spBack > 0 && m_firstLine > 0) {
      m_firstLine--;
      spBack--;
   }

   scissor->popScissor();
}

int SystemTreeView::getSpaces(const std::string &name) {
   int res = 0;
   int count = 0;

   for(int i = 0; i < (int)name.size() ; i++) {
      if(name[i] == ' ') {
         count++;
      } else {
         return res;
      }
      if(count == 3) {
         res++;
         count = 0;
      }
   }
   return res;
}

void SystemTreeView::addInFolder(void) {
   static Kernel *kernel = Kernel::getInstance();

   std::vector<GInfoNode> vx;
   std::string path;
   path = lastPath;

   int a = tree->selected->name.size();
   tModel->getFolders(path.c_str(), vx, modeView);
   std::string n;

   for(int i = 0; i < (int)vx.size(); i++) {
      n.clear();
      n.append(path);
      n.append(vx[i].getName());
      n.append("/");
      vx[i].setHaveChilds(tModel->getIfHaveFolders(n.c_str(), modeView));
   }
   tree->addInPath(vx);
   n.clear();
   path.clear();
   vx.clear();
}

void SystemTreeView::createTexture(void) {
   Kernel *kernel = Kernel::getInstance();
   if ((_cTexture = kernel->getWidgetTexture(TREEVIEW)) != NULL) return;

   // create texture object
   _cTexture = new ComponentTexture(32, 32);
   kernel->setWidgetTexture(TREEVIEW, _cTexture);

   _cTexture->setTextureEnvMode(GL_MODULATE);
   _cTexture->addTexture(Point(0,0), 32, 32, data::TreeView);

   _cTexture->clearTextureIds();
   // middle
   _cTexture->addTextureId(Point(0,0), 1, 1);
   // lines
   _cTexture->addTextureId(Point(1,0), 1, 1);
   // stateDown
   _cTexture->addTextureId(Point(8,16), 8, 16);
   // stateUp
   _cTexture->addTextureId(Point(0,16), 8, 16);
   // openedFolder
   _cTexture->addTextureId(Point(16,16), 16, 16);
   // closedFolder
   _cTexture->addTextureId(Point(16,0), 16, 16);

   _cTexture->createTexture();
}

}
