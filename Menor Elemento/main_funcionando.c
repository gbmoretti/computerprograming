/* Programa Raiz
    Descrição: Para encontrar o 2º menor elemento o programa constrói uma lista simplesmente encadeada com os valores, e passa essa lista para a função
menorElemento. Essa função compara a lista de 2 em 2 nós (salvando o nó maior numa outra lista ligada, que é guardada pelo nó menor), reordena os ponteiros 
de forma que no final da função a lista liga apenas os nós que foram considerados menores pelas comparações, e faz esse mesmo processo para a nova 
lista de forma recursiva, até sobrar uma lista com um único nó que contém um ponteiro para uma outra lista ligada que guarda todos os valores 
comparados com esse nó menor, chamada aqui de "maiores".
	Essa lista "maiores" é repassada à função menorElemento. O nó retornado pela função é o segundo menor elemento da lista geral.
	O pior caso é quando a lista tem uma quantidade ímpar de elementos, porque o último elemento não pode ser comparado com ninguém e tem que ser 
passado para o proximo nível de recursão.
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da última modificação: 13/09/2010 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include "main.h" 
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
	PNo aux, prox, menor_anterior;
	
	aux = prox = *inicio;
	menor_anterior = NULL;
	while(aux != NULL && prox != NULL) { /* laço que percorre a lista até o fim */
		prox = aux->prox;
		if(prox) { /* se prox nao apontar para NULL, é porque aux aponta para um nó e prox para outro e podemos comparar os dois */
			comps++; /* conta mais uma comparação */
			if(aux->valor < prox->valor) { /* se o valor do nó apontado por aux for maior que que o valor de prox */
				insereValor(&aux->maiores,prox->valor); /* insere o valor do nó maior (apontado por prox) na lista de valores maiores do nó 
															apontado por aux */
				if(menor_anterior) menor_anterior->prox = aux; /* se menor_anterior estiver setado, ele passa a apontar para aux (que é o menor valor) */
				aux->prox = NULL; /* aux passa a ser o final da lista ligada (evita problemas de loop infinito em caso de lista com nº de nós impar) */
				menor_anterior = aux; /* salva o ponteiro aux em menor_anterior, pois ele vai apontar para o proximo nó menor na proxima comparação */
				aux = prox->prox;
			}
			else { /* nó prox é maior que nó aux */
				insereValor(&prox->maiores,aux->valor); /* insere o valor do nó maior (apontado por prox) na lista de valores maiores do nó 
															apontado por aux */
				if(menor_anterior) menor_anterior->prox = prox; /* se menor_anterior estiver setado, ele passa a apontar parar prox (que é o menor valor) */
				else *inicio = prox; /* se não, o ponteiro para o inicio da lista passa a apontar para o prox */
				menor_anterior = prox; /* salva o endereço apontado por prox em menor_anterior */
				aux = prox->prox;
			}
		}else { /* se prox nao existe */
			if (menor_anterior) menor_anterior->prox = aux; /* se menor_anterior nao for NULL, o nó apontado por ele passa a apontar para aux */
			aux = NULL; /* seta aux como NULL para sair do laço */
		}
		
	}
	
	if((*inicio)->prox) { /* se a lista tiver mais que dois nós */
		return menorElemento(inicio); /* chama a mesma função recursivamente */
	}else {
		return *inicio; /* o nó que sobrou, é o menor da lista. Retorna ele. */
	}
}

int main(int argc,char* argv[]) {
	int n, i, num;
	PPNo lista;
	PNo menor;
	
	lista = (PPNo) malloc(sizeof(PNo));
	*lista = NULL;
	
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d",&num);
		insereValor(lista,num);
	}
	
	printf("Procurando segundo menor elemento na lista: ");
	imprime(lista);
	menor = menorElemento(lista);
	printf("Menor elemento: %d (comparacoes: %d de %d)\n",menor->valor,comps,maxComps(n));
	if (menor->maiores) { 
		menor = menorElemento(&(menor->maiores));
		printf("Segundo menor: %d (comparacoes: %d de %d)",menor->valor,comps,maxComps(n));	
	}
	return 0;
}
