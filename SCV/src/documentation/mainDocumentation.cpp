/*!
\mainpage SCV Documentation

O SCV é uma API (Application Programming Interface) de facilitação na construção de interfaces de usuário (GUI - Graphic User Interface), orientada ao uso de um programador com experiência na linguagem de programação C++. 

O SCV está implementado sobre a API gráfica OpenGL. Existe uma estrutura hierárquica de componentes, onde cada componente é responsável por desenhar os componentes contidos nele. O componentes utilizam a fucionalidade de scissors do OpenGL para fazer a limitação da área de desenho para apenas o retângulo que engloba o componente, além de fazer o desenho dele mesmo, utilizando mapas de textura, compartilhados por todas as instâncias do mesmo tipo de componente, e fontes, representadas com uma textura contendo todos os caracteres, compartilhada em nível global. Esquemas de cor são implementados modulando-se a cor das texturas dos componentes. A interação entre componentes e o código do usuário da biblioteca faz-se utilizando callbacks, presentes como funções virtuais nos componentes, que devem ser herdados.

Aqui você irá encontrar a documentação de todos componentes e funcionalidades oferecidas. São disponibilizados três manuais para o usuário:

- \subpage scv "SCV"
- \subpage desinger "SCV Desinger"
- \subpage freefrom "SCV Free Form Designer"


\section ide IDEs Suportadas
- Microsoft Visual Studio 2010
- g++ / makefile

A documentação atualizada poderá ser acessada através do endereço: http://www-usr.inf.ufsm.br/~pozzer/scv <br/>
A última versão da biblioteca poderá sempre ser encontrada em: http://www-usr.inf.ufsm.br/~pozzer/scv/scv_4.0.rar

\section home Get Started!

- Para acessar a documentação do SCV presente na pasta "documentation" execute o arquivo "Documentation.bat".
- Para visualizar vários exemplos utilizando o SCV e demonstrando suas funcionalidades execute o arquivo "SCV_Examples.bat".
- Para acessar o InterfaceDesginer execute o "InterfaceDesigner.bat", nele o usuário pode graficamente criar sua Interface, através de DragAndDrop, e gerar o código SCV correspondente para o arquivo "interface.cpp".


\section credits Créditos

- Prof. Cesar Tadeu Pozzer: Coordenador e Idealizador do Projeto
- Cicero Augusto de Lara Pahins: Desenvolvimento, Documentação
- Frederico Artur Limberger: Desenvolvimento, Documentação
- Leonardo Quatrin Campagnolo: Desenvolvimento, Documentação, Suporte
- Yuri Kunde Schlesner: Desenvolvimento, Documentação, Suporte
- Tiago Boelter Mizdal: Desenvolvimento, Documentação
- Eduardo Speroni  (versões anteriores do scv)
- Bernardo Henz
- Celito Much Felipetto 
- Vinicius Gottin

*/

/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************

