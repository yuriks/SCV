/* Exemplo de uso de uma TreeView. 
 * Cada selecao e atualizado o path do arquivo.
 * Imagens podem ser abertas atraves da TreeView.
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Label.h>
#include <SCV/TreeView.h>
#include <SCV/TextField.h>
#include <SCV/Image.h>

namespace {

class MyTreeViewOF : public scv::TreeView {
public: 
   MyTreeViewOF(scv::Point p1, scv::Point p2) : scv::TreeView(p1,p2, scv::TW_FOLDERS_AND_FILES) {
      //Criar um novo Textfield para ser usado junto da classe
      tf = new scv::TextField(scv::Point(-1,399),251," ");
      scv::Kernel::getInstance()->addComponent(tf);

      //Adicionar o componente
      scv::Kernel::getInstance()->addComponent(this);
   }

   //implementacao da callback da TreeView
   void itemSelect(void) {
      //se o ultimo clicado for uma pasta
      if(getTypeLastPath() == scv::T_FOLDER) {
         tf->setString(getLastPath());
      //se o ultimo clicado for um arquivo
      } else if(getTypeLastPath() == scv::T_FILE) {
         tf->setString(getLastPath());

         scv::Image *op = new scv::Image(scv::Point(0,0), getLastPath());
         //Seta para que o usuario possa mover e redimensionar a imagem carregada.
         //(Se for possivel carrega-la)
         op->setDraggable(true);
         op->setResizable(true);
         //Adiciona a imagem
         scv::Kernel::getInstance()->addComponent(op);
      }
   }

private:
   scv::TextField *tf;
};

}

void example7_main() {
   scv::Kernel* kernel = scv::Kernel::getInstance();
	scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

	scheme->loadScheme(scv::ColorScheme::clean);
	kernel->setWindowSize(400, 600);

	MyTreeViewOF *t = new MyTreeViewOF(scv::Point(-1,-1), scv::Point(250,400));

	kernel->setFramesPerSecond(60);
	kernel->run();
}