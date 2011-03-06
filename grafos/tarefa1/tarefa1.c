#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHshow DIGRAPHshow
#define MAXVERTEX 100
#define LINESIZE 4

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
    m = malloc( r*sizeof(int *));
    for ( i = 0; i < r; i++)
        m[i] = malloc( c*sizeof(int));
    for ( i = 0; i < r; i++ )
        for ( j = 0; j < c; j++ )
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
        G->A--;
    }
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

int GRAPHisbipart( Graph G, int bipratite ) {
    return 0;
}

int main() {
    int NumVert, NumArcs, i, *bipratite;
    char *line;
    Graph G;
    
    line = malloc(LINESIZE*sizeof(char));
    
    while ( fgets(line, 5, stdin) != NULL ) {
        line[1] = '\0';
        NumVert = atoi(line);
        NumArcs = atoi(line+2);
        
        bipartite = malloc(NumVert*sizeof(int));
        for ( i = 0; i < NumVert; i++ ) bipartite[i] = 0;
        G = GRAPHinit(NumVert);
        
        for ( i = 0; i < NumArcs; i++ ) {
            fgets(line, 5, stdin);
            line[1] = '\0';
            GRAPHinsertE(G, atoi(line)-1, atoi(line+2)-1);
        }
        GRAPHisbipart(G, bipartite);
    }
    return 0;
}
