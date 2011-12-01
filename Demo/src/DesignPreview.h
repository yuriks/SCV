#ifndef __DESIGN_PREVIEW_H__
#define __DESIGN_PREVIEW_H__

#include "GroupPanelWrapper.h"

class DesignPreview : public scv::Panel, public Singleton<DesignPreview> {
friend class Singleton<DesignPreview>;
public:
   ///////////////////////////////////////////////////////////
   void createPreview(GroupPanelWrapper *hPanelWrapper, GroupPanelWrapper *vPanelWrapper);
   ///////////////////////////////////////////////////////////

   void setFrameSize(int width, int height);

   void display(void);

protected:
   ///////////////////////////////////////////////////////////
   class FramePreview : public scv::InternalFrame {
   public:
      ///////////////////////////////////////////////////////////
      FramePreview(void);
      virtual ~FramePreview(void);
      ///////////////////////////////////////////////////////////
      virtual void onClose(void);
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   DesignPreview(void);
   virtual ~DesignPreview(void);
   ///////////////////////////////////////////////////////////

   scv::InternalFrame *_frame;
   GroupObjectWrapper *_wrappedFrame;
   scv::Group *hGroupLayout, *vGroupLayout;
};

#endif //__DESIGN_PREVIEW_H__