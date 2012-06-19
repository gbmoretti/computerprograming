#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include "funcs.h" 
#include <conio.h>

/* Funcao que aloca um novo n� */
PNo novoNo(int valor) {
	PNo novo;
	
	novo = (PNo) malloc(sizeof(No)); /* aloca espa�o na memoria para o no e salva o endere�o em novo */
	novo->valor = valor;
	novo->prox = novo->maiores = NULL;
	
	return novo; /* retorna o endereco do no alocado */
}

/* Insere um novo valor na lista ligada. O �ltimo n� inserido ser� sempre o primeiro da lista (menor complexidade de inser��o) */
void insereValor(PPNo inicio,int valor) {
	PNo novo;
	
	novo = novoNo(valor); /* aloca o novo n� */
	
	novo->prox = *inicio; /* o ponteiro prox do novo n� passa a apontar para o antigo 1o elemento da lista */
	*inicio = novo; /* o ponteiro que indica o inicio da lista passa a apontar para o novo n� */
	
}

void insereMaior(PPNo inicio,PNo valor) {
	PNo aux;
	while(valor->maiores != NULL) { /* desaloca os n�s que estavam na lista de valores comparadas com o n� apontador por "valor". Eles n�o ser�o mais usados */
		aux = valor->maiores;
		valor->maiores = aux->prox;
		free(aux);
	}
	
	valor->prox = *inicio; /* o ponteiro prox do novo n� passa a apontar para o antigo 1o elemento da lista */
	*inicio = valor; /* o ponteiro que indica o inicio da lista passa a apontar para o novo n� */
}

/* Retorna o numero maximo de compara��es que o programa deve fazer */
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

/* Retorna um n� com o menor elemento da lista apontada por inicio, e guarda nesse n� uma lista com todos os n�s que foram comparados com ele */
PNo menorElemento(PPNo inicio) {
	PNo aux, prox, menor_anterior, prox_prox;
	
	aux = prox = *inicio;
	menor_anterior = NULL;
	while(aux != NULL && prox != NULL) { /* la�o que percorre a lista at� o fim */
		prox = aux->prox;
		if(prox) { /* se prox nao apontar para NULL, � porque aux aponta para um n� e prox para outro e podemos comparar os dois */
			comps++; /* conta mais uma compara��o */
			prox_prox = prox->prox; /* salva o ponteiro para n� que vai ser usado na proxima compa��o */
			if(aux->valor < prox->valor) { /* se o valor do n� apontado por aux for maior que que o valor de prox */
				insereMaior(&aux->maiores,prox); /* insere o n� maior (apontado por prox) na lista de valores maiores do n� 
															apontado por aux */
				if(menor_anterior) menor_anterior->prox = aux; /* se menor_anterior estiver setado, ele passa a apontar para aux (que � o menor valor) */
				aux->prox = NULL; /* aux passa a ser o final da lista ligada (evita problemas de loop infinito em caso de lista com n� de n�s impar) */
				menor_anterior = aux; /* salva o ponteiro aux em menor_anterior, pois ele vai apontar para o proximo n� menor na proxima compara��o */
				aux = prox_prox;
			}
			else { /* n� prox � maior que n� aux */
				insereMaior(&prox->maiores,aux); /* insere o n� maior (apontado por aux) na lista de valores maiores do n� 
															apontado por prox */
				if(menor_anterior) menor_anterior->prox = prox; /* se menor_anterior estiver setado, ele passa a apontar parar prox (que � o menor valor) */
				else *inicio = prox; /* se n�o, o ponteiro para o inicio da lista passa a apontar para o prox */
				menor_anterior = prox; /* salva o endere�o apontado por prox em menor_anterior */
				aux = prox_prox;
			}
		}else { /* se prox nao existe */
			if (menor_anterior) menor_anterior->prox = aux; /* se menor_anterior nao for NULL, o n� apontado por ele passa a apontar para aux */
			aux = NULL; /* seta aux como NULL para sair do la�o */
		}
		
	}
	
	if((*inicio)->prox) { /* se a lista tiver mais que dois n�s */
		return menorElemento(inicio); /* chama a mesma fun��o para a lista, que agora contem apenas os n�s menores */
	}else {
		return *inicio; /* o n� que sobrou, � o menor da lista. Retorna ele. */
	}
}
