/*!
\mainpage SCV Documentation

O SCV é uma API (Application Programming Interface) de facilitação na construção de interfaces de usuário (GUI - Graphic User Interface), orientada ao uso de um programador com experiência na linguagem de programação C++. O SCV está implementado sobre a API gráfica OpenGL. Existe uma estrutura hierárquica de componentes, onde cada componente é responsável por desenhar os componentes contidos nele. O componentes utilizam a fucionalidade de scissors do OpenGL para fazer a limitação da área de desenho para apenas o retângulo que engloba o componente, além de fazer o desenho dele mesmo, utilizando mapas de textura, compartilhados por todas as instâncias do mesmo tipo de componente, e fontes, representadas com uma textura contendo todos os caracteres, compartilhada em nível global. Esquemas de cor são implementados modulando-se a cor das texturas dos componentes. A interação entre componentes e o código do usuário da biblioteca faz-se utilizando callbacks, presentes como funções virtuais nos componentes, que devem ser herdados.

São disponibilizados três manuais para o usuário:

- \subpage scvManual "SCV"
- \subpage designer "SCV Designer"
- \subpage freeform "SCV Free Form Designer"


\section ide Compiladores suportados
- g++
- VisualC++ 2010

A última versão do SCV está disponível em: 
- http://www-usr.inf.ufsm.br/~pozzer/scv/download
- github

\section credits Créditos

Este projeto foi desenvolvido na Universidade Federal de Santa Maria (UFSM), entre 2007 e 2012, pelos seguintes membros:
 
- Prof. Cesar Tadeu Pozzer: Coordenador e Idealizador do Projeto
- Leonardo Quatrin Campagnolo: Desenvolvimento, Documentação, Suporte
- Yuri Kunde Schlesner: Desenvolvimento, Documentação, Suporte
- Cicero Augusto de Lara Pahins: Desenvolvimento, Documentação
- Tiago Boelter Mizdal: Desenvolvimento, Documentação
- Frederico Artur Limberger: Desenvolvimento, Documentação

Desenvolvedores das versões anteriores do SCV:
- Eduardo Speroni
- Bernardo Henz
- Celito Much Felipetto 
- Vinicius Gottin

Pesquisas Iniciais sobre APIs Gráficas
- Vitor Conrado Faria Gomes
- Franciso Tiago Avelar
*/

/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/**************************************************************************************/

