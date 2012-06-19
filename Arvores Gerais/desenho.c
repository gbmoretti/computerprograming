#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include "arvore.h"
#include "caixa.h"
#include "conio_v3.1.h"
#include "console_v1.3.1.h"
#include "desenho.h"

/* Retorna o numero de digitos de n */
int nDigitos(int n) {
	return ceil(log10(n+1));
}

/* Fun��o recursiva que calcula o tamanho ocupado por cada n�. Necess�rio para o calculo do posicionamento de todos os n�s das arvores */
int geraLarguras(PNo raiz) {
	int tamanho_irmao, tamanho_filho, tamanho_filhos;
	
	tamanho_irmao = 0;
	tamanho_filho = 0;
	if(raiz != NULL) {
		if(raiz->irmao) tamanho_irmao = geraLarguras(raiz->irmao); /* se o n� tem irm�os, chama a fun��o para gerar largura deles e salva o total na variavel */
		if(raiz->filho) { /* se o n� tem filho */
			tamanho_filho = geraLarguras(raiz->filho); /* gera a largura dos filhos, e salva o tamanho dela na variavel */
			tamanho_filhos = tamanho_filho + raiz->n_filhos -1; /* calcula o tamanho total dos filhos (com espa�amento) */
			raiz->tamanho_total = tamanho_filhos <= nDigitos(raiz->chave)+2 ? nDigitos(raiz->chave)+2 : tamanho_filhos;
			/* se o tamanho da caixa do n� atual for maior que a soma de todos os seus filhos, salva no campo tamanho_total a largura da caixa do n�
				se n�o, salva em tamanho_total o tamanho da soma das larguras dos filhos*/
		} else { /* se o n� nao tem filho */
			raiz->tamanho_total = nDigitos(raiz->chave) + 2; /* salva em tamanho_total apenas a largura da caixa dele */
		}
		return raiz->tamanho_total + tamanho_irmao; /* retorna a soma da largura do n� mais as larguras de seus irm�es */
	}
	return 0;
}

/* Fun��o que desenha as caixas dos n�s e as linhas de liga��o entre os pais e os filhos */
void desenha(PNo raiz,int nivel,int deslocamento, int x_pai) {
	int x, y;
	
	if (raiz != NULL) {
		x = ((raiz->tamanho_total-nDigitos(raiz->chave))/2)+deslocamento; /* calcula a coluna em que o n� deve ser desenhado */
		y = nivel*4; /* calcula a linha em que digito deve ser desenhado */
		box(y,x,raiz->chave,0);	/* desenha o n� */	
		
		if(x_pai != -1) { /* se o n� tiver pai */
			line(x+(nDigitos(raiz->chave)/2),y-1,x_pai,((nivel-1)*4)+1); /* desenha a linha ligando o n� ao pai */
		}
		
		if(raiz->irmao) desenha(raiz->irmao,nivel,(raiz->tamanho_total)+deslocamento,x_pai); /* chama mesma fun��o para desenhar o irm�o desse n� */
		if(raiz->filho) desenha(raiz->filho,nivel+1,deslocamento,x+(nDigitos(raiz->chave)/2)); /* chama a mesma fun��o para desenhar o filho desse n� */
	}
}

/* Fun��o que chama a fun��o recursiva de desenho */
void desenhaArvore(PNo tree, int deslocamento) {
	desenha(tree,1,deslocamento,-1);
}
