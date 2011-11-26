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
   GroupPanelWrapper(GroupPanel::GroupType type);
   virtual ~GroupPanelWrapper(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   ///////////////////////////////////////////////////////////
   static ParallelGroupPanel *createHorizontalParallelGroupPanel(void);
   static SequetialGroupPanel *createHorizontalSequentialGroupPanel(void);

   static ParallelGroupPanel *createVerticalParallelGroupPanel(void);
   static SequetialGroupPanel *createVerticalSequentialGroupPanel(void);
   ///////////////////////////////////////////////////////////

   //Memory Management
   ///////////////////////////////////////////////////////////
   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   //void setGroup(GroupPanel *group);
   inline GroupPanel *getGroup(void) const;

   std::string getGroupCode(void) const;
   ///////////////////////////////////////////////////////////

   scv::Group *createPreview(void);

   inline GroupPanel::GroupType getType(void) const;

protected:
   GroupPanelWrapperMenu *_contextMenu;
   GroupPanel::GroupType _type;
   GroupPanel *_group;
   scv::Group *_hGroup, *_vGroup;

};

///////////////////////////////////////////////////////////

GroupPanel *GroupPanelWrapper::getGroup(void) const {
   return _group;
}

GroupPanel::GroupType GroupPanelWrapper::getType(void) const {
   return _type;
}

///////////////////////////////////////////////////////////

#endif //__GROUP_PANEL_WRAPPER_H__