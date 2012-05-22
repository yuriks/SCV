#include <SCV/SCV.h>
#include "CodeGenerator.h"
#include "Application.h"

#include <cstring>

CodeGenerator::CodeGenerator(void) {
   _scvFrame = NULL;
}

CodeGenerator::~CodeGenerator(void) {
}

std::string CodeGenerator::addChildren(scv::Component *child, std::string dad, bool customClass) {
   std::string code;
   int x, y;
   scv::Component::Type type = child->getType();

   if(type == scv::Component::PANEL) { // Panel
      if(child == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = count[child->getType()];
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
        code += "   scv::Panel *panel" + scv::toString(count_n) + " = new scv::Panel(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
        code += "   Panel" + scv::toString(count_n) + " *panel" + scv::toString(count_n) + " = new Panel" + scv::toString(count_n) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   panel" + scv::toString(count_n) + "->setParent(" + dad + ");\n";
      code += "\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "panel" + scv::toString(count_n), customClass);
         }
      }
   }else if(type == scv::Component::COLORPICKER) { // ColorPicker
      if(customClass == false)
        code += "   scv::ColorPicker *colorPicker" + scv::toString(count[child->getType()]) + " = new scv::ColorPicker(scv::Point(" + scv::toString(child->getRelativePosition()) + "));\n";
      else
        code += "   ColorPicker" + scv::toString(count[child->getType()]) + " *colorPicker" + scv::toString(count[child->getType()]) + " = new ColorPicker" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "));\n";
      code += "   colorPicker" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::PROGRESSBAR) { // ProgressBar
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
        code += "   scv::ProgressBar *progressBar" + scv::toString(count[child->getType()]) + " = new scv::ProgressBar(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      else
        code += "   ProgressBar" + scv::toString(count[child->getType()]) + " *progressBar" + scv::toString(count[child->getType()]) + " = new ProgressBar" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      code += "   progressBar" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::SCROLL) { // Scroll

   } else if(type == scv::Component::SLIDER) { // Slider
	   if(customClass == false)
         code += "   scv::Slider *slider" + scv::toString(count[child->getType()]) + " = new scv::Slider(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      else
         code += "   Slider" + scv::toString(count[child->getType()]) + " *slider" + scv::toString(count[child->getType()]) + " = new Slider" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   slider" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::SPINNER) { // Spinner
      if(customClass == false)
         code += "   scv::Spinner *spinner" + scv::toString(count[child->getType()]) + " = new scv::Spinner(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      else
         code += "   Spinner" + scv::toString(count[child->getType()]) + " *spinner" + scv::toString(count[child->getType()]) + " = new Spinner" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   spinner" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::BUTTON) { // Button
      scv::Button *button = (scv::Button*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
         code += "   scv::Button *button" + scv::toString(count[child->getType()]) + " = new scv::Button(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      else
         code += "   Button" + scv::toString(count[child->getType()]) + " *button" + scv::toString(count[child->getType()]) + " = new Button" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      code += "   button" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::CHECKBOX) { // CheckBox
      scv::CheckBox *checkBox = (scv::CheckBox*)(child);
      if(customClass == false)
         code += "   scv::CheckBox *checkBox" + scv::toString(count[child->getType()]) + " = new scv::CheckBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      else
         code += "   CheckBox" + scv::toString(count[child->getType()]) + " *checkBox" + scv::toString(count[child->getType()]) + " = new CheckBox" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      code += "   checkBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::RADIOBUTTON) { // RadioButton
      scv::RadioButton *radioButton = (scv::RadioButton*)(child);
      if(customClass == false)
         code += "   scv::RadioButton *radioButton" + scv::toString(count[child->getType()]) + " = new scv::RadioButton(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      else
         code += "   RadioButton" + scv::toString(count[child->getType()]) + " *radioButton" + scv::toString(count[child->getType()]) + " = new RadioButton" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      code += "   radioButton" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TOGGLEBUTTON) {// ToggleButton
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      scv::ToggleButton *toggleButton = (scv::ToggleButton*)(child);
      if(customClass == false)
         code += "   scv::ToggleButton *toggleButton" + scv::toString(count[child->getType()]) + " = new scv::ToggleButton(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      else
         code += "   ToggleButton" + scv::toString(count[child->getType()]) + " *toggleButton" + scv::toString(count[child->getType()]) + " = new ToggleButton" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      code += "   toggleButton" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TEXTFIELD) {// TextField
      scv::TextField *textField = (scv::TextField*)(child);
      if(customClass == false)
         code += "   scv::TextField *textField" + scv::toString(count[child->getType()]) + " = new scv::TextField(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", \"" + textField->getString() + "\");\n";
      else
         code += "   TextField" + scv::toString(count[child->getType()]) + " *textField" + scv::toString(count[child->getType()]) + " = new TextField" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", \"" + textField->getString() + "\");\n";
      code += "   textField" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TEXTBOX) {// TextBox
      scv::TextBox *textBox = (scv::TextBox*)(child);
      x = child->getRelativePosition().x + child->getHeight();
      y = child->getRelativePosition().y + child->getWidth();
      if(customClass == false)
         code += "   scv::TextBox *textBox" + scv::toString(count[child->getType()]) + " = new scv::TextBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(textBox->getInternalSize()) + "), \"" + textBox->getString() + "\");\n";
      else
         code += "   TextBox" + scv::toString(count[child->getType()]) + " *textBox" + scv::toString(count[child->getType()]) + " = new TextBox" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(textBox->getInternalSize()) + "), \"" + textBox->getString() + "\");\n";
      code += "   textBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::SEPARATOR) {// Separator
      scv::Separator *separator = (scv::Separator*)(child);
      int lenght = separator->getWidth();
      if(lenght < separator->getHeight())
         lenght = separator->getHeight();
      if(customClass == false)
         code += "   scv::Separator *separator" + scv::toString(count[child->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(child->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(lenght) + ");\n";
      else
         code += "   Separator" + scv::toString(count[child->getType()]) + " *separator" + scv::toString(count[child->getType()]) + " = new Separator" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(lenght) + ");\n";
      code += "   separator" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::WINDOW) {// Window
      scv::InternalFrame *internalFrame = (scv::InternalFrame*)(child);
      int count_n = count[child->getType()];
      if(customClass == false)
         code += "   scv::InternalFrame *internalFrame" + scv::toString(count[child->getType()]) + " = new scv::InternalFrame(" + scv::toString(internalFrame->getInternalSize()) + ", \"" + scv::toString(internalFrame->getTitle()) + "\");\n";
      else
         code += "   InternalFrame" + scv::toString(count[child->getType()]) + " *internalFrame" + scv::toString(count[child->getType()]) + " = new InternalFrame" + scv::toString(count[child->getType()]) + "(" + scv::toString(internalFrame->getInternalSize()) + ", \"" + scv::toString(internalFrame->getTitle()) + "\");\n";
      code += "   addComponent(internalFrame" + scv::toString(count[child->getType()]) + ");\n";
      code += "\n";
      count[child->getType()] += 1;
       if(!child->_children.empty()) {
         auto c = child->_children.begin();
         scv::Component *a = *c;
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "internalFrame"+scv::toString(count_n)+"->getPanel()", customClass);
            }
         }
      }
   } else if(type == scv::Component::MENUBAR) {// MenuBar
      if(customClass == false)
         code += "   scv::MenuBar *menuBar" + scv::toString(count[child->getType()]) + " = new scv::MenuBar(" + scv::toString(child->getWidth()) + ");\n";
      else
         code += "   MenuBar" + scv::toString(count[child->getType()]) + " *menuBar" + scv::toString(count[child->getType()]) + " = new MenuBar" + scv::toString(count[child->getType()]) + "(" + scv::toString(child->getWidth()) + ");\n";
      code += "   menuBar" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      scv::MenuBar *menu = (scv::MenuBar*)(child);
      for(int i=0; i<menu->getNumberOfMenus(); i++)
         code += "   menuBar" + scv::toString(count[child->getType()]) + "->addMenu(new scv::ContextMenu(\"menu" + scv::toString(i) + "\"));\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TABBEDPANE) {// TabbedPane
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      int count_n = count[child->getType()];
      if(customClass == false)
         code += "   scv::TabbedPane *tabbedPane" + scv::toString(count[child->getType()]) + " = new scv::TabbedPane(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   TabbedPane" + scv::toString(count[child->getType()]) + " *tabbedPane" + scv::toString(count[child->getType()]) + " = new TabbedPane" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   tabbedPane" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      code += "\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "tabbedPane" + scv::toString(count_n), customClass);
         }
      }
   } else if(type == scv::Component::SCROLLCOMPONENT) {// ScrollComponent
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      int count_n = count[child->getType()];
      if(customClass == false)
         code += "   scv::ScrollComponent *scrollComponent" + scv::toString(count[child->getType()]) + " = new scv::ScrollComponent(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   ScrollComponent" + scv::toString(count[child->getType()]) + " *scrollComponent" + scv::toString(count[child->getType()]) + " = new ScrollComponent" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   scrollComponent" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         auto c = child->_children.begin();
         scv::Component *a = *c;
         int panelNumber = count[a->getType()];
         if(customClass == false)
            code += "   scv::Panel *panel" + scv::toString(panelNumber) + " = new scv::Panel(scv::Point(" + scv::toString(a->getRelativePosition().x) + ", " + scv::toString(a->getRelativePosition().y) + "),  scv::Point(" + scv::toString(a->getWidth()) + ", " + scv::toString(a->getHeight()) + "));\n";
         else
            code += "   Panel" + scv::toString(panelNumber) + " *panel" + scv::toString(panelNumber) + " = new Panel" + scv::toString(panelNumber) + "(scv::Point(" + scv::toString(a->getRelativePosition().x) + ", " + scv::toString(a->getRelativePosition().y) + "),  scv::Point(" + scv::toString(a->getWidth()) + ", " + scv::toString(a->getHeight()) + "));\n";
         code += "   scrollComponent" + scv::toString(count_n) + "->setComponent(panel" + scv::toString(panelNumber) + ");\n";
         code += "\n";
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "panel" + scv::toString(panelNumber), customClass);
            }
         }
      }
   } else if(type == scv::Component::IMAGE) {// Image
      scv::Image *image = (scv::Image*)(child);
      int count_n = count[child->getType()];
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
         code += "   scv::Image *image" + scv::toString(count[child->getType()]) + " = new scv::Image(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      else
         code += "   Image" + scv::toString(count[child->getType()]) + " *image" + scv::toString(count[child->getType()]) + " = new Image" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      code += "   image" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      code += "\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "image" + scv::toString(count_n), customClass);
         }
      }
   } else if(type == scv::Component::TABLE) {//Table
      scv::Table *table = (scv::Table*)(child);
      if(customClass == false)
         code += "   scv::Table *table" + scv::toString(count[child->getType()]) + " = new scv::Table(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      else
         code += "   Table" + scv::toString(count[child->getType()]) + " *table" + scv::toString(count[child->getType()]) + " = new Table" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      code += "   table" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::COMBOBOX) {//ComboBox
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
         code += "   scv::ComboBox *comboBox" + scv::toString(count[child->getType()]) + " = new scv::ComboBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   ComboBox" + scv::toString(count[child->getType()]) + " *comboBox" + scv::toString(count[child->getType()]) + " = new ComboBox" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   comboBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::CANVAS) {//Canvas
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
         code += "   scv::Canvas *canvas" + scv::toString(count[child->getType()]) + " = new scv::Canvas(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   Canvas" + scv::toString(count[child->getType()]) + " *canvas" + scv::toString(count[child->getType()]) + " = new Canvas" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   canvas" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::GENERICTREE) {//GenericTree
      scv::GenericTree *genericTree = (scv::GenericTree*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
         code += "   scv::GenericTree *genericTree" + scv::toString(count[child->getType()]) + " = new scv::GenericTree(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), new scv::GenericNode(\"Root\") );\n";
      else
         code += "   GenericTree" + scv::toString(count[child->getType()]) + " *genericTree" + scv::toString(count[child->getType()]) + " = new GenericTree" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), new scv::GenericNode(\"Root\") );\n";
      code += "   genericTree" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::LABEL) {//Label
      scv::Label *label = (scv::Label*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      if(customClass == false)
         code += "   scv::Label *label" + scv::toString(count[child->getType()]) + " = new scv::Label(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      else
         code += "   Label" + scv::toString(count[child->getType()]) + " *label" + scv::toString(count[child->getType()]) + " = new Label" + scv::toString(count[child->getType()]) + "(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      code += "   label" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   }
   return code;
}

std::string CodeGenerator::createAllocationCode(scv::Component *comp, bool customClass) {
   std::string code;
   int x, y;
   int type = comp->getType();

   if(type == scv::Component::PANEL) { // Panel
      if(comp == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = count[comp->getType()];
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
        code += "   scv::Panel *panel" + scv::toString(count[comp->getType()]) + " = new scv::Panel(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
        code += "   Panel" + scv::toString(count[comp->getType()]) + " *panel" + scv::toString(count[comp->getType()]) + " = new Panel" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";        
      code += "   addComponent(panel" + scv::toString(count[comp->getType()]) + ");\n";
      code += "\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "panel" + scv::toString(count_n), customClass);
         }
      }
   } else if(type == scv::Component::COLORPICKER) { // ColorPicker
      if(customClass == false)
        code += "   scv::ColorPicker *colorPicker" + scv::toString(count[comp->getType()]) + " = new scv::ColorPicker(scv::Point(" + scv::toString(comp->getRelativePosition()) + "));\n";
      else
        code += "   ColorPicker" + scv::toString(count[comp->getType()]) + " *colorPicker" + scv::toString(count[comp->getType()]) + " = new ColorPicker" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "));\n";
      code += "   addComponent(colorPicker" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::PROGRESSBAR) { // ProgressBar
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
        code += "   scv::ProgressBar *progressBar" + scv::toString(count[comp->getType()]) + " = new scv::ProgressBar(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      else
        code += "   ProgressBar" + scv::toString(count[comp->getType()]) + " *progressBar" + scv::toString(count[comp->getType()]) + " = new ProgressBar" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      code += "   addComponent(progressBar" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::SCROLL) { // Scroll

   } else if(type == scv::Component::SLIDER) { // Slider
      if(customClass == false)
         code += "   scv::Slider *slider" + scv::toString(count[comp->getType()]) + " = new scv::Slider(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      else
         code += "   Slider" + scv::toString(count[comp->getType()]) + " *slider" + scv::toString(count[comp->getType()]) + " = new Slider" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   addComponent(slider" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::SPINNER) { // Spinner
      if(customClass == false)
         code += "   scv::Spinner *spinner" + scv::toString(count[comp->getType()]) + " = new scv::Spinner(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      else
         code += "   Spinner" + scv::toString(count[comp->getType()]) + " *spinner" + scv::toString(count[comp->getType()]) + " = new Spinner" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   addComponent(spinner" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::BUTTON) { // Button
      scv::Button *button = (scv::Button*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::Button *button" + scv::toString(count[comp->getType()]) + " = new scv::Button(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      else
         code += "   Button" + scv::toString(count[comp->getType()]) + " *button" + scv::toString(count[comp->getType()]) + " = new Button" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      code += "   addComponent(button" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::CHECKBOX) { // CheckBox
      scv::CheckBox *checkBox = (scv::CheckBox*)(comp);
      if(customClass == false)
         code += "   scv::CheckBox *checkBox" + scv::toString(count[comp->getType()]) + " = new scv::CheckBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      else
         code += "   CheckBox" + scv::toString(count[comp->getType()]) + " *checkBox" + scv::toString(count[comp->getType()]) + " = new CheckBox" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      code += "   addComponent(checkBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::RADIOBUTTON) { // RadioButton
      scv::RadioButton *radioButton = (scv::RadioButton*)(comp);
      if(customClass == false)
         code += "   scv::RadioButton *radioButton" + scv::toString(count[comp->getType()]) + " = new scv::RadioButton(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      else
         code += "   RadioButton" + scv::toString(count[comp->getType()]) + " *radioButton" + scv::toString(count[comp->getType()]) + " = new RadioButton" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      code += "   addComponent(radioButton" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TOGGLEBUTTON) {// ToggleButton
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      scv::ToggleButton *toggleButton = (scv::ToggleButton*)(comp);
      if(customClass == false)
         code += "   scv::ToggleButton *toggleButton" + scv::toString(count[comp->getType()]) + " = new scv::ToggleButton(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      else
         code += "   ToggleButton" + scv::toString(count[comp->getType()]) + " *toggleButton" + scv::toString(count[comp->getType()]) + " = new ToggleButton" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      code += "   addComponent(toggleButton" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TEXTFIELD) {// TextField
      scv::TextField *textField = (scv::TextField*)(comp);
      if(customClass == false)
         code += "   scv::TextField *textField" + scv::toString(count[comp->getType()]) + " = new scv::TextField(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", \"" + textField->getString() + "\");\n";
      else
         code += "   TextField" + scv::toString(count[comp->getType()]) + " *textField" + scv::toString(count[comp->getType()]) + " = new TextField" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", \"" + textField->getString() + "\");\n";
      code += "   addComponent(textField" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::TEXTBOX) {// TextBox
      scv::TextBox *textBox = (scv::TextBox*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::TextBox *textBox" + scv::toString(count[comp->getType()]) + " = new scv::TextBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(textBox->getInternalSize()) + "), \"" + textBox->getString() + "\");\n";
      else
         code += "   TextBox" + scv::toString(count[comp->getType()]) + " *textBox" + scv::toString(count[comp->getType()]) + " = new TextBox" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(textBox->getInternalSize()) + "), \"" + textBox->getString() + "\");\n";
      code += "   addComponent(textBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::SEPARATOR) {// Separator
      scv::Separator *separator = (scv::Separator*)(comp);
      int lenght = separator->getWidth();
      if(lenght < separator->getHeight())
         lenght = separator->getHeight();
      if(customClass == false)
         code += "   scv::Separator *separator" + scv::toString(count[comp->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(lenght) + ");\n";
      else
         code += "   Separator" + scv::toString(count[comp->getType()]) + " *separator" + scv::toString(count[comp->getType()]) + " = new Separator" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(lenght) + ");\n";
      code += "   addComponent(separator" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::WINDOW) {// Window
      scv::InternalFrame *internalFrame = (scv::InternalFrame*)(comp);
      int count_n = count[comp->getType()];
      if(customClass == false)
         code += "   scv::InternalFrame *internalFrame" + scv::toString(count[comp->getType()]) + " = new scv::InternalFrame(" + scv::toString(internalFrame->getInternalSize()) + ", \"" + scv::toString(internalFrame->getTitle()) + "\");\n";
      else
         code += "   InternalFrame" + scv::toString(count[comp->getType()]) + " *internalFrame" + scv::toString(count[comp->getType()]) + " = new InternalFrame" + scv::toString(count[comp->getType()]) + "(" + scv::toString(internalFrame->getInternalSize()) + ", \"" + scv::toString(internalFrame->getTitle()) + "\");\n";
      code += "   internalFrame" + scv::toString(count[comp->getType()]) + "->setRelativePosition(scv::Point(" + scv::toString(comp->getRelativePosition()) + "));\n";
      code += "   addComponent(internalFrame" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
       if(!comp->_children.empty()) {
         auto c = comp->_children.begin();
         scv::Component *a = *c;
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "internalFrame"+scv::toString(count_n)+"->getPanel()", customClass);
            }
         }
      }
      code += "\n";
   } else if(type == scv::Component::MENUBAR) {// MenuBar
      if(customClass == false)
         code += "   scv::MenuBar *menuBar" + scv::toString(count[comp->getType()]) + " = new scv::MenuBar(" + scv::toString(comp->getWidth()) + ");\n";
      else
         code += "   MenuBar" + scv::toString(count[comp->getType()]) + " *menuBar" + scv::toString(count[comp->getType()]) + " = new MenuBar" + scv::toString(count[comp->getType()]) + "(" + scv::toString(comp->getWidth()) + ");\n";
      code += "   addComponent(menuBar" + scv::toString(count[comp->getType()]) + ");\n";
      scv::MenuBar *menu = (scv::MenuBar*)(comp);
      for(int i=0; i<menu->getNumberOfMenus(); i++)
         code += "   menuBar" + scv::toString(count[comp->getType()]) + "->addMenu(new scv::ContextMenu(\"menu" + scv::toString(i) + "\"));\n";
      code += "\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TABBEDPANE) {// TabbedPane
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      int count_n = count[comp->getType()];
      if(customClass == false)
         code += "   scv::TabbedPane *tabbedPane" + scv::toString(count[comp->getType()]) + " = new scv::TabbedPane(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   TabbedPane" + scv::toString(count[comp->getType()]) + " *tabbedPane" + scv::toString(count[comp->getType()]) + " = new TabbedPane" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(tabbedPane" + scv::toString(count[comp->getType()]) + ");\n";
      code += "\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "tabbedPane" + scv::toString(count_n), customClass);
         }
      }
   } else if(type == scv::Component::SCROLLCOMPONENT) {// ScrollComponent
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      int count_n = count[comp->getType()];
      if(customClass == false)         code += "   scv::ScrollComponent *scrollComponent" + scv::toString(count[comp->getType()]) + " = new scv::ScrollComponent(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   ScrollComponent" + scv::toString(count[comp->getType()]) + " *scrollComponent" + scv::toString(count[comp->getType()]) + " = new ScrollComponent" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(scrollComponent" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         auto c = comp->_children.begin();
         scv::Component *a = *c;
         int panelNumber = count[a->getType()];
         if(customClass == false)
            code += "   scv::Panel *panel" + scv::toString(panelNumber) + " = new scv::Panel(scv::Point(" + scv::toString(a->getRelativePosition().x) + ", " + scv::toString(a->getRelativePosition().y) + "),  scv::Point(" + scv::toString(a->getWidth()) + ", " + scv::toString(a->getHeight()) + "));\n";
         else
            code += "   Panel" + scv::toString(panelNumber) + " *panel" + scv::toString(panelNumber) + " = new Panel" + scv::toString(panelNumber) + "(scv::Point(" + scv::toString(a->getRelativePosition().x) + ", " + scv::toString(a->getRelativePosition().y) + "),  scv::Point(" + scv::toString(a->getWidth()) + ", " + scv::toString(a->getHeight()) + "));\n";
         code += "   scrollComponent" + scv::toString(count_n) + "->setComponent(panel" + scv::toString(panelNumber) + ");\n";
         code += "\n";
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "panel" + scv::toString(panelNumber), customClass);
            }
         }
      }
   } else if(type == scv::Component::IMAGE) {// Image
      scv::Image *image = (scv::Image*)(comp);
      int count_n = count[comp->getType()];
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::Image *image" + scv::toString(count[comp->getType()]) + " = new scv::Image(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      else
         code += "   Image" + scv::toString(count[comp->getType()]) + " *image" + scv::toString(count[comp->getType()]) + " = new Image" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      code += "   addComponent(image" + scv::toString(count[comp->getType()]) + ");\n";
      code += "\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "image" + scv::toString(count_n), customClass);
         }
      }
   } else if(type == scv::Component::TABLE) {//Table
      scv::Table *table = (scv::Table*)(comp);
      if(customClass == false)
         code += "   scv::Table *table" + scv::toString(count[comp->getType()]) + " = new scv::Table(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      else
         code += "   Table" + scv::toString(count[comp->getType()]) + " *table" + scv::toString(count[comp->getType()]) + " = new Table" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      code += "   addComponent(table" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::COMBOBOX) {//ComboBox
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::ComboBox *comboBox" + scv::toString(count[comp->getType()]) + " = new scv::ComboBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   ComboBox" + scv::toString(count[comp->getType()]) + " *comboBox" + scv::toString(count[comp->getType()]) + " = new ComboBox" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(comboBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::CANVAS) {//Canvas
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::Canvas *canvas" + scv::toString(count[comp->getType()]) + " = new scv::Canvas(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      else
         code += "   Canvas" + scv::toString(count[comp->getType()]) + " *canvas" + scv::toString(count[comp->getType()]) + " = new Canvas" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(canvas" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::GENERICTREE) {//GenericTree
      scv::GenericTree *genericTree = (scv::GenericTree*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::GenericTree *genericTree" + scv::toString(count[comp->getType()]) + " = new scv::GenericTree(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), new scv::GenericNode(\"Root\") );\n";
      else
         code += "   GenericTree" + scv::toString(count[comp->getType()]) + " *genericTree" + scv::toString(count[comp->getType()]) + " = new GenericTree" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), new scv::GenericNode(\"Root\") );\n";
      code += "   addComponent(genericTree" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == scv::Component::LABEL) {//Label
      scv::Label *label = (scv::Label*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      if(customClass == false)
         code += "   scv::Label *label" + scv::toString(count[comp->getType()]) + " = new scv::Label(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      else
         code += "   Label" + scv::toString(count[comp->getType()]) + " *label" + scv::toString(count[comp->getType()]) + " = new Label" + scv::toString(count[comp->getType()]) + "(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      code += "   addComponent(label" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   }
   return code;
}

std::string CodeGenerator::createCustomClassCodeH(scv::Component *comp) {
    std::string code, childCode;
    int type = comp->getType();

    if(type == scv::Component::PANEL) { // Panel
      if(comp == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = count[comp->getType()];
      code += "class Panel" + scv::toString(count[comp->getType()]) + " : public scv::Panel {\n";
      code += "public:\n";
      code += "   Panel" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2);\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeH(a);
         }
      }
   } else if(type == scv::Component::COLORPICKER) { // ColorPicker
      code += "class ColorPicker" + scv::toString(count[comp->getType()]) + " : public scv::ColorPicker {\n";
      code += "public:\n";
      code += "   ColorPicker" + scv::toString(count[comp->getType()]) + "(scv::Point p);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::PROGRESSBAR) { // ProgressBar
      code += "class ProgressBar" + scv::toString(count[comp->getType()]) + " : public scv::ProgressBar {\n";
      code += "public:\n";
      code += "   ProgressBar" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, double startValue);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::SLIDER) { //Slider
      code += "class Slider" + scv::toString(count[comp->getType()]) + " : public scv::Slider {\n";
      code += "public:\n";
      code += "   Slider" + scv::toString(count[comp->getType()]) + "(scv::Point p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);\n"; 
      count[comp->getType()] += 1;
   } else if(type == scv::Component::SPINNER) { //Spinner
      code += "class Spinner" + scv::toString(count[comp->getType()]) + " : public scv::Spinner {\n";
      code += "public:\n";
      code += "   Spinner" + scv::toString(count[comp->getType()]) + "(scv::Point p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::BUTTON) { //Button
      code += "class Button" + scv::toString(count[comp->getType()]) + " : public scv::Button {\n";
      code += "public:\n";
      code += "   Button" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, std::string str);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::CHECKBOX){ //Checkbox
      code += "class CheckBox" + scv::toString(count[comp->getType()]) + " : public scv::CheckBox {\n";
      code += "public:\n";
      code += "   CheckBox" + scv::toString(count[comp->getType()]) + "(scv::Point p, bool state, const std::string str);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::RADIOBUTTON) { //RadioButton
      code += "class RadioButton" + scv::toString(count[comp->getType()]) + " : public scv::RadioButton {\n";
      code += "public:\n";
      code += "   RadioButton" + scv::toString(count[comp->getType()]) + "(scv::Point p, bool state, const std::string str);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TOGGLEBUTTON) { //tooglebutton
      code += "class ToggleButton" + scv::toString(count[comp->getType()]) + " : public scv::ToggleButton {\n";
      code += "public:\n";
      code += "   ToggleButton" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, bool state, std::string str);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TEXTFIELD) { //textfield
      code += "class TextField" + scv::toString(count[comp->getType()]) + " : public scv::TextField {\n"; 
      code += "public:\n";
      code += "   TextField" + scv::toString(count[comp->getType()]) + "(scv::Point p, unsigned int width, std::string str);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TEXTBOX) { //textbox
      code += "class TextBox" + scv::toString(count[comp->getType()]) + " : public scv::TextBox {\n";
      code += "public:\n";
      code += "   TextBox" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, std::string str);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::SEPARATOR) { //separator
      code += "class Separator" + scv::toString(count[comp->getType()]) + " : public scv::Separator {\n";
      code += "public:\n";
      code += "   Separator" + scv::toString(count[comp->getType()]) + "(scv::Point p, Separator::Orientation align, unsigned int size);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::WINDOW) { //window
      code += "class InternalFrame" + scv::toString(count[comp->getType()]) + " : public scv::InternalFrame {\n";
      code += "public:\n";
      code += "   InternalFrame" + scv::toString(count[comp->getType()]) + "(int width, int height, std::string title);\n";
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeH(a);
         }
      }
      count[comp->getType()] += 1;
   } else if(type == scv::Component::MENUBAR) {
      code += "class MenuBar" + scv::toString(count[comp->getType()]) + " : public scv::MenuBar {\n";
      code += "public:\n";
      code += "   MenuBar" + scv::toString(count[comp->getType()]) + "(int width);";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TABBEDPANE) {
      code += "class TabbedPane" + scv::toString(count[comp->getType()]) + " : public scv::TabbedPane {\n";
      code += "public:\n";
      code += "   TabbedPane" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2);\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeH(a);
         }
      }
   } else if(type == scv::Component::SCROLLCOMPONENT) {
      code += "class ScrollComponent" + scv::toString(count[comp->getType()]) + " : public scv::ScrollComponent {\n";
      code += "public:\n";
      code += "   ScrollComponent" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2);\n";
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeH(a);
         }
      }
      count[comp->getType()] += 1;
   } else if(type == scv::Component::IMAGE) {
      code += "class Image" + scv::toString(count[comp->getType()]) + " : public scv::Image {\n";
      code += "public:\n";
      code += "   Image" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, std::string path);\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeH(a);
         }
      }
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TABLE) {
      code += "class Table" + scv::toString(count[comp->getType()]) + " : public scv::Table {\n";
      code += "public:\n";
      code += "   Table" + scv::toString(count[comp->getType()]) + "(scv::Point p, int rows, int columns, int LinesPerCell, int CellWidth);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::COMBOBOX) {
      code += "class ComboBox" + scv::toString(count[comp->getType()]) + " : public scv::ComboBox {\n";
      code += "public:\n";
      code += "   ComboBox" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::CANVAS) {
      code += "class Canvas" + scv::toString(count[comp->getType()]) + " : public scv::Canvas {\n";
      code += "public:\n";
      code += "   Canvas" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::GENERICTREE) {
      code += "class GenericTree" + scv::toString(count[comp->getType()]) + " : public scv::GenericTree {\n";
      code += "public:\n";
      code += "   GenericTree" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, scv::GenericNode *root);\n";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::LABEL) {
      code += "class Label" + scv::toString(count[comp->getType()]) + " : public scv::Label {\n";
      code += "public:\n";
      code += "   Label" + scv::toString(count[comp->getType()]) + "(scv::Point p1, scv::Point p2, std::string str);\n";
      count[comp->getType()] += 1;
   }

   code += "\n";
   code += CallbacksCode(comp->getType());
   code += "\n};\n\n";
   code += childCode;
   return code;

}

