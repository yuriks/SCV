#include "SCV.h"
#include "CodeGenerator.h"


namespace scv {

CodeGenerator::CodeGenerator(void) {
   initCounters();

}


std::string CodeGenerator::includeDefaultClassStyle(void) {
   std::string str;
   /*str += "\n      void onMouseClick(const scv::MouseEvent &evt) {}";
   str += "\n      void onMouseHold(const scv::MouseEvent &evt) {}";
   str += "\n      void onMouseOver(const scv::MouseEvent &evt) {}";
   str += "\n      void onMouseUp(const scv::MouseEvent &evt) {}";
   str += "\n      void onKeyPressed(const scv::KeyEvent &evt) {}";
   str += "\n      void onKeyUp(const scv::KeyEvent &evt) {}";
   str += "\n      void onMouseWheel(const scv::MouseEvent &evt) {}";
   str += "\n      void onResizing(void) {}";
   str += "\n      void onDragging(void) {}";*/
   str += "\n\n   protected:";
   str += "\n   private:\n\n};\n";
   return str;
}


/************************************************************************/
/* BUTTON                                                               */
/************************************************************************/
std::string CodeGenerator::includeButton(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Button * comp = static_cast<Button*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Button" + toString(contButton++);

   str += "class " + classname + " : public scv::Button {\n   public:\n\n      " + classname + "() : scv::Button(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "),scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + "), \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}

/************************************************************************/
/* CANVAS                                                               */
/************************************************************************/
std::string CodeGenerator::includeCanvas(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Canvas * comp = static_cast<Canvas*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Canvas" + toString(contCanvas++);

   str += "class " + classname + " : public scv::Canvas {\n   public:\n\n      " + classname + "() : scv::Canvas(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "),scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + ")";
   str += ") {\n\n      }\n      ~" + classname + "() {}";

   str += "\n      void update(void) {}";
   str += "\n      void render(void) {}\n";
   
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}

