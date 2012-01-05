/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include "queue.h"

int inicio, fim, *q;

void PQinit(int maxN) {
	q = malloc(maxN*sizeof(int));
	inicio = 0;
	fim = 0;
}

int PQempty() {
	return inicio==fim;
}

void PQshow() {
	int i;
	printf("\n");
	for ( i = inicio; i < fim; i++ ) printf("%d  ", q[i]);
	printf("\n");
}

void PQinsert(int V) {
	q[fim++] = V;
}

int PQdelmax(double cst[]) {
	int i, j, x;
	i = inicio;
	for (j=i+1; j < fim; j++) if (cst[q[i]] - cst[q[j]] < 0.0) i = j;
	x = q[i];
	q[i] = q[--fim];
	return x;
}

void PQfree() {
	free(q);
}
