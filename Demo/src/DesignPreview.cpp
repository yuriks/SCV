#include "stdafx.h"
#include "DesignPreview.h"

DesignPreview::FramePreview::FramePreview(void) : scv::InternalFrame(0, 0, "SCV Preview") {
   setDraggable(false);
   setResizable(false);
}

DesignPreview::FramePreview::~FramePreview(void) {
}

void DesignPreview::FramePreview::onClose(void) {
   setVisible(true);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

DesignPreview::DesignPreview(void) : scv::Panel(scv::Point(), scv::Point()) {
   _frame = new FramePreview();
   addChild(_frame);

   scv::GroupLayout *layout = new scv::GroupLayout(this);
   setLayout(layout);

   hGroupLayout = scv::GroupLayout::createParallelGroup();
   vGroupLayout = scv::GroupLayout::createParallelGroup();

   layout->setHorizontalGroup(scv::GroupLayout::createSequentialGroup()->addGap(15, 15, -1)->addGroup(hGroupLayout)->addGap(15, 15, -1));
   layout->setVerticalGroup(scv::GroupLayout::createSequentialGroup()->addGap(15, 15, -1)->addGroup(vGroupLayout)->addGap(15, 15, -1));

   setFrameSize(-1, -1);
}

DesignPreview::~DesignPreview(void) {

}

void DesignPreview::createPreview(GroupPanelWrapper *hPanelWrapper, GroupPanelWrapper *vPanelWrapper) {
   if (_frame->getPanel() != NULL) {
      delete _frame->getPanel();
   }
   _frame->setPanel(new scv::Panel(scv::Point(), scv::Point()));

   scv::GroupLayout *layout = new scv::GroupLayout(_frame->getPanel());
   _frame->getPanel()->setLayout(layout);

   GroupPanelWrapper::prepareDesignPreview();

   layout->setHorizontalGroup(hPanelWrapper->createPreview());
   layout->setVerticalGroup(vPanelWrapper->createPreview());

   GroupPanelWrapper::DesignList designList = GroupPanelWrapper::getDesignObjectWrapperList();
   for (GroupPanelWrapper::DesignList::iterator iter = designList.begin(); iter != designList.end(); ++iter) {
      _frame->getPanel()->addChild(*iter);
   }
}

void DesignPreview::setFrameSize(int width, int height) {
   hGroupLayout->removeComponent(_frame);
   vGroupLayout->removeComponent(_frame);

   hGroupLayout->addComponent(_frame, width);
   vGroupLayout->addComponent(_frame, height);
}

