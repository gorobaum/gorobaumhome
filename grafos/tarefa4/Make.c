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

int lookfornome(char *target) {
    int i;
    for ( i = 1; i < maxV; i++) {
        if ( nome[i] == NULL ) return 0;
        else if ( strcmp(nome[i], target) == 0 ) return i;
    }
    return 0;
}

long mtime(const char *filename) {
   struct stat bufst;

   if (stat(filename, &bufst) == -1) return -1;
   return bufst.st_mtime;
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

int runComandos( Vertex v ) {
    char * aux, * last, **coms;
    int numcom, i;
    
    if ( comandos[v] == NULL ) return 1;
    
    for ( numcom = 0, aux = comandos[v]; aux[0] != '\0'; aux += sizeof(char) )
    	if ( aux[0] == ';' ) numcom++;  
    
    coms = malloc(numcom*sizeof(char*));
    for ( i = 0; i < numcom; i++ ) {
    	coms[i] = malloc(MAXP*sizeof(char));
    	coms[i] = '\0';
	}
    
    i = 0;
    aux = comandos[i];
    last = comandos[i];
 	while ( last[0] != '\0' ) {
		aux += sizeof(char);
		if( aux[0] == ';' ) {
			aux[0] = '\0';
			strcat(coms[i], last);
			printf("%s \n", coms[i]);
			i++;
			aux[0] = ';';
			aux += 1*sizeof(char);
			last = aux;
		}
	}
	
	for ( i = 0; i < numcom; i++ )
		if (system(coms[i]) != 0) {
			printf("Erro na reconstrução do target %s.\n",nome[v]);
 		 	fprintf(stderr,"Erro na reconstrução do target %s.\n",nome[v]);
 		 	return 0;
    	}
	return 1;
}

int rebuildTarget(Digraph G, Vertex v ) {
	int i, sop[maxV];
	printf("Rebuild de %d \n", v);
	getchar();
	for ( i = 0; i < maxV; i++ ) sop[i] = -1;
	
	if ( up_to_date[v] == FALSE) {
		if ( DIGRAPHcycle(G, v) == 0 ) {
			printf("Nao tem ciclo a partir de %d \n", v);
			DIGRAPHdfs(G, v, sop);
			for ( i = 0; sop[i] != -1; i++ ) {
				printf("sop[%d]=%d \n",i, sop[i]);
				if ( rebuildTarget(G, sop[i]) == 0 ) return 0;
			}
			for ( i = 0; sop[i] != -1; i++ ) {
				if ( mtime(nome[v]) < mtime(nome[sop[i]]) ) {
					if ( runComandos(v) == 1 ) {
						up_to_date[v] = TRUE;
						return 1;
					}
					else return 0;
				}
			}
		}
		else {
			printf("Ciclo detectado partindo de %s.\n", nome[v]);
			fprintf(stderr,"Ciclo detectado partindo de %s.\n", nome[v]);
			return 0;
		}
	}
	return 1;
}

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
    int i, numgoals;
    char* goals[maxV];

    G = DIGRAPHinit(maxV);
    MakeFile = fopen("MakeFile", "r");
    posnome = 1;
    numgoals = argc-1;
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
    
    readTargets(MakeFile, G);
    if ( argc > 1 && strcmp( argv[1], "-s" ) == 0) {
    	if ( argc == 2 ) strcpy( goals[0], nome[1] );
		else {
			for ( i = 2; i < argc; i++ ) {
				strcpy(goals[i-2], argv[i] );
				printf("%s \n", goals[i-2]);
			}
		}
		DIGRAPHshow(G);
		rebuildMakeFile(G, goals, numgoals);
	 	MakeFiledg = fopen("MakeFile.dg", "w+");
		writeMake(MakeFiledg, G);
	}
    return 0;
}
