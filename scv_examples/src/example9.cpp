/* Exemplo de uso de Group Layouts
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Label.h>
#include <SCV/GenericTree.h>
#include <SCV/GenericNode.h>
#include <SCV/TextField.h>
#include <SCV/Image.h>
#include <SCV/SCV.h>




namespace {

class Application : public scv::Kernel {
public:
   ///////////////////////////////////////////////////////////
   Application(void);
   virtual ~Application(void);
   ///////////////////////////////////////////////////////////

   void init(void);

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////

protected:
   static const int s_defaultWindowWidth = 1280;
   static const int s_defaultWindowHeight = 720;
   scv::Panel *_mainPanel;
private:
};


Application::Application(void) : Kernel() {
   setWindowSize(400 - 20, 120 - 40);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("SCV Example");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(2, 2), scv::Point(2, 2));
   scv::Label *label0 = new scv::Label(scv::Point(0, 0), "Find What:");
   _mainPanel->addChild(label0);
   scv::TextField *textfield0 = new scv::TextField(scv::Point(0, 0), 200, "SCV TextField");
   _mainPanel->addChild(textfield0);
  
   scv::Button *button0 = new scv::Button(scv::Point(0, 0), "Find");
   _mainPanel->addChild(button0);
   scv::Button *button1 = new scv::Button(scv::Point(0, 0), "Cancel");
   _mainPanel->addChild(button1);
   scv::CheckBox *checkbox0 = new scv::CheckBox(scv::Point(0, 0), 0, "Match Case");
   _mainPanel->addChild(checkbox0);
   scv::CheckBox *checkbox1 = new scv::CheckBox(scv::Point(0, 0), 0, "Whole Words");
   _mainPanel->addChild(checkbox1);
   scv::CheckBox *checkbox2 = new scv::CheckBox(scv::Point(0, 0), 0, "Wrap Around");
   _mainPanel->addChild(checkbox2);
   scv::CheckBox *checkbox3 = new scv::CheckBox(scv::Point(0, 0), 0, "Search Backwards");
   _mainPanel->addChild(checkbox3);
   scv::GroupLayout *layout = new scv::GroupLayout(_mainPanel);
   _mainPanel->setLayout(layout);

   layout->setHorizontalGroup(
      scv::GroupLayout::createParallelGroup()
         ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
            ->addComponent(label0)
            ->addGroup(scv::GroupLayout::createParallelGroup()
               ->addComponent(textfield0)
               ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
                  ->addGroup(scv::GroupLayout::createParallelGroup()
                     ->addComponent(checkbox0)
                     ->addComponent(checkbox1)
                  )
                  ->addGroup(scv::GroupLayout::createParallelGroup()
                     ->addComponent(checkbox2)
                     ->addComponent(checkbox3)
                  )
               )
            )
            ->addGroup(scv::GroupLayout::createParallelGroup()
               ->addComponent(button0)
               ->addComponent(button1)
            )
         )
   );
   layout->setVerticalGroup(
      scv::GroupLayout::createParallelGroup()
         ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
            ->addGroup(scv::GroupLayout::createParallelGroup()
               ->addComponent(label0)
               ->addComponent(textfield0)
               ->addComponent(button0)
            )
            ->addGroup(scv::GroupLayout::createParallelGroup()
               ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
                  ->addComponent(checkbox0)
                  ->addComponent(checkbox1)
               )
               ->addGroup(scv::GroupLayout::createSequentialGroup()->setAutoCreateGaps(true)
                  ->addComponent(checkbox2)
                  ->addComponent(checkbox3)
               )
               ->addComponent(button1)
            )
         )
   );


   addComponent(_mainPanel);
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
   _mainPanel->setSize(getWidth() - 4, getHeight() - 4);
}
void Application::onPositionChange(void) {
}



}

void example9_main() 
{
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);
   kernel->init();


   kernel->run();
}