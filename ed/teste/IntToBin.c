#include <stdio.h>
#include <stdlib.h>

int main()
{
	int Cont, Aux, *Buffer;
	
	Aux = 10;
	Buffer = malloc(4*sizeof(int));
	
	for ( Cont = 3; Cont >= 0 ; Cont-- )
	{
		Buffer[Cont] = Aux%2;
		printf("Buffer[%d] = %d \n", Cont, Buffer[Cont]);
		Aux=Aux/2;
	}
	return 0;
}
