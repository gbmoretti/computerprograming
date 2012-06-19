/*
Fila de inteiros
*/

#include <stdio.h>
#include <stdlib.h>
#include "lib_fila.h"

Fila* fila_novoNo() {
	Fila *novo;
	
	novo = (Fila*) malloc(sizeof(Fila));
	novo->prox = NULL;
	
	return novo;
}

Fila* novaFila() {
	Fila *inicio;
	
	inicio = fila_novoNo();
	
	return inicio;
}

Fila* percorre(Fila *inicio) {
	while(inicio->prox != NULL) {
		inicio = inicio->prox;
	}
	
	return inicio;
}

int Insere(Fila *inicio,void *dados) {
	Fila *novo, *ultimo;
	
	novo = fila_novoNo();
	novo->dados = dados;
	
	ultimo = percorre(inicio);
	ultimo->prox = novo;
	
	return 1;
}

void* Retira(Fila *inicio) {
	Fila *aux;
	void *dados;
	
	aux = inicio->prox;
	if(aux != NULL) {
		dados = aux->dados;
		inicio->prox = aux->prox;
		free(aux);
		return dados;
	}else {
		return NULL;
	}
}

int estaVazia(Fila *inicio) {
	return inicio->prox == NULL ? 1 : 0; 
}
