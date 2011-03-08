#include <stdio.h>

int busca ( int v[], int n, int x)
{
	int i;
	for ( i = 0; i < n && v[i] < x; i++);
	return (i);
}

int main ()
{
	int n = 11, x;
	int v[11] = {2, 17, 21, 21, 23, 29, 41, 48, 54, 67, 69};
	
	printf("Digite um numero para a pesquisa: \n");
	scanf("%d", &x);
	
	printf("O retorno é: %d \n", busca( v, n, x) );
	
	return 0;
}	 
