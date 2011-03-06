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

int BitToDecimal( int* Buffer, int Size )
{
    int Cont, Decimal;
    
    for ( Cont = 0, Decimal = 0; Cont < (Size - 1); Cont++ ) 
    {
        Decimal+= Buffer[Cont]*pow( 2, Size - Cont - 2 );
    }
    return Decimal;
}

void WriteOnOut( char* Buffer, FILE* Out )
{
    fputs( Buffer, Out );
    free(Buffer);
}

char* BufferToString( int* Buffer, int Size )
{
    int Cont, Offset = 0, StrCont, AuxCont;
    char *String, AuxChar = 0;
    
    if ( Size%8 == 0 ) String = malloc( (Size/(8 * sizeof(char))) + sizeof(char));
    else String = malloc( (Size/(8 * sizeof(char))) + 2*sizeof(char));
    
    for ( Cont = 0, StrCont = 0; Offset < Size; Cont++ )
    {
        if ( Size%8 != 0 && Offset + 8 > Size )
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

int SizeinBin( int Number )
{
    int Cont = 0;
    for ( Cont = 0; Number; Cont++ ) Number >>= 1;
    return Cont;
}

/*************************************************
    Funcoes Auxiliares para Compressao
*************************************************/

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
    
    Size = SizeinBin( NODEindex( Node ) - 1 ) + 1;
    Buffer = malloc(Size*sizeof(int));
    
    Aux = NODEpair( Node )/10;
    for ( Cont = 0; Cont <= Size - 2 ; Cont++ ) Buffer[Cont] = Aux >> (Size - 2 - Cont) & 1;
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
            /*printf("Index: %d Pair: %d \n", *Index, Pair);*/
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
        	/*printf("Index: %d Pair: %d \n", *Index, Pair);*/
        	CompressNodeInfo( CompBuffer, Position, AuxNode, Out );
        }
    }
    return AuxNode;
}

/*************************************************
   Funcoes Auxiliares para Decompressao
*************************************************/

int FileSizeInBit( FILE* File )
{
    int Size;
    
    fseek( File, 0, SEEK_END );
    Size = ftell( File );
    rewind( File );
    
    return Size*8; 
}

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

void DecompressInfo(int *IndexBuffer, int Index, int *DecompBuffer, int *Position, FILE* Out)
{
    int *AuxBuffer, AuxSize, Cont, Aux;

    Aux = Index;
    
    for ( Cont = 0; IndexBuffer[Aux] != -1; Cont++ )
    {
        /*printf("IndexBuffer[%d] = %d \n", Aux, IndexBuffer[Aux]);*/
        Aux = IndexBuffer[Aux]/10;   
    }
    
    AuxSize = Cont;
    AuxBuffer = malloc(Cont*sizeof(int));
    Aux = Index;
    
    for ( Cont = AuxSize - 1; Cont >= 0; Cont-- )
    {
        if ( IndexBuffer[Aux] != - 1 )
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
        /*printf("Pos: %d \n", *Position);*/
    }
    free( AuxBuffer );
}

void Decompress( int *Buffer, int *IndexBuffer, int *Index, FILE* Entry, FILE* Out  )
{
    int BitsToRead, Cont, *AuxBuffer, DecompBuffer[BUFFER_SIZE], *Position, RealSize, Offset, AuxCont, BufCont;
    
    RealSize = GetBinary( Entry, Buffer );
    if ( RealSize == 0 ) return;
    /*printf("NovoBuffer!!! %d", RealSize);*/
    Position = malloc(sizeof(int));
    *Position = 0;
	
    for ( Cont = 0, Offset = 0; Cont < RealSize; Cont++ )
    {
        BitsToRead = SizeinBin( (*Index) - 1 ) + 1;
        /*printf("BitsToRead: %d OffSet: %d Cont: %d\n", BitsToRead, Offset, Cont);*/
        if ( Offset+BitsToRead >= RealSize ) 
        {
            AuxBuffer = malloc(BitsToRead*sizeof(int));
            for ( AuxCont = 0, BufCont = 0; AuxCont < BitsToRead; AuxCont++, BufCont++ )
            {
                if ( Offset+AuxCont >= RealSize )
                {
                    RealSize = GetBinary( Entry, Buffer );
                    /*printf("NovoBuffer!!! %d", RealSize);*/
                    BufCont = 0;
                    Offset = 0;
                    Cont = 0;
                }
                AuxBuffer[AuxCont] = Buffer[Offset+BufCont];
            }
            IndexBuffer[*Index] = BitToDecimal( AuxBuffer, BitsToRead )*10 + *(AuxBuffer+BitsToRead-1);
            if ( IndexBuffer[*Index]/10 >= *Index )
            {
                printf("Deu Caca1! \n");
                exit(0);
            }
            /*printf("Index: %d Pair: %d \n", *Index, IndexBuffer[*Index]);*/
            DecompressInfo( IndexBuffer, *Index, DecompBuffer, Position, Out);
            Offset+=BufCont;
            free(AuxBuffer);
        }
        else 
        {
            AuxBuffer = Buffer+Offset; 
            IndexBuffer[*Index] = BitToDecimal( AuxBuffer, BitsToRead )*10 + *(AuxBuffer+BitsToRead-1);
            if ( IndexBuffer[*Index]/10 >= *Index )
            {
                printf("Deu Caca! \n");
                exit(0);
            }
            /*printf("Index: %d Pair: %d \n", *Index, IndexBuffer[*Index]);*/
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
	    /*printf("Novo Buffer!!! %d", RealSize);*/
	    if ( RealSize == 0 ) break;
	    AuxNode = Compress( Root, AuxNode, Buffer, CompBuffer, Position, Index, RealSize, Out, Entry );
	}
    if ( *Position != 0 ) WriteOnOut( BufferToString( CompBuffer, *Position ) , Out );
    
    TRIEdestroy( TrieCompress );
    free(Index);
    free(Position);
}

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
