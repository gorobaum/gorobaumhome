/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP3.c

Aluno:									Numero USP:
Thiago G. Nunes							6797289

19/06/2010

***********************************************************************************************************/

#include <math.h>
#include "compress.h"
#include "trie.h"

#define ZEROASCII 48
#define BUFFER_SIZE 256

/*************************************************
           Funcoes Auxiliares Gerais
*************************************************/

/* Funcao que preenche um Buffer com 256 posicoes com Bits do arquivo File. Ela
   pega um char do arquivo e usa operacoes bit-a-bit para colocar seus 8 bits
   no Buffer. Ela retorna o tamanho real lido, ja que no final do arquivo nao
   ha garantia que possam ser lidos 256 Bits. */
int GetBinary( FILE* File, int *Buffer )
{
    int Get, Bit, i, Aux, Cont = 0, RealSize = 0;
    
    Get = fgetc( File );
    while ( !feof(File) )
    {
    	for ( i = 0; i <= 7; i++ )
		{
			Aux = Get;
			Bit = ( (Aux >> ( 7 - i ) ) & 1 );
			if ( Cont < BUFFER_SIZE ) 
			{
				Buffer[Cont] = Bit;
				Cont++;
				RealSize++;
			}
		}
		if ( Cont >= BUFFER_SIZE ) break;
		Get = fgetc( File );
    }
    return RealSize;
}

/* Esta funcao transforma um Buffer que representa um numero binario de tamanho
   Size em um decimal, retornando o decimal calculado. */
int BitToDecimal( int* Buffer, int Size )
{
    int Cont, Decimal;
    
    for ( Cont = 0, Decimal = 0; Cont < (Size - 1); Cont++ ) 
    {
        Decimal+= Buffer[Cont]*pow( 2, Size - Cont - 2 );
    }
    return Decimal;
}

/* Esta funcao e a responsavel por escrever qualquer saida para o arquivo de sa
   ida ( Out ). Ela usa a funcao puts para escrever o Buffer no arquivo Out. */
void WriteOnOut( char* Buffer, FILE* Out )
{
    fputs( Buffer, Out );
    free(Buffer);
}

/* Esta funcao transforma um Buffer preenchido de Bits em uma String. Para tal,
   e preciso se preocupar se ela tem o tamanho necessario para escrever n chars,
   ou seja, que o tamanho do Buffer seja multiplo de 8. Se ele for, alocamos
   Size/8 + 1 chars, e se nao alocamos Size/8 + 2 chars. Um char extra para cada
   caso para colocarmos o '\0' no String e um extra no ultimo caso pois podemos
   escrever mais um char com o que "sobra" do tamanho modulo 8. A partir dai a 
   funcao calcula o valor dos chars e coloca na String. O primeiro IF do loop ve
   rifica se caimos no caso em que o buffer nao e multiplo de 8 e se nao teremos
   como escrever o ultimo char, pois nao temos 8 Bits. A partir disso ele coloca
   1 nos Bits que faltam e termina de escrever o char. O segundo IF verifica 
   quando um char ja foi escrito e o coloca em String. O ultimo IF calcula o valor
   do novo char. No final a funcao coloca o '\0' da String e retorna a mesma. */
char* BufferToString( int* Buffer, int Size )
{
    int Cont, Offset = 0, StrCont, AuxCont;
    char *String, AuxChar = 0;
    
    if ( Size%8 == 0 ) String = malloc( (Size/(8 * sizeof(char))) + sizeof(char));
    else String = malloc( (Size/(8 * sizeof(char))) + 2*sizeof(char));
    
    for ( Cont = 0, StrCont = 0; Offset < Size; Cont++ )
    {
        if ( Size%8 != 0 && Offset + 8 >= Size )
        {
            for ( AuxCont = 8 - ( Size - Offset ); AuxCont >= 0; AuxCont--, Cont++ ) 
                AuxChar += 1*pow( 2, (7 - Cont) );
            for ( AuxCont = Cont; AuxCont <= 7; AuxCont++ )
                AuxChar += Buffer[Offset+Cont]*pow( 2, (7 - AuxCont) );
            String[StrCont] = AuxChar;
            break;
        }
        if ( Cont > 7 )
        {
            Cont = 0;
            Offset += 8;
            String[StrCont] = AuxChar;
            StrCont++;
            AuxChar = 0;
        }
        if ( Offset + Cont < Size ) AuxChar += Buffer[Offset+Cont]*pow( 2, (7 - Cont) );
    }
    String[StrCont] = 0;
    return String;
}

