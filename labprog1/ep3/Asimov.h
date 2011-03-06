/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Bote.h - interface do tipo Bote, uma variacao de entidade.
          C nao e' orientado a objetos, mas implementamos um sistema de gerenciamento das entidades
          que faz com que seja bem parecido com OO.
          Assim, podemos dizer que um Bote e' praticamente uma derivacao do tipo basico de uma entidade.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/

#ifndef ASIMOV_H
#define ASIMOV_H

#include "Entity.h"

/*Cria o Asimov baseado nos defines do arquivo. */
Entity criaAsimov();

/*Funcoes Auxiliares*/
unsigned int getRaioAsimov(int Base, int Altura); /*Calcula o raio de um Asimov de base e altura passados.*/
#endif