std::string CodeGenerator::CallbacksCode(int type){
   std::string code = 
   "   virtual void onMouseClick(const scv::MouseEvent &evt);\n"
   "   virtual void onMouseHold (const scv::MouseEvent &evt);\n"
   "   virtual void onMouseOver (const scv::MouseEvent &evt);\n"
   "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n"
   "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n"
   "\n"
   "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n"
   "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n"
   "\n"
   "   virtual void onSizeChange(void);\n"
   "   virtual void onPositionChange(void);\n";

   if(type == scv::Component::PROGRESSBAR || type == scv::Component::SLIDER || type == scv::Component::SPINNER || type == scv::Component::CHECKBOX || type == scv::Component::RADIOBUTTON || type == scv::Component::TOGGLEBUTTON)
      code += "\n   virtual void onValueChange(void);\n";
   if(type == scv::Component::COMBOBOX)
      code += "\n   virtual void onSelectionChanged(void);\n";
   if(type == scv::Component::GENERICTREE)
      code += "\n   virtual void onItemSelected(void);\n";
   if(type == scv::Component::COLORPICKER)
      code += "\n   virtual void onColorChange(void);\n";
   if(type == scv::Component::WINDOW) {
      code += "\n   virtual void onClose(void);\n";
      code += "\n   virtual void onOpen(void);\n";
   }
   if(type == scv::Component::TABBEDPANE)
      code += "\n   virtual void onTabChange(void);\n";
   if(type == scv::Component::TEXTBOX || type == scv::Component::TEXTFIELD)
      code += "\n   virtual void onStringChange(void);\n";
   return code;
}

