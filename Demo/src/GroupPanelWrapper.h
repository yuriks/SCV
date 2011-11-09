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

   ///////////////////////////////////////////////////////////
   static ParallelGroupPanel *createHorizontalParallelGroupPanel(void);
   static ParallelGroupPanel *createHorizontalSequentialGroupPanel(void);

   static ParallelGroupPanel *createVerticalParallelGroupPanel(void);
   static ParallelGroupPanel *createVerticalSequentialGroupPanel(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setHorizontalGroup(GroupPanel *group);
   void setVerticalGroup(GroupPanel *group);
   ///////////////////////////////////////////////////////////

protected:
   scv::Panel *_host;
   GroupPanel *_verticalGroup, *_horizontalGroup;

};

#endif //__GROUP_PANEL_WRAPPER_H__