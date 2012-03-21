#ifndef __PALLETE_COMPONENTS_H__
#define __PALLETE_COMPONENTS_H__

#include "GroupPanelWrapper.h"

class ButtonPallete :public scv::Button {
public:
   ///////////////////////////////////////////////////////////
   ButtonPallete(const scv::Point &p, const std::string &str);
   virtual ~ButtonPallete(void);
   ///////////////////////////////////////////////////////////

   void onMouseClick(const scv::MouseEvent &evt);
};

///////////////////////////////////////////////////////////
class ButtonDeletePallete :public scv::Button {
public:
   ///////////////////////////////////////////////////////////
   ButtonDeletePallete(const scv::Point &p, const std::string &str, GroupPanelWrapper*, GroupPanelWrapper*);
   virtual ~ButtonDeletePallete(void);
   ///////////////////////////////////////////////////////////

   void onMouseClick(const scv::MouseEvent &evt);
private:
    GroupPanelWrapper* _h;
    GroupPanelWrapper* _v;

};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class PalleteComponents : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   PalleteComponents(std::string title, const scv::Point &p1, const scv::Point &p2);
   virtual ~PalleteComponents(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void addComponent(std::string name);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void adjustButtonsWidth(void);
   ///////////////////////////////////////////////////////////

protected:
   void adjustButtons(void);
   bool valid(int componentsPerLine);

   static const int s_defaultGap = 5;
   int _componentsPerLine;
   bool _widthSet;
};

class PalleteDeleteComponents : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   PalleteDeleteComponents(std::string title, const scv::Point &p1, const scv::Point &p2);
   virtual ~PalleteDeleteComponents(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void addComponent(std::string name, GroupPanelWrapper*, GroupPanelWrapper*);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void adjustButtonsWidth(void);
   ///////////////////////////////////////////////////////////

protected:
   void adjustButtons(void);
   bool valid(int componentsPerLine);

   static const int s_defaultGap = 5;
   int _componentsPerLine;
   bool _widthSet;
};

#endif //__PALLETE_COMPONENTS_H__