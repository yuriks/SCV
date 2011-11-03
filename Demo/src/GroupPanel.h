#ifndef __GROUP_PANEL_H__
#define __GROUP_PANEL_H__

#include "Group.h"

class GroupPanel : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   GroupPanel(scv::Group *group);
   virtual ~GroupPanel(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   scv::Group *getGroup(void) const;
   ///////////////////////////////////////////////////////////

   //Memory Management
   ///////////////////////////////////////////////////////////
   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);
   ///////////////////////////////////////////////////////////

protected:
   scv::Group *_group;
private:
};

class GroupContextMenu : public scv::ContextMenu {
public:
   ///////////////////////////////////////////////////////////
   GroupContextMenu(GroupPanel *panel);
   virtual ~GroupContextMenu(void);
   ///////////////////////////////////////////////////////////

   virtual void onMenuAccessed(const std::deque<std::string> &address);
protected:
   GroupPanel *_panel;
private:
};

#endif //__GROUP_PANEL_H__