/*! \page scvManual SCV
A estrutura de arquivos do SCV é apresentada na seguinte figura.  

 \image html images/diretorios.png

- SCV: contém todo o código fonte do SCV. Quando compilado, gera as libs (scv-debug e scv-release) que são necessárias para compilação dos demais projetos (os designers de interface e os exemplos).
- Include: contém os arquivos de cabeçalho do SCV. 
- Lib: contém as libs usadas para compilar o SCV (glew, freeglut, freeimage e openGL) e as libs geradas a partir da compilação do SCV.
- InterfaceDesigner: contém o código do SCVDesigner, uma aplicação desenvolvida para criação de interfaces com componentes redimensionáveis. Para maiores detalhes da aplicação, consultar o manual.
- FreeFormInterfaceDesigner: semelhante ao InterfaceDesigner, é um aplicação que permite a construção de interfaces gráficas do SVC que não tem o recurso de redimensionamento de componentes. 
- Documentation: contém páginas HTML geradas pelo Doxygen com a documentação da API, e também manuais de uso da API e das ferramentas de geração de interfaces.
- UserProject: pasta que contém um projeto para compilação de aplicativos desenvolvidos com a API
- SCVExamples: contém vários exemplos de aplicativos desenvolvidos com a API SCV que fazem o uso de widgets. 

\section linux Linux - Makefile

Para compilar a biblioeca no Linux, é necessário instalar os pacotes de desenvolvimento da FreeImage, Freeglut e GLEW, além das bibliotecas do OpenGL (do Projeto Mesa ou de alguma implementação de proprietária). Após, basta executar o make no diretório raiz do projeto. Para realizar uma build otimizada use 'make release'. Os binários serão colocados no diretório bin/.

Os 4 módulos principais estão divididos em diretórios separados. O makefile do diretório raiz automaticamente faz build de todos os módulos. Regras específicas de cada módulo estão no arquivo rules.mk presente em cada diretório, e os arquivos Makefile e common-rules.mk contém o framework geral de compilação.

O diretório userProject tem makefile próprio e é compilado independentemente do resto do código. Ele pode ser usado como modelo para seus projetos que usam o SCV.

\section windows Windows - Microsoft Visual Studio

A solution scv.sln engloba 4 projetos Microsoft Visual Studio 10, que compilam os 4 componentes executáveis do projeto.

 \image html images/sln.png
  
 Para compilar cada projeto deve-se definí-lo como projeto de inicialização ("Startup project").
 
  \image html images/startupproject.png
 
 Para compilar uma aplicação com o SCV deve-se adicionar 5 bibliotecas: Freeglut.lib, Freeimage.lib, Glew32.lib, openGL.lib e scv-debug.lib (ou scv-release.lib). Na interface do Visual Studio 2010, isso pode ser feito nos campos properties/VC++ Directories e  properties/Linker/Input, como mostrado nas seguintes figuras. Esta configuração leva em consideração a organização de pastas do SCV. Isso pode ser modificado livremente pelo programador. 

 \image html images/include.png
 
 <BR>
 
 \image html images/lib.png

Para rodar os demos ou programas desenvolvidos no VS2010 em máquinas que não tenham o VS, deve-se instalar também o Microsoft Visual C++ 2010 Redistributable. Sem ele, vem um aviso que faltam dlls para execução, mais especificamente as MSVCP100.dll e MSVCR100.dll.

O instalador da runtime pode ser baixado da Microsoft através deste link: http://www.microsoft.com/downloads/en/confirmation.aspx?familyid=A7B7A05E-6DE6-4D3A-A423-37BF0912DB84&displaylang=en

Outra opção é simplesmente copiar essas duas DLLs do seu computador com VS para a pasta do exe. (Ficam em C:\\Windows\\System32\\msvcp100.dll e C:\\Windows\\System32\\msvcr100.dll)

Também existe um projeto standalone "userProject" para compilação de projetos desenvolvidos pelo usuario, com o uso das ferramentas de geração automática de código (InterfaceDesigner e FreeFormInterfaceDesigner) 
 
 \image html images/sln2.png



\section references Trabalhos Publicados


PAHINS, C. A. L. Ambiente para construção de Interfaces gráficas de usuário com o SCV. Trabalho de Graduação em Ciência da Computação, UFSM, 2011.

PAHINS, C. A. L.; POZZER, C. T. SCV - Simple Components for Visual. Jornada Acadêmica Integrada da Universidade Federal de Santa Maria, Santa Maria, RS, 2011.

PAHINS, C. A. L.; LIMBERGER, F. A.; HENZ, B.; SPERONI, E. A.; GOTTIN, V. M.; POZZER, C. T. Uma API Livre para Composição de GUI em Aplicativos Gráficos. Fórum Internacional de Software Livre 2010 - Workshop de Software Livre, Porto Alegre, RS, 2010.

PAHINS, C. A. L.; LIMBERGER, F. A.; POZZER, C. T. Uma Abordagem Gráfica Utilizando o SCV. Jornada Acadêmica Integrada da Universidade Federal de Santa Maria, Santa Maria, RS, 2010.

PAHINS, C. A. L.; LIMBERGER, F. A.; HENZ, B.; POZZER, C. T. SCV: uma ferramenta para programação de aplicativos de interfaces gráficas. Congresso Regional de Iniciação Científica e Tecnológica em Engenharia, Rio Grande, RS, BR, 2010.

LIMBERGER, F. A.; PAHINS, C. A. L.; POZZER, C. T. SCV: uma ferramenta para programação de aplicativos de interfaces gráficas. Jornada Acadêmica Integrada da Universidade Federal de Santa Maria. Santa Maria, Santa Maria, RS, BR, 2010.

AVELAR, F. T.; GOMES, V. C. F.; POZZER, C. T. Estudo Comparativo de Bibliotecas Gráficas Integradas com OpenGL. XXII Congresso Regional de Iniciação Científica e Tecnológica em Engenharia - CRICTE, Passo Fundo, RS, 2007.

AVELAR, F. T.; GOMES, V. C. F.; POZZER, C. T. Estudo Comparativo de Bibliotecas Gráficas Integradas com OpenGL. XXII Congresso Regional de Iniciação Científica e Tecnológica em Engenharia - CRICTE, Passo Fundo, RS, 2007.

  
*/

 /*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/**************************************************************************************/

 
