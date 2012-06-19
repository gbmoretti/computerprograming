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

/* Aloca novo n� e retorna o endere�o */
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

/* Busca um n� e caso esse n� existe retorna o endere�o dele */
PNo busca(PNo raiz,int chave, PNo no) {
	
	if(raiz != NULL) { /* se o ponteiro recebido por argumento nao for nulo */
		if(raiz->chave == chave) { /* se a chave for igual ao valor que a funcao deve encontrar */
			no = raiz; /* no recebe o endere�o de raiz */
		}else { /* se n�o */
			if(chave > raiz->chave) { /* se o valor procurado for maior que a chave do n� */
				if(raiz->dir == NULL) no = raiz; /* se o ponteiro nao existe, o n� procurado nao existe, retorna esse n� */
				else no = busca(raiz->dir,chave,no); /* se o ponteiro direito existe, faz a busca nesse n� */
			}else  { /* se o valor procurado for menor que a chave do n� */
				if(raiz->esq == NULL) no = raiz; /* se o ponteiro esquerdo for nulo, retorna o n� atual */
				else no = busca(raiz->esq,chave,no); /* se n�o, vai para o n� esquerdo */
			}
		}
	}
	return no;	
}


/* Insere um novo n� */
void insereNo(PPNo raiz,int chave) {
	PNo novo, pai;
	
	novo = novoNo(chave); /* aloca mem�ria para o novo n� */
	pai = busca(*raiz,chave,NULL); /* busca endere�o do pai do novo n� */
	
	if(pai) { /* se o pai existe, adiciona novo n� como filho dele */
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

/* Fun��o que calcula o fator de balanceamento da arvore */
int balanceamento(PPNo raiz) {
	int alt_e, alt_d;
	
	if(*raiz) {
		alt_e = balanceamento(&(*raiz)->esq); /* funcao balanceamento retorna a altura total da sub-arvore esquerda */
		alt_d = balanceamento(&(*raiz)->dir); /* mesma coisa para a sub-arvore direita */
		(*raiz)->balanc = alt_e - alt_d; /* calcula o fator de balanceamento do n� usando as alturas das sub-arvores como parametro */
		
		if((*raiz)->balanc < -1) { /* se o n� esta desbalanceado para direita */
			if(((*raiz)->dir)->balanc <= 0) rotacionaDir(raiz); /* se o n� filho da direita esta balanceado ou desbalanceado para direita, entao faz uma
																	rota��o simples para a direita*/
			else rotacionaDirEsq(raiz); /* se n�o, faz uma rota��o dupla direita-esquerda */
			alt_e = balanceamento(&(*raiz)->esq); /* recalcula os balanceamentos das sub-arvores */
			alt_d = balanceamento(&(*raiz)->dir);
			(*raiz)->balanc = alt_e - alt_d;
		}
		
		if((*raiz)->balanc > 1) { /* se o n� esta desbalanceado para a esquerda */
			if(((*raiz)->esq)->balanc >= 0) rotacionaEsq(raiz); /* se o n� filho da esquerda esta balanceado ou desbalanceado para esquerda, entao faz uma 
																	rota��o para esquerda */
			else rotacionaEsqDir(raiz); /* se n�o, faz uma rota��o dupla esquerda-direita */
			alt_d = balanceamento(&(*raiz)->dir); /* recalcula os balanceamentos das sub-arvores */
			alt_e = balanceamento(&(*raiz)->esq);
			(*raiz)->balanc = alt_e - alt_d;
		}
		/* retorna a altura do n� */
		if(alt_e > alt_d) return alt_e +1;
		else return alt_d +1;
	}else {
		return 0; /* se o n� nao existe, entao altura = 0 */
	}
}

/* Fun��o que faz a rota��o dupla direita-esquerda */
void rotacionaDirEsq(PPNo raiz) {
	gotoxy(1,1);
	printf("Fazendo rotacao direita-esquerda...\n");
	getch();
	
	rotacionaEsq(&(*raiz)->dir); /* primeiro faz uma rota��o a esquerda do n� a direita */
	rotacionaDir(raiz); /* depois uma rota��o a direita do n� desbalanceado */
}

/* Fun��o que faz a rota�ao dupla esquerda-direita */
void rotacionaEsqDir(PPNo raiz) {	
	gotoxy(1,1);
	printf("Fazendo rotacao esquerda-direita...\n");
	getch();
	
	rotacionaDir(&(*raiz)->esq); /* primeiro faz uma rota��o a direita do n� a esquerda */
	rotacionaEsq(raiz); /* depois faz uma rota��o a esquerda do n� desbalanceado */
	
}

/* Fun��o que faz a rota��o a direita */
void rotacionaDir(PPNo raiz) {
	PNo q, temp;
	
	gotoxy(1,1);
	printf("Fazendo rotacao direita para o no %d...\n",(*raiz)->chave);
	getch();
	
	q = (*raiz)->dir; /* q aponta para o filho a direita do n� */
	temp = q->esq; /* temp aponta para o n� a esquerda do n� apontado por q */
	q->esq = *raiz; /* filho esquerdo do n� apontado por q passa a apontar para o n� raiz da subarvore recebida pela fun��o */
	(*raiz)->dir = temp; /* filho direito do n� raiz aponta para o n� apontado por temp */
	*raiz = q; /* a nova raiz da subarvore recebida pela fun��o passa a ser q */
}

/* Fun��o que faz a rota��o a esquerda */
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
		else return altura_dir+1; /* se n�o, retorna a altura da subarvore direita +1 */
	}else { 
		return 0; /* se raiz n�o existe entao a altura = 0 */
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

/* libera a mem�ria ocupada por toda a arvore */
void freeArvore(PPNo raiz) {
	freeNos(*raiz);
	raiz = NULL;
	free(raiz);
}

/* libera a memoria ocupada por n� */
void freeNos(PNo raiz) {
	if(raiz != NULL) {
		freeNos(raiz->esq);
		freeNos(raiz->dir);
		free(raiz);
	}
}

/* Imprime �rvore usando metodo em-ordem */
void imprime(PNo raiz) {
	if(raiz != NULL) {
		imprime(raiz->esq);
		printf("%d -- tt: %d -- balanc: %d\n",raiz->chave,raiz->tamanho_total,raiz->balanc);
		imprime(raiz->dir);
	}
}
