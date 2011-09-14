#ifndef __SCV_CODE_GENERATOR_H__
#define __SCV_CODE_GENERATOR_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "ComponentInterface.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class CodeGenerator : public Singleton<CodeGenerator> {
   friend class Singleton<CodeGenerator>;
public:

   std::string includeDefaultClassStyle(void);

   std::string includeButton(ComponentInterface * component, bool isAtPanel);
   std::string includeCanvas(ComponentInterface * component, bool isAtPanel);
   std::string includeCheckBox(ComponentInterface * component, bool isAtPanel);
   std::string includeColorPicker(ComponentInterface * component, bool isAtPanel);
   std::string includeComboBox(ComponentInterface * component, bool isAtPanel);
   std::string includeImage(ComponentInterface * component, bool isAtPanel);
   std::string includeInternalFrame(ComponentInterface * component, bool isAtPanel);
   std::string includeLabel(ComponentInterface * component, bool isAtPanel);
   std::string includeMenuBar(ComponentInterface * component, bool isAtPanel);
   std::string includePanel(ComponentInterface * component, bool isAtPanel);
   std::string includeProgressBar(ComponentInterface * component, bool isAtPanel);
   std::string includeRadioButton(ComponentInterface * component, bool isAtPanel);
   std::string includeSeparator(ComponentInterface * component, bool isAtPanel);
   std::string includeSlider(ComponentInterface * component, bool isAtPanel);
   std::string includeSpinner(ComponentInterface * component, bool isAtPanel);
   std::string includeScrollPane(ComponentInterface * component, bool isAtPanel);
   std::string includeTabbedPane(ComponentInterface * component, bool isAtPanel);
   std::string includeTable(ComponentInterface * component, bool isAtPanel);
   std::string includeTextBox(ComponentInterface * component, bool isAtPanel);
   std::string includeTextField(ComponentInterface * component, bool isAtPanel);
   std::string includeToggleButton(ComponentInterface * component, bool isAtPanel);
   std::string includeTreeView(ComponentInterface * component, bool isAtPanel);
   
   std::string generateMainProgram(void);
   void initCounters(void);


private:
   CodeGenerator(void);
   ~CodeGenerator(void) {}

   int contButton, contTreeView, contCanvas, contCheckBox, contColorPicker,
      contMenuBar, contPanel, contProgressBar, contRadioButton, contScrollPane,
      contSlider, contSpinner, contSeparator, contTabbedPane, contTextField,
      contTextBox, contToggleButton, contInternalFrame, contTable, contComboBox,
      contImage, contLabel;

   std::string instance;

};

} // namespace scv

#endif // __SCV_CODE_GENERATOR_H__
