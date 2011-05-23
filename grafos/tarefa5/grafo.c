/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "queue.h"

static int cnt, time, conta;
static int f[maxV], d[maxV], lbl[maxV], pos[maxV];

typedef struct {
    Vertex v;
    Vertex w;
    double cst;
} Arc;

typedef struct node *link;

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

Arc ARC (Vertex v, Vertex w, double cst) {
    Arc e;
    e.v = v;
    e.w = w;
    e.cst = cst;
    return e;
}

int **MATRIXinit (int r, int c, int val) {
    Vertex i, j;
    int **m;
    m = malloc( r*sizeof(int *));    
    for ( i = 0; i < r; i++ ) {
        m[i] = malloc( c*sizeof(int));
        for ( j = 0; j < c; j++ )
            m[i][j] = val;
    }
    return m;
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

void DIGRAPHshow (Digraph G) {
    Vertex v;
    link p;
    for ( v = 0; v < G->V; v++ ) {
        printf("%3d:",v);
        for ( p = G->adj[v]; p != NULL; p = p->next ) printf("%3d", p->w);
        printf("\n");
    }
}

void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst) {
    DIGRAPHinsertA(G, v, w, cst); 
    DIGRAPHinsertA(G, w, v, cst);
}

int DIGRAPHNumArcs( Vertex w, Digraph G ) {
    int i;
    link p;
    for ( p = G->adj[w], i = 0; p != NULL; p = p->next, i++ );
    return i;
}

int* DIGRAPHVertexArcs( Vertex w, Digraph G ) {
    int *Arcs;
    int i;
    link p;
    
    Arcs = malloc(DIGRAPHNumArcs( w, G)*sizeof(int));
    if ( G->adj[w] == NULL ) return NULL;
    for ( p = G->adj[w], i = 0; p != NULL; p = p->next, i++ ) Arcs[i] = p->w;

    return Arcs;
}

int DIGRAPHGetNumVet( Digraph G ) {
    return G->V;
}

void pathR (Digraph G, Vertex v, int parnt[]) {
    link p;
    lbl[v] = 0;
    for ( p = G->adj[v]; p != NULL; p = p->next )
        if ( lbl[p->w] == -1 ) {
            parnt[p->w] = v;
            pathR(G, p->w, parnt);
        }
}

int DIGRAPHpath ( Digraph G, int parnt[]) {
    Vertex v, w;    
    for ( w = 0; w < G->V; w++ ) {
        for ( v = 0; v < G->V; v++ ) {
            lbl[v] = -1;
            parnt[v] = -1;
        }
        parnt[w] = w;
		pathR(G, w, parnt);
        for ( v = 0; v < G->V; v++ ) {
            if ( parnt[v] == -1 ) return 0;
        }
    }
    return 1;   
}

int cycleR (Digraph G,Vertex v,Vertex ts[], int parnt[]) {
	Vertex w;
	link p;
	d[v] = time++;
	
	for (p = G->adj[v]; p != NULL; p= p->next) {
		if (d[w=p->w] == -1) {
			parnt[w] = v;
			if(cycleR(G,w,ts, parnt)==1) return 1;
		}
		else if (f[w] == -1) return 1;
	}	
	f[v] = time++; 
	ts[cnt--] = v;
	return 0;
}

int DIGRAPHcycle (Digraph G, Vertex s, int parnt[]) {
	Vertex v;
	int *ts;
	time = 0; 
	cnt = G->V-1;
	
	ts = malloc((G->V)*sizeof(int));
	
	for (v = 0; v < G->V; v++) ts[v] = d[v] = f[v] = parnt[v] = -1;
	parnt[s] = s;
	if (cycleR(G,s,ts,parnt) == 1) return 1;
	return 0;
}

void dfsR (Digraph G, Vertex v, int *sop) { 
	link p;
	lbl[v] = 1;
	for (p = G->adj[v]; p != NULL; p = p->next)
	  	if (lbl[p->w] == -1) dfsR(G, p->w, sop);
 	if ( pos[v] == -1 ) {
	 	pos[v] = conta;
		sop[conta++] = v;
 	}
}

void DIGRAPHdfs (Digraph G, Vertex s, int *sop) { 
   	Vertex v;
   	conta = -1;
   	for (v = 0; v < G->V; v++) lbl[v] = pos[v] = -1; 
 	dfsR(G, s, sop);
}	

void dijkstra(Graph G, Vertex s, Vertex parnt[], double cst[]) {
	Vertex v, w; 
	link p;
	for (v = 0; v < G->V; v++) {
		cst[v] = 0;
		parnt[v] = -1;
	}
	
	PQinit(G->V);
	cst[s] = 1;
	parnt[s] = s;
	PQinsert(s);
	
	while (!PQempty()) {
		v = PQdelmax(cst);
		for(p=G->adj[v];p!=NULL;p=p->next) {
			if (cst[w=p->w] == 0) {
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
