#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tam. de uma linha */
#define MAXLN 1000
/* Tam. de uma palavra */
#define MAXP 50

void readTargets(FILE * MakeFile){
  char line[MAXLN];
  int terminou = 0;

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
    posLine = tam;

    while (sscanf(line+posLine, "%s %n", dep, &tam) == 1){
      printf("Adicionar a aresta %s->%s\n", target, dep);
      posLine += tam;
    }

    if (fgets(line, MAXLN, MakeFile) == NULL)
      break;
    /*printf("%s \n%cmacaco\n",line, line[0]);*/
    while (line[0] == '\t'){
      strcpy(com, line+1);
      com[strlen(com)-1] = '\0';
      printf("Adicionar \"%s\" à lista de comandos para %s\n", com, target);
      if (fgets(line, MAXLN, MakeFile) == NULL){
        terminou = 1;
	    break;
      }
    }
  }
}

int main(){
  FILE * MakeFile;
  
  MakeFile = fopen("MakeFile", "r");

  if (MakeFile == NULL){
    printf("ERRO: Arquivo MakeFile não encontrado\n");
    return 1;
  }
  readTargets(MakeFile);

  return 0;
}
