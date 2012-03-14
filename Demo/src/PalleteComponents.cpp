#include "stdafx.h"
#include "PalleteComponents.h"
#include "Application.h"

ButtonPallete::ButtonPallete(const scv::Point &p, const std::string &str) : Button(p, str) {
}

ButtonPallete::~ButtonPallete(void) {

}

void ButtonPallete::onMouseClick(const scv::MouseEvent &evt) {
   Application *app = static_cast<Application*>(scv::Kernel::getInstance());
   app->addComponentFromPalette(getString());
}
/////////////////////////////////////////////////////////
ButtonDeletePallete::ButtonDeletePallete(const scv::Point &p, const std::string &str, GroupPanelWrapper* H, GroupPanelWrapper* V) : Button(p, str) {
    _h = H;
    _v = V;
}

ButtonDeletePallete::~ButtonDeletePallete(void) {

}

void ButtonDeletePallete::onMouseClick(const scv::MouseEvent &evt) {
    CodeGenerator::getInstance()->deleteComponents();
    _h->removeAllChild();
    _v->removeAllChild();
    (static_cast<Application *>(Application::getInstance()))->createPreview();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


PalleteComponents::PalleteComponents(std::string title, const scv::Point &p1, const scv::Point &p2) : Panel(p1, p2) {
   _componentsPerLine = 0;
   _widthSet = false;
   addChild(new scv::Label(scv::Point(s_defaultGap, s_defaultGap), title));
}

PalleteComponents::~PalleteComponents(void) {
}

void PalleteComponents::addComponent(std::string name) {
   if (!_widthSet) {
      addChild(new ButtonPallete(scv::Point(), name));
   }
}

void PalleteComponents::adjustButtonsWidth(void) {
   if (!_widthSet) {
      _widthSet = true;
      adjustButtons();
      if (_children.size() == 2) {
         scv::Component::List::iterator iter = ++_children.begin();
         (*iter)->setWidth(getWidth() - s_defaultGap + 1);
      } else {         
         for (scv::Component::List::iterator iter = ++_children.begin(); iter != _children.end(); ++iter) {
            (*iter)->setWidth(getWidth() / _componentsPerLine - s_defaultGap + 2);
         }
      }
   }
}

void PalleteComponents::adjustButtons(void) {
   _componentsPerLine = _children.size();

   while (!valid(_componentsPerLine)) {
      _componentsPerLine--;
   }
   if (_componentsPerLine <= 0) _componentsPerLine = 1;

   int currLine = 0, componets = _componentsPerLine, lastEnd = 0;
   scv::Component::List::iterator iter = _children.begin();
   int x, y;
   for (scv::Component::List::iterator iter = ++_children.begin(); iter != _children.end(); ++iter) {
      y = (*_children.begin())->getHeight() + s_defaultGap;
      if (currLine == 0) {
         y += s_defaultGap;
      } else {
         y += currLine * (*++_children.begin())->getHeight() + s_defaultGap + (s_defaultGap * currLine - 1);
      }            
      if (_componentsPerLine - componets == 0) {
         x = s_defaultGap / 2;
      } else {
         x = s_defaultGap / 2 + (getWidth() / _componentsPerLine) * (_componentsPerLine - componets);
      }
      (*iter)->setRelativePosition(scv::Point(x, y));         
      lastEnd = x + (*iter)->getWidth();
      componets--;
      if (componets == 0) {
         componets = _componentsPerLine;
         currLine++;
      }
   }
   setHeight(y + (*++_children.begin())->getHeight() + s_defaultGap);
}

bool PalleteComponents::valid(int componentsPerLine) {
   int width = 0, line = componentsPerLine;
   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      width += (*iter)->getWidth() + s_defaultGap * 2;
      line--;
      if (line == 0) {
         if (width > getWidth()) {
            return false;
         } else {
            width = 0;
            line = componentsPerLine;
         }
      }         
   }
   return true;
}

///////////////////////////////////////////////////////

PalleteDeleteComponents::PalleteDeleteComponents(std::string title, const scv::Point &p1, const scv::Point &p2) : Panel(p1, p2) {
   _componentsPerLine = 0;
   _widthSet = false;
   addChild(new scv::Label(scv::Point(s_defaultGap, s_defaultGap), title));
}

PalleteDeleteComponents::~PalleteDeleteComponents(void) {
}

void PalleteDeleteComponents::addComponent(std::string name, GroupPanelWrapper* H, GroupPanelWrapper* V) {
   if (!_widthSet) {
      addChild(new ButtonDeletePallete(scv::Point(), name, H, V));
   }
}

void PalleteDeleteComponents::adjustButtonsWidth(void) {
   if (!_widthSet) {
      _widthSet = true;
      adjustButtons();
      if (_children.size() == 2) {
         scv::Component::List::iterator iter = ++_children.begin();
         (*iter)->setWidth(getWidth() - s_defaultGap + 1);
      } else {         
         for (scv::Component::List::iterator iter = ++_children.begin(); iter != _children.end(); ++iter) {
            (*iter)->setWidth(getWidth() / _componentsPerLine - s_defaultGap + 2);
         }
      }
   }
}

void PalleteDeleteComponents::adjustButtons(void) {
   _componentsPerLine = _children.size();

   while (!valid(_componentsPerLine)) {
      _componentsPerLine--;
   }
   if (_componentsPerLine <= 0) _componentsPerLine = 1;

   int currLine = 0, componets = _componentsPerLine, lastEnd = 0;
   scv::Component::List::iterator iter = _children.begin();
   int x, y;
   for (scv::Component::List::iterator iter = ++_children.begin(); iter != _children.end(); ++iter) {
      y = (*_children.begin())->getHeight() + s_defaultGap;
      if (currLine == 0) {
         y += s_defaultGap;
      } else {
         y += currLine * (*++_children.begin())->getHeight() + s_defaultGap + (s_defaultGap * currLine - 1);
      }            
      if (_componentsPerLine - componets == 0) {
         x = s_defaultGap / 2;
      } else {
         x = s_defaultGap / 2 + (getWidth() / _componentsPerLine) * (_componentsPerLine - componets);
      }
      (*iter)->setRelativePosition(scv::Point(x, y));         
      lastEnd = x + (*iter)->getWidth();
      componets--;
      if (componets == 0) {
         componets = _componentsPerLine;
         currLine++;
      }
   }
   setHeight(y + (*++_children.begin())->getHeight() + s_defaultGap);
}

bool PalleteDeleteComponents::valid(int componentsPerLine) {
   int width = 0, line = componentsPerLine;
   for (scv::Component::List::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
      width += (*iter)->getWidth() + s_defaultGap * 2;
      line--;
      if (line == 0) {
         if (width > getWidth()) {
            return false;
         } else {
            width = 0;
            line = componentsPerLine;
         }
      }         
   }
   return true;
}