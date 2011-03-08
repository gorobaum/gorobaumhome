#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv )
{
    int Cont = 0, Number;
    
    if ( argc < 2 ) printf("O NUMERO JISUIS! \n");
    else
    {
        Number = atoi( argv[1] );
        printf("Numero: %d \n", Number);
        while( ( Number = Number/2 ) >= 2 ) 
        {
            Cont++;
            printf("Numero: %d \n", Number);
        }
        printf("Tamanho em Binario: %d \n", Cont + 2);
    }
    return 0;
}
