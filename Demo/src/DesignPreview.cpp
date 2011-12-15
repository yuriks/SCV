#include "stdafx.h"
#include "DesignPreview.h"
#include "CodeGenerator.h"

DesignPreview::FramePreview::FramePreview(void) : scv::InternalFrame(0, 0, "SCV Application") {
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
   _wrappedFrame = new GroupObjectWrapper(_frame, false);
   addChild(_wrappedFrame);

   CodeGenerator::getInstance()->setSCVFrame(_frame);

   scv::GroupLayout *layout = new scv::GroupLayout(this);
   setLayout(layout);

   hGroupLayout = scv::GroupLayout::createParallelGroup();
   vGroupLayout = scv::GroupLayout::createParallelGroup();

   layout->setHorizontalGroup(scv::GroupLayout::createSequentialGroup()->addGap(15, 15, -1)->addGroup(hGroupLayout)->addGap(15, 15, -1));
   layout->setVerticalGroup(scv::GroupLayout::createSequentialGroup()->addGap(15, 15, -1)->addGroup(vGroupLayout)->addGap(15, 15, -1));

   setFrameSize(400, 300);
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
   hGroupLayout->removeComponent(_wrappedFrame);
   vGroupLayout->removeComponent(_wrappedFrame);

   hGroupLayout->addComponent(_wrappedFrame, width);
   vGroupLayout->addComponent(_wrappedFrame, height);

   _wrappedFrame->setSize(width, height);
   _frame->setSize(_wrappedFrame->getWidth(), _wrappedFrame->getHeight());
}

void DesignPreview::display(void) {
   setFrameSize(_frame->getWidth(), _frame->getHeight());
   scv::Panel::display();
}

