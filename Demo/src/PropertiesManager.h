#ifndef __PROPERTIES_MANAGER_H__
#define __PROPERTIES_MANAGER_H__

#include "Properties.h"
#include "SpecializedProperties.h"

class PropertiesManager {
public:
   static Properties *getProperties(scv::Component *object) {
      CountersProperties::Singleton<CountersProperties>::getInstance()->setVisible(false);
      StringsProperties::Singleton<StringsProperties>::getInstance()->setVisible(false);
      StatesProperties::Singleton<StatesProperties>::getInstance()->setVisible(false);
      InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance()->setVisible(false);
      ImageProperties::Singleton<ImageProperties>::getInstance()->setVisible(false);
      Properties::getInstance()->setVisible(false);
      
      if (dynamic_cast<scv::Slider*>(object) || dynamic_cast<scv::Spinner*>(object)) {
         StringsProperties::Singleton<StringsProperties>::getInstance()->setVisible(true);
         return CountersProperties::Singleton<CountersProperties>::getInstance();
      } else if (dynamic_cast<scv::Button*>(object) || dynamic_cast<scv::Label*>(object) || dynamic_cast<scv::TextField*>(object) || dynamic_cast<scv::TextBox*>(object)) {
         StringsProperties::Singleton<StringsProperties>::getInstance()->setVisible(true);
         return StringsProperties::Singleton<StringsProperties>::getInstance();
      }  else if (dynamic_cast<scv::CheckBox*>(object) || dynamic_cast<scv::RadioButton*>(object) || dynamic_cast<scv::ToggleButton*>(object)) {
         StatesProperties::Singleton<StatesProperties>::getInstance()->setVisible(true);
         return StatesProperties::Singleton<StatesProperties>::getInstance();
      }  else if (dynamic_cast<scv::InternalFrame*>(object)) {
         InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance()->setVisible(true);
         return InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance();
      } else if (dynamic_cast<scv::Image*>(object)) {
         ImageProperties::Singleton<ImageProperties>::getInstance()->setVisible(true);
         return ImageProperties::Singleton<ImageProperties>::getInstance();
      }  else {
         return Properties::getInstance();   
      }
   }
protected:
   
private:
};

#endif //__PROPERTIES_MANAGER_H__