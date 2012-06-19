#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include "avl.h"
#include "caixa.h"
#include "conio_v3.1.h"
#include "console_v1.3.1.h"
#include "desenho.h"

/* Retorna o numero de digitos de n */
int nDigitos(int n) {
	if(n == 0) return 1;
	else if(n >= 0) return ceil(log10(n+1));
	else return ceil(log10(fabs(n)+1))+1;
}

/* Função recursiva que calcula o tamanho ocupado por cada nó. Necessário para o calculo do posicionamento de todos os nós das arvores */
int geraLarguras(PNo raiz) {
	int tamanho_esq, tamanho_dir;
	
	if(raiz != NULL) {
		tamanho_esq = geraLarguras(raiz->esq); 
		tamanho_dir = geraLarguras(raiz->dir);
		
		raiz->tamanho_total = nDigitos(raiz->chave) +2 + tamanho_dir + tamanho_esq;
		if(raiz->esq && raiz->dir) raiz->tamanho_total++;
		
		return raiz->tamanho_total;
	}
	return 0;
}

/* Função que desenha as caixas dos nós e as linhas de ligação entre os pais e os filhos */
void desenha(PNo raiz,int nivel,int deslocamento, int x_pai) {
	int x, y;
	
	if (raiz != NULL) {
		x = ((raiz->tamanho_total-nDigitos(raiz->chave))/2)+deslocamento; /* calcula a coluna em que o nó deve ser desenhado */
		y = nivel*4; /* calcula a linha em que digito deve ser desenhado */
		/*gotoxy(1,1);
		printf("Desenhando %d em %d,%d",raiz->chave,x,y);
		getch();*/
		box(y,x,raiz->chave,0,15);	/* desenha o nó */	
		
		if(x_pai != -1) { /* se o nó tiver pai */
			line(x+(nDigitos(raiz->chave)/2),y-1,x_pai,((nivel-1)*4)+1); /* desenha a linha ligando o nó ao pai */
		}
		
		if(raiz->esq) desenha(raiz->esq,nivel+1,deslocamento+(raiz->tamanho_total/4)-(nDigitos((raiz->esq)->chave)+2)/2,x+(nDigitos(raiz->chave)/2)); /* chama mesma função para desenhar o filho esquerdo desse nó */
		if(raiz->dir && raiz->esq) desenha(raiz->dir,nivel+1,deslocamento+((raiz->tamanho_total/4)*3)-(nDigitos((raiz->dir)->chave)+2)/2,x+(nDigitos(raiz->chave)/2)); /* chama a mesma função para desenhar o filho direito desse nó */
		if(raiz->dir && !raiz->esq) desenha(raiz->dir,nivel+1,deslocamento+(raiz->tamanho_total/2)+1,x+(nDigitos(raiz->chave)/2));
	}
}

void desenhaCor(PNo raiz,int nivel,int deslocamento, int x_pai,int destaque) {
	int x, y;
	
	if (raiz != NULL) {
		x = ((raiz->tamanho_total-nDigitos(raiz->chave))/2)+deslocamento; /* calcula a coluna em que o nó deve ser desenhado */
		y = nivel*4; /* calcula a linha em que digito deve ser desenhado */
		if(raiz->chave == destaque) box(y,x,raiz->chave,0,4);
		else box(y,x,raiz->chave,0,15);	/* desenha o nó */	
		
		if(x_pai != -1) { /* se o nó tiver pai */
			line(x+(nDigitos(raiz->chave)/2),y-1,x_pai,((nivel-1)*4)+1); /* desenha a linha ligando o nó ao pai */
		}
		
		if(raiz->esq) desenhaCor(raiz->esq,nivel+1,deslocamento+(raiz->tamanho_total/4)-(nDigitos((raiz->esq)->chave)+2)/2,x+(nDigitos(raiz->chave)/2),destaque); /* chama mesma função para desenhar o filho esquerdo desse nó */
		if(raiz->dir && raiz->esq) desenhaCor(raiz->dir,nivel+1,deslocamento+((raiz->tamanho_total/4)*3)-(nDigitos((raiz->dir)->chave)+2)/2,x+(nDigitos(raiz->chave)/2),destaque); /* chama a mesma função para desenhar o filho direito desse nó */
		if(raiz->dir && !raiz->esq) desenhaCor(raiz->dir,nivel+1,deslocamento+(raiz->tamanho_total/2)+1,x+(nDigitos(raiz->chave)/2),destaque);
	}
}

/* Função que chama a função recursiva de desenho */
void desenhaArvore(PNo tree, int deslocamento) {
	desenha(tree,1,deslocamento,-1);
}

void desenhaArvoreCor(PNo tree, int deslocamento, int destaque) {
	desenhaCor(tree,1,deslocamento,-1,destaque);
}
