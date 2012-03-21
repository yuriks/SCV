#ifndef __SCV_TABEED_PANE_H__
#define __SCV_TABEED_PANE_H__

#include "Panel.h"
#include "ComponentWithTexture.h"

namespace scv {

class TabbedPane : public ComponentWithTexture {
public:
   TabbedPane(const scv::Point &p1, const scv::Point &p2);
   
   virtual void onTabChange(void);
   
   //Memory Management
   virtual void addChild(Component *object);
   virtual void addChild(Component *object, const std::string &label, bool resize = true);

   virtual void removeChild(Component *object);

   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);
   
   void setCurrTabIndex(int index);
   inline int getCurrTabIndex(void) const;

   inline scv::Component *getCurrComponent(void) const;

   void display(void);

private:
   void createTexture(void);
   void configPanel(void);

   static const int s_tabSpacing, s_barHeight;

   int _currecOverTab, _currSelectedTab;

   std::vector<int> _index;
   std::vector<std::string> _labels;
   std::vector<bool> _resize;
};

///////////////////////////////////////////////////////////

int TabbedPane::getCurrTabIndex(void) const {
   return _currSelectedTab;
}

scv::Component *TabbedPane::getCurrComponent(void) const {
   if (_currSelectedTab != -1) {
      return getChild(_currSelectedTab);
   } else {
      return NULL;
   }
}

} // namespace scv

#endif // __SCV_TABEED_PANE_H__
