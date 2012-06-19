/* Programa Raiz
    Descri��o: Para encontrar o 2� menor elemento o programa constr�i uma lista simplesmente encadeada com os valores, e passa essa lista para a fun��o
menorElemento. Essa fun��o compara a lista de 2 em 2 n�s (salvando o n� maior numa outra lista ligada, que � guardada pelo n� menor), reordena os ponteiros 
de forma que no final da fun��o a lista liga apenas os n�s que foram considerados menores pelas compara��es, e faz esse mesmo processo para a nova 
lista de forma recursiva, at� sobrar uma lista com um �nico n� que cont�m um ponteiro para uma outra lista ligada que guarda todos os valores 
comparados com esse n� menor, chamada aqui de "maiores".
	Essa lista "maiores" � repassada � fun��o menorElemento. O n� retornado pela fun��o � o segundo menor elemento da lista geral.
	O pior caso � quando a lista tem uma quantidade �mpar de elementos, porque o �ltimo elemento n�o pode ser comparado com ningu�m e tem que ser 
passado para o proximo n�vel de recurs�o.
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da �ltima modifica��o: 13/09/2010 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include "main.h" 
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
	PNo aux, prox, menor_anterior;
	
	aux = prox = *inicio;
	menor_anterior = NULL;
	while(aux != NULL && prox != NULL) { /* la�o que percorre a lista at� o fim */
		prox = aux->prox;
		if(prox) { /* se prox nao apontar para NULL, � porque aux aponta para um n� e prox para outro e podemos comparar os dois */
			comps++; /* conta mais uma compara��o */
			if(aux->valor < prox->valor) { /* se o valor do n� apontado por aux for maior que que o valor de prox */
				insereValor(&aux->maiores,prox->valor); /* insere o valor do n� maior (apontado por prox) na lista de valores maiores do n� 
															apontado por aux */
				if(menor_anterior) menor_anterior->prox = aux; /* se menor_anterior estiver setado, ele passa a apontar para aux (que � o menor valor) */
				aux->prox = NULL; /* aux passa a ser o final da lista ligada (evita problemas de loop infinito em caso de lista com n� de n�s impar) */
				menor_anterior = aux; /* salva o ponteiro aux em menor_anterior, pois ele vai apontar para o proximo n� menor na proxima compara��o */
				aux = prox->prox;
			}
			else { /* n� prox � maior que n� aux */
				insereValor(&prox->maiores,aux->valor); /* insere o valor do n� maior (apontado por prox) na lista de valores maiores do n� 
															apontado por aux */
				if(menor_anterior) menor_anterior->prox = prox; /* se menor_anterior estiver setado, ele passa a apontar parar prox (que � o menor valor) */
				else *inicio = prox; /* se n�o, o ponteiro para o inicio da lista passa a apontar para o prox */
				menor_anterior = prox; /* salva o endere�o apontado por prox em menor_anterior */
				aux = prox->prox;
			}
		}else { /* se prox nao existe */
			if (menor_anterior) menor_anterior->prox = aux; /* se menor_anterior nao for NULL, o n� apontado por ele passa a apontar para aux */
			aux = NULL; /* seta aux como NULL para sair do la�o */
		}
		
	}
	
	if((*inicio)->prox) { /* se a lista tiver mais que dois n�s */
		return menorElemento(inicio); /* chama a mesma fun��o recursivamente */
	}else {
		return *inicio; /* o n� que sobrou, � o menor da lista. Retorna ele. */
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
