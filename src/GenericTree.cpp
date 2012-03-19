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

   struct GenericNodeDisplay
   {
      GenericNodeDisplay(const GenericNode& node, int indent)
         : label(node.label), selected(false), open(node.open), has_children(!node.children.empty()), indent(indent)
      {}

      std::string label;
      bool selected;
      bool open;
      bool has_children;
      int indent;
   };

   GenericTree::GenericTree(scv::Point p1, scv::Point p2, GenericNode* root)
      : ComponentWithTexture(p1, p2)
   {
      _type = GENERICTREE;
      spaceBack = 0;
      m_firstLine = 0;
      m_nLines = 20;

      _nodesDisplay.clear();
      _nodeRoot = root;
      _nodesDisplay.push_back(GenericNodeDisplay(*_nodeRoot, 1));

      _nodeSelected = 0;

      createTexture();
   }

   GenericTree::~GenericTree() {
      delete _nodeRoot;
   }

   //! Must be called after the tree is changed to refresh the display. Weird things may happen if you don't.
   void GenericTree::refreshDisplay() {
      _nodesDisplay.clear();
      if (_nodeRoot != 0)
         _nodesDisplay.push_back(GenericNodeDisplay(*_nodeRoot, 1));
   }

   void GenericTree::onItemSelected() {
   }

   GenericNode* GenericTree::findSelected(GenericNode* focusNode, int y, int iSpaces)
   {
      GenericNode* resultNode = NULL;
      GenericNode* rNode = NULL;
      for(int i = 0 ; i < focusNode->children.size(); i++)
      {
         if (y - _jumpOnFindSelected == 0)
         {
            resultNode = focusNode->children[i];
            resultNode->open = !resultNode->open;

            GenericNodeDisplay display_node(*focusNode->children[i], iSpaces);
            display_node.selected = true;
            _nodesDisplay.push_back(display_node);
         } else {
            _nodesDisplay.push_back(GenericNodeDisplay(*focusNode->children[i], iSpaces));
         }

         _jumpOnFindSelected++;
         if (focusNode->children[i]->open)
         { 
            rNode = findSelected(focusNode->children[i], y, iSpaces+1);
            if (rNode != NULL)
            {
               resultNode = rNode;
            }                
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
         int y = (int)(((evt.getPosition().y - (p.y) )/s_lineSpacing) + m_firstLine);
         int iSpaces = 1;
         _nodesDisplay.clear();
         if(y == 0)
         {
            _nodeSelected = _nodeRoot;
            _nodeRoot->open = !_nodeRoot->open;

            GenericNodeDisplay display_node(*_nodeRoot, iSpaces);
            display_node.selected = true;
            _nodesDisplay.push_back(display_node);
         }else{
            _nodesDisplay.push_back(GenericNodeDisplay(*_nodeRoot, iSpaces));
         }
         if(_nodeRoot->open)
         {
            _jumpOnFindSelected = 1;
            GenericNode* resultNode = findSelected(_nodeRoot, y, iSpaces+1);
            if(y>0)
            {
               _nodeSelected = resultNode;
            }
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

      glDisable(GL_TEXTURE_2D);

      int i;
      int breakPrint = getHeight() / s_lineSpacing;
      for (i = 0; i + m_firstLine < _nodesDisplay.size() && breakPrint > -2; i++) {
         const GenericNodeDisplay& node = _nodesDisplay[i + m_firstLine];

         if (node.selected) {
            scheme->applyColor(scheme->getColor(ColorScheme::TEXTSELECTION));
         } else {
            scheme->applyColor(scheme->getColor(ColorScheme::TEXT));
         }

         if (node.has_children) {
            int x_pos = currPosition.x + node.indent * 10;
            int y_pos = currPosition.y + i * 12;

            glBegin(GL_LINES);
               glVertex2f(x_pos - 3.5f, y_pos + 7.5f);
               glVertex2f(x_pos + 1.0f, y_pos + 7.5f);
               if (!node.open) {
                  glVertex2f(x_pos + -1.5f, y_pos + 5.5f);
                  glVertex2f(x_pos + -1.5f, y_pos + 11.0f);
               }
            glEnd();
         }
         breakPrint--;
      }

      glEnable(GL_TEXTURE_2D);

      /*draw the tree*/
      breakPrint = getHeight()/s_lineSpacing;
      for (i = 0; (i+m_firstLine) < _nodesDisplay.size() && breakPrint > -2; i++) {
         Color4f text_color;
         if (_nodesDisplay[i + m_firstLine].selected) {
            text_color = scheme->getColor(ColorScheme::TEXTSELECTION);
         } else {
            text_color = scheme->getColor(ColorScheme::TEXT);
         }


         StaticLabel::display(
            scv::Point(
               currPosition.x + s_borderWidth + _nodesDisplay[i + m_firstLine].indent * 10,
               currPosition.y + (i) * s_lineSpacing),
            _nodesDisplay[i + m_firstLine].label, text_color);

         breakPrint--;
      }
      spaceBack = (getHeight()-(i * s_lineSpacing));
      int spBack = spaceBack/s_lineSpacing;

      while (spBack > 0 && m_firstLine > 0) {
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