std::string CodeGenerator::createCustomClassCodeCpp(scv::Component *comp) {
   std::string code, childCode, ComponentName;
    int type = comp->getType();

    if(type == scv::Component::PANEL) { // Panel
      if(comp == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = count[comp->getType()];
      ComponentName = "Panel" + scv::toString(count_n);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2) : scv::Panel(p1, p2) {\n}";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeCpp(a);
         }
      }
   } else if(type == scv::Component::COLORPICKER) { // ColorPicker
      ComponentName = "ColorPicker" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p) : scv::ColorPicker(p) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::PROGRESSBAR) { // ProgressBar
      ComponentName = "ProgressBar" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, double startValue) : scv::ProgressBar(p1, p2, startValue) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::SLIDER) { //Slider
      ComponentName = "Slider" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue) : scv::Slider(p, width, minValue, maxValue, startValue, stepValue) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::SPINNER) { //Spinner
      ComponentName = "Spinner" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, unsigned int width, double minValue, double maxValue, double startValue, double stepValue) : scv::Spinner(p, width, minValue, maxValue, startValue, stepValue) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::BUTTON) { //Button
      ComponentName = "Button" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, std::string str) : scv::Button(p1, p2, str) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::CHECKBOX){ //Checkbox
      ComponentName = "CheckBox" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, bool state, const std::string str) : scv::CheckBox(p, state, str) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::RADIOBUTTON) { //RadioButton
      ComponentName = "RadioButton" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, bool state, const std::string str) : scv::RadioButton(p, state, str) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TOGGLEBUTTON) { //tooglebutton
      ComponentName = "ToggleButton" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, bool state, const std::string str) : scv::ToggleButton(p1, p2, state, str) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TEXTFIELD) { //textfield
      ComponentName = "TextField" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, unsigned int width, std::string str) : scv::TextField(p, width, str) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TEXTBOX) { //textbox
      ComponentName = "TextBox" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, std::string str) : scv::TextBox(p1, p2, str) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::SEPARATOR) { //separator
      ComponentName = "Separator" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, Separator::Orientation align, unsigned int size) : scv::Separator(p, align, size) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::WINDOW) { //window
      ComponentName = "InternalFrame" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(int width, int height, std::string title) : scv::InternalFrame(width, height, title) {\n}";
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeCpp(a);
         }
      }
      count[comp->getType()] += 1;
   } else if(type == scv::Component::MENUBAR) {
      ComponentName = "MenuBar" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(int width) : scv::MenuBar(width) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::TABBEDPANE) {
      ComponentName = "TabbedPane" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2) : scv::TabbedPane(p1, p2) {\n}";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeCpp(a);
         }
      }
   } else if(type == scv::Component::SCROLLCOMPONENT) {
      ComponentName = "ScrollComponent" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2) : scv::ScrollComponent(p1, p2) {\n}";
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeCpp(a);
         }
      }
      count[comp->getType()] += 1;
   } else if(type == scv::Component::IMAGE) {
      ComponentName = "Image" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, std::string path) : scv::Image(p1, p2, path) {\n}";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            childCode += createCustomClassCodeCpp(a);
         }
      }
   } else if(type == scv::Component::TABLE) {
      ComponentName = "Table" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p, int rows, int columns, int LinesPerCell, int CellWidth) : scv::Table(p, rows, columns, LinesPerCell, CellWidth) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::COMBOBOX) {
      ComponentName = "ComboBox" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2) : scv::ComboBox(p1, p2) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::CANVAS) {
      ComponentName = "Canvas" + scv::toString(count[comp->getType()]);
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2) : scv::Canvas(p1, p2) {\n}";
      code += "\n//" + ComponentName;
      count[comp->getType()] += 1;
   } else if(type == scv::Component::GENERICTREE) {
      ComponentName = "GenericTree" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, scv::GenericNode *root) : scv::GenericTree(p1, p2, root) {\n}";
      count[comp->getType()] += 1;
   } else if(type == scv::Component::LABEL) {
      ComponentName = "Label" + scv::toString(count[comp->getType()]);
      code += "\n//" + ComponentName;
      code += "\n" + ComponentName + "::" + ComponentName + "(scv::Point p1, scv::Point p2, std::string str) : scv::Label(p1, p2, str) {\n}";
      count[comp->getType()] += 1;
   }

   code += "\nvoid " + ComponentName + "::onMouseClick(const scv::MouseEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onMouseHold(const scv::MouseEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onMouseOver(const scv::MouseEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onMouseUp(const scv::MouseEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onMouseWheel(const scv::MouseEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onKeyPressed(const scv::KeyEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onKeyUp(const scv::KeyEvent &evt) {\n}";
   code += "\nvoid " + ComponentName + "::onSizeChange(void) {\n}";
   code += "\nvoid " + ComponentName + "::onPositionChange(void) {\n}\n";

   if(type == scv::Component::PROGRESSBAR || type == scv::Component::SLIDER || type == scv::Component::SPINNER || type == scv::Component::CHECKBOX || type == scv::Component::RADIOBUTTON || type == scv::Component::TOGGLEBUTTON)
      code += "void " + ComponentName + "::onValueChange(void) {\n}\n";
   if(type == scv::Component::COMBOBOX)
      code += "void " + ComponentName + "::onSelectionChanged(void) {\n}\n";
   if(type == scv::Component::GENERICTREE)
      code += "void " + ComponentName + "::onItemSelected(void) {\n}\n";
   if(type == scv::Component::COLORPICKER)
      code += "void " + ComponentName + "::onColorChange(void) {\n}\n";
   if(type == scv::Component::WINDOW) {
      code += "void " + ComponentName + "::onClose(void) {\n}\n";
      code += "void " + ComponentName + "::onOpen(void) {\n}\n";
   }
   if(type == scv::Component::TEXTBOX || type == scv::Component::TEXTFIELD)
      code += "void " + ComponentName + "::onStringChange(void) {\n}\n";
   if(type == scv::Component::TABBEDPANE)
      code += "void " + ComponentName + "::onTabChange(void) {\n}\n";
   code += childCode;
   return code;
}



