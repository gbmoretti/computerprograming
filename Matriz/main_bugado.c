#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "matriz_ligada.h"
#include "algebra.h"
#include "arquivo.h"

#define NUM_MATRIZES 30 /* numero que limita a quantidade de matrizes que o programar pode manipular */

/*
	ERRO!!!!!!!!!!!
	VER PQ A FUNCAO listaMatrizes() trava na segunda chamada dela durante a execucao do programa
*/

/* FUNCOES PRONTAS */
char** listaMatrizes(); /* funcao que retorna um vetor de strings com a lista de todas as matrizes salvas em arquivos */
void imprimeMatrizes(char**); /* funcao que imprime a lista de matrizes salvas no vetor de strings passado por parametro */
void freeLista(char**);


void verMatriz(char**); /* funcao que entra no modo Ver Matriz */
void somarMatriz(char**); /* funcao que entra no modo Somar Matrizes */

/* FUNCOES Q EU PROVAVELMENTE VOU TER QUE CONSTRUIR AQUI (ou num provavel extras.c) */
PtrNo constroiMatriz(); /* funcao que permite ao usuario construir uma matriz dentro do console */

/* funcao que retorna um vetor de strings com a lista de todas as matrizes salvas em arquivos */
char** listaMatrizes() {
	FILE *arq;
	char string[31], **lista;
	int i;
	
	system("dir /b matrizes\\*.txt > tmp");
	
	arq = fopen("tmp","r");
	
	if(arq==NULL) printf("PEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
	
	
	lista = (char**)malloc(sizeof(char)*NUM_MATRIZES);
	
	printf("serio vai a merda");
	i = 0;
	while(!feof(arq) && i < NUM_MATRIZES) {
		string[0] = '\0';
		fgets(string,30,arq);
		string[strlen(string)-5] = '\0'; /* cortando o \n e o .txt do final da string */
		
		lista[i] = (char*) malloc(sizeof(char)*strlen(string));
		strcpy(lista[i],string);
		
		i++;
	}
	
	lista[i-1] = '\0';
	
	fclose(arq);
	
	remove("tmp");

	
	return lista;
}

void verMatriz(char **lista) {
	char tecla[5];
	int i, opcao;
	PtrNo mtr;
	
	printf("\nVER MATRIZ\n");
	
	
	i = 0;
	while(lista[i] != '\0') {
		printf("%d - %s\n",i+1,lista[i]);
		i++;
	}
	printf("Escolha uma matriz para imprimir: ");
	
	gets(tecla);
	opcao = atoi(tecla);
	
	if(opcao < 1 || opcao > i+1) {
		printf("Matriz invalida!");
		return;
	}
	
	printf("\nImprimindo matriz %s:\n",lista[opcao-1]);
	

	mtr = carregaMatriz(lista[opcao-1]);
	
	imprimeMatriz(mtr);
	freeMatriz(mtr);
	
	printf("\n\n");
	freeLista(lista);
}

void somarMatriz(char **lista) {
	PtrNo mtr_a, mtr_b, mtr_r;
	char escolha[5], tecla, nome[31];
	int i, opcao;
	
	printf("\nSOMAR MATRIZES\n");
		
	i = 0;
	while(lista[i] != '\0') {
		printf("%d - %s\n",i+1,lista[i]);
		i++;
	}
	printf("\nEscolha uma matriz para somar: ");
	
	gets(escolha);
	opcao = atoi(escolha);
	mtr_a = carregaMatriz(lista[opcao-1]);
	
	i = 0;
	while(lista[i] != '\0') {
		printf("%d - %s\n",i+1,lista[i]);
		i++;
	}
	printf("\nEscolha a matriz para somar com %s: ",lista[opcao-1]);
	
	gets(escolha);
	opcao = atoi(escolha);
	mtr_b = carregaMatriz(lista[opcao-1]);

	if(mtr_a->coluna != mtr_b->coluna || mtr_a->linha != mtr_b->linha) {
		printf("ERRO: Matrizes de tamanho diferente. Impossivel fazer a soma\n");
		return;
	}
	
	mtr_r = somaMatriz(mtr_a,mtr_b);
	printf("\nResultado da soma:\n");
	imprimeMatriz(mtr_r);
	
	do {
		printf("\nDeseja salvar essa matriz em um arquivo? (s/n)\n");
		tecla = getch();
	} while(tecla != 's' && tecla != 'S' && tecla != 'n' && tecla != 'N');
	
	if(tecla == 'n' || tecla == 'N') {
		freeMatriz(mtr_r);
		freeMatriz(mtr_a);
		freeMatriz(mtr_b);
	}else {
		nome[0] = '\0';
		do {
			if(strlen(nome) >= 30) printf("A matriz deve ter no maximo 30 caracteres\n");
			printf("Digite um nome para a matriz: ");
			gets(nome);			
		} while(strlen(nome) > 30);
		printf("Salvando %s\n",nome);
		salvaMatriz(mtr_r,nome);
	}
	
	freeLista(lista);
}

void freeLista(char **lista) {
	int i = 0;
	
	while(lista[i] != '\0') {
		free(lista[i]);
		i++;
	}
	free(lista);
}

int main() {
	char tecla, **lista;
	int i;
	
	printf("Bem vindo!\n");
	
	do {
		printf("\nEscolha uma das opcoes:\nS - Somar matrizes\nV - Ver matriz\nQ - Sair\n");
		printf("Matrizes: ");
		
		lista = listaMatrizes(); /* grava a lista de matrizes no vetor de ponteiro lista */
		
		i = 0;
	
		while(lista[i] != '\0') {
			printf("(%d) %s, ",i,lista[i]);
			i++;
		}
		
		
		
		printf("\n");
		
		tecla = getch();

		switch(tecla) {
			case 's':
				somarMatriz(lista);
				break;
			case 'S':
				somarMatriz(lista);
				break;
			
			case 'V':
				verMatriz(lista);
				break;
			case 'v':
				verMatriz(lista);
				break;
			
			case 'q':
				break;
			case 'Q':
				break;
			
			default:
				printf("Opcao invalida\n");
		}
	} while(tecla != 'q' && tecla != 'Q');
	
	
	return 0;
}
