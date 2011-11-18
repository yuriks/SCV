#include "stdafx.h"
#include "ComponentSelector.h"

ComponentSelectorAccepted::ComponentSelectorAccepted(ComponentSelector *selector) : scv::Button(scv::Point(), "Ok") {
   _selector = selector;
}

ComponentSelectorAccepted::~ComponentSelectorAccepted(void) {
}

void ComponentSelectorAccepted::onMouseClick(const scv::MouseEvent &evt) {
   _selector->accepted();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ComponentSelectorRefused::ComponentSelectorRefused(ComponentSelector *selector) : scv::Button(scv::Point(), "Cancel") {
   _selector = selector;
}

ComponentSelectorRefused::~ComponentSelectorRefused(void) {
}

void ComponentSelectorRefused::onMouseClick(const scv::MouseEvent &evt) {
   _selector->refused();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ComponentSelector::ComponentSelector(void) : scv::InternalFrame(400, 200, "Component Selector") {
   scv::Panel *panel = getPanel();

   scv::Button *acceptButton = new ComponentSelectorAccepted(this);
   scv::Button *refuseButton = new ComponentSelectorRefused(this);

   panel->addChild(acceptButton);
   panel->addChild(refuseButton);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

   layout->setHorizontalGroup(scv::GroupLayout::createParallelGroup()
      ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
         ->addComponent(acceptButton)
         ->addComponent(refuseButton)
      )
   );

   layout->setVerticalGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
      ->addGroup(scv::GroupLayout::createParallelGroup()
         ->addComponent(acceptButton, acceptButton->getHeight())
         ->addComponent(refuseButton, refuseButton->getHeight())
      )   
   );
}

ComponentSelector::~ComponentSelector(void) {

}

void ComponentSelector::accepted(void) {
   setVisible(false);
}

void ComponentSelector::refused(void) {
   setVisible(false);
}
