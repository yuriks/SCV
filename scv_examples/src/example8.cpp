/* Exemplo de uso de uma TreeView. 
 * Cada selecao e atualizado o path do arquivo.
 * Imagens podem ser abertas atraves da TreeView.
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Label.h>
#include <SCV/GenericTree.h>
#include <SCV/GenericNode.h>
#include <SCV/TextField.h>
#include <SCV/Image.h>

namespace {

class MyTree : public scv::GenericTree {
public: 
   MyTree(scv::Point p1, scv::Point p2) : scv::GenericTree(p1, p2, new scv::GenericNode("Coisas")) {
      // Criar um novo Textfield para ser usado junto da classe
      tf = new scv::TextField(scv::Point(-1,399), 251, "");
      scv::Kernel::getInstance()->addComponent(tf);
   }

   void buildTree() {
      scv::GenericNode* node_num = new scv::GenericNode("Numeros");
      for (char c = '0'; c < '9'; ++c) {
         scv::GenericNode* node = new scv::GenericNode(std::string(1, c));
         node_num->children.push_back(node);
      }
      getRootNode()->children.push_back(node_num);

      scv::GenericNode* node_abc = new scv::GenericNode("Letras");
      for (char c = 'A'; c < 'Z'; ++c) {
         scv::GenericNode* node = new scv::GenericNode(std::string(1, c));
         node_abc->children.push_back(node);
      }
      getRootNode()->children.push_back(node_abc);

      refreshDisplay();
   }

   // Implementacao da callback da TreeView
   void onItemSelected() {
      const scv::GenericNode* node = getSelectedNode();
      // Se o ultimo clicado for uma pasta
      tf->setString(node->label);
   }

private:
   scv::TextField *tf;
};

}

void example8_main() {
   scv::Kernel* kernel = scv::Kernel::getInstance();
	scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

    //scheme->loadScheme(scv::ColorScheme::WARCRAFT);
	kernel->setWindowSize(400, 600);

	MyTree *t = new MyTree(scv::Point(-1, -1), scv::Point(250, 400));
   t->buildTree();
   scv::Kernel::getInstance()->addComponent(t);

	kernel->setFramesPerSecond(60);
	kernel->run();
}