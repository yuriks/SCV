#include "stdafx.h"

#include "Application.h"

class ButtonPallete :public scv::Button {
public:
   ButtonPallete(const scv::Point &p, const std::string &str) : Button(p, str) {

   }
   virtual ~ButtonPallete(void) {
   }

   void onMouseClick(const scv::MouseEvent &evt) {
   }
protected:
   
private:
};

class PanelPalleteComponents : public scv::Panel {
public:
   PanelPalleteComponents(std::string title, const scv::Point &p1, const scv::Point &p2) : Panel(p1, p2) {
      _componentsPerLine = 0;
      _widthSet = false;

      addChild(new scv::Label(scv::Point(s_defaultGap, s_defaultGap), title));
   }
   virtual ~PanelPalleteComponents(void) {
   }

   virtual void addComponent(std::string name) {
      if (!_widthSet) {
         addChild(new ButtonPallete(scv::Point(), name));
      }
   }

   void closeWidthButtons(void) {
      if (!_widthSet) {
         _widthSet = true;
         adjustButtons();         
         for (scv::Component::List::iterator iter = ++_children.begin(); iter != _children.end(); ++iter) {
            (*iter)->setWidth(getWidth() / _componentsPerLine - s_defaultGap);
         }
      }
   }

protected:
   void adjustButtons(void) {
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

   bool valid(int componentsPerLine) {
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

   static const int s_defaultGap = 5;
   int _componentsPerLine;
   bool _widthSet;
   
private:
};

int main(int argc, char* argv[]) {
   scv::Kernel::setInstance(new Application());
   scv::Kernel *kernel = scv::Kernel::getInstance();
   scv::ColorScheme *scheme = scv::ColorScheme::getInstance();
   
   scheme->loadScheme(scv::ColorScheme::osx);
   scheme->setColor(scv::ColorScheme::font, scv::Color4f(1,1,1));

   static const int s_defaultWindowWidht = 1280;
   static const int s_defaultWindowHeight = 720;
   
   kernel->setWindowSize(s_defaultWindowWidht, s_defaultWindowHeight);

   static const int s_defaultBorderGap = 10;
   static const int s_defaultRightBarSize = 300;


   scv::Panel *panelRightBar = new scv::Panel(scv::Point(s_defaultWindowWidht - s_defaultRightBarSize + s_defaultBorderGap, s_defaultBorderGap), scv::Point(s_defaultWindowWidht - s_defaultBorderGap, s_defaultWindowHeight - s_defaultBorderGap));
   kernel->addComponent(panelRightBar);
      
   //Palette
   ///////////////////////////////////////////////////////////
   scv::Panel *panelPalette = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultRightBarSize - s_defaultBorderGap - 26, 600));
   scv::ScrollPane *scrollPanePalette = new scv::ScrollPane(scv::Point(0, 0), scv::Point(s_defaultRightBarSize - s_defaultBorderGap - 10, 300), panelPalette);
   panelRightBar->addChild(scrollPanePalette);
   
   PanelPalleteComponents *containers = new PanelPalleteComponents("SCV Containers", scv::Point(0,0), scv::Point(panelPalette->getWidth(), 0));   
   //panelPalette->addChild(containers);
   containers->addComponent("Image");
   containers->addComponent("Panel");
   containers->addComponent("ScroolPane");
   containers->addComponent("TabbedPane");

   PanelPalleteComponents *controls = new PanelPalleteComponents("SCV Controls", scv::Point(0,0), scv::Point(panelPalette->getWidth(), 0));
   panelPalette->addChild(controls);
   controls->addComponent("Button");
   controls->addComponent("ToggleButton");
   controls->addComponent("ProgressBar");
   controls->addComponent("Slider");
   controls->addComponent("Spinner");
   controls->addComponent("ComboBox");
   controls->addComponent("MenuBar");
   controls->addComponent("CheckBox");
   controls->addComponent("RadioButton");
   controls->addComponent("Label");
   controls->addComponent("TextBox");
   controls->addComponent("TextField");
   controls->addComponent("Canvas");
   controls->addComponent("ColorPicker");
   controls->addComponent("Separator");
   controls->addComponent("Table");
   controls->closeWidthButtons();

   PanelPalleteComponents *windows = new PanelPalleteComponents("SCV Windows", scv::Point(0,0), scv::Point(panelPalette->getWidth(), 0));
   //panelPalette->addChild(windows);
   windows->addComponent("InternalFrame");

   ///////////////////////////////////////////////////////////

   //Design
   ///////////////////////////////////////////////////////////
   scv::Panel *panelDesign = new scv::Panel(scv::Point(0, 0), scv::Point(800, 600));
   panelDesign->setResizable(true);
   scv::ScrollPane *scrollPaneDesign = new scv::ScrollPane(scv::Point(s_defaultBorderGap, s_defaultBorderGap), scv::Point(s_defaultWindowWidht - s_defaultRightBarSize, s_defaultWindowHeight - s_defaultBorderGap), panelDesign);
   scrollPaneDesign->setPanel(panelDesign);
   kernel->addComponent(scrollPaneDesign);
   ///////////////////////////////////////////////////////////

   /*   
   scv::Panel *panel = new scv::Panel(scv::Point(40,40), scv::Point(1280 - 920, 720 - 40));
   panel->setResizable(true);

   scv::GroupLayout *layout = new scv::GroupLayout(panel);
   panel->setLayout(layout);

   scv::Label *label = new scv::Label(scv::Point(), "Find What:");
   panel->addChild(label);
   scv::TextField *textField = new scv::TextField(scv::Point(), 200, "");
   panel->addChild(textField);
   scv::CheckBox *caseCheckBox = new scv::CheckBox(scv::Point(), false, "Match Case");
   panel->addChild(caseCheckBox);
   scv::CheckBox *wrapCheckBox = new scv::CheckBox(scv::Point(), false, "Wrap Around");
   panel->addChild(wrapCheckBox);
   scv::CheckBox *wholeCheckBox = new scv::CheckBox(scv::Point(), false, "Whole Words");
   panel->addChild(wholeCheckBox);
   scv::CheckBox *backCheckBox = new scv::CheckBox(scv::Point(), false, "Search Backwards");
   panel->addChild(backCheckBox);
   scv::Button *findButton = new scv::Button(scv::Point(), "Find");
   panel->addChild(findButton);
   scv::Button *cancelButton = new scv::Button(scv::Point(), "Cancel");
   panel->addChild(cancelButton);

   layout->setHorizontalGroup(layout->createSequentialGroup()
      ->addComponent(label)
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
         ->addComponent(textField)
         ->addGroup(layout->createSequentialGroup()
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
               ->addComponent(caseCheckBox)
               ->addComponent(wholeCheckBox))
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING)
                  ->addComponent(wrapCheckBox)
                  ->addComponent(backCheckBox))))
         ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
            ->addComponent(findButton)
            ->addComponent(cancelButton))
      );

   layout->setVerticalGroup(layout->createSequentialGroup()
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addComponent(label)
         ->addComponent(textField)
         ->addComponent(findButton))
      ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
         ->addGroup(layout->createSequentialGroup()
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(caseCheckBox)
               ->addComponent(wrapCheckBox))
            ->addGroup(layout->createParallelGroup(scv::Spring::LEADING, false)
               ->addComponent(wholeCheckBox)
               ->addComponent(backCheckBox)))
         ->addComponent(cancelButton))
      );
   

   kernel->addComponent(panel);
   /**/

   kernel->run();
   return 0;
}
