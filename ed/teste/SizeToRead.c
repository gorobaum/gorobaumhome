#include <stdio.h>
#include <math.h>

int main()
{
    int Number, Size, Cont, AuxCont, Pow;
    
    Number = 3;
    
    for ( Cont = 1, Size = 1; Cont < Number; Cont++ ) 
        for ( Pow = pow( 2, Cont ), AuxCont = 0; AuxCont < Cont; AuxCont++ ) 
            Size = Cont*Pow;
    printf("Size: %d \n", Size);
    return 0;
}
