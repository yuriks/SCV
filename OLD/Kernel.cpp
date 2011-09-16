void Kernel::cbReshape(int w, int h) {
	kernel->mainPanel->setWidth(w);
	kernel->mainPanel->setHeight(h);   
}
   
Panel * Kernel::getPanel() {
   if (mainPanel == NULL) {
      mainPanel = new scv::Panel(Point(0, 0), 1050, 860);

      mainPanel->setDraggable(false);
      mainPanel->setResizable(true);

      addComponent(mainPanel);
   }
   return mainPanel;
}
   
int currentPanel;
 
 
 void Kernel::generateCode() {
   static CodeGenerator *code = CodeGenerator::getInstance();
   static Kernel* kernel = Kernel::getInstance();
   kernel->currentPanel = -1;
   std::string str = "";
   std::string mainInstances = "";
   str += "#include <SCV/SCV.h>\n\n   /* Codes SCV Generator 1.0 \n      SCV Team\n      For more information visit:\n      www.inf.ufsm.br/~pozzer/scv */\n\n";

   for (std::deque<ComponentInterface*>::iterator it = kernel->_components.begin(); it < kernel->_components.end(); it++) {
      str += getComponentAttrib(*it,false,kernel->currentPanel);
   }

   str += code->generateMainProgram();

   std::ofstream outputFile("../interface.cpp");
   outputFile << str;
   outputFile.close();

}

std::string Kernel::getComponentAttrib(ComponentInterface * it, bool isAtPanel, int panelValue) {
   static Kernel* kernel = Kernel::getInstance();
   std::string str = "";

   static CodeGenerator *code = CodeGenerator::getInstance();

   if ((it)->getType() == ComponentInterface::button) {
      return code->includeButton(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::canvas) {
      return code->includeCanvas(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::checkBox) {
      return code->includeCheckBox(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::colorPicker) {
      return code->includeColorPicker(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::comboBox) {
      return code->includeComboBox(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::label) {
      return code->includeLabel(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::menuBar) {
      return code->includeMenuBar(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::panel) {
      str += code->includePanel(it,isAtPanel);
      for (DynamicCastIterator<ComponentInterface, Panel::ObjectList::const_iterator> i (it->getChildren()); i.valid(); ++i) {
         str += getComponentAttrib(*i, true);
      }
      return str;
   } else if (it->getType() == ComponentInterface::progressBar) {
      return code->includeProgressBar(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::radioButton) {
      return code->includeRadioButton(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::scrollPane) {
      ScrollPane * scroll = static_cast<ScrollPane*>(it);
      str += code->includeScrollPane(it,isAtPanel);
      for (DynamicCastIterator<ComponentInterface, Panel::ObjectList::const_iterator> i (scroll->getPanel()->getChildren()); i.valid(); ++i) {
         str += getComponentAttrib(*i, true);
      }
      return str;
   } else if (it->getType() == ComponentInterface::slider) {
      return code->includeSlider(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::spinner) {
      return code->includeSpinner(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::separator) {
      return code->includeSeparator(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::tabbedPane) {
      return code->includeTabbedPane(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::textField) {
      return code->includeTextField(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::textBox) {
      return code->includeTextBox(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::toggleButton) {
      return code->includeToggleButton(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::window) {
      return code->includeInternalFrame(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::table) {
      return code->includeTable(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::image) {
      str += code->includeImage(it,isAtPanel);
      for (DynamicCastIterator<ComponentInterface, Panel::ObjectList::const_iterator> i (it->getChildren()); i.valid(); ++i) {
         str += getComponentAttrib(*i, true);
      }
      return str;
   } else if (it->getType() == ComponentInterface::treeView) {
      return code->includeTreeView(it,isAtPanel);      
   }
   return str;
}
