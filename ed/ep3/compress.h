/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP3.c

Aluno:									Numero USP:
Thiago G. Nunes							6797289

19/06/2010

***********************************************************************************************************/

#ifndef COMPRESS_H_
#define COMPRESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct buffer* Buffer;

void CompressFile( FILE* Entry, FILE* Out );
void DecompressFile( FILE* Entry, FILE* Out );

#endif
