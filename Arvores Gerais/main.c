/* Programa Raiz
    Descrição: Programa que desenha uma árvore geral (com nós com n fihos) no console do windows. O programa usa duas funções principais,
	uma que percorre todos os nós da árvore calculando a largura total de cada nó (a soma das larguras dos filhos desse nó). E outra função
	que desenha as caixas de cada nó e as linhas ligando os filhos aos pais, utilizando como informação a largura total de cada nó.
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da última modificação: 24/09/2010 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include "arvore.h"
#include "caixa.h"
#include "conio_v3.1.h"
#include "console_v1.3.1.h"
#include "desenho.h"

int main(int argc, char *argv[]) {
	int n, n_filhos, valor_filho, i, nivel;
	PPNo tree;
	COORD tamanho_janela;
	
	tree = novaArvore(); /* aloca nova arvore */
	
	tamanho_janela = MaxDimensaoJanela(); /* salva em tamanho_janela as dimensões maximas do console */
	setDimensaoJanela(tamanho_janela.X,tamanho_janela.Y); /* seta o console com a maior dimensão possivel para ele */
	setPosicaoJanela(0,0); /* posiciona janela no topo da tela */
	
	scanf("%d",&n);
	if(n == 0) { /* proximo valor é raiz */
		scanf("%d",&n);
		setaRaiz(tree,n); /* setando raiz */
	}
	
	while(n != -1) {
		scanf("%d",&n); /* seta o pai */
		if(n != -1) {
			scanf("%d",&n_filhos); /* seta quantos filho esse pai vai ter */
			for(i=0;i<n_filhos;i++) {
				scanf("%d",&valor_filho);
				insereFilho(*tree,n,valor_filho); /* insere nó no pai "n" */
			}
		}
	}
	
	system("cls"); /* limpa a tela. Usando a função sytem porque a crlscr() da conio não funciona para telas redimensionadas */
	
	geraLarguras(*tree); /* lista recebe o ponteiro da lista ligada com as informações necessárias para o desenho */
	desenhaArvore(*tree,5);
	nivel = alturaArvore(*tree);
	
	gotoxy(1,(nivel+1)*4);
	getch(); /* aguarda usuário apertão algum botão do teclado para encerrar o programa */
	return 0;
	
}
