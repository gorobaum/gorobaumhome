#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHshow DIGRAPHshow
#define MAXVERTEX 100

static int lbl[MAXVERTEX];

typedef struct {
    Vertex v;
    Vertex w;
} Arc;

typedef struct digraph *Digraph;

struct digraph {
    int V;
    int A;
    int **adj;
};

Arc ARC (Vertex v, Vertex w) {
    Arc e;
    e.v=v;
    e.w=w;
    return e;
}

int **MATRIXinit (int r, int c, int val) {
    Vertex i, j;
    int **m;
    m = malloc( (r+1)*sizeof(int *));
    for ( i = 0; i < (r+1); i++)
        m[i] = malloc( (c+1)*sizeof(int));
    for ( i = 0; i < (r+1); i++ )
        for ( j = 0; j < (c+1); j++ )
            m[i][j] = val;
    return m;
}

Digraph DIGRAPHinit (int V) {
    Digraph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = MATRIXinit( V, V, 0 );
    return G;
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    if (v != w && G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    if ( G->adj[v][w] == 1 ) {
        G->adj[v][w] = 0;
    }
        G->A--;
}

void DIGRAPHshow (Digraph G) {
    Vertex v, w;
    for ( v = 0; v < G->V; v++ ) {
        printf("%2d:", v);
        for ( w = 0; w < G->V; w++ )
            if ( G->adj[v][w] == 1 ) printf(" %2d ", w);
        printf("\n");
    }
}

void GRAPHinsertE (Graph G, Vertex v, Vertex w) {
    DIGRAPHinsertA(G, v, w); 
    DIGRAPHinsertA(G, w, v);
}

int pathR (Digraph G, Vertex v, Vertex t) {
    Vertex w;
    lbl[v] = 0;
    if ( v == t ) return 1;
    for ( w = 0; w < G->V; w++ ) 
        if ( G->adj[v][w] == 1 && lbl[w] == -1 )
            if ( pathR(G, w, t) == 1 )
                return 1;
    return 0;
}

int DIGRAPHpath (Digraph G, Vertex s, Vertex t) {
    Vertex v;
    for ( v = 0; v > G->V; v++ )
        lbl[v] = -1;
    return pathR(G, s, t);
}

int isbipartR (Digraph G, Vertex v, Vertex *bipartite, int *cont ) {
    Vertex w;
    bipartite[v] = (*cont)%2 + 1;
    (*cont)++;
    for ( w = 0; w < G->V; w++ )
        if ( G->adj[v][w] == 1 && bipartite[w] == 0 )
            if ( isbipartR(G, w, bipartite, cont) == 0 )
                return 0;
    return 1;
}   

int DIGRAPHisbipart (Digraph G) {
    int *cont;
    Vertex v, *bipartite;
    bipartite = malloc(V*sizeof(Vertex));
    cont = malloc9sizeof(int));
    (*cont) = 0;

    for ( v = 0; v < G->V; v++ ) bipartite[v] = 0;
    for ( v = 0; v < G->V; v++ ) 
        if ( bipartite[v] == 0 ) { 
            if ( isbipartR(G, v, bipartite, cont) == 0 ) return 0;
            else {
                for ( v = 0; v < G->V; v++ ) if ( bipartite[v] == 0 ) return 0;
                return 1;
            }
        }
}   

int main (int argc, char **argv) {
    int A, V, c, i;
    Vertex vertexs[2];
    Digraph G;    
    
    
    A = getchar() - '0';
    c = getchar();
    V = getchar() - '0';
    c = getchar();
    
    G = DIGRAPHinit(V);
    i = 0;
    while ( ( c = getchar() ) != EOF ) {
        if ( c == '\n' ) {
            i = 0;
            DIGRAPHinsertA(G, vertexs[0], vertexs[1]);
            DIGRAPHinsertA(G, vertexs[1], vertexs[0]);
        }     
        else if (c != ' ') {
            vertexs[i] = c - '0'; 
            i++;
        }
    }
    return 0;
}
