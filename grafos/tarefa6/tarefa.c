/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVERTEX 100
#define LINESIZE 20
#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHshow DIGRAPHshow
#define maxV 100
#define INFINITO maxCST

typedef struct digraph *Digraph;
typedef struct node *link;
int inicio, fim, *q;
double maxCST;

/************/
/*	QUEUE	*/
/************/

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

int PQdelmin(double cst[]) {
    int i, j, x;
    i = inicio;
    for (j=i+1; j < fim; j++)
        if (cst[q[i]] > cst[q[j]]) i = j;
        x = q[i];
        q[i] = q[--fim];
    return x;
}


void PQfree() {
	free(q);
}

/************/
/*	GRAFO	*/
/************/
struct node {
    Vertex w;
    link next;
    double cst;
};

struct digraph {
    int V;
    int A;
    link *adj;
};

link NEW (Vertex w, link next, double cst) {
    link p = malloc(sizeof(*p));
    p->w = w;
    p->next = next;
    p->cst = cst;
    return p;
}

Digraph DIGRAPHinit (int V) {
    Vertex v;
    
    Digraph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V* sizeof(link));
    for ( v = 0; v < V; v++ ) G->adj[v] = NULL;
    
    return G;
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst) {
    link p;
    if ( w == v ) return;
    for ( p = G->adj[v]; p != NULL; p = p->next) if ( p->w == w) return;
    G->adj[v] = NEW(w, G->adj[v], cst);
    G->A++;
}

void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst) {
    DIGRAPHinsertA(G, v, w, cst); 
    DIGRAPHinsertA(G, w, v, cst);
}

void GRAPHmaxcst( Graph G ) {
	int i;
	double max = 0.0;
	link p;
	for ( i = 0; i < G->V; i++ )
		for ( p = G->adj[i]; p != NULL; p = p->next ) 
			if ( p->cst - max > 0.0 ) max = p->cst;  
    maxCST = max*G->V + 1;
}

void dijkstra(Graph G, Vertex s, Vertex parnt[], double cst[]) {
	Vertex v, w; 
	link p;

    GRAPHmaxcst(G);

	for (v = 0; v < G->V; v++) {
		cst[v] = INFINITO;
		parnt[v] = -1;
	}
	
	PQinit(G->V);
	cst[s] = 1;
	parnt[s] = s;
	PQinsert(s);
	
	while (!PQempty()) {
		v = PQdelmax(cst);
		for(p=G->adj[v];p!=NULL;p=p->next) {
			if (cst[w=p->w]==INFINITO) {
				cst[w]=cst[v]*p->cst;
				parnt[w]=v;
				PQinsert(w);
			}
			else if(cst[w]<cst[v]*p->cst) {
				cst[w]=cst[v]*p->cst;
				parnt[w] = v;
			}
		}
	}
	PQfree();
}

void GRAPHmstP2 (Graph G, Vertex parnt[], double cst[]) {
    Vertex v, w, fr[maxV]; 
    link p;

    GRAPHmaxcst(G);

    for (v = 0; v < G->V; v++) {
        cst[v] = INFINITO;
        parnt[v] = -1;
    }
    PQinit(G->V);
    cst[0] = 0;
    fr[0] = 0;
    PQinsert(0);
    while (!PQempty()) {
        v = PQdelmin(cst);
        parnt[v] = fr[v];
        for (p=G->adj[v];p!=NULL;p=p->next){
            w = p->w;
            if (parnt[w] == -1){
                if (cst[w] == INFINITO){
                    cst[w] = p->cst;
                    fr[w] = v;
                    PQinsert(w);
                }
                else if (cst[w] > p->cst){
                    cst[w] = p->cst;
                    fr[w] = v;
                }
            }
        }
    }
}



int main(){
    int NumVert, NumArcs, i, posLine, tam, *parnt, teste;
    double *cst;
    char line[LINESIZE], ptr[LINESIZE], arc1[LINESIZE], arc2[LINESIZE], csts[LINESIZE];
    Graph G;
    teste = 0;
    
    while ( fgets(line, LINESIZE, stdin) != NULL ) {
		sscanf(line, "%s %n", ptr, &tam);
    	NumVert = atoi(ptr);
    	if ( NumVert == 0 ) break;
        teste++;
    	posLine = tam;
    	sscanf(line+posLine, "%s %n", ptr, &tam);
    	NumArcs = atoi(ptr);
    	
    	G = DIGRAPHinit(NumVert);
    	parnt = malloc(NumVert*sizeof(int));
    	cst = malloc(NumVert*sizeof(double));
    	
    	for ( i = 0; i < NumArcs; i++ ) {
    		fgets(line, LINESIZE, stdin);
    		if ( sscanf(line, "%s %s %s", arc1, arc2, csts) == 3 ) {
				GRAPHinsertE( G, atoi(arc1)-1, atoi(arc2)-1, atof(csts) );
			}
		}
		GRAPHmstP2(G, parnt, cst);
		printf("Teste %d\n", teste);
        for ( i = G->V-1; i > 0; i-- ) {
            if ( parnt[i]+1 > i+1 ) printf("%d %d\n", i+1, parnt[i]+1);
            else printf("%d %d\n", parnt[i]+1, i+1);
	    }   
    }
    return 0;
}
