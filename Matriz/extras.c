#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "matriz_ligada.h"
#include "algebra.h"
#include "arquivo.h"

/* Funcao que desaloca a matriz da posicao pos do vetor e tira essa mesma matriz do vetor de ponteiros  */
void desalocaMatriz(PtrNo matrizes[], char *nomes[],int pos) {
	int i, total;
	PtrNo aux;
	
	free(matrizes[pos]); /* liberando a memoria da matriz alocada na posicao pos */
	
	total = contaMatrizes(matrizes);
	i = pos;
	while(i < total) { /* laco que percorre todo o vetor de matrizes e de nomes de matrizes e puxa uma posicao pra tras todos os valores que estao
							a frente da posicao deletada */
		matrizes[i] = matrizes[i+1];
		nomes[i] = nomes[i+1];
		i++;
	}
	
}


/* Conta a quantidade de matrizes carregadas na memoria */
int contaMatrizes(PtrNo* matrizes) {
	int i;
	
	i = 0;
	while(matrizes[i] != '\0') { /* soma 1 a variavel i até que o vetor matrizes chegue ao final */
		i++;
	}
	
	return i;
}

/* Funcao que libera a memoria das matrizes carregadas pelo programa */
void freeMatrizes(PtrNo matrizes[]) {
	int i = 0;
	
	while(matrizes[i] != '\0') { /* soma 1 a variavel i até que o vetor matrizes chegue ao final */
		free(matrizes[i]);
		i++;
	}
}

/* Funcao que libera a memoria das strings usadas para armazenar os nomes das matrizes */
void freeNomes(char* nomes[]) {
	int i = 0;
	
	while(nomes[i] != '\0') { /* soma 1 a variavel i até que o vetor matrizes chegue ao final */
		free(nomes[i]);
		i++;
	}
}

/* Carrega na memoria as matrizes passadas por argumento */
void carregaDeArgumento(int argc, char *argv[],PtrNo matrizes[],char *nomes_matrizes[]) {
	char nome_matriz[30]; /* string que vai guardar o nome das matrizes */
	int i;
	
	i = 1;
	while(i < argc && i < 11) { /* laco que percorre todos os argumentos passados ao programa (no maximo 10) */
		strcpy(nome_matriz,argv[i]);
		nome_matriz[strlen(nome_matriz)-4] = '\0'; /* retira a extensao do final da string */
		
		/*printf(" ");*/
		matrizes[i-1] = carregaMatriz(nome_matriz); /* salva na posicao i-1 do vetor matrizes o ponteiro para a matriz carregada */
	
		nomes_matrizes[i-1] = (char *) malloc(sizeof(char)*strlen(nome_matriz)); /* aloca uma string que ira conter o nome da matriz carregada em matrizes[i-1] */
		if(nomes_matrizes[i-1] == NULL) printf("PEEEEEEEEEEEE");
		
		strcpy(nomes_matrizes[i-1],nome_matriz); /* copia o conteudo de nome_matriz para a posicao i-1 de nome_matrizes */
	
		i++;
	}	
	
	if(i > 10) printf("ATENCAO: Foram carregadas as 10 primeiras matrizes passadas, as outras foram ignoradas\n");
	
	matrizes[i-1] = '\0'; /* colocar NULL no final do vetor para indicar seu término */
	nomes_matrizes[i-1] = '\0'; /* colocar NULL no final do vetor para indicar seu término */
}

/* Funcao que imprime todas as matrizes carregadas na memoria */
void imprimeListaMatrizes(PtrNo matrizes[], char* nomes_matrizes[]) {
	int i;

	i = 0;
	while(matrizes[i] != '\0') { /* laço que percorre todo o vetor de ponteiro para matrizes */
		printf("%d - %s (%d,%d)\n",i+1,nomes_matrizes[i],(matrizes[i]->linha)+1,(matrizes[i]->coluna)+1);		
		i++;
	}
}

