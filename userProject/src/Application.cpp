#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(1050, 800);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV v4.0 - FreeForm Interface Designer");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1050, 800));

   addComponent(_mainPanel);

   scv::Button *button0 = new scv::Button(scv::Point(19,11), scv::Point(70, 35), "dfgdfg");
   addComponent(button0);

   scv::Canvas *canvas0 = new scv::Canvas(scv::Point(8,40), scv::Point(208, 240));
   addComponent(canvas0);

   scv::CheckBox *checkBox0 = new scv::CheckBox(scv::Point(17,251), 1, "vk");
   addComponent(checkBox0);

   scv::ColorPicker *colorPicker0 = new scv::ColorPicker(scv::Point(19,276));
   addComponent(colorPicker0);

   scv::ComboBox *comboBox0 = new scv::ComboBox(scv::Point(37,445), scv::Point(137, 465));
   addComponent(comboBox0);

   scv::ProgressBar *progressBar0 = new scv::ProgressBar(scv::Point(245,510), scv::Point(345, 548), 0);
   addComponent(progressBar0);

   scv::RadioButton *radioButton0 = new scv::RadioButton(scv::Point(44,555), 1, "rb0");
   addComponent(radioButton0);

   scv::Separator *separator0 = new scv::Separator(scv::Point(20,583), (scv::Separator::Orientation)0, 200);
   addComponent(separator0);

   scv::Separator *separator1 = new scv::Separator(scv::Point(240,433), (scv::Separator::Orientation)1, 200);
   addComponent(separator1);

   scv::Slider *slider0 = new scv::Slider(scv::Point(13,610), 100, 0.f, 100.f, 50.f, 1.f);
   addComponent(slider0);

   scv::Spinner *spinner0 = new scv::Spinner(scv::Point(22,646), 35, 0.f, 100.f, 50.f, 1.f);
   addComponent(spinner0);

   scv::TextBox *textBox0 = new scv::TextBox(scv::Point(246,162), scv::Point(346,211), "TextBox 0");
   addComponent(textBox0);

   scv::TextField *textField0 = new scv::TextField(scv::Point(245,235), 100, "TextField 0");
   addComponent(textField0);

   scv::ToggleButton *toggleButton0 = new scv::ToggleButton(scv::Point(366,227), scv::Point(454, 251), 0, "toggle");
   addComponent(toggleButton0);

   scv::GenericTree *genericTree0 = new scv::GenericTree(scv::Point(389,263), scv::Point(589, 463), new scv::GenericNode("Root") );
   addComponent(genericTree0);

   scv::MenuBar *menuBar0 = new scv::MenuBar(1050);
   addComponent(menuBar0);

   scv::Table *table0 = new scv::Table(scv::Point(233,36), 4, 4, 1, 50);
   addComponent(table0);

   scv::Label *label0 = new scv::Label(scv::Point(72,494), scv::Point(148, 507), "Laberl0");
   addComponent(label0);

   scv::InternalFrame *internalFrame0 = new scv::InternalFrame(200,200, "internal frame 0");
   internalFrame0->setRelativePosition(scv::Point(613,34));
   addComponent(internalFrame0);
      scv::Button *button1 = new scv::Button(scv::Point(79,52), scv::Point(132, 76), "ibutton");
      button1->setParent(internalFrame0->getPanel());


   scv::Panel *panel1 = new scv::Panel(scv::Point(424,476), scv::Point(624, 676));
   addComponent(panel1);
      scv::RadioButton *radioButton1 = new scv::RadioButton(scv::Point(58,100), 1, "rdpanel");
      radioButton1->setParent(panel1);

      scv::Label *label1 = new scv::Label(scv::Point(72,42), scv::Point(148, 55), "label");
      label1->setParent(panel1);


   scv::ScrollComponent *scrollComponent0 = new scv::ScrollComponent(scv::Point(669,294), scv::Point(995, 756));
   addComponent(scrollComponent0);
   scv::Panel *panel2 = new scv::Panel(scv::Point(0, 0),  scv::Point(500, 500));
   scrollComponent0->setComponent(panel2);
      scv::TabbedPane *tabbedPane0 = new scv::TabbedPane(scv::Point(47,41), scv::Point(302, 383));
      tabbedPane0->setParent(panel2);
      scv::Panel *panel3 = new scv::Panel(scv::Point(0,22), scv::Point(255, 342));
      panel3->setParent(tabbedPane0);
      scv::Canvas *canvas1 = new scv::Canvas(scv::Point(17,44), scv::Point(217, 244));
      canvas1->setParent(panel3);




}

void Application::onMouseClick(const scv::MouseEvent &evt) {
}
void Application::onMouseHold(const scv::MouseEvent &evt) {
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
}
void Application::onMouseUp(const scv::MouseEvent &evt) {
}
void Application::onMouseWheel(const scv::MouseEvent &evt) {
}

void Application::onKeyPressed(const scv::KeyEvent &evt) {
}
void Application::onKeyUp(const scv::KeyEvent &evt) {
}

void Application::onSizeChange(void) {
   _mainPanel->setSize(getWidth(), getHeight());
}
void Application::onPositionChange(void) {
}
