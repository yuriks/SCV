#ifndef __PARALLEL_GROUP_PANEL_H__
#define __PARALLEL_GROUP_PANEL_H__

#include "GroupPanel.h"

class ParallelGroupPanel : public GroupPanel {
public:
   ///////////////////////////////////////////////////////////
   ParallelGroupPanel(GroupType type);
   virtual ~ParallelGroupPanel(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   void applyColor(void);

   std::string getCode(void);

protected:
   
private:
};

#endif //__PARALLEL_GROUP_PANEL_H__