/* Esta funcao calcula o numero de Bits para representar o decimal Number em
   binario.  */
int SizeinBin( int Number )
{
    int Cont = 0;
    for ( Cont = 0; Number; Cont++ ) Number >>= 1;
    return Cont;
}

/*************************************************
    Funcoes Auxiliares para Compressao
*************************************************/

/* Esta funcao e responsavel por codificar o Par do no Node. Ela calcula o tama
   nho do numero binario para a codificacao e aloca um vetor com esse tamanho, e
   tambem o tamanho do indice que esta no Par desse Node. No primeiro Loop o
   Buffer alocado e preenchido com o Par em binario. No segundo Loop o Buffer e 
   copiado para o CompBuffer, o Buffer de escrita, e se o CompBuffer estiver cheio
   ele e escrito no arquivo de saida e o apontador Position volta a ser zero.*/
void CompressNodeInfo( int* CompBuffer, int* Position, pNode Node, FILE* Out )
{
    int Cont, Size, Aux, *Buffer, PairSize;
    
    Size = SizeinBin( NODEindex( Node ) - 1 ) + 1;
    PairSize = SizeinBin( NODEpair( Node )/10 );
    Buffer = malloc(Size*sizeof(int));
    Aux = NODEpair( Node )/10;
    
    for ( Cont = 0; Cont <= Size - 2 ; Cont++ ) 
    {
        if ( (Size - 1 - Cont) > PairSize ) Buffer[Cont] = 0;
        else Buffer[Cont] = Aux >> (Size - 2 - Cont) & 1;
    }
    Buffer[Size-1] = NODEpair( Node )%10;
    
    for ( Cont = 0; Cont < Size; Cont++ )
    {
        if ( *Position >= BUFFER_SIZE )
        {
            WriteOnOut( BufferToString( CompBuffer, BUFFER_SIZE ) , Out );
            *Position = 0;
        }
        CompBuffer[*Position] = Buffer[Cont];
        (*Position)++;
    }
    free(Buffer);
}

/* Esta funcao comprimi o arquivo Entry usando o algoritmo lz78, usando uma Trie
   para guardar os indices e pares. A iteracao na Trie e feita por dois apontadores,
   um que aponta para o no que esta no Ramo correspondente do Bit lido no arquivo
   de entrada. O NodeBef aponta para o no que estava antes de AuxNode. Quando o 
   AuxNode e igual a NULL podemos inserir um novo no na Trie e comprimir a infor
   macao do no que acabou de ser inserido. Se o arquivo Entry terminou de ser lido
   e AuxNode nao a Raiz da Trie, isso quer dizer que temos que codificar essa pe
   quena informacao que sobrou e colocala no final do arquivo Out. A funcao retorna
   o AuxNode para que a iteracao pela Trie continue intacta com o final da funcao. */
pNode Compress( pNode Root, pNode AuxNode, int* Buffer, int* CompBuffer, int* Position, int* Index, int RealSize, FILE* Out, FILE* Entry )
{
    pNode NodeBef, NewNode;
    int Cont, Pair = 0;
    
    for ( Cont = 0; Cont < RealSize; Cont++ )
    {
        NodeBef = AuxNode;
        AuxNode = TRIEiterate( AuxNode, Buffer[Cont] );
        if ( AuxNode == NULL )
        {
            Pair = NODEindex( NodeBef )*10 + Buffer[Cont];
            NewNode = NODEinit( *Index, Pair );
            NODEput( NodeBef, NewNode, Buffer[Cont] );
            CompressNodeInfo( CompBuffer, Position, NewNode, Out );
            AuxNode = Root;
            Pair = 0;
            (*Index)++;
        }
    }
    if ( feof(Entry) )
    {
        if ( AuxNode != Root )
        {
        	Pair = NODEindex( NodeBef )*10 + Buffer[Cont-1];
        	CompressNodeInfo( CompBuffer, Position, AuxNode, Out );
        }
    }
    return AuxNode;
}

/*************************************************
   Funcoes Auxiliares para Decompressao
*************************************************/

