/* Button Group
 * 
 */

#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/ProgressBar.h>
#include <SCV/Slider.h>
#include <SCV/ButtonGroup.h>
#include <SCV/RadioButton.h>


namespace {

class MyRadioButton : public scv::RadioButton {
public:
   MyRadioButton(scv::Point p1 , std::string name) : scv::RadioButton(p1, false, name) {
      //Adicionar o componente ao kernel
      scv::Kernel::getInstance()->addComponent(this);
   }

private:

};

}

void example5_main() {
	scv::Kernel* kernel = scv::Kernel::getInstance();
	kernel->setWindowSize(300, 300);

   scv::ButtonGroup * bgroup = new scv::ButtonGroup();
   
   MyRadioButton * b1 = new MyRadioButton(scv::Point(20, 20),      "Button 1");
   MyRadioButton * b2 = new MyRadioButton(scv::Point(20, 20+30),   "Button 2");
   MyRadioButton * b3 = new MyRadioButton(scv::Point(20, 20+30*2), "Button 3");
   MyRadioButton * b4 = new MyRadioButton(scv::Point(20, 20+30*3), "Button 4");

   b1->registerButtonGroup(bgroup);
   b2->registerButtonGroup(bgroup);
   b3->registerButtonGroup(bgroup);
   b4->registerButtonGroup(bgroup);

	kernel->setFramesPerSecond(60);
	kernel->run();
}