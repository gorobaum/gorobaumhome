/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

/* Tam. de uma linha */
#define MAXLN 1000
/* Tam. de uma palavra */
#define MAXP 50
#define maxV 100
#define Vertex int

static char *nome[maxV], *comandos[maxV];
static int posnome;

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
        
        if (fgets(line, MAXLN, MakeFile) == NULL)
            break;
        while (line[0] == '\t'){
            strcpy(com, line+1);
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
        if ( Arcs != NULL ) {
            fputs(nome[i], MakeFiledg);
            fputc(':', MakeFiledg);
            for ( j = 0; j < DIGRAPHNumArcs( i, G ); j++ ) {
                fputc(' ', MakeFiledg);
                fputs(nome[Arcs[j]], MakeFiledg);
                fputc(' ', MakeFiledg);
            }
            fputc('\n', MakeFiledg);
        }
        /*if ( comandos[i] != NULL ) {
            aux = comandos[i];
            last = comandos[i];
            while ( last != '\0' ) {
                if( aux[0] == ';' ) {
                    aux[1] = '\0';
                    fputs(last, MakeFiledg);
                    last = aux + 2*sizeof(char);
                }
                aux += sizeof(char);
            }
        }*/
    }
}

int main(){
    FILE * MakeFile, * MakeFiledg;
    Digraph G;
    int i;    

    G = DIGRAPHinit(maxV);
    MakeFile = fopen("MakeFile", "r");
    MakeFiledg = fopen("MakeFile.dg", "w+");
    posnome = 0;

    for(i = 0; i < maxV; i++ ) nome[i] = NULL;
    for(i = 0; i < maxV; i++ ) comandos[i] = NULL;

    if (MakeFile == NULL){
        printf("ERRO: Arquivo MakeFile não encontrado\n");
        return 1;
    }
    readTargets(MakeFile, G);
    writeMake(MakeFiledg, G);

    return 0;
}
