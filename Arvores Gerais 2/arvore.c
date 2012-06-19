#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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

PNo buscaPai(PNo raiz, PNo pai, int chave, PNo no) {
	if(no == NULL && raiz != NULL) { /* se o nó que esta sendo buscado ainda nao foi encontrado e a raiz nao for nula */
		if(raiz->chave == chave) { 
			no = pai; /* raiz é o nó que esta sendo buscado, guarda o endereço dele no ponteiro no */
		}else {
			no = buscaPai(raiz->filho,raiz,chave,no);
			no = buscaPai(raiz->irmao,pai,chave,no);
		}	
	}
	return no;	
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

void removeNo(PPNo raiz, int chave) {
	PNo pai, aux, anterior, ultimo_filho;
	
	pai = buscaPai(*raiz,NULL,chave,NULL); /* busca pelo pai do nó que deve ser deletado */
	
	if(pai != NULL) { /* se o pai existe */
		aux = anterior = pai->filho;
		while(aux->chave != chave) { /* laço que busca o nó a ser deletado */
			anterior = aux; /* anterior vai apontar para o nó anterior ao que deve ser deletado */
			aux = aux->irmao; /* aux vai apontar para o nó que deve ser deletado */
		}
		if(anterior != aux) {
			if(aux->filho != NULL) { /* se o nó a ser deletado tem filho */
				ultimo_filho = aux->filho;
				while(ultimo_filho->irmao != NULL) /* laço que percorre os filhos do nó a ser deletado, até encontrar o ultimo filho */
					ultimo_filho = ultimo_filho->irmao;
				ultimo_filho->irmao = aux->irmao;
				anterior->irmao = aux->filho;
			}else {
				anterior->irmao = aux->irmao;
			}
		}else { /* se o nó a ser deletado é o primeiro da lista dos filhos */
			if(aux->filho != NULL) {
				ultimo_filho = aux->filho;
				while(ultimo_filho->irmao != NULL) /* laço que percorre os filhos do nó a ser deletado, até encontrar o ultimo filho */
					ultimo_filho = ultimo_filho->irmao;
				ultimo_filho->irmao = aux->irmao;
				pai->filho = aux->filho;
			}else {
				pai->filho = aux->irmao;
			}
		}
		free(aux);
	}else { /* se o nó que deve ser deletado é a raiz */
		aux = (*raiz)->filho; /* aux recebe o primeiro filho da raiz, que vai ser a nova raiz */
		if(aux != NULL) {
			if(aux->filho != NULL) {
				ultimo_filho = aux->filho;
				while(ultimo_filho->irmao != NULL) /* precorre os filhos de aux até chegar no ultimo filho */
					ultimo_filho = ultimo_filho->irmao;
				ultimo_filho->irmao = aux->irmao;
			}else {
				aux->filho = aux->irmao;
			}
			aux->irmao = NULL;
			free(*raiz);
			*raiz = aux;
		}else {
			printf("Ultimo no da arvore, nao pode ser deletado");
			getch();
		}
	}
		
	
}


int alturaArvore(PNo raiz) {
	int altura_filho, altura_irmao;
	
	if(raiz) {
		altura_filho = alturaArvore(raiz->filho);
		altura_irmao = alturaArvore(raiz->irmao);
		if(raiz->filho == NULL && raiz->irmao == NULL) return 1;
		
		if(altura_filho+1 > altura_irmao) {
			return altura_filho+1;
		}else {
			return altura_irmao;
		}
	}else { 
		return 0;
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

PPNo copiaArvore(PNo raiz) {
	PPNo nova;
	
	nova = novaArvore();
	setaRaiz(nova,raiz->chave);
	
	copiaNos(raiz->filho,*nova,raiz->chave);
	
	return nova;
}

void copiaNos(PNo velha,PNo nova,int pai) {
	if(velha != NULL) {
		insereFilho(nova,pai,velha->chave);
		copiaNos(velha->irmao,nova,pai);
		copiaNos(velha->filho,nova,velha->chave);
	}
}

void freeArvore(PPNo raiz) {
	freeNos(*raiz);
	raiz = NULL;
	free(raiz);
}

void freeNos(PNo raiz) {
	if(raiz != NULL) {
		freeNos(raiz->irmao);
		freeNos(raiz->filho);
		free(raiz);
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
