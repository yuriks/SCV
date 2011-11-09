#ifndef __GROUP_PANEL_WRAPPER_H__
#define __GROUP_PANEL_WRAPPER_H__

#include "GroupPanel.h"
#include "ParallelGroupPanel.h"
#include "SequentialGroupPanel.h"

class GroupPanelWrapper;
class GroupPanelWrapperMenu : public scv::ContextMenu {
public:
   ///////////////////////////////////////////////////////////
   GroupPanelWrapperMenu(GroupPanelWrapper *host);
   virtual ~GroupPanelWrapperMenu(void);
   ///////////////////////////////////////////////////////////

   virtual void onMenuAccessed(const std::deque<std::string> &address);
protected:
   GroupPanelWrapper *_host;
private:
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class GroupPanelWrapper : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   GroupPanelWrapper(void);
   virtual ~GroupPanelWrapper(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   ///////////////////////////////////////////////////////////
   static ParallelGroupPanel *createHorizontalParallelGroupPanel(void);
   static SequetialGroupPanel *createHorizontalSequentialGroupPanel(void);

   static ParallelGroupPanel *createVerticalParallelGroupPanel(void);
   static SequetialGroupPanel *createVerticalSequentialGroupPanel(void);
   ///////////////////////////////////////////////////////////

   void setHorizontalGroupVisible(bool vibility);
   void setVerticalGroupVisible(bool vibility);

   std::string getHorizontalGroupCode(void) const;
   std::string getVerticalGroupCode(void) const;

   ///////////////////////////////////////////////////////////
   void setHorizontalGroup(GroupPanel *group);
   void setVerticalGroup(GroupPanel *group);
   ///////////////////////////////////////////////////////////

protected:
   GroupPanel *_verticalGroup, *_horizontalGroup;

};

///////////////////////////////////////////////////////////

#endif //__GROUP_PANEL_WRAPPER_H__