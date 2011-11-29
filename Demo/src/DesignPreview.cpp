#include "stdafx.h"
#include "DesignPreview.h"

DesignPreview::DesignPreview(void) : scv::Panel(scv::Point(), scv::Point()) {
}

DesignPreview::~DesignPreview(void) {

}

void DesignPreview::createPreview(GroupPanelWrapper *hPanelWrapper, GroupPanelWrapper *vPanelWrapper) {
   scv::Component::List list = getChildren();
   removeAllChild();

   scv::Component::List::iterator iter = list.begin();
   while (iter != list.end()) {
      scv::Component *pItem = (*iter);
      iter = list.erase(iter);
      delete pItem;
   }

   if (_layout != NULL) {
      delete _layout;
   }

   scv::GroupLayout *layout = new scv::GroupLayout(this);
   setLayout(layout);

   GroupPanelWrapper::prepareDesignPreview();

   layout->setHorizontalGroup(hPanelWrapper->createPreview());
   layout->setVerticalGroup(vPanelWrapper->createPreview());

   GroupPanelWrapper::DesignList designList = GroupPanelWrapper::getDesignObjectWrapperList();
   for (GroupPanelWrapper::DesignList::iterator iter = designList.begin(); iter != designList.end(); ++iter) {
      addChild(*iter);
   }
}
