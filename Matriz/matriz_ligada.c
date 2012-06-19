#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "matriz_ligada.h"

/* funcao que libera a memoria utilizada por toda a matriz */
void freeMatriz(PtrNo inicio) {
	PtrNo aux, aux2, aux3;
	
	aux = inicio->prox_linha;
	while(aux != inicio) { /* laco que percorre todas as linhas cabecas */
		aux2 = aux->prox_coluna;
		while(aux2 != aux) { /* laco que deleta todas as coluna referentes a linha cabeca apontada por aux */
			aux3 = aux2;
			aux2 = aux2->prox_coluna;
			freeNo(aux3);
		}
		aux = aux->prox_linha;
		aux3 = aux2;
		freeNo(aux3); /* Aqui eu estou deletando a mesma posicao na memoria que esta sendo acessada na linha 49, eu sei que é errado
						mas ainda não pensei numa forma melhor de fazer isso */
	}
	freeNo(inicio);
}

/* funcao que libera a memoria de um no */
void freeNo(PtrNo no) {
	free(no);
}

/* aloca um novo nó e retorna o endereco */
PtrNo novoNo() {
	PtrNo novo;
	
	novo = (PtrNo) malloc(sizeof(TipoNo));
	
	if(novo == NULL) {
		printf("<novoNo()>Memoria insuficiente\n");
	}
	
	novo->prox_linha = NULL;
	novo->prox_coluna = NULL;
	
	return novo;
}

void imprimeMatriz(PtrNo inicio) {
	PtrNo aux, aux2; /* aux vai apontar para os nos cabecas das linhas e aux2 para as colunas da linha atual */
	int cols, linhas, i, j;
	
	cols = inicio->coluna;
	linhas = inicio->linha;
	
	i = 0;
	aux = inicio->prox_linha; /* aux comeca apontando para a 1a linha da matriz */
	while(i<linhas) { /* laco para imprimir a quantidade de linhas que tem a matriz */
		if(aux->linha > i || aux == inicio) { /* se o no cabeca para a linha atual nao existir, imprime toda a linha com 0.00 */
			for(j=0;j<linhas;j++) 
				printf("0.00 ");
		}else {
			j = 0;
			aux2 = aux->prox_coluna; /* aux2 comecao apontando para a 1a coluna da linha atual */
			while(j<cols) { /* linha para imprimir todas as colunas da linha atual */
				if(aux2->coluna == j) { /* se a coluna atual for igual a apontada por aux2, imprime o valor apontado por aux2 e passa para a proxima coluna */
					printf("%.2f ",aux2->valor);
					aux2 = aux2->prox_coluna;
				}else {
					printf("0.00 ");
				}
				j++;
			}
			aux = aux->prox_linha;
		}
		i++;
		printf("\n"); /* acabou a linha da matriz, pula uma linha */
	}
}

/* cria o nó inicio da nova matriz e retorna seu endereco */
PtrNo novaMatriz(int linhas, int cols) {
	PtrNo inicio;
	
	/* Alocando o No inicio */
	inicio = novoNo();
	inicio->linha = linhas;
	inicio->coluna = cols;
	inicio->prox_linha = inicio;
	inicio->prox_coluna = inicio;
	
	return inicio;
}

/* insere nó cabeca para a coluna/linha e retorna o endereco dessa nova cabeca */
PtrNo insereCabeca(PtrNo inicio, int linha, int coluna) {
	PtrNo aux, nova, aux2; /* nova aponta para o novo no cabeca; aux e aux2 sao usados para percorrer os nos cabecas ja criados */
	
	/* Criando o novo no */
	nova = novoNo();
	nova->linha = linha;
	nova->coluna = coluna;
	nova->prox_coluna = nova;
	nova->prox_linha = nova;
	
	
	
	/* Se a coluna for -1, o nó cabeca a ser inserido é de uma linha */
	if(coluna == -1) {
		aux = inicio->prox_linha; /* aux comeca apontando pra 1a linha da matriz */
		aux2 = inicio; /* aux2 comeca apontando para inicio */
		nova->prox_linha = inicio;
		
		while(aux != inicio && aux->linha < linha) { /* laco que percorre as linhas cabecas ate a posicao onde o novo no cabeca deve ficar */
			aux2 = aux; /* aux2 vai apontar para o que deve apontar para nova */
			aux = aux->prox_linha; /* aux vai apontar para o no que nova->prox_linha deve apontar */
		}

		aux2->prox_linha = nova; /* aux2 aponta para nova */
		nova->prox_linha = aux; /* nova aponta para aux */
	
		return nova;
	}
	/* Se a linha for -1, o nó cabeça a ser inserido é uma coluna. */ 
	/* A lógica para inserir um nó cabeça de coluna é mesma para um nó cabeça de linha */
	if(linha == -1) {
		aux = inicio->prox_coluna;
		aux2 = inicio;
		nova->prox_coluna = inicio;
		
		while(aux != inicio && aux->coluna < coluna) {
			aux2 = aux;
			aux = aux->prox_coluna;
		}
		
		aux2->prox_coluna = nova;
		nova->prox_coluna = aux;
		
		return nova;
	}

	return NULL;
}

