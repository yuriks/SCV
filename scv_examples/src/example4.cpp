/* Exemplo que mostra o uso da callback onValueChange() da classe Counter
 * Quando o valor do slider é alterado o valor da progressBar é setado para o mesmo valor do slider.
*/
#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/ProgressBar.h>
#include <SCV/Slider.h>

namespace {

class MySlider : public scv::Slider {
public:
   MySlider(scv::ProgressBar* ref)
      : scv::Slider(scv::Point(5,205), 490, 0.0, 100.0, 50.0, 0.01),
      progress_bar(ref) // Armazena o ponteiro do ProgressBar, para poder atualiza-lo qndo a callback for chamada.
   {
   }

   // Implementacao da callback do slider
   void onValueChange(void) {
      // Seta o valor do slider para a ProgressBar
      progress_bar->setValue(getValue());
   }

private:
   scv::ProgressBar *progress_bar;
};

} // namespace

void example4_main() {
	scv::Kernel* kernel = scv::Kernel::getInstance();
	scv::ColorScheme* scheme = scv::ColorScheme::getInstance();

	scheme->loadScheme(scv::ColorScheme::clean);
	kernel->setWindowSize(500, 500);

   scv::ProgressBar* progress_bar = new scv::ProgressBar(scv::Point(5,150),scv::Point(495,200), 50.0);
   MySlider* slider = new MySlider(progress_bar);

   // Adiciona os componentes ao Kernel
   kernel->addComponent(progress_bar);
   kernel->addComponent(slider);

	kernel->setFramesPerSecond(60);
	kernel->run();
}
