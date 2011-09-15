#include "stdafx.h"
#include "InterfaceDesign.h"
#include "MenuDesign.h"
#include "AbstractWindow.h"

InterfaceDesign::InterfaceDesign(scv::Panel *_panel, bool remove) : ContextMenu("InterfaceDesign") {

   m_panel = _panel;
   contButton = contFrame = contTeggleButton = contTextField = contTextBox = contRadioButton = contMenubar = contLabel = contCheckbox = 0;
   contProgressBar = 50;
   ContextMenu * panel = new ContextMenu("Add Panel");
   ContextMenu * component = new ContextMenu("Add Component");

   addMenu(panel);
   addMenu(component);
   if(remove)
      addMenu(new ContextMenu("Remove Component"));
   addMenu(new ContextMenu("Generate Code..."));

   ContextMenu * open = new ContextMenu("Open");
   addMenu(open);
   open->addMenu(new ContextMenu("text"));
   
   panel->addMenu(new ContextMenu("Image"));
   panel->addMenu(new ContextMenu("Internal Frame"));
   panel->addMenu(new ContextMenu("Panel"));
   panel->addMenu(new ContextMenu("Scroll Pane"));
   panel->addMenu(new ContextMenu("Tabbed Pane"));
   
   
   

   component->addMenu(new ContextMenu("Button"));
   component->addMenu(new ContextMenu("Canvas"));
   component->addMenu(new ContextMenu("CheckBox"));
   component->addMenu(new ContextMenu("Color Picker"));
   component->addMenu(new ContextMenu("ComboBox"));
   component->addMenu(new ContextMenu("Label"));
   component->addMenu(new ContextMenu("Menu Bar"));
   component->addMenu(new ContextMenu("Progress Bar"));
   component->addMenu(new ContextMenu("Radio Button"));
   ContextMenu * separator = new ContextMenu("Separator");
   separator->addMenu(new ContextMenu("Horizontal"));
   separator->addMenu(new ContextMenu("Vertical"));
   component->addMenu(separator);
   component->addMenu(new ContextMenu("Slider"));
   component->addMenu(new ContextMenu("Spinner"));
   component->addMenu(new ContextMenu("Table"));
   component->addMenu(new ContextMenu("TextBox"));
   component->addMenu(new ContextMenu("TextField"));
   component->addMenu(new ContextMenu("Toggle Button"));
   component->addMenu(new ContextMenu("Tree View"));

}


