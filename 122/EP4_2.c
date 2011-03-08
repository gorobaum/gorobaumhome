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

static Dados dado_a;
static Dados dado_d;

void criaveta()
{
	int nalunos, i;
	Aluno * vet_a;
	fscanf( fp_a,"%d", &nalunos );
	dado_a.Tamanho = nalunos;
	vet_a = malloc( nalunos * sizeof(Aluno));
	if ( vet_a == NULL ) {
		printf("\tMemoria Insuficiente. \n");
		exit(0);
	}	
	for ( i = 0; i < nalunos; i++ ) {
		fscanf( fp_a, "%d", &(vet_a[i]).nusp );
		fgetc( fp_a );
		fgets( (vet_a[i]).nome, 64, fp_a);
		vet_a[i].inicio = NULL;
	}
	dado_a.vet_a = vet_a;
}

void criavetd()
{
	int ndisci, i;
	Disciplina * vet_d;
	fscanf( fp_d,"%d", &ndisci );
	fgetc( fp_d );
	dado_d.Tamanho = ndisci;
	vet_d = malloc( ndisci * sizeof(Disciplina));
	if ( vet_d == NULL ) {
		printf("\tMemoria Insuficiente. \n");
		exit(0);
	}
	for ( i = 0; i < ndisci; i++ ) {
		fgets( (vet_d[i]).sigla, 8, fp_d);
		fgetc( fp_d );
		fgets( (vet_d[i]).nome, 64, fp_d);
		vet_d[i].inicio = NULL;
	}
	dado_d.vet_d = vet_d;
}	

int buscaveta( int buscado )
{
	int inicio, meio, fim;
	inicio = -1;
	fim = dado_a.Tamanho;
	while ( inicio < (fim-1) ) {
		meio = (inicio + fim)/2;
		if ( dado_a.vet_a[meio].nusp < buscado ) inicio = meio;
		else fim = meio;
	}
	if ( dado_a.vet_a[fim].nusp != buscado ) {
		printf("\tAluno nao encontrado. \n");
		return -1;
	}
	else return fim;
}

int buscavetd( char buscado[8] )
{
	int inicio, meio, fim;
	inicio = -1;
	fim = dado_d.Tamanho;
	while ( inicio < (fim-1) ) {
		meio = (inicio + fim)/2;
		if ( strncmp( dado_d.vet_d[meio].sigla, buscado, 8) < 0 ) inicio = meio;
		else fim = meio;
	}
	if ( strncmp( dado_d.vet_d[fim].sigla, buscado, 8) != 0 ) {
		printf("\tDisciplina nao encontrada. \n");
		return -1;
	}	
	else return fim;
}

void imprimealunos ( int ind_d )
{
	pAluno_Disciplina atual;
	Disciplina disc;
	disc = dado_d.vet_d[ind_d];
	if ( disc.inicio == NULL ) {
		printf("\tNao existe alunos na disciplina %s %s \n", disc.sigla, disc.nome );
		return;
	}
	else {
		atual = disc.inicio;
		printf("\n");
		while ( atual != NULL ) {
			printf("\t%d %s \n", dado_a.vet_a[atual->ind_aluno].nusp, dado_a.vet_a[atual->ind_aluno].nome );
			atual = atual->prox_disc;
		}
	}
}

void imprimedisc ( int ind_a )
{
	pAluno_Disciplina atual;
	Aluno aluno;
	aluno = dado_a.vet_a[ind_a];
	if ( aluno.inicio == NULL ) {
		printf("\tO aluno %s de numero usp %d nao esta em nenhuma disciplina \n", aluno.nome, aluno.nusp );
		return;
	}
	else {
		atual = aluno.inicio;
		printf("\n");
		while ( atual != NULL ) {
			printf("\t%s %s \n", dado_d.vet_d[atual->ind_disc].sigla, dado_d.vet_d[atual->ind_disc].nome );
			atual = atual->prox_aluno;
		}
	}
}

int comparanome( char nome1[64], char nome2[64] )
{
	int i = 64;
	char peq1[64], peq2[64];
	strcpy( peq1 ,nome1 );
	strcpy( peq2 ,nome2 );
	for ( i = 0; i < 64; i++ ) {
		if ( peq1[i] >= 'A' && peq1[i] <= 'Z' ) peq1[i] = ( peq1[i] - 'A' ) + 'a';
	}
	for ( i = 0; i < 64; i++ ) {
		if ( peq2[i] >= 'A' && peq2[i] <= 'Z' ) peq2[i] = ( peq2[i] - 'A' ) + 'a';
	}
	return strncmp( peq1 ,peq2 ,64 );	 
}

