#include "stdafx.h"
#include "ComponentSelector.h"

#include "Application.h"

ComponentSelectorAccepted::ComponentSelectorAccepted(ComponentSelector *selector) : scv::Button(scv::Point(), "Ok") {
   _selector = selector;
}

ComponentSelectorAccepted::~ComponentSelectorAccepted(void) {
}

void ComponentSelectorAccepted::onMouseUp(const scv::MouseEvent &evt) {
   _selector->accepted();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ComponentSelectorRefused::ComponentSelectorRefused(ComponentSelector *selector) : scv::Button(scv::Point(), "Cancel") {
   _selector = selector;
}

ComponentSelectorRefused::~ComponentSelectorRefused(void) {
}

void ComponentSelectorRefused::onMouseUp(const scv::MouseEvent &evt) {
   _selector->refused();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ComponentSelector::ComponentSelector(void) : scv::InternalFrame(400, 0, "Component Selector") {
   scv::Panel *panel = getPanel();

   _comboBox = new scv::ComboBox(scv::Point(), 0);
   panel->addChild(_comboBox);

   scv::Button *acceptButton = new ComponentSelectorAccepted(this);
   scv::Button *refuseButton = new ComponentSelectorRefused(this);

   panel->addChild(acceptButton);
   panel->addChild(refuseButton);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

   layout->setHorizontalGroup(scv::GroupLayout::createSequentialGroup()
      ->addGap(15)
      ->addGroup(scv::GroupLayout::createParallelGroup()         
         ->addComponent(_comboBox)
         ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
            ->addComponent(acceptButton)
            ->addComponent(refuseButton)
         )
      )
      ->addGap(15)
   );

   layout->setVerticalGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
      ->addGap(5)
      ->addComponent(_comboBox, _comboBox->getHeight())
      ->addGroup(scv::GroupLayout::createParallelGroup()
         ->addComponent(acceptButton, acceptButton->getHeight())
         ->addComponent(refuseButton, refuseButton->getHeight())
      )   
   );

   setResizable(false);
}

ComponentSelector::~ComponentSelector(void) {   
}

void ComponentSelector::onOpen(void) {
   setHeight(getPanel()->getMinimumSize().y + s_borderTop + s_borderWidth + 15);

   //_comboBox->setItems();
}

void ComponentSelector::accepted(void) {
   setVisible(false);
}

void ComponentSelector::refused(void) {
   setVisible(false);
}