/*! \page designer SCV Designer

O InterfaceDesigner é uma aplicação que foi desenvolvida sobre a API SCV para agilizar a construção de interfaces gráficas usando a API SCV. Ela deve proporcionar ao usuário a possibilidade de arranjar os componentes gráficos da API SCV de maneira visual, oferecendo recursos para adição e remoção de objetos, geração do código resultante e alinhamento automático dos componentes relacionados por diferentes esquemas de organização. Ele também pode ser usado como ferramenta para estudo das funcionalidades e sintaxe de código do SCV, ou como ferramenta para construção da base da aplicação para posterior expansão manual com demais componentes.

Para maiores detalhes sobre a implementação do SCV e do SCV Designer, consulte (Pahins, 2011) no tópico "Trabalhos publicados" na página do manual do SCV.

\section designinterface Interface

O SCV Designer apresenta uma estrutura modularizada que possibilita a construção interativa da interface do software. Ela apresenta 4 elementos básicos que podem ser visualizados na seguinte figura.

 \image html images/designer.png 

- DesignPreview: responsável pela pré-visualização em tempo real de interfaces produzidas pelo ambiente a partir da construção de uma visualização aproximada, a qual busca refletir o resultado da exportação do trabalho realizado;

- GroupLayout: responsável pela construção hierárquica de agrupamentos lógicos para arranjo de componentes da API SCV;

- ObjectEditor: responsável pela edição de variáveis e características, as quais estarão presentes nas exportações do ambiente, de componentes da API SCV;

 \image html images/custonclass.png

- Code Viewer: responsável pela geração do código produzido pelo ambiente de acordo com parâmetros do usuário. São sempre exibidos 5 arquivos de código fonte em Linguagem C++ que representam os componentes e regras de arranjo de componentes.


\section criacaoInterface Criação de Interfaces

Para se criar uma interface gráfica no SCV Designer deve-se realizar 4 tarefas:
- Criação dos componentes (widgets) que farão parte da interface, como Botões e Textfields. Os componentes criados podem ser visualizados de duas maneiras, como mostrado na figura;

 \image html images/objects.png 

- Selecionar os layouts vertical e horizontal (Group Layout);

 \image html images/group.png 

- Adição de grupos Paralelos e sequenciais (ParallelGroupPanel e SequentialGroupPanel) aos Group Layouts;

 \image html images/panel.png 

- Adição dos componentes aos grupos. 

\image html images/adicao.png 


O SCV permite a definição de layouts nos eixos horizontal e vertical. Cabe a usuário definir quais layouts vão ser usados. Esses dois eixos devem ser definidos se for necessário que os componentes tenham comportamentos de redimensionamento nos dois eixos.

- Horizontal Group Layout: Define a propriedade de redimensionamento e distribuição dos componentes no eixo horizontal. 
- Vertical Group Layout: Define a propriedade de redimensionamento e distribuição dos componentes no eixo vertical. 

Em cada Group Layout pode-se adicionar GroupsPanels, que podem ser sequenciais ou paralelos (ParallelGroupPanel e SequentialGroupPanel). Um grupo sequencial permite que componentes sejam adicionados um ao lado do outro (no Horizontal Group Layout) ou um abaixo no outro (no Vertical Group Layout). Grupos paralelos permitem criar linhas (no Horizontal Group Layout), ou colunas (no Vertical Group Layout) que dividem a tela, para facilitar a distribuição de widgets. Pode-se fazer agrupamentos hierárquicos destes componentes.  

\section exemploInteface Exemplos de Interfaces

- Exemplo 1: Apresenta uma interface que possui dois botões. Esses botões devem ser configurados para sempre ocuparem toda a área da janela, ou seja, todos os espaços vertical e horizontal. Para isso, deve-se usar os Vertical e Horizontal Group Layouts. 

\image html images/exemplo1a.png
<center>Vertical e Horizontal Group Layouts</center>
<BR>

\image html images/exemplo1b.png 
<center>Somente Horizontal Group Layout</center>
<BR>

\image html images/exemplo1c.png

Como a interface possui apenas dois botões, dispostos um ao lado do outro, pode-se criar apenas três GroupPanels: um sequencial no Horizontal Group Layout e dois paralelos no Vertical Group Layout.

O grupo sequencial faz com que um botão fique ao lado do outro (horizontalmente) e ocupe todo o espaço em largura da tela, e o grupo paralelo faz o redimensionamento na vertical. Caso não seja especificado o layout Vertical, os botões não apresentam o redimensionamento vertical, e ficam com a altura padrão definida.


 
- Exemplo 2: Apresenta uma interface com 4 botões, dispostos em linhas e colunas. 

\image html images/exemplo2b.png 
<center>Somente Horizontal Group Layout</center>
<BR>

\image html images/exemplo2a.png 
<center>Vertical e Horizontal Group Layouts</center>
<BR>

\image html images/exemplo2c.png 

Para o Horizontal Group Layout, deve-se inicialmente definir um grupo paralelo que vai englobar dois grupos sequenciais, de modo a formar duas fileiras sequenciais e paralelas de botões. Para o Vertical Group Layout, deve-se ter um grupo paralelo que possui dois grupos sequencias. Caso não fosse usado o Vertical Group Layout, as duas fileiras de botões horizontais ficariam sobrepostas, sendo exibido apenas a segunda fileira. Além disso, por não haver redimensionamento vertical, os botões ocupariam a altura padrão definida. 


- Exemplo 3: Este exemplo é semelhante ao caso anterior, porém possui apenas 1 botão na esquerda e dois a direita. 

\image html images/exemplo3a.png 
<center>Button 0 adicionado nos dois Group Layout</center>
<BR>

\image html images/exemplo3b.png 
<center>Button 0 adicionado apenas no horizontal Group Layout</center>
<BR>
\image html images/exemplo3c.png 

Como o botão da esquerda deve ocupar todo o lado da janela, deve-se mudar a organização dos Layouts. Para este exemplo foi criado um Grupo sequencial no Horizontal Group Layout, adicionado de dois grupos paralelos. O Layout Vertical é igual ao exemplo anterior. Para se obter o resultado da segunda figura, deve-se manter o mesmo layout, porém o "Button 0" deve ser adicionado somente ao Horizontal Group Layout. Isso faz com que ele  não tenha redimensionamento no eixo Vertical. 


\section geracao Geração de Código

O scv designer gera código a partir da especificação dos componentes e do layout. São gerados sempre 5 arquivos em linguagem C++. Esse código pode ser visualizado na própria interface do SCV Designer ou exportado para arquivos fonte (Menu Code):

\image html images/code.png 

- application.h: protótipos das callbacks e definição da classe application.
- application.cpp: Definição e inicialização dos componentes, definição dos layouts.
- main.cpp: inicialização do scv e execução. 
- widgets.h: protótipos das callbacks dos componentes. Deve-se habilitar a opção "Generate Custom Class" para criar classes derivadas de cada widget.
- widgets.cpp: implementação das callbacks dos componentes.

\image html images/custonclass.png


*/