void matricula( int ind_a, int ind_d )
{
	pAluno_Disciplina novo, ult, prox;
	Aluno aluno;
	Disciplina disc;
	aluno = dado_a.vet_a[ind_a];
	disc = dado_d.vet_d[ind_d];
	novo = malloc( sizeof( Aluno_Disciplina ) );
	if ( novo == NULL ) {
		printf("\tMemoria Insuficiente. \n");
		return;
	}
	novo->ind_disc = ind_d;
	novo->ind_aluno = ind_a;
	ult = NULL;
	prox = dado_d.vet_d[ind_d].inicio;
	while ( prox != NULL && comparanome( aluno.nome ,dado_a.vet_a[(prox->ind_aluno)].nome ) > 0 ) {
		ult = prox;
		prox = prox->prox_disc;
	}
	if ( prox != NULL && comparanome( aluno.nome ,dado_a.vet_a[(prox->ind_aluno)].nome ) == 0 ) {
		printf("\tAluno de no. USP %d ja' esta matriculado em %s.\n", aluno.nusp, disc.sigla );
		free(novo);
		return;
	}
	if ( ult == NULL ) {
		dado_d.vet_d[ind_d].inicio = novo;
		novo->prox_disc = prox;
		printf("\tAluno de no. USP %d foi matriculado em %s.\n", aluno.nusp, disc.sigla );
	}
	else {
		ult->prox_disc = novo;
		novo->prox_disc = prox;
		printf("\tAluno de no. USP %d foi matriculado em %s.\n", aluno.nusp, disc.sigla );
	}
	ult = NULL;
	prox = dado_a.vet_a[ind_a].inicio;	
	while ( prox != NULL && strncmp( disc.sigla ,dado_d.vet_d[(prox->ind_disc)].sigla ,8 ) > 0 ) {
		ult = prox;
		prox = prox->prox_aluno;
	}
	if ( prox != NULL && strncmp( disc.sigla ,dado_d.vet_d[(prox->ind_disc)].sigla ,8 ) == 0 ) {
		free(novo);
		return;
	}
	if ( ult == NULL ) {
		dado_a.vet_a[ind_a].inicio = novo;
		novo->prox_aluno = prox;
	}
	else {
		ult->prox_aluno = novo;
		novo->prox_aluno = prox;
	}
}

void desmatricula( int ind_a, int ind_d )
{
	pAluno_Disciplina ant, prox;
	Aluno aluno;
	Disciplina disc;
	aluno = dado_a.vet_a[ind_a];
	disc = dado_d.vet_d[ind_d];
	ant = NULL;
	prox = dado_d.vet_d[ind_d].inicio;
	while ( prox != NULL && comparanome( aluno.nome ,dado_a.vet_a[(prox->ind_aluno)].nome ) != 0 ) {
		ant = prox;
		prox = prox->prox_disc;
	}
	if ( prox == NULL ) {
		if ( ant == NULL ) {
			printf("\tAluno de no. USP %d nao esta matriculado em %s. \n", aluno.nusp, disc.sigla);
			return;
		}
		else {
			ant->prox_disc = NULL;
			printf("\tMatricula do aluno de no. USP %d na disciplina %s foi cancelada. \n", aluno.nusp, disc.sigla);
		}
	}
	else {
		if ( ant == NULL ) {
			printf("\tMatricula do aluno de no. USP %d na disciplina %s foi cancelada. \n", aluno.nusp, disc.sigla);
			dado_d.vet_d[ind_d].inicio = prox->prox_disc;
		}
		else {
			ant->prox_disc = prox->prox_disc;
			printf("\tMatricula do aluno de no. USP %d na disciplina %s foi cancelada. \n", aluno.nusp, disc.sigla);
		}
	}
	ant = NULL;
	prox = dado_a.vet_a[ind_a].inicio;	
	while ( prox != NULL && strncmp( disc.sigla ,dado_d.vet_d[(prox->ind_disc)].sigla ,8 ) != 0 ) {
		ant = prox;
		prox = prox->prox_aluno;
	}
	if ( prox == NULL  ) {
		if ( ant == NULL ) {
			return;
		}
		else {
			ant->prox_aluno = NULL;
		}
	}
	else {
		if ( ant == NULL ) {
			dado_a.vet_a[ind_a].inicio = prox->prox_aluno;
		}
		else {
			ant->prox_aluno = prox->prox_aluno;
			free(prox);
		}
	}
}

