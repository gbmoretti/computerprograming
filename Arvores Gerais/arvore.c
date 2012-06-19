#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

/* Aloca um ponteiro de ponteiro que vai apontar para a raiz da arvore*/
PPNo novaArvore() {
	PPNo t;
	
	t = (PPNo) malloc(sizeof(PNo));
	*t = NULL;
	
	return t;
}

/* Aloca novo n� e retorna o endere�o */
PNo novoNo(int chave) {
	PNo novo;
	
	novo = (PNo) malloc(sizeof(No));
	novo->chave = chave;
	novo->n_filhos = 0;
	novo->filho = NULL;
	novo->irmao = NULL;
	
	return novo;
}

/* Busca um n� e caso esse n� existe retorna o endere�o dele */
PNo busca(PNo raiz,int chave, PNo no) {
	
	if(no == NULL && raiz != NULL) { /* se o n� que esta sendo buscado ainda nao foi encontrado e a raiz nao for nula */
		if(raiz->chave == chave) { 
			no = raiz; /* raiz � o n� que esta sendo buscado, guarda o endere�o dele no ponteiro no */
		}else {
			no = busca(raiz->filho,chave,no);
			no = busca(raiz->irmao,chave,no);
		}	
	}
	return no;	
}

/* Fun��o que retorna a altura da arvore */
int alturaArvore(PNo raiz) {
	int altura_filho, altura_irmao;
	
	altura_filho = altura_irmao = 0;	
	if(raiz) {
		if(raiz->filho)	altura_filho = alturaArvore(raiz->filho);
		if(raiz->irmao) altura_irmao = alturaArvore(raiz->irmao);
		if(raiz->filho == NULL && raiz->irmao == NULL) return 1; /* se o n� � folha, e n�o tem mais irm�o, retorna 1 */
		
		if(altura_filho > altura_irmao) { /* verifica qual n� tem altura maior, ele ou o seu irm�o. E retorna a maior altura  */
			return altura_filho+1;
		}else {
			return altura_irmao;
		}
	}
	return 0;
}

/* Insere um filho no n� especificado */
void insereFilho(PNo raiz, int chave_pai,int chave) {
	PNo novo, pai, aux;
	
	novo = novoNo(chave); /* aloca mem�ria para o novo n� */
	pai = busca(raiz,chave_pai,NULL); /* busca endere�o do pai do novo n� */
	
	if(pai) { /* se o pai existe, adiciona novo n� como filho dele */
		pai->n_filhos++; /* atualiza numero de filhos do n� pai */
		aux = pai->filho;
		pai->filho = novo;
		novo->irmao = aux;
	}else {
		printf("Pai %d nao encontrado\n",chave_pai);
	}
}

/* Seta valor de raiz */
void setaRaiz(PPNo raiz,int chave) {
	PNo novo;
	
	if(!*raiz) {
		novo = novoNo(chave);
		*raiz = novo;
	}
}

/* Imprime �rvore usando metodo pre-ordem */
void imprime(PNo raiz) {
	if(raiz != NULL) {
		printf(" %d (t: %d - n_filhos: %d)\n",raiz->chave,raiz->tamanho_total,raiz->n_filhos);
		imprime(raiz->irmao);
		imprime(raiz->filho);
	}
}