/* insere novo valor na matriz */
int insereCasa(PtrNo inicio, int linha, int coluna,float valor) {
	PtrNo novo, aux, anterior, cabeca; /* novo vai apontar para o no do valor que esta sendo inserido; 
										aux e anterior sao usados para percorrer os nos da matriz; 
										cabeca armezena o endereco do no cabeca da linha e da coluna em que o novo valor sera inserido */
	
	if(linha >= inicio->linha || coluna >= inicio->coluna) { /* verifica se a posicao x,y nao é invalida */
		printf("<insereCasa()> Posicao de insercao(%d,%d) invalida, matriz de tamanho (%d,%d)\n",linha,coluna,inicio->linha,inicio->coluna);
		return 0;
	}
	
	/* Criando o novo no */
	novo = novoNo();
	novo->valor = valor;
	novo->coluna = coluna;
	novo->linha = linha;
	
	if(novo == NULL) {
		printf("<insereCasa()>Nao consegui criar o no ");
		return 0;
	}
	
	/* Ligando a linha */
	cabeca = inicio->prox_linha;
	while(cabeca->linha < linha && cabeca->prox_linha != inicio) /* laco que vai ateh a linha onde sera inserido o no */
		cabeca = cabeca->prox_linha;
	
	
	/* Verifica se nao existe no cabeça para aquela linha */
	if(cabeca->linha != linha) {
		cabeca = insereCabeca(inicio,linha,-1); /* cria nó cabeca para a linha e guarda endereco em cabeca */
	}
	
	aux = cabeca->prox_coluna; 
	anterior = cabeca;
	
	while(aux != cabeca && aux->coluna < coluna) { /* laco que vai ateh a coluna onde sera inserido o no */
		anterior = aux; /* anterior vai armezenar o endereco do no que vai apontar para o novo nó */
		aux = aux->prox_coluna; /* aux vai apontar para o nó que deve ser apontado por novo->prox_coluna */
	}
	
	if(aux->linha == novo->linha && aux->coluna == novo->coluna) { /* se a posicao que quer ser inserida ja existir, apenas substitui o valor */
		aux->valor = valor;
		return 0;
	}
	
	anterior->prox_coluna = novo;
	novo->prox_coluna = aux;
	/* ---------------- */
	
	/* Ligando a coluna. A lógica é mesma da ligação da linha */
	cabeca = inicio->prox_coluna;
	while(cabeca->coluna < coluna && cabeca->prox_coluna != inicio) { /* laco que vai ateh a coluna onde sera inserido o no */
		cabeca = cabeca->prox_coluna;
	}
	
	/* Verifica se nao existe no cabeça para aquela coluna */
	if(cabeca->coluna != coluna) {
		cabeca = insereCabeca(inicio,-1,coluna); /* cria nó cabeca para a coluna e guarda endereco em cabeca */
	}
	
	aux = cabeca->prox_linha;
	anterior = cabeca;
	while(aux != cabeca && aux->linha < linha) { /* laco que vai ateh a linha onde sera inserido o no */
		anterior = aux; /* anterior vai armezenar o endereco do no que vai apontar para o novo nó */
		aux = aux->prox_linha; /* aux vai apontar para o nó que deve ser apontado por novo->prox_linha */
	}

	anterior->prox_linha = novo;
	novo->prox_linha = aux;
	/* ---------------- */
	
	return 0;
}
