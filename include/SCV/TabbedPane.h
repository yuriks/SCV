/*!
\file       TabbedPane.h
\brief      Implementation of a TabbedPane widget.
\author     SCV Team
*/

#ifndef __SCV_TABEED_PANE_H__
#define __SCV_TABEED_PANE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Panel.h"
#include "ComponentWithTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A panel that allows multiple panels to be contained within a single window.
 * \ingroup widgets
 */

class TabbedPane : public ComponentWithTexture {
public:

   //! Constructor
   /*!
   This constructor automatically adjusts the component size based on name.
   \param p1 The upper left corner of the component.
   \param p2 The bottom right corner of the component.
   */
   TabbedPane(const scv::Point &p1, const scv::Point &p2);
   //! Constructor
   /*!
   This constructor automatically adjusts the component size based on name.
   \param p1 The upper left corner of the component.
   \param width Width of the component.
   \param height Height of the component.
   */
   TabbedPane(const scv::Point &p1, unsigned int width, unsigned int height);


   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);


   //! Adds a new panel to the component.
   /*!
   \param panel Reference to the new panel.
   \param label Name of the new panel.
   */
   void addPanel(Panel *panel, const std::string &label);
   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   //! Key function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processKey(const scv::KeyEvent &evt);
   void display(void);

private:
   void createTexture(void);
   void refreshPosition(int tab);
   void refreshScissor(void);

   static const int s_tabSpacing;
   static const int s_barHeight;

   int _currecOverTab, _currSelectedTab;

   std::vector<int> _index;
   std::vector<std::string> _labels;
   std::vector<Panel*> _tabs;
};

} // namespace scv

#endif // __SCV_TABEED_PANE_H__
