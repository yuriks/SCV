#ifndef __SCV_TABEED_PANE_H__
#define __SCV_TABEED_PANE_H__

#include "Panel.h"
#include "ComponentWithTexture.h"

namespace scv {

class TabbedPane : public ComponentWithTexture {
public:
   ///////////////////////////////////////////////////////////
   TabbedPane(const scv::Point &p1, const scv::Point &p2);
   TabbedPane(const scv::Point &p1, unsigned int width, unsigned int height);
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
   
   ///////////////////////////////////////////////////////////
   void addPanel(Panel *panel, const std::string &label);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////
   
   void display(void);

private:
   void createTexture(void);

   void refreshPosition(int tab);
   void refreshScissor(void);

   static const int s_tabSpacing, s_barHeight;

   int _currecOverTab, _currSelectedTab;

   std::vector<int> _index;
   std::vector<std::string> _labels;
   std::vector<Panel*> _tabs;
};

} // namespace scv

#endif // __SCV_TABEED_PANE_H__
