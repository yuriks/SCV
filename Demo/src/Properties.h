#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

#include "PropertieOption.h"

class Properties : public Singleton<Properties>, public scv::Panel {
friend class Singleton<Properties>;
public:
   ///////////////////////////////////////////////////////////
   void addChild(std::string title, PropertieOption::Type type);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setComponent(scv::Component *component);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setValue(const std::string &title, const std::string &str);
   virtual void setValue(const std::string &title, bool state);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void onValueChange(const std::string &title, const std::string &str);
   virtual void onValueChange(const std::string &title, bool state);
   ///////////////////////////////////////////////////////////

protected:
   ///////////////////////////////////////////////////////////
   Properties(void);
   virtual ~Properties(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   static const std::string s_MinimumSize;
   static const std::string s_PreferredSize;
   static const std::string s_MaximumSize;
   ///////////////////////////////////////////////////////////

   typedef std::list<PropertieOption*> PropertieList;
   PropertieList _propertieList;

   scv::Group *_hGroup, *_hLeftGroup, *_hRightGroup, *_vGroup;
   scv::Component *_currComponent;
};

#endif //__PROPERTIES_H__