/* Programa Raiz
    Descri��o: Programa que desenha uma �rvore geral (com n�s com n fihos) no console do windows. O programa ainda permite que o usuario insira/remova n�s
	em tempo de execu��o.
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da �ltima modifica��o: 05/10/2010 
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

void inserir(PPNo tree) {
	int chave_pai, nova_chave, largura, largura_antiga, altura;
	PNo pai;
	
	printf("Digite o valor do novo no: ");
	scanf("%d",&nova_chave); /* guarda o valor do novo n� em nova_chave */
	
	do { /* la�o que pergunta para o usuario escolher o pai do novo n� (mensagem se repete at� que o pai seja valido) */
		printf("Digite o valor do noh pai do novo noh: ");
		scanf("%d",&chave_pai);
		pai = busca(*tree,chave_pai,NULL);
	} while(pai == NULL);
	
	system("cls");
	largura_antiga = geraLarguras(*tree); /* gera a a largura da arvore, e guarda a largura total em largura_antiga */
	desenhaArvore(*tree,5); /* desenha a arvore sem altera��o do usuario */
	insereFilho(*tree,chave_pai,nova_chave); /* insere o n� que o usuario digitou */
	largura = geraLarguras(*tree); /* gera novamente as larguras, agora ja contando com o novo n� */
	desenhaArvoreCor(*tree,largura_antiga+5,nova_chave); /* desenha a nova arvore, colorindo o novo n� */
	altura = alturaArvore(*tree); /* altura recebe a altura da arvore */
	
	gotoxy((largura/2)+largura_antiga,altura*4+2);
	printf("Novo no: %d",nova_chave);
	gotoxy((largura/2)+largura_antiga,altura*4+3);
	printf("No pai: %d",chave_pai);
	
	getch();	
	
}

void remover(PPNo tree) {
	PNo no;
	int largura, largura_antiga, altura, chave;
	
	no = NULL;
	do { /* enquanto o usuario nao digitar um n� que exista na arvore, a mensagem se repete */
		printf("Digite o valor do no que deve ser deletado: ");
		scanf("%d",&chave);
		no = busca(*tree,chave,NULL);
	} while(no == NULL);	
	
	system("cls");
	largura_antiga = geraLarguras(*tree); /* gera novamente a largura, salvando a largura total em largura_antiga */
	desenhaArvoreCor(*tree,5,chave); /* desenha a arvore sem altera��o do usuario */
	altura = alturaArvore(*tree); /* altura recebe a altura total da arvore, antes da remo��o do n� escolhido pelo usuario */
	removeNo(tree,chave); /* remove o n� escolhido pelo usu�rio */
	largura = geraLarguras(*tree); /* gera a largura da arvore, j� com o novo n� */
	desenhaArvore(*tree,largura_antiga+5); /* desenha a nova arvore */
	
	gotoxy(largura_antiga/2,altura*4+2);
	printf("No removido: %d",chave);
	
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
		printf("Escolha uma opcao:\n I - Inserir no\n R - Remover no\n F - Fechar\n");
		opcao = getch();
		switch(opcao) {
			case 'I':
				inserir(tree);
				break;
			case 'i':
				inserir(tree);
				break;
			case 'R':
				remover(tree);
				break;
			case 'r':
				remover(tree);
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
	int n, n_filhos, valor_filho, i;
	PPNo tree;
	COORD tamanho_janela;
	
	tamanho_janela = MaxDimensaoJanela(); /* salva em tamanho_janela as dimens�es maximas do console */
	setDimensaoJanela(tamanho_janela.X,tamanho_janela.Y); /* seta o console com a maior dimens�o possivel para ele */
	setPosicaoJanela(0,0); /* posiciona janela no topo da tela */
	
	tree = novaArvore(); /* aloca nova arvore */
	
	scanf("%d",&n);
	if(n == 0) { /* proximo valor � raiz */
		scanf("%d",&n);
		setaRaiz(tree,n); /* setando raiz */
	}
	
	while(n != -1) {
		scanf("%d",&n); /* seta o pai */
		if(n != -1) {
			scanf("%d",&n_filhos); /* seta quantos filho esse pai vai ter */
			for(i=0;i<n_filhos;i++) {
				scanf("%d",&valor_filho);
				insereFilho(*tree,n,valor_filho); /* insere n� no pai "n" */
			}
		}
	}
	
	freopen("con", "r", stdin); /* muda arquivo de entrada para o console */
	menu(tree);

	return 0;
	
}
