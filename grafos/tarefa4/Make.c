/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


#define HASH_MULT  314159 /* random multiplier */
#define HASH_PRIME 516595003 /* the 27182818th prime; it's less than $2^{29}$ */
#define MAXLN 1000 /* Tam. de uma linha */
#define MAXP 50 /* Tam. de uma palavra */
#define maxV 100
#define Vertex int

typedef enum {FALSE,TRUE} Boolean;
static char  *nome[maxV];
static char  *comandos[maxV];
int           mod_time[maxV];
Boolean       up_to_date[maxV];
static int posnome;
static Vertex hash_head[maxV];
static Vertex hash_link[maxV];

/*  HASH        

void hash_setup(Digraph G) {
    Vertex v;
    
    if (G != NULL && G->V > 0) 
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
  
    Find vertex u, whose location is the hash code for string t;
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

    Find vertex u, whose location is the hash code for string t;
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

  FIM DO HASH */

int lookfornome(char *target) {
    int i;
    for ( i = 0; i < maxV; i++) {
        if ( nome[i] == NULL ) return 0;
        else if ( strcmp(nome[i], target) == 0 ) return i;
    }
    return 0;
}


void readTargets(FILE * MakeFile, Digraph G){
    char line[MAXLN];
    int terminou = 0, poscom = 0;
    char comandosaux[MAXLN];

    if (fgets(line, MAXLN, MakeFile) == NULL)
        terminou = 1;
    while (terminou == 0){
        int tam;
        int posLine;
        char target[MAXP];
        char dep[MAXP];
        char com[MAXP];

        if (strlen(line) == 1) {
            if (fgets(line, MAXLN, MakeFile) == NULL)
            terminou = 1;
            continue;
        }

        sscanf(line, "%s %n", target, &tam);
        if (target[strlen(target)-1] != ':'){
            printf("ERRO: Target inválida %s \n", target);
            exit(1);
        }  
        target[strlen(target)-1] = '\0';
        poscom = lookfornome(target);
        if ( lookfornome(target) == 0 ) {
            nome[posnome] = malloc(tam*sizeof(char));
            poscom = posnome;
            strcpy( nome[posnome++], target );
        }
        posLine = tam;
        
        while (sscanf(line+posLine, "%s %n", dep, &tam) == 1){
            if ( lookfornome(dep) == 0 ) {
                nome[posnome] = malloc(tam*sizeof(char));
                strcpy( nome[posnome++], dep );
            }
            DIGRAPHinsertA(G, lookfornome(target), lookfornome(dep));
            posLine += tam;
        }
        
		comandosaux[0] = '\0';
        if (fgets(line, MAXLN, MakeFile) == NULL)
            break;
        while (line[0] == '\t'){
            strcpy(com, line);
            com[strlen(com)-1] = ';';
            strcat(comandosaux, com);
            if (fgets(line, MAXLN, MakeFile) == NULL){
                terminou = 1;
                break;
            }
        }
        comandos[poscom] = malloc(strlen(comandosaux)*sizeof(char));
        strcpy(comandos[poscom], comandosaux );
    }
}

void writeMake(FILE * MakeFiledg, Digraph G){
    int i, j;
    int *Arcs;
    char * aux, * last;    

    for ( i = 0; i < DIGRAPHGetNumVet( G ); i++ ) {
        Arcs = DIGRAPHVertexArcs( i, G );
        if ( comandos[i] != NULL ) {
            fputs(nome[i], MakeFiledg);
            fputc(':', MakeFiledg);
            for ( j = 0; j < DIGRAPHNumArcs( i, G ); j++ ) {
                fputc(' ', MakeFiledg);
                fputs(nome[Arcs[j]], MakeFiledg);
                fputc(' ', MakeFiledg);
            }
            fputc('\n', MakeFiledg);
            aux = comandos[i];
            last = comandos[i];
            while ( last[0] != '\0' ) {
            	aux += sizeof(char);
                if( aux[0] == ';' ) {
					fputc('\t', MakeFiledg);
                    aux[0] = '\0';
                    fputs(last, MakeFiledg);
					fputc('\n', MakeFiledg);
					aux += 1*sizeof(char);
					last = aux;
                }
            }
			fputc('\n', MakeFiledg);
        }
    }
}

int main( int argc, char **argv ){
    FILE * MakeFile, * MakeFiledg;
    Digraph G;
    int i;    

    G = DIGRAPHinit(maxV);
    MakeFile = fopen("MakeFile", "r");
    posnome = 0;
    for(i = 0; i < maxV; i++ ) nome[i] = NULL;
    for(i = 0; i < maxV; i++ ) comandos[i] = NULL;
    for(i = 0; i < maxV; i++ ) mod_time[maxV] = -1;
    for(i = 0; i < maxV; i++ ) up_to_date[maxV] = FALSE;

    if (MakeFile == NULL){
        printf("ERRO: Arquivo MakeFile não encontrado\n");
        return 1;
    }
    readTargets(MakeFile, G);
    if ( argc > 1 )
    	if (strcmp( argv[1], "-s" )) {
		    MakeFiledg = fopen("MakeFile.dg", "w+");
    		writeMake(MakeFiledg, G);
		}

    return 0;
}
