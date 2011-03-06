/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

Esse EP foi desenvolvido em Linux.

Esse EP tem seu proprio Makefile. Para compilar o EP, basta escrever Make no Ter
minal do Linux dentro da pasta em que o EP se encontra.

Para executa-lo, digite ./EP2 <argumentos> no Terminal. O argumento pode ser o 
nome de um livro ou um arquivo com o nome de varios livros, com o nome do arquivo
precedido de -f.

As estruturas de dados deste EP estao organizadas da seguinte maneira:

	1 - BST : Uma BST e inicializada no inicio do processo do EP. Ela sera usada para
	guardar cada palavra de cada livro. Somente uma palavra e guardada, por exemplo:
	Se a palavra Bola existe no Livro 1 e no Livro 2, existira somente um NODE
	na BST, e ela ira guardar a informacoes dos dois livros.
	Cada NODE da BST tem 2 campos, o primeiro ( o Campo KEY ), guarda as palavras
	dos livros. o segundo ( o Campo Occurence ) usa uma lista ligada para guardar
	as informacoes sobre cada palavra, como quais livros elas aparecem e em quais
	linhas. A lista ligada sera melhor explicada abaixo. 
	O algoritmo de preenchimento da BST e feito da seguinte maneira:
	A cada livro recebido pelo EP, o algoritmo e executado. Ele pega caracter por
	caracter do arquivo do livro, identificando as palavras. A cada palavra nova,
	um novo NODE e colocado na BST, representando essa palavra. Quando uma palavra
	ja existe, a nova informacao e colocada na BST.
	
	2 - Lista Ligada : As listas ligadas encontradas nos NODES da BST do EP sao
	as responsaveis por armazenar as informacoes sobre as palavras a elas associ
	adas. Elas guardam o a linha do livro, o livro e um offset chamado de pLine
	que e usado para achar a linha que deve ser imprimida no livro.
	
	3 - Pilha : A pilha e usada no EP para implementar uma RPN ( Reverse Polish
	Notation ). Quando uma pesquisa e feita, a lista ligada associada com o termo
	de pesquisa e empilhado na PilhaRPN para posterior visualizacao ou para 
	efetuar as operacoes da RPN com outras listas. A PilhaRPN e implementada
	usando uma Lista Ligada.
	
O loop Principal do EP e o seguinte:

	Primeiro Passo - O programa inicializa a BST e a PilhaRPN.
	
	Segundo Passo - Se o programa recebeu algum argumento inicial, ele o trata.
	Se so um livro foi passado, o mesmo e adicionado na BST, e se um arquivo de
	livros e passado, cada livro do arquivo e adicionado na BST.
	
	Terceiro Passo - Aqui o prompt do EP e iniciado. Com o prompt podemos adicio
	nar livros, remover livros, checar o numero de pesquisar na pilha bem como
	opera-las, realizar novas pesquisas, imprimir a ultima pesquisa ou operacao
	feita, e sair do programa.
	
	Quarto Passo - Quando o programa e fechado, o programa libera a memoria da 
	BST e da PilhaRPN e se fecha.
	
Todos os algoritmos com maior complexidade estao comentados nos seus respectivos
arquivos.
