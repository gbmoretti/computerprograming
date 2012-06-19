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

PNo buscaPai(PNo raiz, PNo pai, int chave, PNo no) {
	if(no == NULL && raiz != NULL) { /* se o n� que esta sendo buscado ainda nao foi encontrado e a raiz nao for nula */
		if(raiz->chave == chave) { 
			no = pai; /* raiz � o n� que esta sendo buscado, guarda o endere�o dele no ponteiro no */
		}else {
			no = buscaPai(raiz->filho,raiz,chave,no);
			no = buscaPai(raiz->irmao,pai,chave,no);
		}	
	}
	return no;	
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

void removeNo(PPNo raiz, int chave) {
	PNo pai, aux, anterior, ultimo_filho;
	
	pai = buscaPai(*raiz,NULL,chave,NULL); /* busca pelo pai do n� que deve ser deletado */
	
	if(pai != NULL) { /* se o pai existe */
		aux = anterior = pai->filho;
		while(aux->chave != chave) { /* la�o que busca o n� a ser deletado */
			anterior = aux; /* anterior vai apontar para o n� anterior ao que deve ser deletado */
			aux = aux->irmao; /* aux vai apontar para o n� que deve ser deletado */
		}
		if(anterior != aux) {
			if(aux->filho != NULL) { /* se o n� a ser deletado tem filho */
				ultimo_filho = aux->filho;
				while(ultimo_filho->irmao != NULL) /* la�o que percorre os filhos do n� a ser deletado, at� encontrar o ultimo filho */
					ultimo_filho = ultimo_filho->irmao;
				ultimo_filho->irmao = aux->irmao;
				anterior->irmao = aux->filho;
			}else {
				anterior->irmao = aux->irmao;
			}
		}else { /* se o n� a ser deletado � o primeiro da lista dos filhos */
			if(aux->filho != NULL) {
				ultimo_filho = aux->filho;
				while(ultimo_filho->irmao != NULL) /* la�o que percorre os filhos do n� a ser deletado, at� encontrar o ultimo filho */
					ultimo_filho = ultimo_filho->irmao;
				ultimo_filho->irmao = aux->irmao;
				pai->filho = aux->filho;
			}else {
				pai->filho = aux->irmao;
			}
		}
		free(aux);
	}else { /* se o n� que deve ser deletado � a raiz */
		aux = (*raiz)->filho; /* aux recebe o primeiro filho da raiz, que vai ser a nova raiz */
		if(aux != NULL) {
			if(aux->filho != NULL) {
				ultimo_filho = aux->filho;
				while(ultimo_filho->irmao != NULL) /* precorre os filhos de aux at� chegar no ultimo filho */
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

/* Imprime �rvore usando metodo pre-ordem */
void imprime(PNo raiz) {
	if(raiz != NULL) {
		printf(" %d (t: %d - n_filhos: %d)\n",raiz->chave,raiz->tamanho_total,raiz->n_filhos);
		imprime(raiz->irmao);
		imprime(raiz->filho);
	}
}