/*! \page scv SCV
A estrutura de arquivos do SCV é apresentada na seguinte figura.  

 \image html images/diretorio.png

- Documentation: contém páginas HTML gerados pelo Doxygem com a documentação da API, e também manuais de uso da API e das ferramentas
- Lib: contém as libs usadas para compilar o SCV e as libs geradas a partir da compilação do SCV
- Include: os arquivos de cabeçalho para compilar o SCV. 
- SCV: contém todo o código fonte do SCV. Quando compilado, geras as libs (scv-debub e scv-release) que são necessárias na compilação dos demais projetos (os designers de interface e os exemplos)
- ExportedSource: armazena os arquivos gerados pelos designers de Interface
- UserProject: Pasta que contém um projeto para compilação de aplicativos desenvolvidos com a API
- InterfaceDesigner: contém o código do SCVDesigner, uma aplicação desenvolvida para criação de interfaces com componentes redimensionáveis . Para maiores detalhes da aplicação, consultar o manual
- FreeFormInterfaceDesigner: semelhante ao InterfaceDesigner, é um aplicação que permite a construção de interfaces gráficas do SVC que não tem o recurso de redimensionamento de componentes. 
- ExportedSource: projeto para compilação dos códigos-fonte gerados pelas aplicações InterfaceDesigner e FreeFormInterfaceDesigner. 
- SCVExamples: Contém vários exemplos de aplicativos desenvolvidos com a API SCV, destacando o uso de widgets. 


O projeto scv.sln engloba 5 projetos Microsoft Visual Studio 10, que são descritos na sequencia. 
•	InterfaceDesigner: contém o código do SCVDesigner, uma aplicação desenvolvida para criação de interfaces com componentes redimensionáveis . Para maiores detalhes da aplicação, consultar o manual
•	FreeFormInterfaceDesigner: semelhante ao InterfaceDesigner, é um aplicação que permite a construção de interfaces gráficas do SVC que não tem o recurso de redimensionamento de componentes. 
•	ExportedSource: projeto para compilação dos códigos-fonte gerados pelas aplicações InterfaceDesigner e FreeFormInterfaceDesigner. 
•	SCV: projeto que contém todo o código da API SCV. Quando executado, gera as libs do SCV. 
•	SCVExamples: Contém vários exemplos de aplicativos desenvolvidos com a API SCV, destacando o uso de widgets. 

 \image html images/sln.png

 Para compilar uma aplicação com o SCV deve-se adicionar 4 bibliotecas: Freeglut.lib, Freeimage.lib, Glew32.lib e Scv-debub.lib (ou scv-release.lib). Na interface do Visual Studio 2010, isso pode ser feito nos campos properties/VC++ Directories e  properties/Linker/Input, como mostrado nas seguintes figuras. Esta configuração leva em consideração a organização de pastas do SCV. Isso pode ser modificado livremente pelo programador. 

 \image html images/include.png
 \image html images/lib.png

Para rodar os demos ou programas desenvolvidos no VS2010 em máquinas que não tenham o VS, deve-se instalar também o Microsoft Visual C++ 2010 Redistributable. Sem ele, vem um aviso que faltam dlls para execução, mais especificamente as MSVCP100.dll e MSVCR100.dll.

O instalador da runtime pode ser baixado da Microsoft através deste link: http://www.microsoft.com/downloads/en/confirmation.aspx?familyid=A7B7A05E-6DE6-4D3A-A423-37BF0912DB84&displaylang=en

Outra opção é simplesmente copiar essas duas DLLs do seu computador com VS para a pasta do exe. (Ficam em C:\\Windows\\System32\\msvcp100.dll e C:\\Windows\\System32\\msvcr100.dll)

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
/*************************************************************************************

 
/*! \page designder SCV Designer 

O InterfaceDesigner é uma aplicação que foi desenvolvida sobre a API SCV para agilizar a construção de interfaces gráficas usando a API SCV. Ela deve proporcionar ao usuário a possibilidade de arranjar os componentes gráficos da API SCV de maneira visual, oferecendo recursos para adição ou remoção de objetos, exportação do código resultante e alinhamento automático de componentes relacionados por diferentes esquemas de organização. Ele também pode ser usado como ferramenta para estudo das funcionalidades e sintaxe de código do SCV, ou como ferramenta para construção da base da aplicação para posterior expansão manual com demais componentes.

Para maiores detalhes sobre a implementação do SCV e do SCV Designer, consulte [1].

\section designinterface Interface

O SCV Designer apresenta uma estrutura modularizada, que possibilita a construção iterativa da interface do software. Ela apresenta 4 elementos básicos, como podem ser visualizados na seguinte Figura.

 \image html images/designer.png 

- DesignPreview: responsável pela pré-visualização em tempo real de interfaces produzidas pelo ambiente a partir da construção de uma visualização aproximada, a qual busca refletir o resultado da exportação do trabalho realizado;

- GroupLayout: responsável pela construção hierárquica de agrupamentos lógicos para arranjo de componentes da API SCV;

- ObjectEditor: responsável pela edição de variáveis e características, as quais estarão presentes nas exportações do ambiente, de componentes da API SCV;

 \image html images/custonclass.png

- Code Viewer: responsável pela exportação do resultado produzido pelo ambiente de acordo com parâmetros do usuário. São sempre exibidos 5 arquivos de código fonte em Linguagem C++ que representam os componentes e regras de arranjo de componentes.


\section Criação de Interfaces

Para se criar uma interface gráfica no SCV Designer deve-se realizar 4 tarefas:
1.	Criação dos componentes (widgets) que farão parte da interface, como Botões e Textfields. Os componentes criados podem ser visualizados de duas maneiras, como mostrado na figura;

 \image html images/objects.png 

2.	Selecionar os layouts vertical e horizontal (Group Layout);

 \image html images/group.png 

3.	Adição de grupos Paralelos e sequenciais (ParallelGroupPanel e SequentialGroupPanel) aos Group Layouts;

 \image html images/panel.png 

4.	Adição dos componentes aos grupos. 

\image html images/adicao.png 


O SCV permite a definição de layouts nos eixos horizontal e vertical. Cabe a usuário definir quais layouts vão ser usados. Esses dois eixos devem ser definidos caso se deseje que os componentes tenham comportamentos de redimensionamento nos dois eixos.

- Horizontal Group Layout: Define a propriedade de redimensionamento e distribuição dos componentes no eixo horizontal. 
- Vertical Group Layout: Define a propriedade de redimensionamento e distribuição dos componentes no eixo horizontal. 

Em cada Group Layout pode-se adicionar GroupsPanels, que podem ser sequenciais ou paralelos (ParallelGroupPanel e SequentialGroupPanel). Um grupo sequencial permite que componentes sejam adicionados um ao lado do outro (no Horizontal Group Layout) ou um abaixo no outro (no Vertical Group Layout). Grupos paralelos permitem criar linhas (no Horizontal Group Layout), ou colunas (no Vertical Group Layout) que dividem a tela, para facilitar a distribuição de widgets. Pode-se fazer agrupamentos hierárquicos destes componentes.  

\section Exemplos de Interfaces

- Exemplo 1: A Figura apresenta (a) Vertical e Horizontal Group Layouts  b) Somente Horizontal Group Layout) uma interface que possui dois botões. Esses botões devem ser configurados para sempre ocuparem toda a área da janela, ou seja, todos os espaços vertical e horizontal. Para isso, deve-se usar os Vertical e Horizontal Group Layouts. 

\image html images/exemplo1.png 



*/

/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************

/*! \page freeform SCV Free Form Designer 


*/

