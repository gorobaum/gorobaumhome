/*username Gorobaum */
/*password rajimema */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1000

void isbiggersmarter(int w[], int s[]m int size) {
    
}

int main() {
    int w[LINESIZE], s[LINESIZE], i, aux;
    char line[LINESIZE];
    i = 0;
    while (fgets(line, LINESIZE, stdin) != NULL) {
    	if ( sscanf(line, "%d %d", &w[i], &s[i]) == 2 ) i++;
    }
    for ( aux = 0; aux < i; aux++) printf("%d %d\n", w[aux], s[aux]);
    return 0;
}