/************************************************************************/
/* CHECKBOX                                                             */
/************************************************************************/
std::string CodeGenerator::includeCheckBox(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   CheckBox * comp = static_cast<CheckBox*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "CheckBox" + toString(contCheckBox++);

   std::string state;
   if (comp->getState()) state = "true";
   else                  state = "false";


   str += "class " + classname + " : public scv::CheckBox {\n   public:\n\n      " + classname + "() : scv::CheckBox(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), " + state + ", \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}

/************************************************************************/
/* COLORPICKER                                                          */
/************************************************************************/
std::string CodeGenerator::includeColorPicker(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   ColorPicker * comp = static_cast<ColorPicker*>(component);
   Point p1 = comp->getRelativePosition();

   std::string classname = "ColorPicker" + toString(contColorPicker++);

   str += "class " + classname + " : public scv::ColorPicker {\n   public:\n\n      " + classname + "() : scv::ColorPicker(scv::Point(" + toString(p1.x) + ", " + toString(p1.y);
   str += ")) {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* COMBO BOX                                                            */
/************************************************************************/
std::string CodeGenerator::includeComboBox(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   ComboBox * comp = static_cast<ComboBox*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "ComboBox" + toString(contComboBox++);

   str += "class " + classname + " : public scv::ComboBox {\n   public:\n\n      " + classname + "() : scv::ComboBox(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y);
   str += ")) {\n";
   str += "         addItem(\"ComboBox Example 1\");\n         addItem(\"ComboBox Example 2\");\n";
   str += "\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}

/************************************************************************/
/* LABEL                                                                */
/************************************************************************/
std::string CodeGenerator::includeLabel(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Label * comp = static_cast<Label*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Label" + toString(contLabel++);

   str += "class " + classname + " : public scv::Label {\n   public:\n\n      " + classname + "() : scv::Label(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* MENU BAR                                                             */
/************************************************************************/
std::string CodeGenerator::includeMenuBar(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   MenuBar * comp = static_cast<MenuBar*>(component);

   std::string classname = "MenuBar" + toString(contMenuBar++);

   str += "class " + classname + " : public scv::MenuBar {\n   public:\n\n      " + classname + "() : scv::MenuBar(" + toString(comp->getSize());
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}



/************************************************************************/
/* PANEL                                                                */
/************************************************************************/
std::string CodeGenerator::includePanel(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Panel * comp = static_cast<Panel*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Panel" + toString(contPanel++);

   str += "class " + classname + " : public scv::Panel {\n   public:\n\n      " + classname + "() : scv::Panel(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y);
   str += ")) {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();


   if (isAtPanel)  { 
      instance += "   panel_tmp = panel;\n";
      instance += "   panel = new " + classname + "();\n";
      instance += "   panel_tmp->addComponent(panel);\n\n"; 
   }
   else { 
      instance += "   panel = new " + classname + "();\n";
      instance += "   kernel->addComponent(panel);\n\n"; 
   }

   return str;

}

/************************************************************************/
/* PROGRESS BAR                                                         */
/************************************************************************/
std::string CodeGenerator::includeProgressBar(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   ProgressBar * comp = static_cast<ProgressBar*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "ProgressBar" + toString(contProgressBar++);

   str += "class " + classname + " : public scv::ProgressBar {\n   public:\n\n      " + classname + "() : scv::ProgressBar(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + "), ";
   str += toString(comp->getValue());
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* RADIO BUTTON                                                         */
/************************************************************************/
std::string CodeGenerator::includeRadioButton(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   RadioButton * comp = static_cast<RadioButton*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "RadioButton" + toString(contRadioButton++);

   std::string state;
   if (comp->getState()) state = "true";
   else                  state = "false";

   str += "class " + classname + " : public scv::RadioButton {\n   public:\n\n      " + classname + "() : scv::RadioButton(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), " + state + ", \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* SCROLL PANE                                                          */
/************************************************************************/
std::string CodeGenerator::includeScrollPane(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   ScrollPane * comp = static_cast<ScrollPane*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "ScrollPane" + toString(contScrollPane++);

   str += "class " + classname + " : public scv::ScrollPane {\n   public:\n\n      " + classname + "() : scv::ScrollPane(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + ")";
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   instance += "   scrollpane = new " + classname + "();\n";

   if (isAtPanel)  instance += "   panel->addComponent(scrollpane);\n";
   else            instance += "   kernel->addComponent(scrollpane);\n";
   

   Panel * comppp = comp->getPanel();
   p1 = comppp->getRelativePosition();
   p2 = comppp->getRelativePosition() + comppp->getSize();

   classname = "Panel" + toString(contPanel++);

   str += "class " + classname + " : public scv::Panel {\n   public:\n\n      " + classname + "() : scv::Panel(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y);
   str += ")) {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   instance += "   panel = new " + classname + "();\n";
   instance += "   scrollpane->registerPanel(panel);\n";

   

   return str;
}
/************************************************************************/
/* SLIDER                                                               */
/************************************************************************/
std::string CodeGenerator::includeSlider(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Slider * comp = static_cast<Slider*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Slider" + toString(contSlider++);

   str += "class " + classname + " : public scv::Slider {\n   public:\n\n      " + classname + "() : scv::Slider(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), " + toString(comp->getWidth()) + ", " + toString(comp->getMinValue()) + ", " + toString(comp->getMaxValue()) + ", " + toString(comp->getValue()) + ", " + toString(comp->getStep());
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* SPINNER                                                              */
/************************************************************************/
std::string CodeGenerator::includeSpinner(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Spinner * comp = static_cast<Spinner*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Spinner" + toString(contSpinner++);

   str += "class " + classname + " : public scv::Spinner {\n   public:\n\n      " + classname + "() : scv::Spinner(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), " + toString(comp->getWidth()) + ", " + toString(comp->getMinValue()) + ", " + toString(comp->getMaxValue()) + ", " + toString(comp->getValue()) + ", " + toString(comp->getStep());
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* SEPARATOR                                                            */
/************************************************************************/
std::string CodeGenerator::includeSeparator(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Separator * comp = static_cast<Separator*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Separator" + toString(contSeparator++);

   if (comp->getAlign() == Separator::horizontal) {
      str += "class " + classname + " : public scv::Separator {\n   public:\n\n      " + classname + "() : scv::Separator(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Separator::horizontal, " + toString(comp->getWidth());
   } else {
      str += "class " + classname + " : public scv::Separator {\n   public:\n\n      " + classname + "() : scv::Separator(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Separator::vertical, " + toString(comp->getHeight());
   }

   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* TABBED PANE                                                          */
/************************************************************************/
std::string CodeGenerator::includeTabbedPane(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   TabbedPane * comp = static_cast<TabbedPane*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "TabbedPane" + toString(contTabbedPane++);

   str += "class " + classname + " : public scv::TabbedPane {\n   public:\n\n      " + classname + "() : scv::TabbedPane(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "),scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + ")";
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   instance += "tabbedpane = new " + classname + "();";

   if (isAtPanel)  instance += "   panel->addComponent(tabbedpane);\n";
   else            instance += "   kernel->addComponent(tabbedpane);\n";

   instance += "panel = new scv::Panel();\n";
   instance += "tabbedpane->addPanel(panel,\"Example Painel 1\");\n\n";

   instance += "panel = new scv::Panel();\n";
   instance += "tabbedpane->addPanel(panel,\"Example Painel 2\");\n\n";

   return str;
}



/************************************************************************/
/* TEXTFIELD                                                            */
/************************************************************************/
std::string CodeGenerator::includeTextField(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   TextField * comp = static_cast<TextField*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "TextField" + toString(contTextField++);

   str += "class " + classname + " : public scv::TextField {\n   public:\n\n      " + classname + "() : scv::TextField(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), " + toString(comp->getWidth()) + ", \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* TEXTBOX                                                              */
/************************************************************************/
std::string CodeGenerator::includeTextBox(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   TextBox * comp = static_cast<TextBox*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "TextBox" + toString(contTextBox++);

   str += "class " + classname + " : public scv::TextBox {\n   public:\n\n      " + classname + "() : scv::TextBox(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + "), \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* TOOGLE BUTTON                                                        */
/************************************************************************/
std::string CodeGenerator::includeToggleButton(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   ToggleButton * comp = static_cast<ToggleButton*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "ToggleButton" + toString(contToggleButton++);

   std::string state;
   if (comp->getState()) state = "true";
   else                  state = "false";

   str += "class " + classname + " : public scv::ToggleButton {\n   public:\n\n      " + classname + "() : scv::ToggleButton(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + "), " + state + ", \"";
   str += comp->getString();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* INTERNAL FRAME                                                       */
/************************************************************************/
std::string CodeGenerator::includeInternalFrame(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   InternalFrame * comp = static_cast<InternalFrame*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "InternalFrame" + toString(contInternalFrame++);

   str += "class " + classname + " : public scv::InternalFrame {\n   public:\n\n      " + classname + "() : scv::InternalFrame(" + toString(comp->getWidth()) + ", " + toString(comp->getHeight()) + "), \"";
   str += comp->getTitle();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* TABLE                                                                */
/************************************************************************/
std::string CodeGenerator::includeTable(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Table * comp = static_cast<Table*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Table" + toString(contTable++);

   str += "class " + classname + " : public scv::Table {\n   public:\n\n      " + classname + "() : scv::Table(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), " + toString(comp->getNumberOfRows()) + ", " + toString(comp->getNumberOfColumns()) + ", " + toString(comp->getNumberOfLinesPerCell()) + ", " + toString(comp->getCellWidth());
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}


/************************************************************************/
/* IMAGE                                                                */
/************************************************************************/
std::string CodeGenerator::includeImage(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   Image * comp = static_cast<Image*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "Image" + toString(contImage++);

   str += "class " + classname + " : public scv::Image {\n   public:\n\n      " + classname + "() : scv::Image(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "), scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + "), \"" + comp->getPath();
   str += "\") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();


   if (isAtPanel)  { 
      instance += "   panel_tmp = panel;\n";
      instance += "   panel = new " + classname + "();\n";
      instance += "   panel_tmp->addComponent(panel);\n\n"; 
   }
   else { 
      instance += "   panel = new " + classname + "();\n";
      instance += "   kernel->addComponent(panel);\n\n"; 
   }

   return str;
}


std::string CodeGenerator::includeTreeView(ComponentInterface * component, bool isAtPanel) {
   std::string str = "";

   TreeView * comp = static_cast<TreeView*>(component);
   Point p1 = comp->getRelativePosition();
   Point p2 = comp->getRelativePosition() + comp->getSize();

   std::string classname = "TreeView" + toString(contTreeView++);

   str += "class " + classname + " : public scv::TreeView {\n   public:\n\n      " + classname + "() : scv::TreeView(scv::Point(" + toString(p1.x) + ", " + toString(p1.y) + "),scv::Point(" + toString(p2.x) + ", " + toString(p2.y) + "), ";
   str += "scv::TW_ONLY_FOLDERS";
   str += ") {\n\n      }\n      ~" + classname + "() {}";
   str += includeDefaultClassStyle();

   if (isAtPanel)  instance += "   panel->addComponent(new " + classname + "());\n\n";
   else            instance += "   kernel->addComponent(new " + classname + "());\n\n";

   return str;
}



std::string CodeGenerator::generateMainProgram(void) {
   scv::Point size = scv::Point(scv::Kernel::getInstance()->getWidth(),scv::Kernel::getInstance()->getHeight());
   std::string str = "";
   str += " int main(int argc, char* argv[]) {\n\n   using namespace scv;\n\n   // Kernel Instance\n   static Kernel *kernel = Kernel::getInstance();\n\n   // Load ColorScheme\n   static ColorScheme *scheme = ColorScheme::getInstance();\n   scheme->loadScheme(ColorScheme::clean);\n\n   // Set Windows Size\n   kernel->setWindowSize(" + toString(size.x) + ", " + toString(size.y) + ");\n\n   // Set Frame Rate\n   kernel->setFramesPerSecond(40.f);\n\n   /************************************************/\n   scv::Panel * panel, * panel_tmp;\n   scv::ScrollPane * scrollpane;\n   scv::TabbedPane * tabbedpane;\n\n" + instance + "   /************************************************/\n\n   kernel->run();\n\n   return 0;\n\n}";
   initCounters();
   return str;
}

void CodeGenerator::initCounters(void) {
   contButton = contCanvas = contCheckBox = contColorPicker = contMenuBar = contPanel = contTextField = contTextBox =
   contProgressBar = contRadioButton = contScrollPane = contSlider = contSpinner = contSeparator = contTabbedPane = 
   contToggleButton = contInternalFrame = contTable = contComboBox = contImage = contTreeView = contLabel = 0;

   instance = "";

}


} // namespace scv