/* Calcula o numero de Bits que existem no arquivo File. */
int FileSizeInBit( FILE* File )
{
    int Size;
    
    fseek( File, 0, SEEK_END );
    Size = ftell( File );
    rewind( File );
    
    return Size*8; 
}

/* Calcula o tamanho do Buffer da descompressao usando como parametro numero de 
   Bits do arquivo. Isso e feito estimando no numero de indices que a codificacao
   fez. */
int SizeDecompressBuffer( int FileSize )
{
    int DecompSize, Cont, AuxCont, Pow;
    
    for ( Cont = 1, DecompSize = 1; DecompSize < FileSize; Cont++ ) 
        for ( Pow = pow( 2, Cont ), AuxCont = 0; AuxCont < Cont; AuxCont++ ) 
        {
            if ( DecompSize >= FileSize) break;
            else  DecompSize += Cont*Pow;
        }  
    return DecompSize;
}

/* Esta funcao descomprime um Par recuperado pelo Buffer da descompressao. Ele 
   usa um vetor, onde estao guardados todos os pares, por ordem de indice, e cal
   cula a sequencia de Bits da descompactacao, copiando ela no Buffer usando para
   escrever a descompactacao no arquivo de saida. O primeiro Loop calcula o tamanho
   do Buffer, o segundo preenche esse Buffer e o terceiro copia a informacao do 
   Buffer para o DecompBuffer. Se o DecompBuffer esta cheio ele e impresso e o 
   ponteiro Position e setado para 0. */
void DecompressInfo(int *IndexBuffer, int Index, int *DecompBuffer, int *Position, FILE* Out)
{
    int *AuxBuffer, AuxSize, Cont, Aux;

    Aux = Index;
    
    for ( Cont = 0; IndexBuffer[Aux] != -1; Cont++ ) Aux = IndexBuffer[Aux]/10;   
    
    AuxSize = Cont;
    AuxBuffer = malloc(Cont*sizeof(int));
    Aux = Index;
    
    for ( Cont = AuxSize - 1; Cont >= 0; Cont-- )
    {
        if ( IndexBuffer[Aux] != -1 )
        {
            AuxBuffer[Cont] = IndexBuffer[Aux]%10;
            Aux = IndexBuffer[Aux]/10;
            if ( Aux > Index ) break;
        }
        else AuxBuffer[Cont] = 0;
    }
    
    for ( Cont = 0; Cont < AuxSize; Cont++ )
    {
        if ( *Position >= BUFFER_SIZE )
        {
            WriteOnOut( BufferToString( DecompBuffer, BUFFER_SIZE ) , Out );
            *Position = 0;
        }
        DecompBuffer[*Position] = AuxBuffer[Cont];  
        (*Position)++;
    }
    free( AuxBuffer );
}

/* Esta funcao e responsavel por preencher o DecompBuffer com a informacao do
   arquivo resultando da compressao. Ela guarda no Buffer o que foi lido do 
   arquivo Entry, e usa o DecompBuffer para guardar e escrever o resultado da
   descompressao. O ponteiro Position guarda o ultimo local nao escrito do 
   DecompBuffer, para sempre ter a informacao de onde escrever. No Loop, se o
   programa entra no IF, quer dizer que teremos que reencher o Buffer, pois nao
   temos Bits o sulficientes para montar a codificacao do indice em questao. Mas
   se o programa entra no ELSE temos Bits o sulficiente, e a operacao e mais simples.
   Se, na saida da funcao, o DecompBuffer nao esta vazio, escrevemos o que estiver
   nele na saida, que sera o ultimo indice. */
