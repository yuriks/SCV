#ifndef __SCV_TREE_ITEM_H__
#define __SCV_TREE_ITEM_H__

#include "Component.h"
#include "PopupItemStyle.h"

#include "ComponentTexture.h"
#include "ColorScheme.h"
#include "StaticLabel.h"

#include "Texture2D.h"

namespace scv {

class DefaultSytle;

class TreeItem : public scv::Component {
public:
   ///////////////////////////////////////////////////////////
   TreeItem(const std::string& name);
   virtual ~TreeItem(void);
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
   ///////////////////////////////////////////////////////////

   //SCV Callbacks
   ///////////////////////////////////////////////////////////
   virtual void onItemAccessed(const std::deque<std::string> &address);
   virtual void onItemSelection(const std::deque<std::string> &address);
   virtual void onItemOver(const std::deque<std::string> &address);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);
   //virtual void removeAllItems(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual std::string getString(void);
   virtual void setString(const std::string &label);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual bool getStatus(void) const;
   virtual void setStatus(bool status);
   ///////////////////////////////////////////////////////////

   virtual bool hasSubItems(void) const;

   virtual void setItemStyle(const scv::PopupItemStyle *style);

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

private:
   virtual bool isInsideItem(const scv::Point &position, int index) const;

   virtual bool hasSubMenuActive(void);

   virtual void setSubItemsStatus(bool status);

   virtual void processMouseCallback(const scv::MouseEvent &evt, std::deque<std::string> address);
   virtual void processKeyboardCallback(const scv::KeyEvent &evt, std::deque<std::string> address);

   bool _recentlyChange;
   bool _status;
   int _currSelectedItem;

   TreeItem *_parentItem;
   std::string _label;
   const DefaultSytle* _style;
protected:
   
private:
};

class DefaultSytle {
public:
   ///////////////////////////////////////////////////////////
   DefaultSytle(void) {
      createTexture();
   }
   virtual ~DefaultSytle(void) {}
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void drawItem(const TreeItem &item, int selectedItem) const {
      //const ContextMenu::MenuList& menus = item.getMenus();


      const Point& pos = item.getAbsolutePosition();
      const int width = item.getWidth();
      const int height = item.getHeight();

      static ColorScheme *scheme = ColorScheme::getInstance();

      _cTexture->enable();
      {
         scheme->applyDefaultModulate();
         // shadow
         _cTexture->display(pos.x + 1, pos.y + 1, 2, width + 2, height + 2);

         // border
         _cTexture->display(pos.x - 1, pos.y - 1, 1, width + 2, height + 2);

         scheme->applyColor(ColorScheme::CONTEXTMENU);
         // center
         _cTexture->display(pos.x, pos.y, 0, width, height);

         scheme->applyDefaultModulate();
         // center line
         _cTexture->display(pos.x + s_leftBorder, pos.y + 4, 1, 1, height - 8);

         if (selectedItem != -1) {
            scheme->applyColor(ColorScheme::OVERCOMPONENTS);
            //vertical
            _cTexture->display(pos.x + s_borderWidth / 2, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2 + 2, 4, 1, s_menuHeight-4);
            _cTexture->display(pos.x + s_borderWidth / 2 + width - s_borderWidth - 1, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2 + 2, 4, 1, s_menuHeight-4);
            //horizontal
            _cTexture->display(pos.x + s_borderWidth / 2 + 2, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2, 4, width - s_borderWidth-4, 1);
            _cTexture->display(pos.x + s_borderWidth / 2 + 2, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2 + s_menuHeight - 1, 4, width - s_borderWidth-4, 1);

            // pixel border
            _cTexture->display(pos.x + s_borderWidth / 2, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2, 5, 2, 2);
            _cTexture->display(pos.x + s_borderWidth / 2, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2 + s_menuHeight, 5, 2, -2);
            _cTexture->display(pos.x + s_borderWidth / 2 + width - s_borderWidth, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2, 5, -2, 2);
            _cTexture->display(pos.x + s_borderWidth / 2 + width - s_borderWidth, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2 + s_menuHeight, 5, -2, -2);

            // center select
            _cTexture->display(pos.x + s_borderWidth / 2 + 2, pos.y + selectedItem * s_menuHeight + s_borderHeight / 2 + 2, 3, width - s_borderWidth - 4, s_menuHeight - 4);
            scheme->applyDefaultModulate();
         }

         // arrow

         int i = 0;
         TreeItem *pItem;
         for (Component::List::const_iterator iter = item.getChildren().begin(); iter != item.getChildren().end(); ++iter, ++i) {
            pItem = static_cast<TreeItem*>(*iter);
            if (pItem->hasSubItems()) {
               _cTexture->display(pos.x + width - s_borderWidth / 2 - 8, pos.y + i * s_menuHeight + s_menuHeight / 2, 6);
            }
         }
      }
      _cTexture->disable();

      int i = 0;
      TreeItem *pItem;
      for (Component::List::const_iterator iter = item.getChildren().begin(); iter != item.getChildren().end(); ++iter, ++i) {
         pItem = static_cast<TreeItem*>(*iter);
         std::cout << pItem->getString() << std::endl;
         StaticLabel::display(s_leftBorder + pos.x + s_borderHeight, pos.y + i * s_menuHeight + s_borderHeight, pItem->getString(), scheme->getColor(ColorScheme::CONTEXTMENUFONT));
      }
   }
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual bool isInsideItem(const TreeItem &item, const Point &pos, int index) const {
      return (pos.x >= item.getAbsolutePosition().x + 2 && pos.x <= item.getAbsolutePosition().x + item.getWidth() - 2 &&
         pos.y >= item.getAbsolutePosition().y + index * s_menuHeight + s_borderHeight/2.f && pos.y <= item.getAbsolutePosition().y + index * s_menuHeight + s_menuHeight + s_borderHeight/2.f - 1);
   }
   virtual Point getSubItemPosition(TreeItem &item, int index) const {
      return Point(item.getAbsolutePosition().x - item.getChild(index)->getWidth() + s_borderWidth, item.getAbsolutePosition().y + index * s_menuHeight);
   }
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int calculateWidth(const TreeItem &item) const {
      static const FontTahoma *font = FontTahoma::getInstance();

      int width = 0;

      TreeItem *pItem;
      for (Component::List::const_iterator iter = item.getChildren().begin(); iter != item.getChildren().end(); ++iter) {
         pItem = static_cast<TreeItem*>(*iter);

         int str_width = font->getStringLength(pItem->getString());
         if (str_width > width) width = str_width;
      }

      return width + s_borderWidth * 5 + s_leftBorder;
   }
   virtual int calculateHeight(const TreeItem &item) const {
       return item.getChildren().size() * s_menuHeight + s_borderHeight;
   }
   ///////////////////////////////////////////////////////////

