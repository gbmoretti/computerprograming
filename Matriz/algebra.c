#include "matriz_ligada.h"
#include <stdio.h>

/* Funcao que soma duas matrizes e retorna o endereço de uma 3a matriz que contem o resultado da soma */
PtrNo somaMatriz(PtrNo mtr_a,PtrNo mtr_b) {
	PtrNo mtr_r; /* ponteiro para a matriz resultante da soma */
	PtrNo aux_a, aux_b, aux2_a, aux2_b;
	
	/* Verifica se as duas matrizes são do mesmo tamanho */
	if(mtr_a->linha != mtr_b->linha || mtr_a->coluna != mtr_b->coluna) {
		printf("<somaMatriz()>Erro! Matrizes nao sao do mesmo tamanho\n");
		return NULL;
	}
	
	mtr_r = novaMatriz(mtr_a->linha,mtr_a->coluna); /* criando a matriz resultante */
	
	aux_a = mtr_a->prox_linha;
	aux_b = mtr_b->prox_linha;
	while(aux_a != mtr_a || aux_b != mtr_b) { /* laco para percorrer todas as linhas das matrizes A e B */
		if(aux_a->linha == aux_b->linha) { /* a linha existe nas duas matrizes */
			aux2_a = aux_a->prox_coluna; /* ponteiros de coluna das duas matrizes apontando para o primeiro valor da primeira linha das matrizes */
			aux2_b = aux_b->prox_coluna;
			while(aux2_a->coluna != -1 || aux2_b->coluna != -1) { /* enquanto aux2_a e aux2_b não voltam ao nó cabeça da linha atual */
				if(aux2_a->coluna == aux2_b->coluna) { /* se essa casa existe nas duas matrizes */
					insereCasa(mtr_r,aux2_a->linha,aux2_a->coluna,aux2_a->valor+aux2_b->valor); /* soma o valor da casa das duas matrizes e cola na matriz resultada */
					aux2_a = aux2_a->prox_coluna; /* anda com o ponteiro da matriz A e da matriz B */
					aux2_b = aux2_b->prox_coluna;	
				}else { /* essa casa existe apenas em uma das matrizes */
					
					if((aux2_a->coluna < aux2_b->coluna && aux2_a->coluna != -1) || aux2_b->coluna == -1) { /* se a coluna de aux2_a for menor que a coluna de aux2_b ou a coluna de aux2_b ja voltou ao no cabeca */
						insereCasa(mtr_r,aux2_a->linha,aux2_a->coluna,aux2_a->valor); /* insere a casa da matriz A à matriz resultante */
						aux2_a = aux2_a->prox_coluna; /* anda apenas com o ponteiro de colunas da matriz A */
					}else {
						if((aux2_b->coluna < aux2_a->coluna && aux2_b->coluna != -1) || aux2_a->coluna == -1) { /* se a coluna de aux2_b for menor que a coluna de aux2_a ou a coluna de aux2_a ja voltou ao no cabeca */
							insereCasa(mtr_r,aux2_b->linha,aux2_b->coluna,aux2_b->valor); /* insere a casa da matria B à matriz resultante */
							aux2_b = aux2_b->prox_coluna; /* anda apenas com o ponteiro de colunas da matriz B */
						}
					}
				}
				
			}
			aux_a = aux_a->prox_linha;
			aux_b = aux_b->prox_linha;
		}else { /* a linha existe apenas em uma das matrizes */
			if(aux_a->linha < aux_b->linha) { /* se a linha de aux_a for menor que a linha de aux_b */
				aux2_a = aux_a->prox_coluna;
				while(aux2_a->coluna != -1) { /* laco que percorre toda a linha da matriz A e adiciona na matriz resultante */
					insereCasa(mtr_r,aux2_a->linha,aux2_a->coluna,aux2_a->valor); 
					aux2_a = aux2_a->prox_coluna;
				}
				aux_a = aux_a->prox_linha; /* anda com o ponteiro de linha da matriz A */
			}else { /* a linha de aux_b é menor que a linha de aux_a */
				aux2_b = aux_b->prox_coluna;
				while(aux2_b->coluna != -1) { /* laco que percorre toda a linha da matriz B e adiciona na matriz resultante */
					insereCasa(mtr_r,aux2_b->linha,aux2_b->coluna,aux2_b->valor);
					aux2_b = aux2_b->prox_coluna;
				}
				aux_b = aux_b->prox_linha; /* anda com o ponteiro de linha da matriz B */
			}
		}
	}
	
	return mtr_r;
}
