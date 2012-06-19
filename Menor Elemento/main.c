#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(int argc,char* argv[]) {
	int n, i, num;
	PPNo lista;
	PNo menor;
	
	lista = (PPNo) malloc(sizeof(PNo));
	*lista = NULL;
	
	scanf("%d",&n); /* le a quantidade de valores da lista */
	for(i=0;i<n;i++) { /* laço que le os valores de stdin */
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
	
