/* Biblioteca de funções de interação com o usuario */

#ifndef extras
#define extras

void apagar(PtrNo*,char**); /* Funcao que apaga o arquivo de uma das matrizes carregadas na memoria */
void imprimir(PtrNo*,char**); /* Funcao que imprime uma das matrizes carregadas na memoria */
void somar(PtrNo*,char**); /* Funcao que soma duas matrizes carregadas na memoria, e imprime a matriz resultante */
void salvar(PtrNo); /* Funcao que salva uma matriz num arquivo se o usuario quiser */
void imprimeListaMatrizes(PtrNo*,char**); /* Funcao que imprime uma lista de todas as matrizes carregadas na memoria */
void carregaDeArgumento(int,char**,PtrNo*,char**); /* Funcao que carrega na memoria todos as matrizes passadas por argumento */
void desalocaMatriz(PtrNo*,char**,int); /* desaloca uma posicao na lista de matrizes */

void freeMatrizes(PtrNo*); /* Funcao que libera a memoria das matrizes carregadas pelo programa */
void freeNomes(char**); /* Funcao que libera a memoria das strings usadas para armazenar os nomes das matrizes */

int contaMatrizes(PtrNo*); /* Conta as matrizes carregadas na memoria */

#endif
