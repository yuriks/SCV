#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

#include "PropertieOption.h"

class Properties : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   Properties(int width);
   virtual ~Properties(void);
   ///////////////////////////////////////////////////////////

   void addChild(std::string title, PropertieOption::Type type);

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
   static const std::string s_RelativePosition;
   static const std::string s_AbsolutePosition;
   static const std::string s_Width;
   static const std::string s_Height;
   static const std::string s_MinimumSize;
   static const std::string s_PreferredSize;
   static const std::string s_MaximumSize;
   static const std::string s_Draggable;
   static const std::string s_Resizable;
   static const std::string s_Visible;
   static const std::string s_CallbacksStatus;
   static const std::string s_ParentScissor;
   static const std::string s_Scissor;

   typedef std::list<PropertieOption*> PropertieList;
   PropertieList _propertieList;

   scv::Group *_hGroup, *_hLeftGroup, *_hRightGroup, *_vGroup;
   scv::Component *_currComponent;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class PanelProperties : public Singleton<PanelProperties>, public Properties {
friend class Singleton<PanelProperties>;
public:   
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
   PanelProperties(void);
   virtual ~PanelProperties(void);
   ///////////////////////////////////////////////////////////

private:
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

#endif //__PROPERTIES_H__