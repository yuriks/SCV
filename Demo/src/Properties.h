#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

#include "PropertieOption.h"

class Properties : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   Properties(int width);
   virtual ~Properties(void);
   ///////////////////////////////////////////////////////////   
   virtual void setComponent(scv::Component *component) = 0;

   void addChild(std::string title, PropertieOption::Type type);

   void onValueChange(const std::string &title, const std::string &str);
   void onValueChange(const std::string &title, bool state);
protected:
   
   scv::Component *_currComponent;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class PanelProperties : public Singleton<PanelProperties>, public Properties {
friend class Singleton<PanelProperties>;
public:   
   void setComponent(scv::Component *component);

protected:
   PanelProperties(void);
   virtual ~PanelProperties(void);

private:
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

#endif //__PROPERTIES_H__