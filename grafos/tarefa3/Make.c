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


void readTargets(FILE * MakeFile){
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
        nome[posnome] = malloc(strlen(target)*sizeof(char));
        strcpy( nome[posnome++], target );
        /*printf("%s \n", nome[--posnome]);*/
        posLine = tam;

        while (sscanf(line+posLine, "%s %n", dep, &tam) == 1){
            /*printf("Adicionar a aresta %s->%s\n", target, dep);*/
            posLine += tam;
        }
        
        comandosaux = malloc(MAXLN*sizeof(char));
        if (fgets(line, MAXLN, MakeFile) == NULL)
            break;
        while (line[0] == '\t'){
            strcpy(com, line+1);
            com[strlen(com)-1] = ';';
            strcat(comandosaux, com);
            /*printf("%s \n", comandosaux);*/
            /*printf("Adicionar \"%s\" à lista de comandos para %s\n", com, target);*/
            if (fgets(line, MAXLN, MakeFile) == NULL){
                terminou = 1;
                free(comandosaux);
                break;
            }
        }
    }
}

int main(){
    FILE * MakeFile;
  
    MakeFile = fopen("MakeFile", "r");
    posnome = 0;
    poscomandos = 0;

    if (MakeFile == NULL){
        printf("ERRO: Arquivo MakeFile não encontrado\n");
        return 1;
    }
    readTargets(MakeFile);

    return 0;
}
