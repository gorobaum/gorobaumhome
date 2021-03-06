/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "grafo.h"

#define MAXLN 1000 /* Tam. de uma linha */
#define MAXP 50 /* Tam. de uma palavra */
#define maxV 100
#define maxCom 10
#define Vertex int

typedef enum {FALSE,TRUE} Boolean;
static char  *nome[maxV];
static char  *comandos[maxV];
int           mod_time[maxV];
Boolean       up_to_date[maxV];
static int posnome;

/*	Funcao que procura target no vetor name. Se o acha, devolve a sua posicao no
	vetor, se nao devolve 0.*/
int lookfornome(char *target) {
    int i;
    for ( i = 1; i < maxV; i++) {
        if ( nome[i] == NULL ) return 0;
        else if ( strcmp(nome[i], target) == 0 ) return i;
    }
    return 0;
}

/*	Funcao que ve o instante da ultima modificacao de filename.*/
long mtime(const char *filename) {
   struct stat bufst;

   if (stat(filename, &bufst) == -1) return -1;
   return bufst.st_mtime;
}

/*	Funcao que le um MakeFile e cria o grafo correspondente.*/
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
            mod_time[posnome] = mtime( target );
        }
        posLine = tam;
        
        while (sscanf(line+posLine, "%s %n", dep, &tam) == 1){
            if ( lookfornome(dep) == 0 ) {
                nome[posnome] = malloc(tam*sizeof(char));
                strcpy( nome[posnome++], dep );
                mod_time[posnome] = mtime( dep );
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

/*	Funcao que cria o MakeFile.dg se -s foi passado para o Make.*/
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
					aux[0] = ';';
					aux += 1*sizeof(char);
					last = aux;
                }
            }
			fputc('\n', MakeFiledg);
        }
    }
}

/*	Essa funcao roda os comandos associados a um vertice, e retorna 1 se essa
	acao foi concluida com sucesso. Retorna 0 caso contrario.*/
int runComandos( Vertex v ) {
    char * aux, * last, **coms;
    int numcom, i;
    
    if ( comandos[v] == NULL ) return 1;
    for ( numcom = 0, aux = comandos[v]; aux[0] != '\0'; aux += sizeof(char) )
    	if ( aux[0] == ';' ) numcom++;  
    	
    coms = malloc(numcom*sizeof(char*));
    for ( i = 0; i < numcom; i++ ) {
    	coms[i] = malloc(MAXP*sizeof(char));
	}
    i = 0;
    aux = comandos[v];
    last = comandos[v];
 	while ( last[0] != '\0' ) {
		aux += sizeof(char);
		if( aux[0] == ';' ) {
			aux[0] = '\0';
			strcpy(coms[i], last);
			i++;
			aux[0] = ';';
			aux += 1*sizeof(char);
			last = aux;
		}
	}
	for ( i = 0; i < numcom; i++ ) if (system(coms[i]) != 0) return 0;
	return 1;
}
/* 	Funcao que cuida da atualizacao das dependencias dos goals e dos goals.
   	Ela cria uma ordenacao pos-ordem das dependencias do goal passado e com isso
   	vai atualizando-as conforme elas aparecem na ordenacao pos. Assim garantimos
   	que nenhuma dependencia sera atualizada antes de suas proprias dependencias. */
void rebuildTarget(Digraph G, Vertex v ) {
	int i, sop[maxV];

	for ( i = 0; i < maxV; i++ ) sop[i] = -1;
	
	if ( up_to_date[v] == FALSE) {
		if ( DIGRAPHcycle(G, v) == 0 ) {
			DIGRAPHdfs(G, v, sop);
			for ( i = 0; sop[i] != -1; i++ ) {
				if ( up_to_date[sop[i]] == FALSE ) {
					if ( runComandos( sop[i] ) == 1 ) up_to_date[sop[i]] = TRUE;
					else fprintf(stderr,"Erro na reconstrução do target %s.\n",nome[v]);
				}
			}
			if ( runComandos(v) == 1 ) {
				up_to_date[v] = TRUE;
			}
		}
		else {
			fprintf(stderr,"Ciclo detectado partindo de %s.\n", nome[v]);
		}
	}
}

/* Funcao que cuida do rebuild dos goals passados pelo usuario. */
void rebuildMakeFile(Digraph G, char* goals[], int numgoals ) {
	int i;
	Vertex s;
	
	for ( i = 0; i < numgoals; i++ ) {
		s = lookfornome(goals[i]);
		if ( s == 0 ) fprintf(stderr,"%s: goal nao encontrado.\n", goals[i]);
		else rebuildTarget(G, s);
	}
}

int main( int argc, char **argv ) {
    FILE * MakeFile, * MakeFiledg;
    Digraph G;
    int i, numgoals, write;
    char* goals[maxV];
	
	/*	Inicializacao das variaveis globais e locais.*/
    G = DIGRAPHinit(maxV);
    MakeFile = fopen("MakeFile", "r");
    posnome = 1;
    numgoals = argc-1;
    write = 0;
    for(i = 0; i < maxV; i++ ) {
    	nome[i] = NULL;
    	comandos[i] = NULL;
    	mod_time[i] = -1;
    	up_to_date[i] = FALSE;
    	goals[i] = malloc(MAXP*sizeof(char));
	}
	
    if (MakeFile == NULL){
        printf("ERRO: Arquivo MakeFile não encontrado\n");
        return 1;
    }
    
    /*	Final da inicializacao.*/
    readTargets(MakeFile, G);
    
    /*	Leitura dos parametros de entrada.*/
    if ( argc > 1 ) {
    	for ( i = 1; i < argc; i++ ) {
    		if ( strcmp( argv[i], "-s" ) == 0 ) {
    			write = 1;
    			numgoals--;
			}
    		else strcpy(goals[i-1-write], argv[i] );
		}
	}
	if ( numgoals == 0 ) {
		strcpy( goals[0], nome[1] );
		numgoals++;
	}
	/*	Final da leitura*/
	rebuildMakeFile(G, goals, numgoals);
	
	if ( write ) {
	 	MakeFiledg = fopen("MakeFile.dg", "w+");
		writeMake(MakeFiledg, G);
	}
    return 0;
}
