/* Exemplo que mostra como usar a Canvas para exibir uma simples animacao de
 * um objeto quicante.
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Color4f.h>
#include <SCV/Canvas.h>
#include <SCV/MenuBar.h>
#include <SCV/ContextMenu.h>
#include <string>

static const int WINDOW_WIDTH = 320;
static const int WINDOW_HEIGHT = 240;

namespace {

class MyCanvas : public scv::Canvas {
public:
   MyCanvas(const scv::Point& canvas_pos) : scv::Canvas(canvas_pos, canvas_pos + scv::Point(WINDOW_WIDTH, WINDOW_HEIGHT)),
      pos(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), cur_speed(2, 2), bg_color(.5f, .2f, .2f)
   {

   }

   // Muda a cor de fundo do canvas. (Esta funcao eh chamada pelo menu.)
   void setBackground(const scv::Color4f& color) { bg_color = color; }

   //// Callbacks do SCV
   // Esta funcao sera chamada para renderizar a sua cena.
   void render();
   // Esta funcao sera chamada uma vez por frame para voce atualizar as
   // posicoes de seus objetos, animacoes, etc.
   void update();
   // Esta funcao sera chamada enquanto o usuario manter o mouse pressionado
   // sobre o canvas.
   void onMouseHold(const scv::MouseEvent&);

private:
   static const int RECT_SIZE = 8;
   static const int TRIANGLE_SIZE = 16;

   // Posicao atual dos triangulos
   scv::Point pos;
   // Velocidade atual dos triangulos
   scv::Point cur_speed;
   // Cor do fundo
   scv::Color4f bg_color;
};

void MyCanvas::render() {
   // Limpa a tela com a cor de fundo.
   glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
   glClear(GL_COLOR_BUFFER_BIT);

   // Desenha uma linha (com cor RGB(0, 0, 1)) do centro do canvas ate a
   // posicao dos triangulos.
   glBegin(GL_LINES);
      glColor3f(0.f, 0.f, 1.f);
      glVertex2i(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
      glVertex2i(pos.x, pos.y);
   glEnd();

   // Desenha um retangulo no centro do canvas.
   glBegin(GL_QUADS);
      glColor3f(0.f, 1.f, 0.f);
      glVertex2i(WINDOW_WIDTH/2 - RECT_SIZE, WINDOW_HEIGHT/2 - RECT_SIZE);
      glVertex2i(WINDOW_WIDTH/2 + RECT_SIZE, WINDOW_HEIGHT/2 - RECT_SIZE);
      glVertex2i(WINDOW_WIDTH/2 + RECT_SIZE, WINDOW_HEIGHT/2 + RECT_SIZE);
      glVertex2i(WINDOW_WIDTH/2 - RECT_SIZE, WINDOW_HEIGHT/2 + RECT_SIZE);
   glEnd();

   // Desenha os dois triangulos.
   glBegin(GL_TRIANGLES);
      glColor3f(1.f, 1.f, 1.f);
      glVertex2i(pos.x - TRIANGLE_SIZE, pos.y + TRIANGLE_SIZE);
      glVertex2i(pos.x - TRIANGLE_SIZE, pos.y - TRIANGLE_SIZE);
      glColor3f(0.f, 0.f, 0.f);
      glVertex2i(pos.x, pos.y);

      glColor3f(1.f, 1.f, 1.f);
      glVertex2i(pos.x, pos.y);
      glColor3f(0.f, 0.f, 0.f);
      glVertex2i(pos.x + TRIANGLE_SIZE, pos.y - TRIANGLE_SIZE);
      glVertex2i(pos.x + TRIANGLE_SIZE, pos.y + TRIANGLE_SIZE);
   glEnd();
}

void MyCanvas::update() {
   // Move os triangulos.
   pos += cur_speed;

   // Se ele passar para fora da tela, inverta sua velocidade (bounce).
   if (pos.x < 0 || pos.x > getWidth())
      cur_speed.x = -cur_speed.x;
   if (pos.y < 0 || pos.y > getHeight())
      cur_speed.y = -cur_speed.y;
}

void MyCanvas::onMouseHold(const scv::MouseEvent& evt)
{
   // Move os triangulos para a posicao onde o mouse esta.
   pos = evt.getPosition();
}


// Menu de troca de cores de background.
class ColorsMenu : public scv::ContextMenu {
public:
   ColorsMenu(MyCanvas* canvas) : scv::ContextMenu("Cores"),
      canvas(canvas)
   {
      // Adiciona os itens ao menu.
      addMenu(new scv::ContextMenu("Vermelho"));
      addMenu(new scv::ContextMenu("Verde"));
      addMenu(new scv::ContextMenu("Azul"));
      addMenu(new scv::ContextMenu("Preto"));
      addMenu(new scv::ContextMenu("Branco"));
      addMenu(new scv::ContextMenu("Cinza"));
   }

   // Callback chamada quando algum menu for acessado.
   virtual void onMenuAccessed(const std::deque<std::string>& address);

private:
   // Referencia ao canvas, para trocar sua cor.
   MyCanvas* canvas;
};

void ColorsMenu::onMenuAccessed(const std::deque<std::string>& address) {
   // `address` contem o 'caminho' de nomes de menus seguidos para se chegar
   // no escolhido. O ultimo elemento eh o item que o usuario clicou.
   const std::string& str = address.back();
   scv::Color4f color;

   // Decide a cor a atribuir baseado no item de menu selecionado.
   if (str == "Vermelho")
      color = scv::Color4f(.5f, .2f, .2f);
   else if (str == "Verde")
      color = scv::Color4f(.2f, .5f, .2f);
   else if (str == "Azul")
      color = scv::Color4f(.2f, .2f, .5f);
   else if (str == "Preto")
      color = scv::Color4f(0.f, 0.f, 0.f);
   else if (str == "Branco")
      color = scv::Color4f(1.f, 1.f, 1.f);
   else if (str == "Cinza")
      color = scv::Color4f(.5f, .5f, .5f);
   else
      // Nunca deve acontecer
      color = scv::Color4f(1.f, 1.f, 0.f); // Magenta

   // Muda a cor do canvas.
   canvas->setBackground(color);
}

}

void example6_main() {
   // Inicializa o SCV.
   scv::Kernel* kernel = scv::Kernel::getInstance();
   scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

   // Carrega o equema de cores e seta o tamanho da janela.
   //scheme->loadScheme(scv::ColorScheme::clean);
   kernel->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT + 22);

   // Cria e adiciona nosso canvas a janela principal.
   MyCanvas* canvas = new MyCanvas(scv::Point(0, 22));
   kernel->addComponent(canvas);

   // Cria e adiciona a barra de menu e itens
   scv::MenuBar* menu_bar = new scv::MenuBar(WINDOW_WIDTH);
   scv::ContextMenu* colors_menu = new ColorsMenu(canvas);
   menu_bar->addMenu(colors_menu);
   kernel->addComponent(menu_bar);

   // Roda a interface a 60 frames por segundo.
   kernel->setFramesPerSecond(60);
   kernel->run();
}
