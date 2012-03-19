/* Exemplo que mostra como usar as funcoes de desenho da Canvas 
Autor: Cesar Tadeu Pozzer
 */
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/Color4f.h>
#include <SCV/Canvas.h>
#include <SCV/MenuBar.h>
#include <SCV/ContextMenu.h>
#include <string>

static const int WINDOW_WIDTH = 620;
static const int WINDOW_HEIGHT = 640;

namespace {

class MyCanvas : public scv::Canvas {
public:
   MyCanvas(const scv::Point& canvas_pos) : scv::Canvas(canvas_pos, canvas_pos + scv::Point(WINDOW_WIDTH, WINDOW_HEIGHT))
   {
	   bg_color = scv::Color4f(.5f, .2f, .2f);

	   time = 0.0;
   }

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

   // Posicao atual dos quadrado
   scv::Point pos;
   // Cor do fundo
   scv::Color4f bg_color;

   double time;
};

void MyCanvas::render() 
{
   clear(bg_color[0], bg_color[1], bg_color[2]);
   color(1,0,0);
   rect(pos.x + 10, pos.y+ 10, 200, 200);
   circleFill(150, 150, 40, 3 + (int)(pos.x/100.0));
   text(100,100,"canvas");

   //desenha um relogio
   int x = (int)(cos(time) * 150);
   int y = (int)(sin(time) * 150);
   clear(0, 1, 0);
   color(0,0,0);
   circle(300, 300, 110, 30);
   line(300, 300, x + 300, y + 300);
}

void MyCanvas::update() 
{
	time += 0.1;
}

void onKeyPressed(const scv::KeyEvent &evt)
{

}

void MyCanvas::onMouseHold(const scv::MouseEvent& evt)
{
   // redimensiona o quadrado e resolucao do circulo
   pos = evt.getPosition();
}
}

void example7_main() {
   // Inicializa o SCV.
   scv::Kernel* kernel = scv::Kernel::getInstance();
   scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

   // seta o tamanho da janela.
   kernel->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

   // Cria e adiciona nosso canvas a janela principal.
   MyCanvas* canvas = new MyCanvas(scv::Point(0, 0));
   kernel->addComponent(canvas);

   // Roda a interface a 60 frames por segundo.
   kernel->setFramesPerSecond(60);
   kernel->run();
}