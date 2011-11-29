#ifndef __DESIGN_PREVIEW_H__
#define __DESIGN_PREVIEW_H__

#include "GroupPanelWrapper.h"

class DesignPreview : public scv::Panel, public Singleton<DesignPreview> {
friend class Singleton<DesignPreview>;
public:
   ///////////////////////////////////////////////////////////
   void createPreview(GroupPanelWrapper *hPanelWrapper, GroupPanelWrapper *vPanelWrapper);
   ///////////////////////////////////////////////////////////

protected:
   ///////////////////////////////////////////////////////////
   DesignPreview(void);
   virtual ~DesignPreview(void);
   ///////////////////////////////////////////////////////////
};

#endif //__DESIGN_PREVIEW_H__