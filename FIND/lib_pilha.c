#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {CHEIA, SUCESSO, VAZIA} Msg;

typedef struct tipo_pilha {
    int topo;
    char **vetor;
} Pilha;

void copia_vetor(char *vet1[],char *vet2[],int tam) {
	int i;	
	//printf("tam: %d\n",tam);
	for(i=0;i<tam;i++) {
		vet2[i] = (char *)malloc(sizeof(char)*strlen(vet1[i]));
		strcpy(vet2[i],vet1[i]);
		printf(">>>inserindo %s... %p em %p\n",vet1[i],vet1[i],vet2[i]);
	}
}

Pilha* novaPilha() {
	Pilha *pilha;
	
	pilha = malloc(sizeof(Pilha));
	pilha->topo = 0;
	
	return pilha;
}

void excluiPilha(Pilha *pilha) {
	int i;
	
	for(i=0;i<pilha->topo;i++) {
		free(pilha->vetor[i]);
	}		
	free(pilha->vetor);
	free(pilha);
}

void imprimePilha(Pilha *pilha) {
	int i;
	for(i=0;i<pilha->topo;i++) {
		printf("%s (%p), ",pilha->vetor[i],pilha->vetor[i]);
	}
	printf("\n");
}

/*int localizaValor(Pilha *pilha,int *pos,int valor) {
	int i, achou = -1;
	
	for(i=0;i < pilha->topo && achou == -1;i++) {
		if(valor == pilha->vetor[i]) {
			achou = i;
		}
	}
	if(achou != -1) {
		*pos = i;
		return 1;
	}else {
		return 0;
	}
}*/

int vazia(Pilha *pilha) {
	if(pilha->topo == 0) {
		return 1;
	}else {
		return 0;
	}
}

int getTopo(Pilha *pilha) {
	return pilha->topo;
}

Msg push(Pilha *pilha, char *string) {
	char **novo_vetor;
	
	novo_vetor = (char **) malloc(sizeof(char)*(pilha->topo+1));
	
	copia_vetor(pilha->vetor,novo_vetor,pilha->topo);
	
	free(pilha->vetor);
	
	novo_vetor[pilha->topo] = string;
	pilha->vetor = novo_vetor;
	pilha->topo++;
	
	return SUCESSO;
}

Msg pop(Pilha *pilha, char *string) {
	int topo = pilha->topo;	
	if(pilha->topo >= 1) { 
		string = pilha->vetor[topo-1];
		pilha->topo--;
		return SUCESSO;
	}else {
		return VAZIA;
	}
}

int main(int argc, char *argv[]) {
	void *pilha;
	char valor[100];
	int count;
	
	pilha = novaPilha();
	
	count = 5;
	do {
		printf("Digite uma palavra: ");
		gets(valor);
		push(pilha,valor);
		imprimePilha(pilha);
		count--;
	} while(count > 0);
	
	imprimePilha(pilha);
	while(pop(pilha,valor) != 2) {		
		printf("Desempilhando: %s\n",valor);
		imprimePilha(pilha);
	}
	
	excluiPilha(pilha);
	
	return 0;
}
