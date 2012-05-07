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
   MyButton(scv::Point p1, scv::Point p2, scv::TextField* tf, scv::TextBox* tb)
      : scv::Button(p1, p2, "Add Text"),
      tf(tf), tb(tb)
   {
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
	kernel->setWindowSize(500, 500);

   //Criar um novo Textfield para ser usado junto da classe
   scv::TextField* tf = new scv::TextField(scv::Point(100, 200), 100, "Type a text");
   scv::Kernel::getInstance()->addComponent(tf);

   //Criar um novo Textbox para ser usado junto da classe
   scv::TextBox* tb = new scv::TextBox(scv::Point(0, 0), scv::Point(200, 180), "");
   scv::Kernel::getInstance()->addComponent(tb);

   MyButton *but = new MyButton(scv::Point(0, 200), scv::Point(100, 220), tf, tb);
   scv::Kernel::getInstance()->addComponent(but);

	kernel->setFramesPerSecond(60);
	kernel->run();
}