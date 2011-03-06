#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
    FILE *pFile, *pFileOut, *pFileNew;
    int Get, Bit, i, Aux;
    
    if ( argc < 2 ) printf("O ARQUIVO JESUS!!!! \n");
    else
    {
        pFile = fopen(argv[1], "rb+");
        Get = fgetc( pFile );
        pFileOut = fopen("macaco.cod", "wb+" );
        pFileNew = fopen("macaco.des", "wb+" );
        /* PASSA PRA BINARIO*/
        while ( Get != EOF ) 
        {
            for ( i = 7; i >= 0; i-- )
            {
                Aux = Get;
                Bit = (Aux >> i) & 1;
                fputc( Bit + '0', pFileOut);
            }
            Get = fgetc( pFile );
        }
        /* VOLTA O ARQUIVO */
        i = 8;
        Aux = 0;
        rewind(pFileOut);
        while ( ( Get = fgetc( pFileOut ) ) != EOF )
        {
            if ( i == 0 ) 
            {
                fputc( Aux, pFileNew );
                Aux = 0;
                i = 8;
            }
            i--;
            Aux += ( Get - '0')*pow( 2, i );  
        }
        fclose(pFile);
        fclose(pFileOut);
        fclose(pFileNew);
    }
    return 0;
}   
