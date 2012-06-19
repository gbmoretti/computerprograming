/* Programa Raiz
    Descri��o: Programa que demonstra como � feita a inser��o num �rvore AVL, mostrando todas as rota��es necess�rias para a 
	inser��o de cada n�.
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da �ltima modifica��o: 22/11/2010 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include "avl.h"
#include "caixa.h"
#include "conio_v3.1.h"
#include "console_v1.3.1.h"
#include "desenho.h"

void inserir(PPNo tree) {
	int nova_chave, largura, largura_antiga, altura;
	
	
	printf("Digite o valor do novo no: ");
	scanf("%d",&nova_chave); /* guarda o valor do novo n� em nova_chave */
	
	
	system("cls");
	largura_antiga = geraLarguras(*tree); /* gera a a largura da arvore, e guarda a largura total em largura_antiga */
	desenhaArvore(*tree,5); /* desenha a arvore sem altera��o do usuario */
	insereNo(tree,nova_chave); /* insere o n� que o usuario digitou */
	largura = geraLarguras(*tree); /* gera novamente as larguras, agora ja contando com o novo n� */
	desenhaArvoreCor(*tree,largura_antiga+5,nova_chave); /* desenha a nova arvore, colorindo o novo n� */
	altura = alturaArvore(*tree); /* altura recebe a altura da arvore */
	
	gotoxy((largura/2)+largura_antiga,altura*4+2);
	printf("Novo no: %d",nova_chave);
	
	getch();	
	
}

void menu(PPNo tree) {
	int altura_arvore;
	char opcao;
	
	do {
		system("cls");
		geraLarguras(*tree);  /* lista recebe o ponteiro da lista ligada com as informa��es necess�rias para o desenho */
		desenhaArvore(*tree,5);
		
		altura_arvore = alturaArvore(*tree);
		gotoxy(1,(altura_arvore+2)*4);
		imprime(*tree);
		printf("Escolha uma opcao:\n I - Inserir no\n F - Fechar\n");
		opcao = getch();
		switch(opcao) {
			case 'I':
				inserir(tree);
				break;
			case 'i':
				inserir(tree);
				break;
			case 'F':
				break;
			case 'f':
				break;
			default:
				printf("Opcao invalida\n");
		}
	} while(opcao != 'f' && opcao != 'F');
	
}

int main(int argc, char *argv[]) {
	int valor_raiz;
	PPNo tree;
	COORD tamanho_janela;
	
	tamanho_janela = MaxDimensaoJanela(); /* salva em tamanho_janela as dimens�es maximas do console */
	setDimensaoJanela(tamanho_janela.X,tamanho_janela.Y); /* seta o console com a maior dimens�o possivel para ele */
	setPosicaoJanela(0,0); /* posiciona janela no topo da tela */
	
	tree = novaArvore(); /* aloca nova arvore */
	
	printf("Digite o valor da raiz da arvore: ");
	scanf("%d",&valor_raiz);
	setaRaiz(tree,valor_raiz);
	
	menu(tree);

	return 0;
	
}
