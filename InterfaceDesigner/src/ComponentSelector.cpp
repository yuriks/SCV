#include <SCV/SCV.h>
#include "ComponentSelector.h"

#include "Application.h"
#include "CodeGenerator.h"

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

   _comboBox = new scv::ComboBox(scv::Point(), 200);
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

   std::vector<std::string> vector;
   CodeGenerator::ManagedList list = CodeGenerator::getInstance()->getManagedComponents();
   for (CodeGenerator::ManagedList::iterator iter = list.begin(); iter != list.end(); ++iter) {
      vector.push_back((*iter)->getClassName());
   }

   _comboBox->setItems(vector);
}

void ComponentSelector::setVisible(bool state, GroupPanel *group) {
   _currGroup = group;

   if (_currGroup != NULL) {
      scv::Point groupPosition(group->getAbsolutePosition());
      setAbsolutePosition(scv::Point(groupPosition.x + (_currGroup->getWidth() - getWidth()) / 2, groupPosition.y + (_currGroup->getHeight() - getHeight()) / 2));
   }

   scv::InternalFrame::setVisible(state);
}

void ComponentSelector::accepted(void) {
   if (_currGroup != NULL) {
      ManagedComponent *managed = CodeGenerator::getInstance()->getManagedComponent(_comboBox->getValue());
      if (managed != NULL) {
         _currGroup->addChild(managed->getComponent());
      }
   }
   setVisible(false, NULL);   
}

void ComponentSelector::refused(void) {
   setVisible(false, NULL);
}
