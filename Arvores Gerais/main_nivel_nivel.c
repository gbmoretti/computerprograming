#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include "arvore.h"
#include "caixa.h"
#include "conio_v3.1.h"
#include "lib_fila.h"
#include "lista_ligada.h"
#include "console_v1.3.1.h"

/* Estrutura usada na fila */
typedef struct _dados {
	int nivel; /* nivel do nó na arvore */
	PNo no_pai; /* ponteiro para nó (da arvore) do pai */
	PNo no_arvore; /* ponteiro para o nó (da arvore) */
} TDados, *PDados;

/* Função que gera uma lista ligada com todos os nós com as coordenadas de onde as caixas devem ser desenhadas */
ListaNo** geraLista(PNo raiz, int maxX, int maxY) {
	PNo aux;
	Fila *fila;/* fila usada para percorrer a arvore em largura */
	PDados dado, novo_dado;
	ListaNo **lista, *no_lista;
	int nivel, cont, nivel_ant, alinhamento, largura_prox_nivel, largura, tam;
	
	fila = novaFila(); /* cria nova fila */
	
	lista = (ListaNo**) malloc(sizeof(ListaNo*)); /* aloca na memoria o ponteiro para o ponteiro do 1o nó da lista */
	*lista = NULL;
	
	/* alocando dados do nó raiz (da arvore) na fila */
	dado = (PDados)malloc(sizeof(TDados));
	dado->no_arvore = raiz;
	dado->nivel = 1;
	dado->no_pai = NULL;
	
	Insere(fila,dado); /* insere nó raiz na fila */
	nivel_ant = 0;
	while(!estaVazia(fila)) { /* laço que percorre a arvore em largura */
		dado = Retira(fila); /* retira o proximo nó da fila, que passa a ser apontado por dado */
		nivel = dado->nivel; /* nivel  */
		if(nivel != nivel_ant) { /* se nivel for diferente de nivel_ant, é porque o laço passou para o próximo nivel da arvore */
			cont = 0; /* contador de nós de cada nivel é zerado */
			nivel_ant = nivel; /* nivel_ant passa a ser o mesmo que nivel */
			largura = largura_prox_nivel; /* largura recebe o valor de largura_prox_nivel. */
			largura_prox_nivel = 0; /* largura_prox_nivel é zerada */
			tam = 0; /* tam zerado */
		}
		if(dado->no_pai == NULL) { /* se o dado retirado da fila for a raiz */
			largura = ceil(log10((dado->no_arvore)->chave+1)) +2; /*seta largura como a quantidade de digitos da chave de raiz +2*/
		}
		
		Lista_novoNo(lista,(dado->no_arvore)->chave); /* cria novo nó na lista ligada, com o nó retirado da fila1 */
		no_lista = Lista_buscaValor(lista,(dado->no_arvore)->chave); /* no_lista aponta para esse nó recem-criado na lista */
		
		alinhamento = (ceil(largura/2) -maxX/2)*(-1); /* calcula o alinhamento do nó */
		/* salvando dados necesarios para a função desenha na lista ligada */
		no_lista->nivel = nivel; /* nivel do nó */
		no_lista->linha = nivel*4; /* coordenada Y da caixa desse nó */
		no_lista->coluna = tam + alinhamento; /* coordenada X da caixa desse nó */
		no_lista->pai = dado->no_pai; /* ponteiro para o pai do nó */
		/* ---------------- */
		
		aux = dado->no_arvore;
		if(aux->filho) { /* se o nó tem filho */
			nivel++;
			aux = aux->filho;
			do { /* laço que percorre os filhos do nó */ 
				if(aux) {
					/* Aloca dados do nó (da arvore) apontado por aux */
					novo_dado = malloc(sizeof(TDados));
					novo_dado->nivel = nivel;
					novo_dado->no_pai = no_lista;
					novo_dado->no_arvore = aux;
					/* ------------------------ */
					Insere(fila,novo_dado); /* insere nó filho na fila */
					largura_prox_nivel = largura_prox_nivel + ceil(log10(aux->chave+1)) + 3; /* calcula a largura total do proximo nível */
					aux = aux->irmao;
				}
			} while(aux);
		}
		tam = tam + ceil(log10((dado->no_arvore)->chave+1)) +3; /* soma ao tamanho do atual nivel o tamanho desse nó */
	}
	
	return lista; /* retorna o ponteiro para a lista ligada */
}

/* Função que recebe uma lista ligada com informações necessárias para desenhar a arvore no console */
void desenha(ListaNo **lista) {
	ListaNo *aux, *pai;
	int x1, y1, x2, y2;
	
	aux = *lista;
	while(aux!=NULL) { /* laço que desenha as caixas */
		box(aux->linha,aux->coluna,aux->valor,0);
		aux = aux->prox;
	}
	
	aux = *lista;
	while(aux!=NULL) { /* laço para desenhar as linhas ligando os filhos aos pais */
		pai = aux->pai;
		if(pai!=NULL) { /* se o nó nao for a raiz */
			x1 = aux->coluna + ((ceil(log10(aux->valor+1))) /2); /* calcula o X em que a linha deve começar (meio da caixa do nó filho) */
			y1 = aux->linha-1;
			x2 = pai->coluna + ((ceil(log10(pai->valor+1))) /2); /* calcula o X em que a linha deve terminar (meio da caixa do nó pai) */
			y2 = pai->linha+1;
			line(x1,y1,x2,y2);
		}
		aux = aux->prox;
	}
	
	gotoxy(1,(*lista)->nivel *5); /* reposiona cursor para ele ficar fora do desenho da arvore */
}

int main(int argc, char *argv[]) {
	int n, m, o, i;
	ListaNo **lista;
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
			scanf("%d",&m); /* seta quantos filho esse pai vai ter */
			for(i=0;i<m;i++) {
				scanf("%d",&o);
				insereFilho(*tree,n,o); /* insere filho "o" no pai "n" */
			}
		}
	}
	
	clrscr(); /* limpa a tela */
	lista = geraLista(*tree,tamanho_janela.X,tamanho_janela.Y); /* lista recebe o ponteiro da lista ligada com as informações necessárias para o desenho */
	desenha(lista); /* desenha a arvore */
	
	getch(); /* aguarda usuário apertão algum botão do teclado para encerrar o programa */
	return 0;
	
}
