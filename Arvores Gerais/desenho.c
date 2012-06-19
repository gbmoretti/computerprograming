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

/* Função recursiva que calcula o tamanho ocupado por cada nó. Necessário para o calculo do posicionamento de todos os nós das arvores */
int geraLarguras(PNo raiz) {
	int tamanho_irmao, tamanho_filho, tamanho_filhos;
	
	tamanho_irmao = 0;
	tamanho_filho = 0;
	if(raiz != NULL) {
		if(raiz->irmao) tamanho_irmao = geraLarguras(raiz->irmao); /* se o nó tem irmãos, chama a função para gerar largura deles e salva o total na variavel */
		if(raiz->filho) { /* se o nó tem filho */
			tamanho_filho = geraLarguras(raiz->filho); /* gera a largura dos filhos, e salva o tamanho dela na variavel */
			tamanho_filhos = tamanho_filho + raiz->n_filhos -1; /* calcula o tamanho total dos filhos (com espaçamento) */
			raiz->tamanho_total = tamanho_filhos <= nDigitos(raiz->chave)+2 ? nDigitos(raiz->chave)+2 : tamanho_filhos;
			/* se o tamanho da caixa do nó atual for maior que a soma de todos os seus filhos, salva no campo tamanho_total a largura da caixa do nó
				se não, salva em tamanho_total o tamanho da soma das larguras dos filhos*/
		} else { /* se o nó nao tem filho */
			raiz->tamanho_total = nDigitos(raiz->chave) + 2; /* salva em tamanho_total apenas a largura da caixa dele */
		}
		return raiz->tamanho_total + tamanho_irmao; /* retorna a soma da largura do nó mais as larguras de seus irmões */
	}
	return 0;
}

/* Função que desenha as caixas dos nós e as linhas de ligação entre os pais e os filhos */
void desenha(PNo raiz,int nivel,int deslocamento, int x_pai) {
	int x, y;
	
	if (raiz != NULL) {
		x = ((raiz->tamanho_total-nDigitos(raiz->chave))/2)+deslocamento; /* calcula a coluna em que o nó deve ser desenhado */
		y = nivel*4; /* calcula a linha em que digito deve ser desenhado */
		box(y,x,raiz->chave,0);	/* desenha o nó */	
		
		if(x_pai != -1) { /* se o nó tiver pai */
			line(x+(nDigitos(raiz->chave)/2),y-1,x_pai,((nivel-1)*4)+1); /* desenha a linha ligando o nó ao pai */
		}
		
		if(raiz->irmao) desenha(raiz->irmao,nivel,(raiz->tamanho_total)+deslocamento,x_pai); /* chama mesma função para desenhar o irmão desse nó */
		if(raiz->filho) desenha(raiz->filho,nivel+1,deslocamento,x+(nDigitos(raiz->chave)/2)); /* chama a mesma função para desenhar o filho desse nó */
	}
}

/* Função que chama a função recursiva de desenho */
void desenhaArvore(PNo tree, int deslocamento) {
	desenha(tree,1,deslocamento,-1);
}
