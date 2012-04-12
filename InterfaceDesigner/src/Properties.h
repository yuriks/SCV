#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

#include "PropertieOption.h"

class Properties : public scv::Panel, public Singleton<Properties> {
friend class Singleton<Properties>;
public:
   ///////////////////////////////////////////////////////////
   void addChild(std::string title, PropertieOption::Type type);
   using scv::Panel::addChild;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void setComponent(scv::Component *component);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setValue(const std::string &title, const std::string &str);
   void setValue(const std::string &title, bool state);
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
   static const std::string s_CustomClass;
   ///////////////////////////////////////////////////////////

   typedef std::list<PropertieOption*> PropertieList;
   PropertieList _propertieList;

   scv::Group *_hGroup, *_hLeftGroup, *_hRightGroup, *_vGroup;
   scv::Component *_currComponent;
};

#endif //__PROPERTIES_H__