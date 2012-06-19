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

/* Aloca novo nó e retorna o endereço */
PNo novoNo(int chave) {
	PNo novo;
	
	novo = (PNo) malloc(sizeof(No));
	novo->chave = chave;
	novo->n_filhos = 0;
	novo->filho = NULL;
	novo->irmao = NULL;
	
	return novo;
}

/* Busca um nó e caso esse nó existe retorna o endereço dele */
PNo busca(PNo raiz,int chave, PNo no) {
	
	if(no == NULL && raiz != NULL) { /* se o nó que esta sendo buscado ainda nao foi encontrado e a raiz nao for nula */
		if(raiz->chave == chave) { 
			no = raiz; /* raiz é o nó que esta sendo buscado, guarda o endereço dele no ponteiro no */
		}else {
			no = busca(raiz->filho,chave,no);
			no = busca(raiz->irmao,chave,no);
		}	
	}
	return no;	
}

/* Função que retorna a altura da arvore */
int alturaArvore(PNo raiz) {
	int altura_filho, altura_irmao;
	
	altura_filho = altura_irmao = 0;	
	if(raiz) {
		if(raiz->filho)	altura_filho = alturaArvore(raiz->filho);
		if(raiz->irmao) altura_irmao = alturaArvore(raiz->irmao);
		if(raiz->filho == NULL && raiz->irmao == NULL) return 1; /* se o nó é folha, e não tem mais irmão, retorna 1 */
		
		if(altura_filho > altura_irmao) { /* verifica qual nó tem altura maior, ele ou o seu irmão. E retorna a maior altura  */
			return altura_filho+1;
		}else {
			return altura_irmao;
		}
	}
	return 0;
}

/* Insere um filho no nó especificado */
void insereFilho(PNo raiz, int chave_pai,int chave) {
	PNo novo, pai, aux;
	
	novo = novoNo(chave); /* aloca memória para o novo nó */
	pai = busca(raiz,chave_pai,NULL); /* busca endereço do pai do novo nó */
	
	if(pai) { /* se o pai existe, adiciona novo nó como filho dele */
		pai->n_filhos++; /* atualiza numero de filhos do nó pai */
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

/* Imprime árvore usando metodo pre-ordem */
void imprime(PNo raiz) {
	if(raiz != NULL) {
		printf(" %d (t: %d - n_filhos: %d)\n",raiz->chave,raiz->tamanho_total,raiz->n_filhos);
		imprime(raiz->irmao);
		imprime(raiz->filho);
	}
}