void InterfaceDesign::onMenuAccessed(const std::deque<std::string> &address) {

   if (address.size() == 0) {
      return;
   } else if (address.size() == 1) {

   } else  if (address.size() == 2) {
      if (address[1] == "Remove Component") {
		  scv::Kernel::getInstance()->removeComponent(m_panel);
      } else if (address[1] == "Generate Code...") {
         //scv::Kernel::getInstance()->generateCode();
      }

   } else  if (address.size() == 3) {
      if (address[2] == "Button") {

         scv::Button * button;
         if (m_panel != NULL) button = new scv::Button(getCurrPosition() - m_panel->getAbsolutePosition(), "button " + scv::toString(contButton));
         else                 button = new scv::Button(getCurrPosition() , "button " + scv::toString(contButton));

         contButton++;
         button->setDraggable(true);
         button->setResizable(true);
         button->registerContextMenu(new MenuRename(button));

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(button);
         else m_panel->addComponent(button);

         AbstractWindow *win = new AbstractWindow(button);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);


      } else if (address[2] == "Canvas") {

         scv::Canvas * canvas;
         if (m_panel != NULL) canvas = new scv::Canvas(getCurrPosition() - m_panel->getAbsolutePosition(), 200, 200);
         else                 canvas = new scv::Canvas(getCurrPosition() , 200, 200);

         canvas->setDraggable(true);
         canvas->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(canvas);
         else m_panel->addComponent(canvas);

         canvas->registerContextMenu(new RemoveComponent(canvas));

      } else if (address[2] == "CheckBox") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::CheckBox * checkbox;
         if (m_panel != NULL) checkbox = new scv::CheckBox(getCurrPosition() - m_panel->getAbsolutePosition(), true,"checkbox " + scv::toString(contCheckbox));
         else                 checkbox = new scv::CheckBox(getCurrPosition(), true,"checkbox " + scv::toString(contCheckbox));

         contCheckbox++;
         checkbox->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(checkbox);
         else panel->addComponent(checkbox);

         AbstractWindow *win = new AbstractWindow(checkbox);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         checkbox->registerContextMenu(new RemoveComponent(checkbox));

      } else if (address[2] == "Color Picker") {

         scv::ColorPicker * colorpicker;
         if (m_panel != NULL) colorpicker = new scv::ColorPicker(getCurrPosition() - m_panel->getAbsolutePosition());
         else                 colorpicker = new scv::ColorPicker(getCurrPosition());

         colorpicker->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(colorpicker);
         else  m_panel->addComponent(colorpicker);

         colorpicker->registerContextMenu(new RemoveComponent(colorpicker));

      } else if (address[2] == "ComboBox") {

         scv::ComboBox * combobox;
         if (m_panel != NULL) combobox = new scv::ComboBox(getCurrPosition() - m_panel->getAbsolutePosition(), 100);
         else                 combobox = new scv::ComboBox(getCurrPosition(), 100);

         combobox->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(combobox);
         else  m_panel->addComponent(combobox);

         combobox->registerContextMenu(new RemoveComponent(combobox));

      } else if (address[2] == "Image") {

         scv::Image *opImage;

         scv::Kernel::getInstance()->OpenFile();

         if(!scv::FileOpen::getInstance()->getSpath().empty()) {
            if (m_panel != NULL) opImage = new scv::Image(getCurrPosition() - m_panel->getRelativePosition(), scv::FileOpen::getInstance()->getSpath());
            else                 opImage = new scv::Image(getCurrPosition(), scv::FileOpen::getInstance()->getSpath());

            if(opImage != NULL) {
               opImage->setDraggable(true);
               opImage->setResizable(true);

               if (m_panel != NULL) m_panel->addComponent(opImage);
               else scv::Kernel::getInstance()->addComponent(opImage);
               
               opImage->registerContextMenu(new InterfaceDesign(opImage, true));
            }
         }
     
      } else if (address[2] == "Label") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::Label * label;
         if (m_panel != NULL) label = new scv::Label(getCurrPosition() - m_panel->getAbsolutePosition(), "Label Example" + scv::toString(contLabel));
         else                 label = new scv::Label(getCurrPosition(), "Label Example" + scv::toString(contLabel));

         contLabel++;
         label->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(label);
         else panel->addComponent(label);

         AbstractWindow *win = new AbstractWindow(label);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         label->registerContextMenu(new RemoveComponent(label));

      } else if (address[2] == "Menu Bar") {


         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::MenuBar * menubar;
         if (m_panel != NULL) menubar = new scv::MenuBar(m_panel->getWidth());
         else                 menubar = new scv::MenuBar(scv::Kernel::getInstance()->getWidth());

         menubar->setResizable(true);
         menubar->setDraggable(true);
         menubar->registerContextMenu(new MenuDesign(menubar)); //here is the add menu, and remove menu.

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(menubar);
         else m_panel->addComponent(menubar);
         contMenubar++;

      } else if (address[2] == "Progress Bar") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::ProgressBar * progressbar;
         if (m_panel != NULL) progressbar = new scv::ProgressBar(getCurrPosition() - m_panel->getAbsolutePosition(),(float)contProgressBar);
         else                 progressbar = new scv::ProgressBar(getCurrPosition(), (float)contProgressBar);

         progressbar->setDraggable(true);
         progressbar->setResizable(true);
         contProgressBar++; contProgressBar = contProgressBar%101;
         progressbar->setDraggable(true);
         
         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(progressbar);
         else panel->addComponent(progressbar);

         progressbar->registerContextMenu(new RemoveComponent(progressbar));

      } else if (address[2] == "Radio Button") {

         scv::RadioButton * radiobutton;
         if (m_panel != NULL) radiobutton = new scv::RadioButton(getCurrPosition() - m_panel->getAbsolutePosition(), true, "radiobutton " + scv::toString(contRadioButton));
         else                 radiobutton = new scv::RadioButton(getCurrPosition(), true, "radiobutton " + scv::toString(contRadioButton));

         contRadioButton++;
         radiobutton->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(radiobutton);
         else m_panel->addComponent(radiobutton);

         AbstractWindow *win = new AbstractWindow(radiobutton);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         radiobutton->registerContextMenu(new RemoveComponent(radiobutton));

      } else if (address[2] == "Slider") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::Slider * slider;
         if (m_panel != NULL) slider = new scv::Slider(getCurrPosition() - m_panel->getAbsolutePosition(), 0.f, 100.f, 50.f, 1.f);
         else                 slider = new scv::Slider(getCurrPosition(), 0.f, 100.f, 50.f, 1.f);

         slider->setDraggable(true);
         slider->setResizable(true);
         

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(slider);
         else panel->addComponent(slider);

         slider->registerContextMenu(new RemoveComponent(slider));

      } else if (address[2] == "Spinner") {

         scv::Spinner * spinner;
         if (m_panel != NULL) spinner = new scv::Spinner(getCurrPosition() - m_panel->getAbsolutePosition(),0.f,100.f,50.f,1.f);
         else                 spinner = new scv::Spinner(getCurrPosition(),0.f,100.f,50.f,1.f);

         spinner->setDraggable(true);
         spinner->setResizable(true);
         
         spinner->registerContextMenu(new RemoveComponent(spinner));

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(spinner);
         else m_panel->addComponent(spinner);

         

      } else if (address[2] == "Table") {

         scv::Table * table;
         if (m_panel != NULL) table = new scv::Table(getCurrPosition() - m_panel->getAbsolutePosition(), 4, 4, 1, 50);
         else                 table = new scv::Table(getCurrPosition(), 4, 4, 1, 50);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(table);
         else m_panel->addComponent(table);

         table->setDraggable(true);
         table->setResizable(true);

         table->registerContextMenu(new RemoveComponent(table)); //need to click under the buttons or textbox.

      } else if (address[2] == "TextBox") {

         scv::TextBox * textbox;
         if (m_panel != NULL) textbox = new scv::TextBox(getCurrPosition() - m_panel->getAbsolutePosition(), 100, 4, "textbox " + scv::toString(contTextBox));
         else                 textbox = new scv::TextBox(getCurrPosition(), 100, 4, "textbox " + scv::toString(contTextBox));

         contTextBox++;
         textbox->setDraggable(true);
         textbox->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(textbox);
         else m_panel->addComponent(textbox);

         AbstractWindow *win = new AbstractWindow(textbox);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         textbox->registerContextMenu(new RemoveComponent(textbox));

      } else if (address[2] == "TextField") {

         scv::TextField * textfield;
         if (m_panel != NULL) textfield = new scv::TextField(getCurrPosition() - m_panel->getAbsolutePosition(), 100, "textfield " + scv::toString(contTextField));
         else                 textfield = new scv::TextField(getCurrPosition(), 100, "textfield " + scv::toString(contTextField));

         contTextField++;
         textfield->setDraggable(true);
         textfield->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(textfield);
         else m_panel->addComponent(textfield);

         AbstractWindow *win = new AbstractWindow(textfield);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         textfield->registerContextMenu(new RemoveComponent(textfield));

      } else if (address[2] == "Toggle Button") {

         scv::ToggleButton * togglebutton;
         if (m_panel != NULL) togglebutton = new scv::ToggleButton(getCurrPosition() - m_panel->getAbsolutePosition(), false, "toggle button " + scv::toString(contTeggleButton));
         else                 togglebutton = new scv::ToggleButton(getCurrPosition(), false, "toggle button " + scv::toString(contTeggleButton));

         contTeggleButton++;
         togglebutton->setDraggable(true);
         togglebutton->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(togglebutton);
         else m_panel->addComponent(togglebutton);

         AbstractWindow *win = new AbstractWindow(togglebutton);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         togglebutton->registerContextMenu(new RemoveComponent(togglebutton));

      } else if (address[2] == "Panel") {

         scv::Panel * newpanel;
         if (m_panel != NULL) newpanel = new scv::Panel(getCurrPosition() - m_panel->getAbsolutePosition(), 200, 200);
         else                 newpanel = new scv::Panel(getCurrPosition(), 200, 200);

         newpanel->registerContextMenu(new InterfaceDesign(newpanel, true));
         newpanel->setDraggable(true);
         newpanel->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newpanel);
         else m_panel->addComponent(newpanel);

      } else if (address[2] == "Tabbed Pane") {

         scv::TabbedPane * newtabbedpane;
         if (m_panel != NULL) newtabbedpane = new scv::TabbedPane(getCurrPosition() - m_panel->getRelativePosition(), 200, 200);
         else                 newtabbedpane = new scv::TabbedPane(getCurrPosition(), 200, 200);

         newtabbedpane->setDraggable(true);
         newtabbedpane->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newtabbedpane);
         else m_panel->addComponent(newtabbedpane);

         scv::Panel *panel = new scv::Panel();
         newtabbedpane->addPanel(panel,"Painel 1");

         panel->registerContextMenu(new InterfaceDesign(panel));

         newtabbedpane->registerContextMenu(new RemoveComponent(newtabbedpane));

      } else if (address[2] == "Scroll Pane") {

         scv::Panel * panel = new scv::Panel(scv::Point(),500,500);
         scv::ScrollPane * newscrollpane;
         if (m_panel != NULL) newscrollpane = new scv::ScrollPane(getCurrPosition() - m_panel->getRelativePosition(), 300, 300);
         else                 newscrollpane = new scv::ScrollPane(getCurrPosition(), 300, 300);
         newscrollpane->registerPanel(panel);
         newscrollpane->setDraggable(true);
         newscrollpane->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newscrollpane);
         else m_panel->addComponent(newscrollpane);

         panel->registerContextMenu(new InterfaceDesign(panel));

         newscrollpane->registerContextMenu(new RemoveComponent(newscrollpane));

      } else if (address[2] == "Internal Frame") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::InternalFrame * iframe = new scv::InternalFrame(200,200,"internal frame " + scv::toString(contFrame));
         contFrame++;
         iframe->setDraggable(true);
         iframe->setResizable(true);
         scv::Kernel::getInstance()->addWindow(iframe);

         iframe->getPanel()->registerContextMenu(new InterfaceDesign(iframe->getPanel()));

         //iframe->registerContextMenu(new RemoveComponent(iframe));

      } else if (address[2] == "Tree View") {

         scv::TreeView *tbTV;

         if (m_panel != NULL) tbTV = new scv::TreeView(getCurrPosition() - m_panel->getRelativePosition(), (getCurrPosition() - m_panel->getRelativePosition()) + 200, scv::TW_ONLY_FOLDERS );
         else                 tbTV = new scv::TreeView(getCurrPosition(), getCurrPosition() + 200, scv::TW_ONLY_FOLDERS );

         tbTV->setDraggable(true);
         tbTV->setResizable(true);

         if (m_panel == NULL)  scv::Kernel::getInstance()->addComponent(tbTV);
         else m_panel->addComponent(tbTV);

         tbTV->registerContextMenu(new RemoveComponent(tbTV));

      }  else if (address[2] == "text") {
         scv::Kernel::getInstance()->OpenFile();

      } 

   } else if (address.size() == 4) {

      scv::Separator * separator;

      if (address[3] == "Horizontal") {

         if (m_panel != NULL) separator = new scv::Separator(getCurrPosition() - m_panel->getAbsolutePosition(), scv::Separator::horizontal, 200);
         else                 separator = new scv::Separator(getCurrPosition(), scv::Separator::horizontal, 200);

         separator->setDraggable(true);
         separator->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(separator);
         else m_panel->addComponent(separator);

      } else if (address[3] == "Vertical") {

         if (m_panel != NULL) separator = new scv::Separator(getCurrPosition() - m_panel->getAbsolutePosition(),scv::Separator::vertical, 200);
         else                 separator = new scv::Separator(getCurrPosition(), scv::Separator::vertical, 200);

         separator->setDraggable(true);
         separator->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(separator);
         else m_panel->addComponent(separator);

      }

      separator->registerContextMenu(new RemoveComponent(separator));
   }
}