void CodeGenerator::generateCode(bool customClass) {

   std::memset(count, 0, sizeof(int)*NTYPES);
   // main.cpp
   ///////////////////////////////////////////////////////////
   std::string mainDotCpp, allocationCode, widgetCodeH, widgetCodeCpp;
   mainDotCpp += "#include <SCV/SCV.h>\n";
   mainDotCpp += "#include \"Application.h\"\n";
   mainDotCpp += "\n";
   mainDotCpp += "int main(int argc, char* argv[]) {\n";
   mainDotCpp += "   Application *kernel = new Application();\n";
   mainDotCpp += "   scv::Kernel::setInstance(kernel);\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->init();\n";
   mainDotCpp += "\n";

   for(auto comp = Application::getInstance()->_objects.begin(); comp != Application::getInstance()->_objects.end(); comp++) {
      allocationCode += createAllocationCode(*comp, customClass);
   }
   
   if(customClass == true) {
       std::memset(count, 0, sizeof(int)*NTYPES);
       for(auto comp = Application::getInstance()->_objects.begin(); comp != Application::getInstance()->_objects.end(); comp++) {
          widgetCodeH += createCustomClassCodeH(*comp);
       }
       std::memset(count, 0, sizeof(int)*NTYPES);
       for(auto comp = Application::getInstance()->_objects.begin(); comp != Application::getInstance()->_objects.end(); comp++) {
          widgetCodeCpp += createCustomClassCodeCpp(*comp);
       }
   }

   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";
   ///////////////////////////////////////////////////////////
   //Widget.h
   ///////////////////////////////////////////////////////////
   std::string widgetDotH = 
       "#ifndef __WIDGET_H__\n"
       "#define __WIDGET_H__\n"
       "\n"
       "#include <SCV/SCV.h>\n"
       "\n"
       + widgetCodeH +
       "#endif";
   ///////////////////////////////////////////////////////////
   //Widget.cpp
   std::string widgetDotCpp =
      "#include \"widget.h\"\n"
      + widgetCodeCpp;
   // Application.h
   ///////////////////////////////////////////////////////////
   std::string applicationDotH =
      "#ifndef __APPLICATION_H__\n"
      "#define __APPLICATION_H__\n"
      "\n"
      "#include <SCV/SCV.h>\n"
      "#include \"Widget.h\"\n"
      "\n"
      "class Application : public scv::Kernel {\n"
      "public:\n"
      "   ///////////////////////////////////////////////////////////\n"
      "   Application(void);\n"
      "   virtual ~Application(void);\n"
      "   ///////////////////////////////////////////////////////////\n"
      "\n"
      "   void init(void);\n"
      "\n"
      "   //SCVCallbacks\n"
      "   ///////////////////////////////////////////////////////////\n"
      "   virtual void onMouseClick(const scv::MouseEvent &evt);\n"
      "   virtual void onMouseHold (const scv::MouseEvent &evt);\n"
      "   virtual void onMouseOver (const scv::MouseEvent &evt);\n"
      "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n"
      "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n"
      "\n"
      "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n"
      "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n"
      "\n"
      "   virtual void onSizeChange(void);\n"
      "   virtual void onPositionChange(void);\n"
      "   ///////////////////////////////////////////////////////////\n"
      "\n"
      "protected:\n"
      "   static const int s_defaultWindowWidth = 1280;\n"
      "   static const int s_defaultWindowHeight = 720;\n"
      "   scv::Panel *_mainPanel;\n"
      "private:\n"
      "};\n"
      "\n"
      "#endif //__APPLICATION_H__\n";
   ///////////////////////////////////////////////////////////

   // Application.cpp
   ///////////////////////////////////////////////////////////
   std::string applicationDotCpp =
      "#include \"Application.h\"\n"
      "\n"
      "Application::Application(void) : Kernel() {\n"
      "   setWindowSize(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + ");\n"
      "   lockWindowSize(false);\n"
      "   setFramesPerSecond(60);\n"
      "\n"
      "   setWindowTitle(\"SCV v4.1 - FreeForm Interface Designer\");\n"
      "}\n"
      "\n"
      "Application::~Application(void) {\n"
      "}\n"
      "\n"
      "void Application::init(void) {\n"
      "   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + "));\n"
      "\n"
      "   addComponent(_mainPanel);\n"
      "\n" +
      allocationCode +
      "}\n"
      "\n"
      "void Application::onMouseClick(const scv::MouseEvent &evt) {\n"
      "}\n"
      "void Application::onMouseHold(const scv::MouseEvent &evt) {\n"
      "}\n"
      "void Application::onMouseOver(const scv::MouseEvent &evt) {\n"
      "}\n"
      "void Application::onMouseUp(const scv::MouseEvent &evt) {\n"
      "}\n"
      "void Application::onMouseWheel(const scv::MouseEvent &evt) {\n"
      "}\n"
      "\n"
      "void Application::onKeyPressed(const scv::KeyEvent &evt) {\n"
      "}\n"
      "void Application::onKeyUp(const scv::KeyEvent &evt) {\n"
      "}\n"
      "\n"
      "void Application::onSizeChange(void) {\n"
      "   _mainPanel->setSize(getWidth(), getHeight());\n"
      "}\n"
      "void Application::onPositionChange(void) {\n"
      "}\n";

   std::ofstream outputFile;
   
   outputFile.open("Application.h");
   outputFile << applicationDotH;
   outputFile.close();

   outputFile.open("Application.cpp");
   outputFile << applicationDotCpp;
   outputFile.close();

   outputFile.open("main.cpp");
   outputFile << mainDotCpp;
   outputFile.close();

   outputFile.open("Widget.h");
   outputFile << widgetDotH;
   outputFile.close();

   outputFile.open("Widget.cpp");
   outputFile << widgetDotCpp;
   outputFile.close();
   
   std::cout << "Arquivos gerados na pasta corrente" << std::endl;
}

