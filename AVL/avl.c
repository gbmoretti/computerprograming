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
	
	if(raiz != NULL) { /* se o ponteiro recebido por argumento nao for nulo */
		if(raiz->chave == chave) { /* se a chave for igual ao valor que a funcao deve encontrar */
			no = raiz; /* no recebe o endereço de raiz */
		}else { /* se não */
			if(chave > raiz->chave) { /* se o valor procurado for maior que a chave do nó */
				if(raiz->dir == NULL) no = raiz; /* se o ponteiro nao existe, o nó procurado nao existe, retorna esse nó */
				else no = busca(raiz->dir,chave,no); /* se o ponteiro direito existe, faz a busca nesse nó */
			}else  { /* se o valor procurado for menor que a chave do nó */
				if(raiz->esq == NULL) no = raiz; /* se o ponteiro esquerdo for nulo, retorna o nó atual */
				else no = busca(raiz->esq,chave,no); /* se não, vai para o nó esquerdo */
			}
		}
	}
	return no;	
}


/* Insere um novo nó */
void insereNo(PPNo raiz,int chave) {
	PNo novo, pai;
	
	novo = novoNo(chave); /* aloca memória para o novo nó */
	pai = busca(*raiz,chave,NULL); /* busca endereço do pai do novo nó */
	
	if(pai) { /* se o pai existe, adiciona novo nó como filho dele */
		if(pai->chave == chave) { /* se a chave a ser inserida ja existe, mostra aviso na tela */
			gotoxy(1,1);
			printf("Chave ja existe!\n");
		}else {
			if(chave > pai->chave) pai->dir = novo;
			else pai->esq = novo;
		}
	}
	balanceamento(raiz); /* recalcula balanceamento da arvore */
}

/* Função que calcula o fator de balanceamento da arvore */
int balanceamento(PPNo raiz) {
	int alt_e, alt_d;
	
	if(*raiz) {
		alt_e = balanceamento(&(*raiz)->esq); /* funcao balanceamento retorna a altura total da sub-arvore esquerda */
		alt_d = balanceamento(&(*raiz)->dir); /* mesma coisa para a sub-arvore direita */
		(*raiz)->balanc = alt_e - alt_d; /* calcula o fator de balanceamento do nó usando as alturas das sub-arvores como parametro */
		
		if((*raiz)->balanc < -1) { /* se o nó esta desbalanceado para direita */
			if(((*raiz)->dir)->balanc <= 0) rotacionaDir(raiz); /* se o nó filho da direita esta balanceado ou desbalanceado para direita, entao faz uma
																	rotação simples para a direita*/
			else rotacionaDirEsq(raiz); /* se não, faz uma rotação dupla direita-esquerda */
			alt_e = balanceamento(&(*raiz)->esq); /* recalcula os balanceamentos das sub-arvores */
			alt_d = balanceamento(&(*raiz)->dir);
			(*raiz)->balanc = alt_e - alt_d;
		}
		
		if((*raiz)->balanc > 1) { /* se o nó esta desbalanceado para a esquerda */
			if(((*raiz)->esq)->balanc >= 0) rotacionaEsq(raiz); /* se o nó filho da esquerda esta balanceado ou desbalanceado para esquerda, entao faz uma 
																	rotação para esquerda */
			else rotacionaEsqDir(raiz); /* se não, faz uma rotação dupla esquerda-direita */
			alt_d = balanceamento(&(*raiz)->dir); /* recalcula os balanceamentos das sub-arvores */
			alt_e = balanceamento(&(*raiz)->esq);
			(*raiz)->balanc = alt_e - alt_d;
		}
		/* retorna a altura do nó */
		if(alt_e > alt_d) return alt_e +1;
		else return alt_d +1;
	}else {
		return 0; /* se o nó nao existe, entao altura = 0 */
	}
}

/* Função que faz a rotação dupla direita-esquerda */
void rotacionaDirEsq(PPNo raiz) {
	gotoxy(1,1);
	printf("Fazendo rotacao direita-esquerda...\n");
	getch();
	
	rotacionaEsq(&(*raiz)->dir); /* primeiro faz uma rotação a esquerda do nó a direita */
	rotacionaDir(raiz); /* depois uma rotação a direita do nó desbalanceado */
}

/* Função que faz a rotaçao dupla esquerda-direita */
void rotacionaEsqDir(PPNo raiz) {	
	gotoxy(1,1);
	printf("Fazendo rotacao esquerda-direita...\n");
	getch();
	
	rotacionaDir(&(*raiz)->esq); /* primeiro faz uma rotação a direita do nó a esquerda */
	rotacionaEsq(raiz); /* depois faz uma rotação a esquerda do nó desbalanceado */
	
}

/* Função que faz a rotação a direita */
void rotacionaDir(PPNo raiz) {
	PNo q, temp;
	
	gotoxy(1,1);
	printf("Fazendo rotacao direita para o no %d...\n",(*raiz)->chave);
	getch();
	
	q = (*raiz)->dir; /* q aponta para o filho a direita do nó */
	temp = q->esq; /* temp aponta para o nó a esquerda do nó apontado por q */
	q->esq = *raiz; /* filho esquerdo do nó apontado por q passa a apontar para o nó raiz da subarvore recebida pela função */
	(*raiz)->dir = temp; /* filho direito do nó raiz aponta para o nó apontado por temp */
	*raiz = q; /* a nova raiz da subarvore recebida pela função passa a ser q */
}

/* Função que faz a rotação a esquerda */
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

/* Retorna a altura da arvore */
int alturaArvore(PNo raiz) {
	int altura_esq, altura_dir;
	
	if(raiz) {
		altura_esq = alturaArvore(raiz->esq); /* calcula a altura da subarvore esquerda */
		altura_dir = alturaArvore(raiz->dir); /* calcula a altura da subarvore direita */
		
		if(altura_esq > altura_dir)	return altura_esq+1; /* se a altura da subarvore esquerda for maior que a altura da subarvore direita entao retorna 
															a altura esquerda +1 */
		else return altura_dir+1; /* se não, retorna a altura da subarvore direita +1 */
	}else { 
		return 0; /* se raiz não existe entao a altura = 0 */
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

/* libera a memória ocupada por toda a arvore */
void freeArvore(PPNo raiz) {
	freeNos(*raiz);
	raiz = NULL;
	free(raiz);
}

/* libera a memoria ocupada por nó */
void freeNos(PNo raiz) {
	if(raiz != NULL) {
		freeNos(raiz->esq);
		freeNos(raiz->dir);
		free(raiz);
	}
}

/* Imprime árvore usando metodo em-ordem */
void imprime(PNo raiz) {
	if(raiz != NULL) {
		imprime(raiz->esq);
		printf("%d -- tt: %d -- balanc: %d\n",raiz->chave,raiz->tamanho_total,raiz->balanc);
		imprime(raiz->dir);
	}
}
