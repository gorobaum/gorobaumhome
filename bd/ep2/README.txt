Alunos:
    Nome                        NUSP
    Thiago de Gouveia Nunes     6797289
    Wilson Kazuo Mizutani       6797230

<<< MAC0426 - Primeiro Semestre de 2011 - Prof. Marcelo Finger >>>

    Segundo exercício para nota - Modelagem de um Banco de Dados

- Primeira parte: Telas do sistema

    Como o Pencil gera uma pasta junto com o arquivo HTML quando exportamos as telas, deixamos os
dois (o HTML e a pasta gerados) juntos na pasta 'telas_do_sistema', ao invés de só o arquivo HTML,
como pedia o enunciado.
    A maioria das telas têm comentários anexados. Eles explicam como funcionam as telas.
    Pode ser que algum link das telas não esteja funcionando direito, mas como tem os comentários,
não é nada que comprometa a compreensão delas.

- Segunda parte: MER da Biblioteca

    Usamos o Dia para fazer o diagrama, com aquela notação que não é a dos slides (a que o
professor mostrou na lousa). Como não tinha ela por padrão no Dia, tivemos que dar uma contornada
e por isso não ficou muito bonito.
    O diagrama está no arquivo 'mer_da_biblioteca.pdf'.
    Algumas obsercações sobre o nosso modelo:
        >   Consideramos que edições diferentes de um mesmo livro são livros diferentes no banco
            de dados, e portanto terão IDs diferentes.
        >   Consideramos que não existem dois livros com mesmo nome, autor e edição.
        >   Consideramos que não existem dois periódicos com mesmo nome e editora.
        >   Consideramos que não existem dois artigos com mesmo nome e mesmo autor numa mesma
            edição de um periódico.

- Terceira parte: Esquema da Biblioteca e depências funcionais

    O esquema e as dependências funcionais de cada relação estão descritos no arquivo
'esquema_bd.txt'. Não usamos notação SQL, mas tentamos ser o mais claros possíveis. Algumas
observações sobre a notação estão nesse mesmo arquivo.