std::string CodeGenerator::generateCodeMain(void)
{
   std::string mainDotCpp;
   mainDotCpp += "#include <SCV/SCV.h>\n";
   mainDotCpp += "#include \"Application.h\"\n";
   mainDotCpp += "\n";
   mainDotCpp += "int main(int argc, char* argv[]) {\n";
   mainDotCpp += "   scv::Kernel *kernel = scv::Kernel::getInstance();\n";
   mainDotCpp += "   scv::Kernel::setInstance(kernel);\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->init();\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";

   return mainDotCpp;
}
std::string CodeGenerator::generateCodeAppH(void)
{
   // Application.h
   std::string applicationDotH;   
   applicationDotH += "#ifndef __APPLICATION_H__\n";
   applicationDotH += "#define __APPLICATION_H__\n";
   applicationDotH += "\n";
   applicationDotH += "#include <SCV/SCV.h>\n";
   applicationDotH += "\n";
   applicationDotH += "class Application : public scv::Kernel {\n";
   applicationDotH += "public:\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   Application(void);\n";
   applicationDotH += "   virtual ~Application(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "   void init(void);\n";
   applicationDotH += "\n";
   applicationDotH += "   //SCVCallbacks\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   virtual void onMouseClick(const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseHold (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseOver (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n";
   applicationDotH += "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onSizeChange(void);\n";
   applicationDotH += "   virtual void onPositionChange(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "protected:\n";
   applicationDotH += "   static const int s_defaultWindowWidth = 1280;\n";
   applicationDotH += "   static const int s_defaultWindowHeight = 720;\n";
   applicationDotH += "   scv::Panel *_mainPanel;\n";
   applicationDotH += "private:\n";
   applicationDotH += "};\n";
   applicationDotH += "\n";
   applicationDotH += "#endif //__APPLICATION_H__\n";
   ///////////////////////////////////////////////////////////

   return applicationDotH;

}

