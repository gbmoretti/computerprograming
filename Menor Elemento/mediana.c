#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int comps;

int maxComps(int n) { 
	return n + ceil(log10(n)/log10(2)) -2;
}

/*
	
*/

/* Retorna o menor elemento do vetor e guarda os potenciais 2os menores valores no vetor vet_menores */
int menorElemento(int *v,int max,int *vet_menores,int* tam_menores) {
	int i, tam2, *v2;
	static int menor;
	
	v2 = malloc(sizeof(int)*max/2+1);
	tam2 = 0;
	
	for(i=0;i<max && i+1<max;i=i+2) {
		comps++;
		tam2++;
		if(v[i] > v[i+1]) { 
			v2[i/2] = v[i+1];
		} else { 
			v2[i/2] = v[i];
		}
	}
	
	if(max % 2 == 1) { /* se numero de elementos for impar, passa o ultimo elemento (que nao foi comparado com ninguem para o v2 */
		v2[tam2] = v[max-1];
		tam2++;
	}
	
	if(tam2 > 1) {
		menor = menorElemento(v2,tam2,vet_menores,tam_menores);
	}else {
		menor = v2[0];
	}
	
	for(i=0;v[i]!=menor;i++) { } /* laço que procura a posicao do menor elemento do vetor */
	if(i % 2 == 0) vet_menores[*tam_menores] = v[i+1];			
	else vet_menores[*tam_menores] = v[i-1];

	(*tam_menores)++;		
	
	return menor;
}

int main(int argc,char* argv[]) {
	int *vetor, *vet_menores, i, menor, tam_menores, segundo_menor, max;
	
	srand(time(NULL));
	
	if(argc > 1) max = argc-1;
	else max = rand()%100;
	
	printf("MAX: %d\n",max);
	
	vetor = malloc(sizeof(int)*max);
	vet_menores = malloc(sizeof(int)*max);
	
	if(argc > 1) {
		for(i=1;i<argc;i++) {
			vetor[i-1] = atoi(argv[i]);
		}
	}else {
		for(i=0;i<max;i++) {
			vetor[i] = rand()%100;
			printf("%d ",vetor[i]);
		}
		printf("\n");
	}
	
	tam_menores = 0;
	menor = menorElemento(vetor,max,vet_menores,&tam_menores); /* chama funcao que retorna o menor elemento, 
																	e guarda no vetor vet_menores os potenciais segundos menores valores */
	printf("Menor elemento: %d -- %d / %d\n",menor,comps,maxComps(max));
	
	segundo_menor = menorElemento(vet_menores,tam_menores,vetor,&tam_menores); /* procura o menor elemento dentro do vetor com os potenciais segundos
																				menores valores (os 2 ultimos argumentos são irrelevantes para esse caso */
	printf("Segundo menor elemento: %d -- %d / %d\n",segundo_menor,comps,maxComps(max));
	
	return 0;
}
