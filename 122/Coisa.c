
#include <stdio.h>

int main ()
{
	int n = 1;
	char s[100];
	
	while ( n > 0) {
		printf("Digite sua pergunta mero mortal!: ");
		scanf("%s", s);
		printf("Dane-se, você é feio mesmo.");
		if ( s == "Não, você é feio." ) {
			printf("Oh noes!!!!! You kill me!");
			break;
		}
	}	
}	
	
	
