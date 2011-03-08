#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
    FILE *pFile;
    int Get, Bit, i;
    
    if ( argc < 2 ) printf("O ARQUIVO JESUS!!!! \n");
    else
    {
        pFile = fopen(argv[1], "rb+");
        Get = fgetc( pFile );
        while ( Get != EOF ) 
        {
            for ( i = 0; i < 8; i++ )
            {
                Bit = (Get >> i) & 1;
                printf("%d", Bit);
            }
            Get = fgetc( pFile );
        }
    }
    return 0;
}   
