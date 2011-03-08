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
		printf("Memoria Insuficiente. \n");
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
		printf("Memoria Insuficiente. \n");
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
		printf("Aluno nao encontrado. \n");
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
		printf("Disciplina nao encontrada. \n");
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
		printf("Nao existe alunos na disciplina %s %s \n", disc.sigla, disc.nome );
		return;
	}
	else {
		atual = disc.inicio;
		while ( atual != NULL ) {
			printf("%d %s \n", dado_a.vet_a[atual->ind_aluno].nusp, dado_a.vet_a[atual->ind_aluno].nome );
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
		printf("O aluno %s de numero usp %d nao esta em nenhuma disciplina \n", aluno.nome, aluno.nusp );
		return;
	}
	else {
		atual = aluno.inicio;
		while ( atual != NULL ) {
			printf("%s %s \n", dado_d.vet_d[atual->ind_disc].sigla, dado_d.vet_d[atual->ind_disc].nome );
			atual = atual->prox_aluno;
		}
	}
}

void matricula( int ind_a, int ind_d )
{
	pAluno_Disciplina novo, atual, prox1, prox2;
	Aluno aluno;
	Disciplina disc;
	aluno = dado_a.vet_a[ind_a];
	disc = dado_d.vet_d[ind_d];
	novo = malloc( sizeof( Aluno_Disciplina ) );
	if ( novo == NULL ) {
		printf("Memoria Insuficiente. \n");
		return;
	}
	novo->ind_disc = ind_d;
	novo->ind_aluno = ind_a;
	atual = dado_d.vet_d[ind_d].inicio;
	if ( atual == NULL ) {
		printf("O aluno %s de numero usp %d foi matriculado em %s %s. I\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
		dado_d.vet_d[ind_d].inicio = novo;
		novo->prox_disc = NULL;
	}	
	else {
		prox1 = atual->prox_disc;
		if ( prox1 == NULL ) {
			if ( strncmp( aluno.nome ,dado_a.vet_a[(atual->ind_aluno)].nome ,64 ) < 0 ) {
				printf("O aluno %s de numero usp %d foi matriculado em %s %s. II\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				dado_d.vet_d[ind_d].inicio = novo;
				novo->prox_disc = atual;
			}
			else if ( strncmp( aluno.nome ,dado_a.vet_a[(atual->ind_aluno)].nome ,64 ) == 0 ) { 
				printf("O aluno %s de numero usp %d ja esta matriculado em %s %s. I\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				free(novo);
				return;
			}
			else {
				printf("O aluno %s de numero usp %d foi matriculado em %s %s. III\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				prox1 = novo;
				novo->prox_disc = NULL;
			}
		}
		else {		
			while ( prox1 != NULL && strncmp( aluno.nome ,dado_a.vet_a[(atual->ind_aluno)].nome ,64 ) < 0 ) {
				atual = prox1;
				prox1 = prox1->prox_disc;
			}
			if ( strncmp( aluno.nome ,dado_a.vet_a[(atual->ind_aluno)].nome ,64 ) == 0 ) {
				printf("O aluno %s de numero usp %d ja esta matriculado em %s %s. II\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				free(novo);
				return;
			}	
			else {
				printf("O aluno %s de numero usp %d foi matriculado em %s %s. IIII\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				atual->prox_disc = novo;
				novo->prox_disc = prox1;
			}
		}
	}
	atual = dado_a.vet_a[ind_a].inicio;
	if ( atual == NULL ) {
		dado_a.vet_a[ind_a].inicio = novo;
		novo->prox_aluno = NULL;
	}
	else {
		prox2 = atual->prox_aluno;
		if ( prox2 == NULL ) {
				if ( strncmp( disc.sigla ,dado_d.vet_d[(atual->ind_disc)].sigla ,8 ) < 0 ) {
					dado_a.vet_a[ind_a].inicio = novo;
					novo->prox_disc = atual;
				}
				else if ( strncmp( disc.sigla ,dado_d.vet_d[(atual->ind_disc)].sigla ,8 ) == 0 ) { 
					free(novo);
					return;
				}
				else {
					prox2 = novo;
					novo->prox_disc = NULL;
				}
			}
		else {
			prox2 = atual->prox_aluno;
			while ( prox2 != NULL && strncmp( disc.sigla ,dado_d.vet_d[(atual->ind_disc)].sigla ,8 ) < 0 ) {
				atual = prox2;
				prox2 = prox2->prox_aluno;
			}
			if ( strncmp( disc.sigla ,dado_d.vet_d[(atual->ind_disc)].sigla ,8 ) == 0 ) {
				printf("O aluno %s de numero usp %d ja esta matriculado em %s %s. II\n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);	
				free(novo);
				return;
			}	
			else {
				atual->prox_aluno = novo;	
				novo->prox_aluno = prox2;
			}
		}
	}
	imprimealunos( ind_d );
}

void desmatricula( int ind_a, int ind_d )
{
	pAluno_Disciplina ant, atual, prox;
	Aluno aluno;
	Disciplina disc;
	aluno = dado_a.vet_a[ind_a];
	disc = dado_d.vet_d[ind_d];
	if ( dado_d.vet_d[ind_d].inicio == NULL ) {
		printf("Essa disciplina nao tem alunos!\n");
		return;
	}
	
	else {
		ant = dado_d.vet_d[ind_d].inicio;
		atual = dado_d.vet_d[ind_d].inicio;
		prox = atual->prox_disc;
		while ( prox != NULL ) {
			if ( strncmp( aluno.nome ,dado_a.vet_a[(atual->ind_aluno)].nome ,64 ) == 0 ) {
				printf("O aluno %s de numero usp %d foi desmatriculado em %s %s. \n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				ant = prox;
				free(atual);
				break;
			}
			ant = atual;
			atual = prox;
			prox = atual->prox_disc;		
		}
	}
	if ( dado_a.vet_a[ind_a].inicio == NULL ) {
		printf("Essa disciplina nao tem alunos!\n");
		return;
	}
	else {
		ant = dado_a.vet_a[ind_a].inicio;	
		atual = dado_a.vet_a[ind_a].inicio;
		prox = atual->prox_aluno;
		while ( prox != NULL ) {
			if ( strncmp( disc.sigla ,dado_d.vet_d[(atual->ind_disc)].nome ,64 ) == 0 ) {
				printf("O aluno %s de numero usp %d foi desmatriculado em %s %s. \n", aluno.nome, aluno.nusp, disc.sigla, disc.nome);
				ant = prox;
				free(atual);
				break;
			}
			ant = atual;
			atual = prox;
			prox = atual->prox_aluno;		
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
		printf("%c -> \n",uqfazer);
		getchar();
		switch (uqfazer) {
			case ('M'):
				fscanf( fp_i, "%d %s", &nusp, sigla );
				ind_a = buscaveta( nusp );
				ind_d = buscavetd( sigla );
				printf(" A:%d D:%d \n", ind_a, ind_d);
				matricula( ind_a, ind_d );
				break;
			case ('C'):						
				fscanf( fp_i, "%d %s", &nusp, sigla );
				ind_a = buscaveta( nusp );
				ind_d = buscavetd( sigla );
				desmatricula( ind_a, ind_d	);
				break;	
			case ('A'):
				fscanf( fp_i, "%s", sigla );
				ind_d = buscavetd( sigla );
				imprimealunos( ind_d );
				break;
			case ('D'):
				fscanf( fp_i, "%d", &nusp );
				ind_a = buscaveta( nusp );
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
	/*
	printf("Vet A:");
	getchar();
	imprimea();
 	printf("Vet D:");	
 	getchar();
 	imprimed();
 	*/
 	printf("Instrucoes");
 	getchar();
	leinstrucoes();
	
  fclose(fp_a);
  fclose(fp_d);
  fclose(fp_i);
  fclose(fp_s);
  return 0;
}