void Decompress( int *Buffer, int *IndexBuffer, int *Index, FILE* Entry, FILE* Out  )
{
    int BitsToRead, Cont, *AuxBuffer, DecompBuffer[BUFFER_SIZE], *Position, RealSize, Offset, AuxCont, BufCont;
    
    RealSize = GetBinary( Entry, Buffer );
    if ( RealSize == 0 ) return;
    Position = malloc(sizeof(int));
    *Position = 0;
	
    for ( Cont = 0, Offset = 0; Cont < RealSize; Cont++ )
    {
        BitsToRead = SizeinBin( (*Index) - 1 ) + 1;
        if ( Offset+BitsToRead >= RealSize ) 
        {
            AuxBuffer = malloc(BitsToRead*sizeof(int));
            for ( AuxCont = 0, BufCont = 0; AuxCont < BitsToRead; AuxCont++, BufCont++ )
            {
                if ( Offset+AuxCont >= RealSize )
                {
                    RealSize = GetBinary( Entry, Buffer );
                    BufCont = 0;
                    Offset = 0;
                    Cont = 0;
                }
                AuxBuffer[AuxCont] = Buffer[Offset+BufCont];
            }
            IndexBuffer[*Index] = BitToDecimal( AuxBuffer, BitsToRead )*10 + *(AuxBuffer+BitsToRead-1);
            DecompressInfo( IndexBuffer, *Index, DecompBuffer, Position, Out);
            Offset+=BufCont;
            free(AuxBuffer);
        }
        else 
        {
            AuxBuffer = Buffer+Offset; 
            IndexBuffer[*Index] = BitToDecimal( AuxBuffer, BitsToRead )*10 + *(AuxBuffer+BitsToRead-1);
            DecompressInfo( IndexBuffer, *Index, DecompBuffer, Position, Out);
            Offset+=BitsToRead; 
        }
        (*Index)++;
    }
    
    if ( *Position != 0 ) WriteOnOut( BufferToString( DecompBuffer, *Position ) , Out );
    
    free(Position);
}

/********************************
    Funcoes Principais
********************************/

/* Esta funcao e a principal da compressao. Ela cria dois vetores estaticos, o 
   Buffer, responsavel por pegar os Bits do arquivo de entrada, e o CompBuffer
   onde os Bits comprimidos ficaram para serem impressos no arquivo de saida.
   Os ponteiros Index, usando para marcar qual indice estamos usando, e o Posi
   tion, usando para marcar a ultima posicao nao usada do CompBuffer, sao criados
   aqui. a Trie e inicializada e um ponteiro que sempre aponta para sua Raiz, o
   Root, e criado aqui tambem. O Loop do programa faz com que o Buffer sempre tenha
   algo nele, e logo depois essa informacao e comprimida. Se, apos o Loop, Posi
   tion for diferente de zero imprimimos o que falta no CompBuffer, que provavelmente
   e o ultimo indice e o resto de algum que nao preencheu o CompBuffer. */
void CompressFile( FILE* Entry, FILE* Out )
{
    TRIE TrieCompress;
    pNode AuxNode, Root;
    int Buffer[BUFFER_SIZE], CompBuffer[BUFFER_SIZE], *Index, RealSize, *Position;
    
    Index = malloc(sizeof(int));
    Position = malloc(sizeof(int));
    TrieCompress = TRIEinit();
    AuxNode = TRIEroot( TrieCompress );
    Root = TRIEroot( TrieCompress );
    
	if ( Index == NULL )
	{
		printf("Erro na alocacao \n");
		exit(0);
	}
	
	*Index = 1;
	*Position = 0;
	
	while ( !feof( Entry ) )
	{
	    RealSize = GetBinary( Entry, Buffer );
	    if ( RealSize == 0 ) break;
	    AuxNode = Compress( Root, AuxNode, Buffer, CompBuffer, Position, Index, RealSize, Out, Entry );
	}
    if ( *Position != 0 ) WriteOnOut( BufferToString( CompBuffer, *Position ) , Out );
    
    TRIEdestroy( TrieCompress );
    free(Index);
    free(Position);
}

/* Esta e a funcao inicial da descompressao. Ela cria os vetores Buffer, que e o
   usando para ler do arquivo de entrada, e o IndexBuffer, que guarda os pares
   descomprimidos para podermos descomprimir os restandes. Ela chama a funcao
   Decompress, que e a principal da descompressao. */
void DecompressFile( FILE* Entry, FILE* Out )
{
	int *IndexBuffer, IndexBufSize, Buffer[BUFFER_SIZE], *Index;
	
	IndexBufSize = SizeDecompressBuffer( FileSizeInBit( Entry ) );
	IndexBuffer = malloc(IndexBufSize*sizeof(int));
	Index = malloc(sizeof(int));
	
    IndexBuffer[0] = -1;
	*Index = 1;
	
	Decompress( Buffer, IndexBuffer, Index, Entry, Out );
	
	free(Index);
	free(IndexBuffer);
}
