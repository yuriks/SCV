/*!
\file       SCV.h
\brief      Include all SCV dependencies and components.
\author     SCV Team.
*/

#ifndef __SCV_H__
#define __SCV_H__

/*!
\mainpage SCV Documentation

O SCV é uma API (Application Programming Interface) de facilitação na construção de interfaces de usuário (GUI - Graphic User Interface), orientada ao uso de um programador com experiência na linguagem de programação C++. Aqui você irá encontrar a documentação de todos componentes e funcionalidades oferecidas. Na pasta 'scv_examples' são dados exemplos de uso da API com projetos do Microsoft Visual Studio 2010.

\section ide IDEs Suportadas
- Microsoft Visual Studio 2010

\subsection ide_so Sistemas Operacionais
- Windows

A documentação atualizada poderá ser acessada através do endereço: http://www-usr.inf.ufsm.br/~pozzer/scv <br/>
A última versão da biblioteca poderá sempre ser encontrada em: http://www-usr.inf.ufsm.br/~pozzer/scv/scv3.0b.rar

\section home Get Started!

- Para acessar a documentação do SCV presente na pasta "documentation" execute o arquivo "Documentation.bat".
- Para visualizar vários exemplos utilizando o SCV e demonstrando suas funcionalidades execute o arquivo "SCV_Examples.bat".
- Para acessar o InterfaceDesginer execute o "InterfaceDesigner.bat", nele o usuário pode graficamente criar sua Interface, através de DragAndDrop, e gerar o código SCV correspondente para o arquivo "interface.cpp".

\section runtimes Runtimes do Visual Studio

Caso forem rodar os demos ou programas desenvolvidos no VS2010
em máquinas que nao tenham o VS, deve-se instalar também o Microsoft
Visual C++ 2010 Redistributable. Sem ele, vem um aviso que faltam dlls
para execucao, mais especificamente as MSVCP100.dll e MSVCR100.dll.

O instalador da runtime pode ser baixado da Microsoft através deste link: http://www.microsoft.com/downloads/en/confirmation.aspx?familyid=A7B7A05E-6DE6-4D3A-A423-37BF0912DB84&displaylang=en

Caso prefira, pode-se também simplesmente copiar essas duas DLLs do seu computador com VS para a pasta do exe. (Ficam em C:\\Windows\\System32\\msvcp100.dll e C:\\Windows\\System32\\msvcr100.dll)

\section tech Detalhes Técnicos

O SCV está implementado sobre a API gráfica OpenGL. Existe uma estrutura hierárquica de componentes, onde cada componente é responsavel por desenhar os componentes contidos nele. O componentes utilizam a fucionalidade de scissors do OpenGL para fazer a limitação da área de desenho para apenas o retângulo que engloba o componente, além de fazer o desenho dele mesmo, utilizando mapas de textura, compartilhados por todas as instâncias do mesmo tipo de componente, e fontes, representadas com uma textura contendo todos os caracteres, compartilhada em nível global. Esquemas de cor são implementados modulando-se a cor das texturas dos componentes. A interação entre componentes e o código do usuário da biblioteca faz-se utilizando callbacks, presentes como funções virtuais nos componentes, que devem ser herdados.

\section credits Créditos

- Prof. Cesar Tadeu Pozzer: Coordenador e Idealizador do Projeto
- Cicero Augusto de Lara Pahins: Desenvolvimento, Documentação
- Frederico Artur Limberger: Desenvolvimento, Documentação
- Leonardo Quatrin Campagnolo: Desenvolvimento, Documentação, Suporte
- Yuri Kunde Schlesner: Desenvolvimento, Documentação, Suporte
- Bernardo Henz: Beta-testing

\subsection prev_versions Versões Anteriores

- SCV 1.0: Celito Much Felipetto e Vinicius Gottin
- SCV 2.0: Eduardo Speroni e Bernardo Henz

*/


//|||||||||||||||||||||||||||||||||||||||||||||||

#ifdef _WIN32
   #ifdef _MSC_VER
      #pragma warning(disable:4018)
   #endif // _WIN32
#endif // _MSC_VER

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "stdafx.h"

#include "Kernel.h"

#include "Button.h"
#include "Canvas.h"
#include "CheckBox.h"
#include "ColorPicker.h"
#include "ComboBox.h"
#include "ContextMenu.h"
#include "FileOpen.h"
#include "GlslShader.h"
#include "Image.h"
#include "InternalFrame.h"
#include "Label.h"
#include "Mathematic.h"
#include "MenuBar.h"
#include "ProgressBar.h"
#include "RadioButton.h"
#include "ScrollPane.h"
#include "Separator.h"
#include "Singleton.h"
#include "Slider.h"
#include "StateButton.h"
#include "TabbedPane.h"
#include "Table.h"
#include "util.h"
#include "TreeView.h"

#include "GroupLayout.h"
#include "SequentialGroup.h"
#include "ParallelGroup.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif // __SCV_H__