std::string CodeGenerator::generateCodeAppCpp(void)
{
   ///////////////////////////////////////////////////////////
   std::string allocationCode = "";
   ///////////////////////////////////////////////////////////

   // Application.cpp
   ///////////////////////////////////////////////////////////
   std::string applicationDotCpp;
   applicationDotCpp += "#include \"Application.h\"\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::Application(void) : Kernel() {\n";
   applicationDotCpp += "   setWindowSize(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + ");\n";
   applicationDotCpp += "   lockWindowSize(false);\n";
   applicationDotCpp += "   setFramesPerSecond(60);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   setWindowTitle(\"SCV v4.1 - FreeForm Interface Designer\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultWindowWidth, s_defaultWindowHeight));\n";
   applicationDotCpp += allocationCode;
   applicationDotCpp += "\n";
   applicationDotCpp += "   addComponent(_mainPanel);\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onMouseClick(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseHold(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseOver(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseUp(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseWheel(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onKeyPressed(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onKeyUp(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onSizeChange(void) {\n";
   applicationDotCpp += "   _mainPanel->setSize(getWidth(), getHeight());\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onPositionChange(void) {\n";
   applicationDotCpp += "}\n";   
   ///////////////////////////////////////////////////////////

   return applicationDotCpp;
}

int CodeGenerator::getComponentCount(scv::Component::Type type) {
   return _counter[type]++;
}

std::string SpacesToUnderlines(std::string s)
{
    for(int i = 0 ; i < s.length() ; i++)
    {
        if(s[i] == ' ')
        {
            s[i] = '_';
        }
    }
    return s;
}


