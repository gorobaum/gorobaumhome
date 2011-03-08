#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno             Aluno;
typedef struct disciplina        Disciplina;
typedef struct aluno_disciplina  Aluno_Disciplina;
typedef struct aluno_disciplina* pAluno_Disciplina;

FILE *fp_a; /* arquivo de alunos */
FILE *fp_d; /* arquivo de disciplinas */
FILE *fp_i; /* arquivo de instrucoes */
FILE *fp_s; /* arquivo de saida */

struct aluno_disciplina {
  int ind_aluno;
  int ind_disc;
  pAluno_Disciplina prox_aluno;
  pAluno_Disciplina prox_disc;
};

struct aluno {
  int               nusp;
  char              nome[64];
  pAluno_Disciplina inicio;
};

struct disciplina {
  char              sigla[8];
  char              nome[64];
  pAluno_Disciplina inicio;
};

typedef struct dados {
	Aluno *				vet_a;		
	Disciplina *	vet_d;
	int 				Tamanho;
}Dados;

Dados criaveta()
{
	int nalunos, i;
	Aluno * vet_a;
	Dados Alunos;
	fscanf( fp_a,"%d", &nalunos );
	Alunos.Tamanho = nalunos;
	vet_a = malloc( nalunos * sizeof(Aluno));
	if ( vet_a == NULL ) {
		printf("Memoria Insuficiente. \n");
		exit(0);
	}	
	for ( i = 0; i < nalunos; i++ ) {
		fscanf( fp_a, "%d", &(vet_a[i]).nusp );
		fgets( (vet_a[i]).nome, 64, fp_a);
	}
	Alunos.vet_a = vet_a;
	return Alunos;
}

Dados criavetd()
{
	int ndisci, i;
	Disciplina * vet_d;
	Dados Disciplina;
	fscanf( fp_d,"%d", &ndisci );
	Disciplina.Tamanho = ndisci;
	vet_d = malloc( ndisci * sizeof(Disciplina));
	if ( vet_d == NULL ) {
		printf("Memoria Insuficiente. \n");
		exit(0);
	}
	for ( i = 0; i < ndisci; i++ ) {
		fgets( (vet_d[i]).sigla, 8, fp_d);
		fgets( (vet_d[i]).nome, 64, fp_d);
	}
	Disciplina.vet_d = vet_d;
	return Disciplina;
}	

int buscaveta( Dados vet_a, Aluno buscado )
{
	int inicio, meio, fim;
	inicio = -1;
	fim = vet_a.Tamanho;
	while ( inicio < (fim-1) ) {
		meio = (inicio + fim)/2;
		if ( vet_a.vet_a[meio].nusp < buscado.nusp ) inicio = meio;
		else fim = meio;
	}
	return fim;
}

int buscavetd( Dados vet_d, Disciplina buscado )
{
	int inicio, meio, fim;
	inicio = -1;
	fim = vet_d.Tamanho;
	while ( inicio < (fim-1) ) {
		meio = (inicio + fim)/2;
		if ( strncmp( vet_d.vet_d[meio].sigla ,buscado.sigla, 8) <= 0 ) inicio = meio;
		else fim = meio;
	}
	return fim;
}

void matricula( Aluno aluno, Disciplina disc, Dados vet_a, Dados vet_d )
{
	pAluno_Disciplina novo, atual, prox;
	novo = malloc( sizeof( Aluno_Disciplina ) );
	if ( novo == NULL ) {
		printf("Memoria Insuficiente. \n");
		exit(0);
	} 
	novo->ind_disc = buscavetd( vet_d, disc );
	novo->ind_aluno = buscaveta( vet_a, aluno );
	if ( disc.inicio == NULL ) {
		disc.inicio = novo;
		novo->prox_aluno = NULL;
	}
	else {	
		atual = disc.inicio;
		prox = atual->prox_aluno;
		while ( prox != NULL ) {
			atual = prox;
			prox = atual->prox_aluno;		
			if ( strncmp( aluno.nome ,vet_a.vet_a[(atual->ind_aluno)].nome ,64 ) == 0 ) {
				printf("O aluno %s de numero usp %d ja esta matriculado em %s %s. \n", aluno.nome, aluno.nusp, disc.sigla, 	  disc.nome);
				free(novo);
				break;
			}	
			else if ( strncmp( aluno.nome ,vet_a.vet_a[(atual->ind_aluno)].nome ,64 ) < 0 ) {
				novo->prox_aluno = prox;
				atual->prox_aluno = novo;
				break;
			}
		}
	}
	if ( aluno.inicio == NULL ) {
		aluno.inicio = novo;
		novo->prox_disc = NULL;
	}
	else {	
		atual = aluno.inicio;
		prox = atual->prox_disc;
		while ( prox != NULL ) {
			atual = prox;
			prox = atual->prox_disc;		
			if ( strncmp( disc.sigla ,vet_d.vet_d[(atual->ind_disc)].sigla ,8 ) == 0 ) {
				printf("O aluno %s de numero usp %d ja esta matriculado em %s %s. \n", aluno.nome, aluno.nusp, disc.sigla, 	  disc.nome);
				free(novo);
				break;
			}	
			else if ( strncmp( disc.sigla ,vet_d.vet_d[(atual->ind_disc)].sigla ,8 ) < 0 ) {
				novo->prox_disc = prox;
				atual->prox_disc = novo;
				break;
			}
		}
	} 	
}

void imprimea( Dados d)
{
	int t;
	for ( t = 0; t <= d.Tamanho; t++ ) {
		printf("%d %s", d.vet_a[t].nusp, d.vet_a[t].nome);
	}
}

void imprimed( Dados d)
{
	int t;
	for ( t = 0; t <= d.Tamanho; t++ ) {
		printf("%s %s", d.vet_d[t].sigla, d.vet_d[t].nome);
	}
}
	  
int main(int argc, char *argv[])
     /* argc = numero de argumentos na linha de comando */
     /* argv = vetor de apontadores para strings contendo esses argumentos */
{
	Dados vet_a, vet_d;
	char nome_arq_a[64], nome_arq_d[64], nome_arq_i[64], nome_arq_s[64];

  if (argc < 5)
    {
      fprintf(stdout,
      "Uso: %s <arq_alunos> <arq_disc> <arq_instr> <arq_saida>\n",
      argv[0]);
      return -1;
    }
    
  if ((fp_a = fopen(argv[1],"r")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de alunos %s nao pode ser aberto.\n",
      argv[0], nome_arq_a);
      return -1;
    }
    
  if ((fp_d = fopen(argv[2],"r")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de disciplinas %s nao pode ser aberto.\n",
              argv[0], nome_arq_d);
      return -1;
    }
    
  if ((fp_i = fopen(argv[3],"r")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de instrucoes %s nao pode ser aberto.\n",
      argv[0], nome_arq_i);
      return -1;
    }
    
  if((fp_s = fopen(argv[4],"w")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de saida %s nao pode ser criado.\n",
      argv[0], nome_arq_s);
      return -1;
    }
  
  printf("Cria vet_a");
  getchar();  
  vet_a = criaveta();
  printf("Imprime vet_a");
  getchar();
  imprimea();
  printf("Cria vet_d");
  getchar();
	vet_d = criavetd();
  printf("Imprime vet_d");
  getchar();
	imprimed();
	
  fclose(fp_a);
  fclose(fp_d);
  fclose(fp_i);
  fclose(fp_s);
  return 0;
}

