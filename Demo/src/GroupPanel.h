#ifndef __GROUP_PANEL_H__
#define __GROUP_PANEL_H__

#include "Group.h"

class GroupPanel : public scv::Panel {
public:
   enum GroupType {HORIZONTAL, VERTICAL};

   ///////////////////////////////////////////////////////////
   GroupPanel(GroupType type);
   virtual ~GroupPanel(void);
   ///////////////////////////////////////////////////////////

   //Memory Management
   ///////////////////////////////////////////////////////////
   virtual void addChild(scv::Component *object);
   virtual void removeChild(scv::Component *object);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual scv::Point getMinimumSize(void) const;
   virtual scv::Point getPreferredSize(void) const;
   virtual scv::Point getMaximumSize(void) const;
   ///////////////////////////////////////////////////////////
   
   virtual void display(void);

   virtual void applyColor(void) = 0;

protected:
   scv::Group *_verticalGroup, *_horizontalGroup;
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