#include <stdio.h>
#include <math.h>

int main()
{
    char Get;
    int Buffer[8], i = 0;
    
    while( ( Get = getchar() ) != EOF )
    {
        Buffer[i] = Get - '0';
        i++;
        if ( i == 7 )
        {
            Get = 0;
            for ( ; i >= 0; i-- ) Get += Buffer[i]*pow( 2, i );
            printf("%c \n", Get);
        }
    }
    return 0;
}
