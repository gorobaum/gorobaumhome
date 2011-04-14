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
static int posnome, poscomandos;

int lookfornome(char *target) {
    int i;
    /*printf("%s \n", target);*/
    for ( i = 0; i < maxV; i++) {
        if ( nome[i] == NULL ) return 0;
        else if ( strcmp(nome[i], target) == 0 ) return i;
    }
    return 0;
}

void readTargets(FILE * MakeFile, Digraph G){
    char line[MAXLN];
    int terminou = 0;
    char *comandosaux;

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
        if ( lookfornome(target) == 0 ) {
            nome[posnome] = malloc(tam*sizeof(char));
            strcpy( nome[posnome++], target );
            /*printf("%s - %d\n", nome[posnome-1], posnome-1);*/
        }
        posLine = tam;

        while (sscanf(line+posLine, "%s %n", dep, &tam) == 1){
            if ( lookfornome(dep) == 0 ) {
                nome[posnome] = malloc(tam*sizeof(char));
                strcpy( nome[posnome++], dep );
                /*printf("%s - %d\n", nome[posnome-1], posnome-1);*/
            }
            DIGRAPHinsertA(G, lookfornome(dep), lookfornome(target));
            printf("Adicionar a aresta %d->%d\n", lookfornome(target), lookfornome(dep));
            posLine += tam;
        }
        
        comandosaux = malloc(MAXLN*sizeof(char));
        if (fgets(line, MAXLN, MakeFile) == NULL)
            break;
        while (line[0] == '\t'){
            strcpy(com, line+1);
            com[strlen(com)-1] = ';';
            strcat(comandosaux, com);
            printf("%s \n", comandosaux);
            /*printf("Adicionar \"%s\" à lista de comandos para %s\n", com, target);*/
            if (fgets(line, MAXLN, MakeFile) == NULL){
                terminou = 1;
                break;
            }
        }
        comandos[poscomandos] = malloc(strlen(comandosaux)*sizeof(char));
        strcpy(comandos[poscomandos++], comandosaux );
        free(comandosaux);
    }
}

int main(){
    FILE * MakeFile;
    Digraph G;
    int i;    

    G = DIGRAPHinit(maxV);
    MakeFile = fopen("MakeFile", "r");
    posnome = 0;
    poscomandos = 0;

    for(i = 0; i < maxV; i++ ) nome[i] = NULL;

    if (MakeFile == NULL){
        printf("ERRO: Arquivo MakeFile não encontrado\n");
        return 1;
    }
    readTargets(MakeFile, G);

    return 0;
}
