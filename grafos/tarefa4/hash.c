#define HASH_MULT  314159 /* random multiplier */
#define HASH_PRIME 516595003 /* the 27182818th prime; it's less than $2^{29}$ */

#include "grafo.h"

static Vertex hash_head[maxV];
static Vertex hash_link[maxV];

void hash_setup(Digraph G) {
    Vertex v;
    
    if (G && G->V > 0) 
    {
        register Vertex v;
        for (v = 0; v < G->V; v++) hash_head[v] = -1;
        for (v = 0; v < G->V; v++) hash_in(v,G);
    }
}

void hash_in(Vertex v, Digraph G) {
    register char *t=nome[v];
    register Vertex u;
    register long h;
  
    /*Find vertex u, whose location is the hash code for string t;*/
    for (h = 0; *t; t++) 
    {
        h += (h^(h>>1)) + HASH_MULT*(unsigned char)*t;
        while (h >= HASH_PRIME) h-=HASH_PRIME;
    }
    u = h % G->V;

    hash_link[v]=hash_head[u];
    hash_head[u]=v;
}


Vertex hash_out(char *s, Digraph G) {
    register char*t= s;
    register Vertex  u;
    register long h;

    /*Find vertex u, whose location is the hash code for string t;*/
    for (h = 0; *t; t++)
    {
        h += (h^(h>>1)) + HASH_MULT*(unsigned char)*t;
        while (h >= HASH_PRIME) h-= HASH_PRIME;
    }
    u = h%G->V;

    for (u = hash_head[u]; u != -1; u = hash_link[u])
    if (strcmp(s,nome[u]) == 0) return u;

    return -1;
}


Vertex hash_lookup(char *s, Digraph G) {
    if (G && G->V > 0)
    {
        register Vertex v;
        v = hash_out(s,G);
        return v;
    }
    else return -1;
}
