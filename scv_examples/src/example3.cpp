/* Exemplo que mostra o uso dos botoes. 
 * Através do botao, adiciona conteudo
 * dos textfield para o textbox.
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Label.h>
#include <SCV/Button.h>
#include <SCV/TextBox.h>
#include <SCV/TextField.h>
#include <string>

namespace {
class MyButton : public scv::Button {
public:
   MyButton(scv::Point p1, std::string t) : scv::Button(scv::Point(p1.x,p1.y + 200),scv::Point(p1.x + 100,p1.y + 220), t) {
      //Criar um novo Textfield para ser usado junto da classe
      tf = new scv::TextField(scv::Point(p1.x + 100,p1.y + 200),100,"");
      scv::Kernel::getInstance()->addComponent(tf);

      //Criar um novo Textbox para ser usado junto da classe
      tb = new scv::TextBox(p1,scv::Point(p1.x + 200,p1.y + 200),"");
      scv::Kernel::getInstance()->addComponent(tb);

      //Adicionar o componente
      scv::Kernel::getInstance()->addComponent(this);

   }

   //Implementacao da callback do botao
   void onMouseClick(const scv::MouseEvent &evt) {
      //seta a string do textbox como a sua String mais a string do Textfield
      tb->setString(tb->getString()+tf->getString());

      //Limpa a Textfield
      tf->setString("");
   }
private:
   scv::TextField *tf;
   scv::TextBox *tb;
};

}

void example3_main() {
	scv::Kernel* kernel = scv::Kernel::getInstance();
	scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

	scheme->loadScheme(scv::ColorScheme::clean);
	kernel->setWindowSize(500, 500);

   MyButton *t = new MyButton(scv::Point(0,0),"Add Text");

	kernel->setFramesPerSecond(60);
	kernel->run();
}