/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/**************************************************************************************/

/*! \page freeform SCV Free Form Designer 

O SCV Free Form Designer é uma aplicação opensource que foi desenvolvida sobre a API SCV para agilizar a construção de interfaces gráficas usando a API SCV. Ela deve proporcionar ao usuário a possibilidade de arranjar os componentes gráficos da API SCV de maneira visual, oferecendo recursos para adição e remoção de objetos e geração do código resultante. Ele também pode ser usado como ferramenta para estudo das funcionalidades e sintaxe de código do SCV, ou como ferramenta para construção da base da aplicação para posterior expansão manual com demais componentes.

\section Interface

O SCV Free Form Designer apresenta uma estrutura simples, que possibilita a construção interativa da interface do software. Ela possui apenas uma janela com um painel, onde é possível incluir componentes. A janela do SCV não possui um tamanho fixo, é possível modificar o tamanho da janela arrastando suas bordas, para melhor se adequar a interface.

\image html images/freeform.png


\section criacao Criação de Interfaces

Para criar uma interface no SCV Free Form Designer deve-se utilizar o menu, clicando com o botão direito na tela. O menu possui cinco opções que estão relacionados com a criação da interface: "Add Panel", "Add Component", "Clear Interface", "Generate Code" e "Open".

\image html images/menu.png

A opção "Add Panel" é usado para adicionar painéis na interface, os painéis são utilizados para agrupar componentes (widgets). Existem cinco tipos de painéis, como uma imagem ou um simples painel. 

\image html images/menu.png

Dentro de um painel é possível adicionar outros painéis ou componentes, os quais não irão aparecer fora do painel.

\image html images/remove.png

Ao mover o painel, todos os componentes que estão em seu interior irão segui-lo. Clicando com o botão direito do mouse, pode-se remover componentes da interface. 



Ao clicar na opção "Add Component" irá aparecer um sub-menu com uma lista de todos os componentes.

\image html images/submenu.png

Ao clicar em algum componente ele será adicionado à tela na posição onde o mouse estava ao clicar com o botão direito, e estará vinculado ao componente superior na hierarquia de componentes que já foram adicionados à interface. Por exemplo, se o menu for aberto sobre um Panel, o novo componente será vinculado a este. Para mover um componente de posição, é preciso clicar no componente e arrastá-lo. É possível modificar o tamanho de alguns componentes clicando em suas bordas e arrastando. Alguns componentes possuem uma Label, e ao adicioná-los aparecerá uma caixa de texto onde deve ser escrito aquilo que se deseja que apareça no componente.

\image html images/caixa.png

A opção "Clear Interface" irá remover todos os componentes e painéis da tela, restando apenas o painel inicial.

\section geracao Geração de Código

O SCV Free Form designer gera código a partir dos componentes incluídos na interface. Para gerar o código é necessário clicar na opção "Generate Code...". São gerados sempre três arquivos em linguagem C++, que são os seguintes:
- application.h: protótipos das callbacks e definição da classe application.
- application.cpp: Definição e inicialização dos componentes.
- main.cpp: inicialização do scv e execução. 

Os arquivos são criados no mesmo local onde a aplicação foi executada. 







*/

