#ifndef __PROPERTIES_MANAGER_H__
#define __PROPERTIES_MANAGER_H__

#include "Properties.h"
#include "SpecializedProperties.h"

class PropertiesManager {
public:
   static Properties *getProperties(scv::Component *object) {
      if (dynamic_cast<scv::Slider*>(object) || dynamic_cast<scv::Spinner*>(object)) {
         return CountersProperties::Singleton<CountersProperties>::getInstance();
      } else if (dynamic_cast<scv::Button*>(object) || dynamic_cast<scv::Label*>(object) || dynamic_cast<scv::TextField*>(object) || dynamic_cast<scv::TextBox*>(object)) {
         return StringsProperties::Singleton<StringsProperties>::getInstance();
      } else if (dynamic_cast<scv::CheckBox*>(object) || dynamic_cast<scv::RadioButton*>(object) || dynamic_cast<scv::ToggleButton*>(object)) {
         return StatesProperties::Singleton<StatesProperties>::getInstance();
      } else if (dynamic_cast<scv::InternalFrame*>(object)) {
         return InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance();
      } else if (dynamic_cast<scv::Image*>(object)) {
         return ImageProperties::Singleton<ImageProperties>::getInstance();
      } else {
         return Properties::getInstance();
      }
   }
protected:
   
private:
};

#endif //__PROPERTIES_MANAGER_H__