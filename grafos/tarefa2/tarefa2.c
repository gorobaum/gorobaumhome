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
#define maxV 100
#define LINESIZE 10

static int lbl[maxV];
static int parnt[maxV];

typedef struct {
    Vertex v;
    Vertex w;
} Arc;

typedef struct digraph *Digraph;

typedef struct node *link;

struct node {
    Vertex w;
    link next;
};

struct digraph {
    int V;
    int A;
    link *adj;
};

link NEW (Vertex w, link next) {
    link p = malloc(sizeof(*p));
    p->w=w;
    p->next=next;
    return p;
}

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
    Vertex v;
    
    Digraph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V* sizeof(link));
    for ( v = 0; v < V; v++ ) G->adj[v] = NULL;
    
    return G;
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    link p;
    if ( w == v ) return;
    for ( p = G->adj[v]; p != NULL; p = p->next) if ( p->w == w) return;
    G->adj[v] = NEW(w, G->adj[v]);
    G->A++;
}

void DIGRAPHshow (Digraph G) {
    Vertex v;
    link p;
    for ( v = 0; v < G->V; v++ ) {
        printf("%2d:",v);
        for ( p = G->adj[v]; p != NULL; p = p->next ) printf("%2d", p->w);
        printf("\n");
    }
}

void GRAPHinsertE (Graph G, Vertex v, Vertex w) {
    DIGRAPHinsertA(G, v, w); 
    DIGRAPHinsertA(G, w, v);
}

void pathR (Digraph G, Vertex v) {
    link p;
    lbl[v] = 0;
    for ( p = G->adj[v]; p != NULL; p = p->next )
        if ( lbl[p->w] == -1 ) {
            parnt[p->w] = v;
            pathR(G, p->w);
        }
}

int DIGRAPHpath ( Digraph G ) {
    Vertex v, w;    
    for ( w = 0; w < G->V; w++ ) {
        for ( v = 0; v < G->V; v++ ) {
            lbl[v] = -1;
            parnt[v] = -1;
        }
        parnt[w] = w;
        pathR(G, w);
        for ( v = 0; v < G->V; v++ ) {
            if ( parnt[v] == -1 ) return 0;
        }
    }
    return 1;
    
}

int main() {
    int NumVert, NumArcs, i, j, inst;
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
        if ( NumVert == 0 && NumArcs == 0 ) break;
        
        G = GRAPHinit(NumVert);
        inst++;
        
        for ( i = 0; i < NumArcs && fgets(line, 10, stdin) != NULL; i++ ) {
            for ( j = 0; j < LINESIZE && line[j] != ' '; j++);
            ptr = line+j*sizeof(char);
            GRAPHinsertE(G, (atoi(line)-1), (atoi(ptr)-1));
        }
        printf("Teste %d\n", inst);
        if ( DIGRAPHpath( G ) == 1 ) printf("normal\n");
        else printf("falha\n");
        free(G);
    }
    free(line);
    return 0;
}
