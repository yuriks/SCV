#ifndef __SEQUENTIAL_GROUP_PANEL_H__
#define __SEQUENTIAL_GROUP_PANEL_H__

#include "GroupPanel.h"

class SequetialGroupPanel : public GroupPanel {
public:
   ///////////////////////////////////////////////////////////
   SequetialGroupPanel(GroupType type);
   virtual ~SequetialGroupPanel(void);
   ///////////////////////////////////////////////////////////

   void applyColor(void);

protected:
   
private:
};

#endif //__SEQUENTIAL_GROUP_PANEL_H__