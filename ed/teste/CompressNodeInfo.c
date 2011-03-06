#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SizeinBin( int Number )
{
    int Cont = 0;
    while ( ( Number = Number/2 ) != 0 ) Cont++;
    return Cont+2;
}

int main( int argc, char **argv )
{
    int *Buffer, Cont, Size, Aux;
    
    if ( argc <= 1 ) printf("Esse programa usa ./EP3 <nome_do_arquivo> \n");
    else
    {
        Aux = atoi( argv[1] )/10;
        printf("%d \n", Aux);
        Size = SizeinBin( Aux - 1 ) + 1;
        printf("Size: %d \n", Size);
        Buffer = malloc(Size*sizeof(int));
    
        for ( Cont = Size - 2; Cont > 0 ; Cont-- )
        {
            Buffer[Cont] = Aux%2;
            Aux = Aux/2;
        }
        Buffer[Size - 1] = atoi( argv[1] )%10;
        
        for ( Cont = 0; Cont < Size; Cont++ ) printf("Buffer[%d] = %d \n", Cont, Buffer[Cont]);
    }
    
    return 0;
}
