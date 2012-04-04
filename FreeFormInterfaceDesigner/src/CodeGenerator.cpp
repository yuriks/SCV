#include <SCV/SCV.h>
#include "CodeGenerator.h"
#include "Application.h"

#include <cstring>

CodeGenerator::CodeGenerator(void) {
   _scvFrame = NULL;
}

CodeGenerator::~CodeGenerator(void) {
}

std::string CodeGenerator::addChildren(scv::Component *child, std::string dad) {
   std::string code;
   int x, y;
   int type = child->getType();

   if(type == 1) { // Panel
      if(child == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = count[child->getType()];
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Panel *panel" + scv::toString(count_n) + " = new scv::Panel(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      panel" + scv::toString(count_n) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "panel" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 2) { // ColorPicker
      code += "      scv::ColorPicker *colorPicker" + scv::toString(count[child->getType()]) + " = new scv::ColorPicker(scv::Point(" + scv::toString(child->getRelativePosition()) + "));\n";
      code += "      colorPicker" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 3) { // ProgressBar
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::ProgressBar *progressBar" + scv::toString(count[child->getType()]) + " = new scv::ProgressBar(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      code += "      progressBar" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 4) { // Scroll

   } else if(type == 5) { // Slider
      code += "      scv::Slider *slider" + scv::toString(count[child->getType()]) + " = new scv::Slider(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "      slider" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 6) { // Spinner
      code += "      scv::Spinner *spinner" + scv::toString(count[child->getType()]) + " = new scv::Spinner(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "      spineer" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 7) { // Button
      scv::Button *button = (scv::Button*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Button *button" + scv::toString(count[child->getType()]) + " = new scv::Button(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      code += "      button" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 8) { // CheckBox
      scv::CheckBox *checkBox = (scv::CheckBox*)(child);
      code += "      scv::CheckBox *checkBox" + scv::toString(count[child->getType()]) + " = new scv::CheckBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      code += "      checkBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 9) { // RadioButton
      scv::RadioButton *radioButton = (scv::RadioButton*)(child);
      code += "      scv::RadioButton *radioButton" + scv::toString(count[child->getType()]) + " = new scv::RadioButton(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      code += "      radioButton" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 10) {// ToggleButton
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      scv::ToggleButton *toggleButton = (scv::ToggleButton*)(child);
      code += "      scv::ToggleButton *toggleButton" + scv::toString(count[child->getType()]) + " = new scv::ToggleButton(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      code += "      toggleButton" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      code += "\n";
   } else if(type == 11) {// TextField
      scv::TextField *textField = (scv::TextField*)(child);
      code += "      scv::TextField *textField" + scv::toString(count[child->getType()]) + " = new scv::TextField(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", \"" + textField->getString() + "\");\n";
      code += "      textField" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 12) {// TextBox
      scv::TextBox *textBox = (scv::TextBox*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::TextBox *textBox" + scv::toString(count[child->getType()]) + " = new scv::TextBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + textBox->getString() + "\");\n";
      code += "      textBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 13) {// Separator
      scv::Separator *separator = (scv::Separator*)(child);
      if(separator->getAlign() == 0)
         code += "      scv::Separator *separator" + scv::toString(count[child->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(child->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getWidth()) + ");\n";
      if(separator->getAlign() == 1)
         code += "      scv::Separator *separator" + scv::toString(count[child->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(child->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getHeight()) + ");\n";
      code += "      separator" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 14) {// Window
      scv::InternalFrame *internalFrame = (scv::InternalFrame*)(child);
      int count_n = count[child->getType()];
      code += "   scv::InternalFrame *internalFrame" + scv::toString(count[child->getType()]) + " = new scv::InternalFrame(" + scv::toString(child->getWidth()) + ", " + scv::toString(child->getHeight()) + ", \"" + scv::toString(internalFrame->getTitle()) + "\");\n";
      code += "   addComponent(internalFrame" + scv::toString(count[child->getType()]) + ");\n";
      count[child->getType()] += 1;
       if(!child->_children.empty()) {
         auto c = child->_children.begin();
         scv::Component *a = *c;
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "internalFrame"+scv::toString(count_n)+"->getPanel()");
            }
         }
      }
      code += "\n";
   } else if(type == 15) {// MenuBar
      code += "      scv::MenuBar *menuBar" + scv::toString(count[child->getType()]) + " = new scv::MenuBar(" + scv::toString(child->getWidth()) + ");\n";
      code += "      menuBar" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 16) {// TabbedPane
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      int count_n = count[child->getType()];
      code += "      scv::TabbedPane *tabbedPane" + scv::toString(count[child->getType()]) + " = new scv::TabbedPane(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      tabbedPane" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "tabbedPane" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 17) {// ScrollComponent
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      int count_n = count[child->getType()];
      code += "      scv::ScrollComponent *scrollComponent" + scv::toString(count[child->getType()]) + " = new scv::ScrollComponent(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      scrollComponent" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         auto c = child->_children.begin();
         scv::Component *a = *c;
         int panelNumber = count[a->getType()];
         code += "   scv::Panel *panel" + scv::toString(panelNumber) + " = new scv::Panel(scv::Point(" + scv::toString(a->getRelativePosition().x) + ", " + scv::toString(a->getRelativePosition().y) + "),  scv::Point(" + scv::toString(a->getWidth()) + ", " + scv::toString(a->getHeight()) + "));\n";
         code += "   scrollComponent" + scv::toString(count_n) + "->setComponent(panel" + scv::toString(panelNumber) + ");\n";
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "panel" + scv::toString(panelNumber));
            }
         }
      }
      code += "\n";
   } else if(type == 18) {// Image
      scv::Image *image = (scv::Image*)(child);
      int count_n = count[child->getType()];
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Image *image" + scv::toString(count[child->getType()]) + " = new scv::Image(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      code += "      image" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "image" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 19) {//Table
      scv::Table *table = (scv::Table*)(child);
      code += "      scv::Table *table" + scv::toString(count[child->getType()]) + " = new scv::Table(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      code += "      table" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 20) {//ComboBox
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::ComboBox *comboBox" + scv::toString(count[child->getType()]) + " = new scv::ComboBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      comboBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 21) {//Canvas
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Canvas *canvas" + scv::toString(count[child->getType()]) + " = new scv::Canvas(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      canvas" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 22) {//TreeView
      scv::GenericTree *genericTree = (scv::GenericTree*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::GenericTree *genericTree" + scv::toString(count[child->getType()]) + " = new scv::GenericTree(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(genericTree->getRootNode()) + ");\n";
      code += "      genericTree" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 23) {//Label
      scv::Label *label = (scv::Label*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Label *label" + scv::toString(count[child->getType()]) + " = new scv::Label(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      code += "      label" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   }
   return code;
}

std::string CodeGenerator::createAllocationCode(scv::Component *comp) {
   std::string code;
   int x, y;
   int type = comp->getType();

   if(type == 1) { // Panel
      if(comp == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = 0;
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Panel *panel" + scv::toString(count[comp->getType()]) + " = new scv::Panel(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(panel" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "panel" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 2) { // ColorPicker
      code += "   scv::ColorPicker *colorPicker" + scv::toString(count[comp->getType()]) + " = new scv::ColorPicker(scv::Point(" + scv::toString(comp->getRelativePosition()) + "));\n";
      code += "   addComponent(colorPicker" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 3) { // ProgressBar
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::ProgressBar *progressBar" + scv::toString(count[comp->getType()]) + " = new scv::ProgressBar(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      code += "   addComponent(progressBar" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 4) { // Scroll

   } else if(type == 5) { // Slider
      code += "   scv::Slider *slider" + scv::toString(count[comp->getType()]) + " = new scv::Slider(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   addComponent(slider" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 6) { // Spinner
      code += "   scv::Spinner *spinner" + scv::toString(count[comp->getType()]) + " = new scv::Spinner(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   addComponent(spineer" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 7) { // Button
      scv::Button *button = (scv::Button*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Button *button" + scv::toString(count[comp->getType()]) + " = new scv::Button(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      code += "   addComponent(button" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 8) { // CheckBox
      scv::CheckBox *checkBox = (scv::CheckBox*)(comp);
      code += "   scv::CheckBox *checkBox" + scv::toString(count[comp->getType()]) + " = new scv::CheckBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      code += "   addComponent(checkBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 9) { // RadioButton
      scv::RadioButton *radioButton = (scv::RadioButton*)(comp);
      code += "   scv::RadioButton *radioButton" + scv::toString(count[comp->getType()]) + " = new scv::RadioButton(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      code += "   addComponent(radioButton" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 10) {// ToggleButton
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      scv::ToggleButton *toggleButton = (scv::ToggleButton*)(comp);
      code += "   scv::ToggleButton *toggleButton" + scv::toString(count[comp->getType()]) + " = new scv::ToggleButton(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      code += "   addComponent(toggleButton" + scv::toString(count[comp->getType()]) + ");\n";
      code += "\n";
   } else if(type == 11) {// TextField
      scv::TextField *textField = (scv::TextField*)(comp);
      code += "   scv::TextField *textField" + scv::toString(count[comp->getType()]) + " = new scv::TextField(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", \"" + textField->getString() + "\");\n";
      code += "   addComponent(textField" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 12) {// TextBox
      scv::TextBox *textBox = (scv::TextBox*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::TextBox *textBox" + scv::toString(count[comp->getType()]) + " = new scv::TextBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + textBox->getString() + "\");\n";
      code += "   addComponent(textBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 13) {// Separator
      scv::Separator *separator = (scv::Separator*)(comp);
      if(separator->getAlign() == 0)
         code += "   scv::Separator *separator" + scv::toString(count[comp->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getWidth()) + ");\n";
      if(separator->getAlign() == 1)
         code += "   scv::Separator *separator" + scv::toString(count[comp->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getHeight()) + ");\n";
      code += "   addComponent(separator" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 14) {// Window
      scv::InternalFrame *internalFrame = (scv::InternalFrame*)(comp);
      int count_n = count[comp->getType()];
      code += "   scv::InternalFrame *internalFrame" + scv::toString(count[comp->getType()]) + " = new scv::InternalFrame(" + scv::toString(comp->getWidth()) + ", " + scv::toString(comp->getHeight()) + ", \"" + scv::toString(internalFrame->getTitle()) + "\");\n";
      code += "   addComponent(internalFrame" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
       if(!comp->_children.empty()) {
         auto c = comp->_children.begin();
         scv::Component *a = *c;
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "internalFrame"+scv::toString(count_n)+"->getPanel()");
            }
         }
      }
      code += "\n";
   } else if(type == 15) {// MenuBar
      code += "   scv::MenuBar *menuBar" + scv::toString(count[comp->getType()]) + " = new scv::MenuBar(" + scv::toString(comp->getWidth()) + ");\n";
      code += "   addComponent(menuBar" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 16) {// TabbedPane
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      int count_n = count[comp->getType()];
      code += "   scv::TabbedPane *tabbedPane" + scv::toString(count[comp->getType()]) + " = new scv::TabbedPane(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(tabbedPane" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "tabbedPane" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 17) {// ScrollComponent
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      int count_n = count[comp->getType()];
      code += "   scv::ScrollComponent *scrollComponent" + scv::toString(count[comp->getType()]) + " = new scv::ScrollComponent(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(scrollComponent" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         auto c = comp->_children.begin();
         scv::Component *a = *c;
         int panelNumber = count[a->getType()];
         code += "   scv::Panel *panel" + scv::toString(panelNumber) + " = new scv::Panel(scv::Point(" + scv::toString(a->getRelativePosition().x) + ", " + scv::toString(a->getRelativePosition().y) + "),  scv::Point(" + scv::toString(a->getWidth()) + ", " + scv::toString(a->getHeight()) + "));\n";
         code += "   scrollComponent" + scv::toString(count_n) + "->setComponent(panel" + scv::toString(panelNumber) + ");\n";
         count[a->getType()] += 1;
         if(!a->_children.empty()) {
            for(auto f = a->_children.begin(); f != a->_children.end();f++) {
               scv::Component *x = *f;
               code += addChildren(x, "panel" + scv::toString(panelNumber));
            }
         }
      }
      code += "\n";
   } else if(type == 18) {// Image
      scv::Image *image = (scv::Image*)(comp);
      int count_n = count[comp->getType()];
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Image *image" + scv::toString(count[comp->getType()]) + " = new scv::Image(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      code += "   addComponent(image" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "image" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 19) {//Table
      scv::Table *table = (scv::Table*)(comp);
      code += "   scv::Table *table" + scv::toString(count[comp->getType()]) + " = new scv::Table(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      code += "   addComponent(table" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 20) {//ComboBox
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::ComboBox *comboBox" + scv::toString(count[comp->getType()]) + " = new scv::ComboBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(comboBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 21) {//Canvas
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Canvas *canvas" + scv::toString(count[comp->getType()]) + " = new scv::Canvas(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(canvas" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 22) {//TreeView
      scv::GenericTree *genericTree = (scv::GenericTree*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::GenericTree *genericTree" + scv::toString(count[comp->getType()]) + " = new scv::GenericTree(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(genericTree->getRootNode()) + ");\n";
      code += "   addComponent(genericTree" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 23) {//Label
      scv::Label *label = (scv::Label*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Label *label" + scv::toString(count[comp->getType()]) + " = new scv::Label(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      code += "   addComponent(label" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   }
   return code;
}

void CodeGenerator::generateCode(void) {

   std::memset(count, 0, sizeof(int)*23);
   // main.cpp
   ///////////////////////////////////////////////////////////
   std::string mainDotCpp, allocationCode;
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
      allocationCode += createAllocationCode(*comp);
   }

   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";
   ///////////////////////////////////////////////////////////

   // Application.h
   ///////////////////////////////////////////////////////////
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
   applicationDotCpp += "   setWindowTitle(\"SCV v4.0 - FreeForm Interface Designer\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + "));\n";
   applicationDotCpp += "\n";
   //applicationDotCpp += static_cast<Application *>(Application::getInstance())->getLayoutCode("_mainPanel") + "\n";
   applicationDotCpp += "   addComponent(_mainPanel);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += allocationCode;
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


   ///////////////////////////////////////////////////////////
   std::ofstream outputFile;

   outputFile.open("../ExportedSource/src/Application.h");
   outputFile << applicationDotH;
   outputFile.close();

   outputFile.open("../ExportedSource/src/Application.cpp");
   outputFile << applicationDotCpp;
   outputFile.close();

   outputFile.open("../ExportedSource/src/main.cpp");
   outputFile << mainDotCpp;
   outputFile.close();
   ///////////////////////////////////////////////////////////
}

std::string CodeGenerator::generateCodeMain(void)
{
    ///////////////////////////////////////////////////////////
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
   ///////////////////////////////////////////////////////////

   return mainDotCpp;
}
std::string CodeGenerator::generateCodeAppH(void)
{
   // Application.h
   ///////////////////////////////////////////////////////////
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
   applicationDotCpp += "   setWindowTitle(\"SCV v4.0 - FreeForm Interface Designer\");\n";
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


