/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laboratório de Computação Aplicada
www.inf.ufsm.br/~pozzer/scv/
2007-2012 

*/

#include <iostream>

struct Example
{
   const char* title;
   void (*func)();
};


void example1_main();
void example2_main();
void example3_main();
void example4_main();
void example5_main();
void example6_main();
void example7_main();
void example8_main();
void example9_main();

Example examples_list[] = {
   {"Hello World!", example1_main},
   {"Using Buttons", example2_main},
   {"TextField to TextBox", example3_main},
   {"Slider & ProgressBar", example4_main},
   {"Button Group",example5_main},
   {"Canvas GL", example6_main},
   {"Canvas Basic", example7_main},
   {"GenericTree", example8_main},
   {"Group Layouts", example9_main}
};
static const unsigned int NUM_EXAMPLES = 9;

int main()
{
   for (unsigned int i = 0; i < NUM_EXAMPLES; ++i) 
   {
      std::cout << i+1 << " - " << examples_list[i].title << '\n';
   }
   std::cout << '\n';

   unsigned int example_num = 0;
   while (example_num == 0 || example_num > NUM_EXAMPLES) 
   {
      std::cout << "Escolha um exemplo: " << std::flush;
      std::cin >> example_num;
   }

   examples_list[example_num-1].func();
}