/* Imprime uma matriz indicada pela usuario e previamente carregada na memoria */
void imprimir(PtrNo matrizes[], char *nomes_matrizes[]) {
	int n_matriz;
	char escolha[4];
		
	printf("\n");
	imprimeListaMatrizes(matrizes,nomes_matrizes); /* imprime uma lista com todas as matrizes carregadas na memória */
	printf("\nEscolha uma matriz para imprimir: ");
	gets(escolha); /* espera o usuario digitar uma string, e salva essa string em escolha */
	
	n_matriz = atoi(escolha); /* converte a string recebida do usuario para um inteiro */
	
	if(n_matriz < 1 || n_matriz > contaMatrizes(matrizes)) { /* verifica se o inteiro digitado pelo usuario corresponde a uma matriz */
		printf("Matriz invalida!\n");
	}else {
		printf("Imprimindo %s\n",nomes_matrizes[n_matriz-1]);
		imprimeMatriz(matrizes[n_matriz-1]); /* imprime a matriz escolhida */
		printf("\n");
	}
}

/* Apaga o arquivo de uma matriz carregada na memoria indicada pelo usuario */
void apagar(PtrNo matrizes[], char* nomes_matrizes[]) {
	int n_matriz;
	char escolha[4], nome_completo[30];
		
	printf("\n");
	imprimeListaMatrizes(matrizes,nomes_matrizes); /* imprime a lista de matrizes */
	printf("\nEscolha uma matriz para apagar: ");
	gets(escolha); /* pega a string digitada pelo usuario */
	
	n_matriz = atoi(escolha); /* converte para inteiro a string digitada pelo usuario */
	
	if(n_matriz < 1 || n_matriz > contaMatrizes(matrizes)) { /* verifica se o usuario digitou uma matriz valida */
		printf("Matriz invalida!\n");
	}else {
		printf("Apagando %s.\n",nomes_matrizes[n_matriz-1]);
		desalocaMatriz(matrizes,nomes_matrizes,n_matriz-1);
		sprintf(nome_completo,"%s.txt",nomes_matrizes[n_matriz-1]); /* adiciona a extensao do arquivo da matriz */
		remove(nome_completo); /* remove o arquivo */ 
	}
}

/* Funcao que salva uma matriz num arquivo se o usuario quiser */
void salvar(PtrNo mtr) {
	char tecla, nome[30];
	
	tecla = 'a';
	do {
		printf("\nDeseja salvar a matriz resultante em um arquivo? (s/n)");
		tecla = getch();
	} while(tecla != 's' && tecla != 'n');
		
	if(tecla == 's') {
		do {
			printf("\nDefina um nome para o arquivo (sem extensao, com o caminho (matrizes\nova por exemplo)): ");
			gets(nome);
		} while(strlen(nome) > 30 && strlen(nome) > 0);
		printf("Salvando %s...\n",nome);
		salvaMatriz(mtr,nome);
	}
}

/* Funcao que soma duas matrizes indicadas pelo usuario */
void somar(PtrNo matrizes[], char* nomes_matrizes[]) {
	int n_matriz1, n_matriz2;
	char escolha[4];
	PtrNo mtr_r, mtr_a, mtr_b;
	
	printf("\n");
	imprimeListaMatrizes(matrizes,nomes_matrizes);
	printf("\nEscolha uma matriz para somar: ");
	gets(escolha);
	
	n_matriz1 = atoi(escolha);
	
	if(n_matriz1 < 1 || n_matriz1 > contaMatrizes(matrizes)) {
		printf("Matriz invalida!\n");
		return;
	}
	
	printf("Escolha uma matriz para somar com %s: ",nomes_matrizes[n_matriz1-1]);
	gets(escolha);
	
	n_matriz2 = atoi(escolha);
	
	if(n_matriz2 < 1 || n_matriz2 > contaMatrizes(matrizes)) {
		printf("Matriz invalida!\n");
		return;
	}
	
	mtr_a = matrizes[n_matriz1-1]; /* mtr_a e mtr_b vao apontar para as matrizes escolhidas pelo usuario para serem somadas */
	mtr_b = matrizes[n_matriz2-1];
	
	if(mtr_a->coluna != mtr_b->coluna || mtr_b->linha != mtr_a->linha) { /* verifica se elas podem ser somadas */
		printf("Matrizes de tamanhos diferentes. Impossivel somar\n");
		return;
	}
	
	printf("Resultado da soma de %s + %s:\n",nomes_matrizes[n_matriz1-1],nomes_matrizes[n_matriz2-1]);
	mtr_r = somaMatriz(mtr_a,mtr_b); /* mtr_r aponta para a matriz resultante da soma */
	imprimeMatriz(mtr_r); /* imprime a matriz resultante */

	salvar(mtr_r);
	
	freeMatriz(mtr_r); /* libera a memoria alocada para a matriz resultante */
}
