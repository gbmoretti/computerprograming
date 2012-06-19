/* Programa Raiz
    Descrição: Programa principal do projeto de Matrizes Esparsas. Ele lê arquivos de matrizes passadas por argumento, 
	depois ele permite que você some duas matrizes carregadas e salve a matriz resultante em um arquivo, permite também imprimir uma matriz e
	apagar o arquivo de uma matriz.
	
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da última modificação: 29/06/10 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "matriz_ligada.h"
#include "algebra.h"
#include "arquivo.h"
#include "extras.h"

int main(int argc, char *argv[]) {
	PPtrNo matrizes; /* matrizes é um vetor de ponteiros para as matrizes carregadas pelo programa */
	char **nomes_matrizes, tecla; /* nomes_matrizes é um vetor de strings, que conterá os nomes das matrizes carregadas no programa */
	int qntd_matrizes;
	
	if(argc < 2) {
		printf("Sintaxe: main [arquivos das matrizes:]\n");
		exit(1);
	}
	
	qntd_matrizes = argc;
	if(qntd_matrizes > 10) qntd_matrizes = 10; /* limitando o numero de matrizes para 10 */
	matrizes = (PPtrNo) malloc(sizeof(PtrNo)*qntd_matrizes); /* alocando o vetor de ponteiros para as matrizes */
	nomes_matrizes = (char **) malloc(sizeof(char*)*argc); /* alocando o vetor de strings */
	carregaDeArgumento(argc,argv,matrizes,nomes_matrizes); /* chama a funcao que carrega as matrizes passadas por argumento */

	printf("Matrizes carregadas (%d):\n",contaMatrizes(matrizes));
	imprimeListaMatrizes(matrizes,nomes_matrizes); /* imprime as matrizes carregadas */
	
	do { /* MENU */
		printf("\nEscolha uma acao:\n[L] para listar,\n[S] para somar,\n[A] apagar,\n[I] para imprimir,\n[F] para fechar\n");
		tecla = getch();
		
		switch(tecla) {
			case 's':
				somar(matrizes,nomes_matrizes);
				break;
			case 'S':
				somar(matrizes,nomes_matrizes);
				break;
			case 'a':
				apagar(matrizes,nomes_matrizes);
				break;
			case 'A':
				apagar(matrizes,nomes_matrizes);
				break;
			case 'I':
				imprimir(matrizes,nomes_matrizes);
				break;
			case 'i':
				imprimir(matrizes,nomes_matrizes);
				break;
			case 'l':
				printf("\n");
				imprimeListaMatrizes(matrizes,nomes_matrizes);
				break;
			case 'L':
				printf("\n");
				imprimeListaMatrizes(matrizes,nomes_matrizes);
				break;
			case 'f':
				break;
			case 'F':
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while(tecla != 'f' && tecla != 'F');
	
	freeMatrizes(matrizes); /* libera as matrizes do vetor matrizes */
	free(matrizes); /* libera a memoria do vetor de ponteiro */
	freeNomes(nomes_matrizes); /* libera as strings com os nomes das matrizes */
	free(nomes_matrizes); /* libera o vetor de strings */
	
	return 0;
}
