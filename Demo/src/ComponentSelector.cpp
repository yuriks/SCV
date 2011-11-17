#include "stdafx.h"
#include "ComponentSelector.h"

ComponentSelectorAccepted::ComponentSelectorAccepted(ComponentSelector *selector) {
   _selector = selector;
}

ComponentSelectorAccepted::~ComponentSelectorAccepted(void) {

}

void ComponentSelectorAccepted::onMouseClick(const scv::MouseEvent &evt) {
   _selector->accepted();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

ComponentSelector::ComponentSelector(Application *app) {
   _app = app;
}

ComponentSelector::~ComponentSelector(void) {

}

void ComponentSelector::accepted(void) {
}
