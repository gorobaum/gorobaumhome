#include <stdio.h>

int busca ( int v[], int n, int x)
{
	int i;
	for ( i = 0; i < n && v[i] < x; i++);
	return (i);
}

int buscabi ( int v[], int n, int x )
{	
	int inicio, fim, meio;
	inicio = 0, fim = n-1, meio = (inicio + fim)/2;
	
	while ( inicio <= fim && v[meio] != x ) {
		if ( v[meio] < x )
			inicio = meio + 1;
		else
			fim = meio - 1;	
		meio = (inicio + fim)/2;
 	}
 	
 	if ( inicio <= fim )	return meio;
 	
 	return inicio;			
}	

int main ()
{
	int n = 11, x;
	int v[11] = {2, 17, 21, 21, 23, 29, 41, 48, 54, 67, 69};
	
	printf("Digite um numero para a pesquisa: \n");
	scanf("%d", &x);
	
	printf("O retorno é: %d %d \n", busca( v, n, x), buscabi( v, n, x) );
	
	return 0;
}	 
