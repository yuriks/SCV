#ifndef __GROUP_PANEL_H__
#define __GROUP_PANEL_H__

#include "Group.h"

class GroupPanel;
class GroupPanelMenu : public scv::ContextMenu {
public:
   ///////////////////////////////////////////////////////////
   GroupPanelMenu(GroupPanel *host);
   virtual ~GroupPanelMenu(void);
   ///////////////////////////////////////////////////////////

   virtual void onMenuAccessed(const std::deque<std::string> &address);
protected:
   GroupPanel *_host;
private:
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

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
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual std::string getCode(const std::string &tab) = 0;
   inline GroupType getType(void) const;
   ///////////////////////////////////////////////////////////

   void createPreview(scv::Group &group);

   ///////////////////////////////////////////////////////////
   virtual void display(void);   
   ///////////////////////////////////////////////////////////

protected:
   static const std::string s_defaultTab;

   GroupType _type;
   scv::Group *_verticalGroup, *_horizontalGroup;
   virtual void createTexture(void);

private:   
   static scv::ComponentTexture *s_customTexture;
};

///////////////////////////////////////////////////////////

GroupPanel::GroupType GroupPanel::getType(void) const {
   return _type;
}


#endif //__GROUP_PANEL_H__