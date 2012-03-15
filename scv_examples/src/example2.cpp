/* Exemplo que mostra o uso dos botoes. 
 * Cada botao modifica a string do Textfield 
 * de uma maneira
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Label.h>
#include <SCV/Button.h>
#include <SCV/TextField.h>
#include <string>

namespace {

class MyCenterButton : public scv::Button {
public:
   MyCenterButton(scv::Point p1, std::string t, scv::TextField* tt) : scv::Button(scv::Point(p1.x,p1.y),scv::Point(p1.x + 80,p1.y + 20), t) {
      //Pega e armazena o ponteiro do Textfield usado
      tf = tt;
     
      //Adicionar o componente
      scv::Kernel::getInstance()->addComponent(this);
   }

   //Implementacao da callback do botao
   void onMouseClick(const scv::MouseEvent &evt) {
      //Seta o conteudo do textfield para Center
      tf->setString("Center"); 
   }
private:
   scv::TextField *tf;
};

class MyRightButton : public scv::Button {
public:
   MyRightButton(scv::Point p1, std::string t, scv::TextField* tt) : scv::Button(scv::Point(p1.x,p1.y),scv::Point(p1.x + 80,p1.y + 20), t) {
      //Pega e armazena o ponteiro do Textfield usado
      tf = tt;

      //Adicionar o componente
      scv::Kernel::getInstance()->addComponent(this);
   }

   //Implementacao da callback do botao
   void onMouseClick(const scv::MouseEvent &evt) {
      //Seta o conteudo do textfield para Right
      tf->setString("Right"); 
   }
private:
   scv::TextField *tf;
};

class MyLeftButton : public scv::Button {
public:
   MyLeftButton(scv::Point p1, std::string t, scv::TextField* tt) : scv::Button(scv::Point(p1.x,p1.y),scv::Point(p1.x + 80,p1.y + 20), t) {
      //Pega e armazena o ponteiro do Textfield usado
      tf = tt;

      //Adicionar o componente
      scv::Kernel::getInstance()->addComponent(this);
   }

   //Implementacao da callback do botao
   void onMouseClick(const scv::MouseEvent &evt) {
      //Seta o conteudo do textfield para Left
      tf->setString("Left");
   }
private:
   scv::TextField *tf;
};

}

void example2_main() {
	scv::Kernel* kernel = scv::Kernel::getInstance();
	
   scv::ColorScheme* scheme = scv::ColorScheme::getInstance();
   scheme->loadScheme(scv::ColorScheme::CLEAN);
	
   kernel->setWindowSize(500, 500);

   scv::TextField *tf = new scv::TextField(scv::Point(0,0),240,"Center");
   scv::Kernel::getInstance()->addComponent(tf);

   MyLeftButton *bLeft = new MyLeftButton(scv::Point(0,20),"Set to left", tf);
   MyCenterButton *bCenter = new MyCenterButton(scv::Point(80,20),"Set to center", tf);
   MyRightButton *bRight = new MyRightButton(scv::Point(160,20),"Set to right", tf);

	kernel->setFramesPerSecond(60);
	kernel->run();
}