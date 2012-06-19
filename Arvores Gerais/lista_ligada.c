#include <stdio.h>
#include <stdlib.h>
#include "lista_ligada.h"

/* Libera a memoria de toda a lista */
void Lista_excluiLista(ListaNo** lista) {
	ListaNo *aux, *aux2;
	
	aux = *lista;
	while(aux != NULL) { /* laço que percorrre toda a lista */
		aux2 = aux;
		aux = aux->prox;
		free(aux2);		
	}
	free(lista);
}

/* Insere valor em uma posicao especifica da lista */
int Lista_inserePos(ListaNo** lista,int valor,int pos) {
	int i;
	ListaNo *aux, *aux2, *novo;
	
	novo = (ListaNo*) malloc(sizeof(ListaNo)); /* alocando novo nó */
	novo->valor = valor;
	
	if(novo == NULL) {
		printf("Sem memoria!\n");
		return 1;
	}
	
	aux = *lista;
	i = 0;
	
	while(i < pos && aux != NULL) { /* laço que percorre a lista até encontrar a posicao correta ou o fim da lista */
		i++;
		aux2 = aux;
		aux = aux->prox;
	}
	
	if(aux == *lista) { /* se aux estiver apontando para a 1a posicao da lista */
		novo->prox = *lista; 
		*lista = novo; /* faz o ponteiro lista apontar para o novo nó */		
	}else {
		novo->prox = aux;
		aux2->prox = novo;	
	}
	return 0;
}

/* Exclui um no da lista que tem valor igual ao passado por parametro */
void Lista_excluiValor(ListaNo** lista,int valor) {
	ListaNo *aux, *aux2;
	
	aux = *lista;
	while(aux != NULL && aux->valor != valor) { /* laço que percorre a lista até encontrar o valor ou até o fim da lista */
		aux2 = aux;
		aux = aux->prox;
	}
	
	if(aux == *lista) { /* se o no for o primeiro da lista */
		*lista = aux->prox; /* ponteiro lista comeca apontar para o segundo no da lista */
	}else {	
		if(aux != NULL) 
			aux2->prox = aux->prox;
	}
	free(aux);
}

/* Retorna o tamanho da lista */
int Lista_tamLista(ListaNo** lista) {
	ListaNo *aux;
	int tam;
	
	tam = 0;
	aux = *lista;
	while(aux != NULL) { /* laço percorre toda a lista e incrementa tam */
		tam++;
		aux = aux->prox;
	}
	
	return tam;
}

/* Funcao que ordena crescentemente a lista (BubleSort) */
void Lista_ordena_asc(ListaNo** lista) {
	ListaNo *aux, *aux2;
	int tam, i, troca;
	
	tam = Lista_tamLista(lista); /* pega o tamanho da lista */
	i = 0;
	while(tam > i) { /* laco para percorrer tamanho da lista vezes a lista */
		aux = *lista;
		aux2 = aux->prox;
		while(aux2 != NULL) { /* laço que percorre toda a lista */
			if(aux2->valor < aux->valor) { /* se o valor de aux2 for maior q aux, entao troca os valores */
				troca = aux->valor;
				aux->valor = aux2->valor;
				aux2->valor = troca;
			}
			aux = aux2;
			aux2 = aux->prox;
		}
		i++;
	}
}

/* Funcao que ordena decrescentemente a lista (BubleSort). Mesma logica da ordena_asc().*/
void Lista_ordena_dec(ListaNo** lista) {
	ListaNo *aux, *aux2;
	int tam, i, troca;
	
	tam = Lista_tamLista(lista);
	i = 0;
	while(tam > i) {
		aux = *lista;
		aux2 = aux->prox;
		while(aux2 != NULL) {
			if(aux2->valor > aux->valor) {
				troca = aux->valor;
				aux->valor = aux2->valor;
				aux2->valor = troca;
			}
			aux = aux2;
			aux2 = aux->prox;
		}
		i++;
	}
}

/* Funcao que busca um determinado valor na lista e retorna o ponteiro para esse valor */
ListaNo* Lista_buscaValor(ListaNo** lista,int valor) {
	ListaNo* aux;
	
	aux = *lista;
	while(aux != NULL && aux->valor != valor) { /* laço que percorre a lista até encontrar o valor ou chegar no final da lista */
		aux = aux->prox;
	}
	
	return aux;
}

/* Insere novo valor no inicio da lista */
int Lista_novoNo(ListaNo** lista, int valor) {
	ListaNo *novo;
	
	novo = (ListaNo*) malloc(sizeof(ListaNo)); /* aloca no para o novo valor */
	novo->valor = valor;
	
	if(novo == NULL) {
		printf("Nao ha mais memoria!\n");
		return 1;
	}
	
	novo->prox = *lista; /* prox do novo nó passa a apontar para o que era o 1o no da lista */
	*lista = novo; /* e o ponteiro para a lsita passa a apontar para o novo nó */
	
	return 0;
}

/* Imprime toda a lista */
void Lista_imprimeLista(ListaNo** lista) {
	ListaNo* aux;
	
	aux = *lista;
	printf("Lista: ");
	while(aux != NULL) { /* Laço que percorre toda a lista e imprime */
		printf("%d ",aux->valor);
		aux = aux->prox;
	}
}
