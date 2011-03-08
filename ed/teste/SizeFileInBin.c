#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv)
{
    int Size;
    FILE* pFile;
    
    if ( argc > 1 )
    {
        pFile = fopen( argv[1], "rb+" );
        fseek( pFile, 0, SEEK_END );
        Size = ftell( pFile );
        printf("Size:%d \n", Size);
        fclose(pFile);    
    }
    else
    {
        printf("O ARQUIVO JISUIS! \n");
        exit(0);
    }
    return 0;
}