void leinstrucoes()
{
	int nintruc, i, nusp, ind_d, ind_a ;
	char uqfazer, sigla[8];
	fscanf( fp_i, "%d", &nintruc );
	fgetc( fp_i );
	for ( i = 0; i < nintruc; i++) {
		uqfazer = fgetc( fp_i );
		switch (uqfazer) {
			case ('M'):
				fscanf( fp_i, "%d %s", &nusp, sigla );
				ind_a = buscaveta( nusp );
				ind_d = buscavetd( sigla );
				if ( ind_a == -1 ) {
					printf("O aluno de n. USP %d nao foi encontrado.\n", dado_a.vet_a[ind_a].nusp );				 
					break;
				}
				if ( ind_d == -1 ) {
					printf("A disciplina %s nao foi encontrado.\n", dado_d.vet_d[ind_d].sigla );				 
					break;
				}
				printf("%c %d %s \n", uqfazer, dado_a.vet_a[ind_a].nusp, dado_d.vet_d[ind_d].sigla);
				matricula( ind_a, ind_d );
				break;
			case ('C'):						
				fscanf( fp_i, "%d %s", &nusp, sigla );
				ind_a = buscaveta( nusp );
				ind_d = buscavetd( sigla );
				if ( ind_a == -1 ) {
					printf("O aluno de n. USP %d nao foi encontrado.\n", dado_a.vet_a[ind_a].nusp );				 
					break;
				}
				if ( ind_d == -1 ) {
					printf("A disciplina %s nao foi encontrado.\n", dado_d.vet_d[ind_d].sigla );				 
					break;
				}
				printf("%c %d %s \n", uqfazer, dado_a.vet_a[ind_a].nusp, dado_d.vet_d[ind_d].sigla);
				desmatricula( ind_a, ind_d	);
				break;	
			case ('A'):
				fscanf( fp_i, "%s", sigla );
				ind_d = buscavetd( sigla );
				if ( ind_d == -1 ) {
					printf("A disciplina %s nao foi encontrado.\n", dado_d.vet_d[ind_d].sigla );				 
					break;
				}
				printf("%c %s \n", uqfazer, dado_d.vet_d[ind_d].sigla);
				imprimealunos( ind_d );
				break;
			case ('D'):
				fscanf( fp_i, "%d", &nusp );
				ind_a = buscaveta( nusp );
				if ( ind_a == -1 ) {
					printf("O aluno de n. USP %d nao foi encontrado.\n", dado_a.vet_a[ind_a].nusp );				 
					break;
				}
				printf("%c %d \n", uqfazer, dado_a.vet_a[ind_a].nusp );
				imprimedisc( ind_a );
				break;
			default:
				printf("A instrucao passada nao esxiste! \n");
				break;	
		}
		fgetc( fp_i );
	}
}		

void imprimea()
{
	int t;
	for ( t = 0; t < dado_a.Tamanho; t++ ) {
		printf("%d %s", dado_a.vet_a[t].nusp, dado_a.vet_a[t].nome);
	}
}

void imprimed()
{
	int t;
	for ( t = 0; t < dado_d.Tamanho; t++ ) {
		printf("%s %s", dado_d.vet_d[t].sigla, dado_d.vet_d[t].nome);
	}
}
	  
int main(int argc, char *argv[])
     /* argc = numero de argumentos na linha de comando */
     /* argv = vetor de apontadores para strings contendo esses argumentos */
{
	
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
      argv[0], argv[1]);
      return -1;
    }
    
  if ((fp_d = fopen(argv[2],"r")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de disciplinas %s nao pode ser aberto.\n",
              argv[0], argv[2]);
      return -1;
    }
    
  if ((fp_i = fopen(argv[3],"r")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de instrucoes %s nao pode ser aberto.\n",
      argv[0], argv[3]);
      return -1;
    }
    
  if((fp_s = fopen(argv[4],"w")) == NULL)
    {
      fprintf(stderr,
      "%s: arquivo de saida %s nao pode ser criado.\n",
      argv[0], argv[4]);
      return -1;
    }
    
	criaveta();
	criavetd();
 	printf("Instrucoes");
	leinstrucoes();
	
  fclose(fp_a);
  fclose(fp_d);
  fclose(fp_i);
  fclose(fp_s);
  return 0;
}
