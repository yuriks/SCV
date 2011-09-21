/*!
\file       ScrollPane.h
\brief      Implementation of a ScrollPane widget.
\author     SCV Team
*/

#ifndef __SCV_SCROLL_PANE_H__
#define __SCV_SCROLL_PANE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Panel.h"
#include "ComponentWithTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! Create a panel with Scrollbars.
 *  \ingroup widgets
*/

class ScrollPane : public ComponentWithTexture {
public:

   /*! Constructor
   \param p1 The upper left corner of the component.
   \param p2 The bottom right corner of the component.
   \param panel A Pane to add inside of the Scrollpane (NULL by default).
   */
   ScrollPane(const scv::Point &p1, const scv::Point &p2, scv::Panel * panel = NULL);
   /*! Constructor
   \param p1 The upper left corner of the component.
   \param width The width of the component.
   \param height The height of the component.
   \param panel A Pane to add inside of the component (NULL by default).
   */
   ScrollPane(const scv::Point &p1, unsigned int width, unsigned int height, scv::Panel * panel = NULL);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);


   /*! Register a new panel to the ScrollPanel.
    *  The older panel will be changed.
   */
   void registerPanel(Panel *panel);
   /*! Returns a pointer to the panel within of the component.
   */
   Panel * getPanel(void);


   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   void refreshSCrollPaneSize(void);
   void setHeight(int height);
   void setWidth(int width);
   void display(void);

private:
   enum Botoes {
      BUT_NONE,
      BUT_UP, BUT_DOWN, BUT_VERT,
      BUT_LEFT, BUT_RIGHT, BUT_HORZ,
      BUT_PAGEUP, BUT_PAGEDOWN,
      BUT_PAGELEFT, BUT_PAGERIGHT
   };

   bool isOnLeftButton(Point p);
   bool isOnRightButton(Point p);
   bool isOnUpButton(Point p);
   bool isOnBottomButton(Point p);

   bool isOnVertButton(Point p);
   bool isOnHorzButton(Point p);
   bool isOnVertBar(Point p);
   bool isOnHorzBar(Point p);

   float pixelToFloat(int pix, bool horz);
   float barPixelToFloat(int pix, bool horz);

   Botoes _overButton;
   bool _holdButton;

   void createTexture(void);
   Panel *_panel;

   /*
   tam = (altura total panel / altura visivel) * altura maxima do sroll
   */

   void refreshContainerPosition(void);
   void setPanelTranslate(const Point &translate);

   int _scrollSizeVertical, _scrollSizeHorizontal;
   float _translateHeight, _translateWidth;
   int _maxDeslocHeight, _maxDeslocWidth;
   int _containerHeight, _containerWidth;
   static const int s_initDesloc = 16;
   static const int s_border = 15;
   static const int s_UnnecessaryBorder = (3 * s_initDesloc + 1);
   Botoes _draggingBar;
   int _dragBarOffset;
   Point _minContainerPos;
};

} // namespace scv

#endif // __SCV_SCROLL_PANE_H__