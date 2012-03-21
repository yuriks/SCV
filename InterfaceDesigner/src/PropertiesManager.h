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
      FrameProperties::Singleton<FrameProperties>::getInstance()->setVisible(false);
      Properties::getInstance()->setVisible(false);

      
      if (dynamic_cast<scv::Slider*>(object) || dynamic_cast<scv::Spinner*>(object)) {
         _curr = CountersProperties::Singleton<CountersProperties>::getInstance();
      } else if (dynamic_cast<scv::Button*>(object) || dynamic_cast<scv::Label*>(object) || dynamic_cast<scv::TextField*>(object) || dynamic_cast<scv::TextBox*>(object)) {
         _curr = StringsProperties::Singleton<StringsProperties>::getInstance();
      }  else if (dynamic_cast<scv::CheckBox*>(object) || dynamic_cast<scv::RadioButton*>(object) || dynamic_cast<scv::ToggleButton*>(object)) {
         _curr = StatesProperties::Singleton<StatesProperties>::getInstance();
      }  else if (dynamic_cast<scv::InternalFrame*>(object)) {
         if (static_cast<scv::InternalFrame*>(object) == CodeGenerator::getInstance()->getSCVFrame()) {
            _curr = FrameProperties::Singleton<FrameProperties>::getInstance();
         } else {            
            _curr = InternalFrameProperties::Singleton<InternalFrameProperties>::getInstance();
         }
      } else if (dynamic_cast<scv::Image*>(object)) {
         _curr = ImageProperties::Singleton<ImageProperties>::getInstance();
      }  else {
         _curr = Properties::getInstance();
      }

      getCurr()->setVisible(true);
      return getCurr();
   }

   static Properties *getCurr(void) {
      if (_curr == NULL) _curr = Properties::getInstance();
      return _curr;
   }

protected:
   static Properties *_curr;
};

__declspec(selectany) Properties *PropertiesManager::_curr = NULL;

#endif //__PROPERTIES_MANAGER_H__