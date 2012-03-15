#include "stdafx.h"
#include "GTree.h"
#include "TreeModel.h"
#include "ComponentWithTexture.h"
#include "GenericTree.h"
#include "data.h"
#include "Image.h"
#include "ContextMenu.h"
#include "Kernel.h"
#include "StaticLabel.h"

namespace scv {

   GenericTree::GenericTree(scv::Point p1, scv::Point p2, GenericNode* root)
      : ComponentWithTexture(p1, p2)
   {
      _type = GENERICTREE;
      spaceBack = 0;
      m_firstLine = 0;
      m_nLines = 20;

      _nodesDisplay.clear();
      _nodeRoot = root;
      _nodesDisplay.push_back("+ " + _nodeRoot->label);

      _nodeSelected = 0;

      createTexture();
   }

   GenericTree::~GenericTree() {
      delete _nodeRoot;
   }

   void GenericTree::onItemSelected() {
   }

   GenericNode* GenericTree::findSelected(GenericNode* focusNode, int y, std::string spaces)
   {
      GenericNode* resultNode = NULL;
      GenericNode* rNode = NULL;
      for(int i = 0 ; i < focusNode->children.size(); i++)
      {

         if(y-_jumpOnFindSelected == 0)
         {
            resultNode = focusNode->children[i];
            resultNode->open = !resultNode->open;
         }
         _jumpOnFindSelected++;
         if(focusNode->children[i]->open)
         { 
            _nodesDisplay.push_back(spaces + "- " + focusNode->children[i]->label);
            rNode = findSelected(focusNode->children[i], y, spaces + " ");
            if(rNode != NULL)
            {
               resultNode = rNode;
            }                
         } else {
            _nodesDisplay.push_back(spaces + "+ " + focusNode->children[i]->label);
         }
      }
      return resultNode;
   }

   void GenericTree::processMouse(const scv::MouseEvent &evt) {
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
         int y = (int)(((evt.getPosition().y - (p.y))/s_lineSpacing) + m_firstLine);

         _nodesDisplay.clear();
         if(y == 0)
         {
            _nodeSelected = _nodeRoot;
            _nodeRoot->open = !_nodeRoot->open;
         }
         if(_nodeRoot->open)
         {
            _nodesDisplay.push_back("- " + _nodeRoot->label);
            _jumpOnFindSelected = 1;
            GenericNode* resultNode = findSelected(_nodeRoot, y, " ");
            if(y>0)
            {
               _nodeSelected = resultNode;
            }
         } else {
            _nodesDisplay.push_back("+ " + _nodeRoot->label);
         } 

         if (_nodeSelected != 0)
            onItemSelected();
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

   void GenericTree::processKey(const scv::KeyEvent &evt) {
   }

   void GenericTree::display(void) {
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

      /*draw the tree*/
      int i;
      int breakPrint = getHeight()/s_lineSpacing;
      for (i = 0; (i+m_firstLine) < _nodesDisplay.size() && breakPrint > -2; i++) {

         StaticLabel::display(scv::Point((currPosition.x  + s_borderWidth / 2), (currPosition.y+1) + ((i) * s_lineSpacing)),
            _nodesDisplay[i + m_firstLine], scheme->getColor(ColorScheme::TEXT));

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

   void GenericTree::createTexture(void) {
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
