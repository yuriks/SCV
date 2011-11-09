#ifndef __GROUP_PANEL_WRAPPER_H__
#define __GROUP_PANEL_WRAPPER_H__

#include "GroupPanel.h"
#include "ParallelGroupPanel.h"
#include "SequentialGroupPanel.h"

class GroupPanelWrapper {
public:
   ///////////////////////////////////////////////////////////
   GroupPanelWrapper(scv::Panel *host);
   virtual ~GroupPanelWrapper(void);
   ///////////////////////////////////////////////////////////

   inline scv::Panel *getHost(void) const;

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
   scv::Panel *_host;
   GroupPanel *_verticalGroup, *_horizontalGroup;

};

///////////////////////////////////////////////////////////

scv::Panel * GroupPanelWrapper::getHost(void) const {
   return _host;
}


#endif //__GROUP_PANEL_WRAPPER_H__