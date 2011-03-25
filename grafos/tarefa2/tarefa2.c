/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHshow DIGRAPHshow
#define MAXVERTEX 100
#define LINESIZE 10

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
    for ( i = 0; i < r; i++ ) {
        m[i] = malloc( c*sizeof(int));
        for ( j = 0; j < c; j++ )
            m[i][j] = val;
    }
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
        printf("%2d:", v+1);
        for ( w = 0; w < G->V; w++ )
            if ( G->adj[v][w] == 1 ) printf(" %2d ", w+1);
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

int isbipartR (Graph G, Vertex s, int *bipartite, int last) {
    Vertex w;
    if ( bipartite[s] == 0 ) bipartite[s] = (last)%2 + 1;
    else if ( bipartite[s] != (last%2+1) ) return 0;
  
    for ( w = 0; w < G->V; w++ ) 
        if ( G->adj[s][w] == 1 && bipartite[w] != bipartite[s]%2 + 1 ) {
            if ( isbipartR(G, w, bipartite, bipartite[s] ) == 0 ) 
                return 0;
        }
    return 1;
}

int GRAPHisbipart (Graph G, int *bipartite) {
    Vertex v;
    
    for ( v = 0; v < G->V; v++ )
        if ( bipartite[v] == 0 ) {
            if ( isbipartR( G, v, bipartite, 0) == 0 ) return 0;
        }
    return 1;
}

int main() {
    int NumVert, NumArcs, i, j,*bipartite, inst;
    char *line, *ptr;
    Graph G;
    
    line = malloc(LINESIZE*sizeof(char));
    inst = 0;
    
    while ( fgets(line, 10, stdin) != NULL ) {
        if ( inst != 0 ) printf("\n");
        for ( j = 0; j < LINESIZE && line[j] != ' '; j++);
        ptr = line+j*sizeof(char);
        NumVert = atoi(line);
        NumArcs = atoi(ptr);
        
        bipartite = malloc(NumVert*sizeof(int));
        for ( i = 0; i < NumVert; i++ ) bipartite[i] = 0;
        G = GRAPHinit(NumVert);
        inst++;
        
        for ( i = 0; i < NumArcs && fgets(line, 10, stdin) != NULL; i++ ) {
            for ( j = 0; j < LINESIZE && line[j] != ' '; j++);
            ptr = line+j*sizeof(char);
            GRAPHinsertE(G, (atoi(line)-1), (atoi(ptr)-1));
        }
        printf("Instancia %d\n", inst);
        if ( GRAPHisbipart(G, bipartite) == 1 ) printf("sim\n");
        else printf("nao\n");
        free(bipartite);
        free(G);
    }
    free(line);
    return 0;
}
