#include <stdlib.h>
#include <stdio.h>
#include "matriz_ligada.h"

/* Funcao que carrega na memoria uma matriz contida num arquivo e retorna o ponteiro para o nó inicial dessa matriz */
PtrNo carregaMatriz(char nome[]) {
	FILE *arq;
	char caminho[100];
	int linhas, colunas, lin, col;
	float val;
	PtrNo mtr; /* ponteiro que apontara para o no inicial da matriz */
	
	sprintf(caminho,"%s.txt",nome); /* construindo nome do arquivo que sera lido a partir do nome informado pelo argumento */
	
	arq = fopen(caminho,"r");
	
	if(!arq) {
		printf("<carregaMatriz()> Matriz %s inexistente",caminho);
		exit(1);
	}
	
	/* identificando tamanho da matriz */
	fscanf(arq,"%d %d",&linhas,&colunas);
	
	/* Criando nova matriz */
	mtr = novaMatriz(linhas,colunas);
		
	while(!feof(arq)) { /* laco que percorre ate o fim do arquivo */
		fscanf(arq,"%d %d %f",&lin,&col,&val); /* le a linha do arquivo */
		insereCasa(mtr,lin-1,col-1,val); /* inserindo a linha do arquivo numa casa matriz 
										(subtraindo 1 de linha e coluna pq a estrutura considera 1a linha e 1a coluna como 0) */
	}
	
	fclose(arq); /* fecha arquivo */

	return mtr; /* retorna endereco do no inicial da matriz */
}


/* Funcao que salva em arquivo uma matriz carregada na memória. Retorna 0 se a matriz foi salva com sucesso, e 1 se houve algum erro */
int salvaMatriz(PtrNo mtr, char nome[]) {
	PtrNo aux, aux2;
	FILE *arq;
	char nome_completo[50];
	
	sprintf(nome_completo,"%s.txt",nome); /* constroi o nome do arquivo a partir do nome informado no argumento */
	
	arq = fopen(nome_completo,"w");
	
	if(!arq) {
		printf("<salvaMatriz()> Nao foi possivel criar arquivo %s\n",nome_completo);
		return 1;
	}
		
	fprintf(arq,"%d %d\n",mtr->linha,mtr->coluna); /* imprime na primeira linha do arquivo o tamanho da matriz */
	
	aux = mtr->prox_linha;
	while(aux != mtr) { /* laco que percorre todas os nós-cabeça das linhas */
		aux2 = aux->prox_coluna;
		while(aux2 != aux) { /* laço que percorre todas as casas da linha apontada por aux */
			fprintf(arq,"%d %d %f\n",aux2->linha+1,aux2->coluna+1,aux2->valor); /* imprimindo no arquivo a linha, a coluna e o valor da casa da matriz
																				(somando um porque a estrutura considera a 1a linha e 1a coluna como 0) */
			aux2 = aux2->prox_coluna;
		}
		aux = aux->prox_linha;
	}

	fclose(arq); /* fechando arquivo */
	return 0;
}
