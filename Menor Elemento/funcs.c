#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include "funcs.h" 
#include <conio.h>

/* Funcao que aloca um novo nó */
PNo novoNo(int valor) {
	PNo novo;
	
	novo = (PNo) malloc(sizeof(No)); /* aloca espaço na memoria para o no e salva o endereço em novo */
	novo->valor = valor;
	novo->prox = novo->maiores = NULL;
	
	return novo; /* retorna o endereco do no alocado */
}

/* Insere um novo valor na lista ligada. O último nó inserido será sempre o primeiro da lista (menor complexidade de inserção) */
void insereValor(PPNo inicio,int valor) {
	PNo novo;
	
	novo = novoNo(valor); /* aloca o novo nó */
	
	novo->prox = *inicio; /* o ponteiro prox do novo nó passa a apontar para o antigo 1o elemento da lista */
	*inicio = novo; /* o ponteiro que indica o inicio da lista passa a apontar para o novo nó */
	
}

void insereMaior(PPNo inicio,PNo valor) {
	PNo aux;
	while(valor->maiores != NULL) { /* desaloca os nós que estavam na lista de valores comparadas com o nó apontador por "valor". Eles não serão mais usados */
		aux = valor->maiores;
		valor->maiores = aux->prox;
		free(aux);
	}
	
	valor->prox = *inicio; /* o ponteiro prox do novo nó passa a apontar para o antigo 1o elemento da lista */
	*inicio = valor; /* o ponteiro que indica o inicio da lista passa a apontar para o novo nó */
}

/* Retorna o numero maximo de comparações que o programa deve fazer */
int maxComps(int n) { 
	return n + ceil(log10(n)/log10(2)) -2;
}

/* Imprime uma lista ligada */
void imprime(PPNo inicio) {
	PNo aux;
	
	aux = *inicio;
	while(aux != NULL) {
		printf("%d ",aux->valor);
		aux = aux->prox;
	}
	printf("\n");
}

/* Retorna um nó com o menor elemento da lista apontada por inicio, e guarda nesse nó uma lista com todos os nós que foram comparados com ele */
PNo menorElemento(PPNo inicio) {
	PNo aux, prox, menor_anterior, prox_prox;
	
	aux = prox = *inicio;
	menor_anterior = NULL;
	while(aux != NULL && prox != NULL) { /* laço que percorre a lista até o fim */
		prox = aux->prox;
		if(prox) { /* se prox nao apontar para NULL, é porque aux aponta para um nó e prox para outro e podemos comparar os dois */
			comps++; /* conta mais uma comparação */
			prox_prox = prox->prox; /* salva o ponteiro para nó que vai ser usado na proxima compação */
			if(aux->valor < prox->valor) { /* se o valor do nó apontado por aux for maior que que o valor de prox */
				insereMaior(&aux->maiores,prox); /* insere o nó maior (apontado por prox) na lista de valores maiores do nó 
															apontado por aux */
				if(menor_anterior) menor_anterior->prox = aux; /* se menor_anterior estiver setado, ele passa a apontar para aux (que é o menor valor) */
				aux->prox = NULL; /* aux passa a ser o final da lista ligada (evita problemas de loop infinito em caso de lista com nº de nós impar) */
				menor_anterior = aux; /* salva o ponteiro aux em menor_anterior, pois ele vai apontar para o proximo nó menor na proxima comparação */
				aux = prox_prox;
			}
			else { /* nó prox é maior que nó aux */
				insereMaior(&prox->maiores,aux); /* insere o nó maior (apontado por aux) na lista de valores maiores do nó 
															apontado por prox */
				if(menor_anterior) menor_anterior->prox = prox; /* se menor_anterior estiver setado, ele passa a apontar parar prox (que é o menor valor) */
				else *inicio = prox; /* se não, o ponteiro para o inicio da lista passa a apontar para o prox */
				menor_anterior = prox; /* salva o endereço apontado por prox em menor_anterior */
				aux = prox_prox;
			}
		}else { /* se prox nao existe */
			if (menor_anterior) menor_anterior->prox = aux; /* se menor_anterior nao for NULL, o nó apontado por ele passa a apontar para aux */
			aux = NULL; /* seta aux como NULL para sair do laço */
		}
		
	}
	
	if((*inicio)->prox) { /* se a lista tiver mais que dois nós */
		return menorElemento(inicio); /* chama a mesma função para a lista, que agora contem apenas os nós menores */
	}else {
		return *inicio; /* o nó que sobrou, é o menor da lista. Retorna ele. */
	}
}
