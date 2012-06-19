#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "conio_v3.1.h"

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
	novo->esq = NULL;
	novo->dir = NULL;
	novo->balanc = 0;
	
	return novo;
}

/* Busca um nó e caso esse nó existe retorna o endereço dele */
PNo busca(PNo raiz,int chave, PNo no) {
	
	if(raiz != NULL) {
		if(raiz->chave == chave) {
			no = raiz;
		}else {
			if(chave > raiz->chave) {
				if(raiz->dir == NULL) no = raiz;
				else no = busca(raiz->dir,chave,no);
			}else  { 
				if(raiz->esq == NULL) no = raiz; 
				else no = busca(raiz->esq,chave,no);
			}
		}
	}
	/*gotoxy(1,1);*/
	/*printf("   Retornando %d",no->chave);*/
	return no;	
}


/* Insere um novo nó */
/* TEM QUE MUDAR ESSE AINDA!!! */
void insereNo(PPNo raiz,int chave) {
	PNo novo, pai;
	
	novo = novoNo(chave); /* aloca memória para o novo nó */
	pai = busca(*raiz,chave,NULL); /* busca endereço do pai do novo nó */
	
	if(pai) { /* se o pai existe, adiciona novo nó como filho dele */
		if(pai->chave == chave) {
			gotoxy(1,1);
			printf("Chave ja existe!\n");
		}else {
			if(chave > pai->chave) pai->dir = novo;
			else pai->esq = novo;
		}
	}
	balanceamento(raiz);
}

int balanceamento(PPNo raiz) {
	int alt_e, alt_d;
	
	printf("(");
	if(*raiz) {
		printf("%d)",(*raiz)->chave);
		alt_e = balanceamento(&(*raiz)->esq);
		alt_d = balanceamento(&(*raiz)->dir);
		(*raiz)->balanc = alt_e - alt_d;
		
		if((*raiz)->balanc < -1) { 
			if(((*raiz)->dir)->balanc < 0) rotacionaDir(raiz);
			else rotacionaDirEsq(raiz);
			alt_e = balanceamento(&(*raiz)->esq);
			alt_d = balanceamento(&(*raiz)->dir);
			(*raiz)->balanc = alt_e - alt_d;
		}
		
		if((*raiz)->balanc > 1) { 
			if(((*raiz)->esq)->balanc > 0) rotacionaEsq(raiz);
			else rotacionaEsqDir(raiz);
			alt_d = balanceamento(&(*raiz)->dir);
			alt_e = balanceamento(&(*raiz)->esq);
			(*raiz)->balanc = alt_e - alt_d;
		}
		
		if(alt_e > alt_d) return alt_e +1;
		else return alt_d +1;
	}else {
		return 0;
	}
}
void rotacionaDirEsq(PPNo raiz) {
	/*
	void rde(PpNo raiz){
	PpNo aux, aux2;
	aux=(PpNo)malloc(sizeof(PtNo));
	aux2=(PpNo)malloc(sizeof(PtNo));
	*aux=(*raiz)->dir;
	(*raiz)->dir=(*aux)->esq;
	*aux2=(*aux)->esq;
	(*aux)->pai=*aux2;
	(*aux2)->pai=*raiz;
	(*aux)->esq=(*aux2)->dir;
	(*aux2)->dir=*aux;
	re(raiz);
}

	*/
	PNo aux, aux2;
	
	gotoxy(1,1);
	printf("Fazendo rotacao direita-esquerda...\n");
	getch();
	
	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux2 = aux->esq;
	aux->esq = aux2->dir;
	aux2->dir = aux;
	rotacionaDir(raiz);
	
}
void rotacionaEsqDir(PPNo raiz) {
	PNo aux, aux2;
	
	gotoxy(1,1);
	printf("Fazendo rotacao esquerda-direita...\n");
	getch();
	
	aux = (*raiz)->esq;
	(*raiz)->esq = aux->dir;
	aux2 = aux->dir;
	aux->dir = aux2->esq;
	aux2->esq = aux;
	rotacionaEsq(raiz);
	
}

void rotacionaDir(PPNo raiz) {
	PNo q, temp;
	
	gotoxy(1,1);
	printf("Fazendo rotacao direita para o no %d...\n",(*raiz)->chave);
	getch();
	
	q = (*raiz)->dir;
	temp = q->esq;
	q->esq = *raiz;
	(*raiz)->dir = temp;
	*raiz = q;
		
}

void rotacionaEsq(PPNo raiz) {
	PNo q, temp;
	
	gotoxy(1,1);
	printf("Fazendo rotacao esquerda para o no %d...\n",(*raiz)->chave);
	getch();
	
	q = (*raiz)->esq;
	temp = q->dir;
	q->dir = *raiz;
	(*raiz)->esq = temp;
	*raiz = q;
	
}

/* TEM QUE MUDAR ESSE TBM */
void removeNo(PPNo raiz, int chave) {
	PNo pai, aux;
	
	pai = busca(*raiz,chave,NULL); /* busca pelo pai do nó que deve ser deletado */
	
	if(pai->chave > chave) {
		aux = pai->esq;
		if(aux->esq == NULL && aux->dir == NULL) {
			pai->esq = NULL;
			free(aux);
		}
	} else if(pai->chave < chave) {
		aux = pai->dir;
	} else {
		printf("OPS! (avl.c:removeNo())\n");
		exit(1);
	}	
}


int alturaArvore(PNo raiz) {
	int altura_esq, altura_dir;
	
	if(raiz) {
		altura_esq = alturaArvore(raiz->esq);
		altura_dir = alturaArvore(raiz->dir);
		if(raiz->esq == NULL && raiz->dir == NULL) return 1;
		
		if(altura_esq > altura_dir) {
			return altura_esq+1;
		}else {
			return altura_dir+1;
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

void freeArvore(PPNo raiz) {
	freeNos(*raiz);
	raiz = NULL;
	free(raiz);
}

void freeNos(PNo raiz) {
	if(raiz != NULL) {
		freeNos(raiz->esq);
		freeNos(raiz->dir);
		free(raiz);
	}
}

/* Imprime árvore usando metodo pre-ordem */
void imprime(PNo raiz) {
	if(raiz != NULL) {
		imprime(raiz->esq);
		printf("%d -- tt: %d -- balanc: %d\n",raiz->chave,raiz->tamanho_total,raiz->balanc);
		imprime(raiz->dir);
	}
}