   void createTexture() {
      //static Kernel *kernel = Kernel::getInstance();
      //if ((_cTexture = kernel->getWidgetTexture(Kernel::CONTEXTMENU)) != NULL) return;

      // create texture object
      _cTexture = new ComponentTexture(16, 8);
      //kernel->setWidgetTexture(Kernel::CONTEXTMENU, _cTexture);

      _cTexture->setTextureEnvMode(GL_MODULATE);

      MatrixTemplate<ColorRGBA> center(1, 1, ColorRGBA(240,240,240,255));
      _cTexture->addTexture(Point(0,0), center); // 0

      MatrixTemplate<ColorRGBA> border(1, 1, ColorRGBA(151,151,151,255));
      _cTexture->addTexture(Point(1,0), border); // 1

      MatrixTemplate<ColorRGBA> shadow(1, 1, ColorRGBA(0,0,0,255));
      _cTexture->addTexture(Point(2,0), shadow); // 2

      // over
      MatrixTemplate<ColorRGBA> overCenter(1,1, ColorRGBA(240,240,240,50));
      _cTexture->addTexture(Point(3,0), overCenter); // 3

      MatrixTemplate<ColorRGBA> overBorder(1,1, ColorRGBA(210,210,210,150));
      _cTexture->addTexture(Point(4,0), overBorder); // 4

      MatrixTemplate<ColorRGBA> pixelBorder(2,2, ColorRGBA(220,220,220,100));
      Texture2D::drawPoint(pixelBorder, Point(0, 0),ColorRGBA(0,0,0,0));
      _cTexture->addTexture(Point(5,0), pixelBorder); // 5

      // arrow
      MatrixTemplate<ColorRGBA> arrow(5, 7, ColorRGBA(0,0,0,0));
      Texture2D::rectFill(arrow,Point(0, 0),Point(4, 6),ColorRGBA(0,0,0,0));
      Texture2D::line(arrow, Point(0, 0),Point(0, 6),ColorRGBA(0,0,0,255));
      Texture2D::line(arrow, Point(1, 1),Point(1, 5),ColorRGBA(0,0,0,255));
      Texture2D::line(arrow, Point(2, 2),Point(2, 4),ColorRGBA(0,0,0,255));
      Texture2D::line(arrow, Point(3, 3),Point(3, 3),ColorRGBA(0,0,0,255));
      _cTexture->addTexture(Point(7,0), arrow); // 6

      _cTexture->createTexture();
   }

   static const int s_menuSpacing  = 10;
   static const int s_borderHeight = 8;
   static const int s_borderWidth  = 8;
   static const int s_leftBorder   = 28;
   static const int s_menuHeight   = 22;

   ComponentTexture* _cTexture;
};


} //namespace scv

#endif //__SCV_TREE_ITEM_H__