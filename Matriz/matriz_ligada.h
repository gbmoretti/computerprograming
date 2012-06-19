/* 
Biblioteca responsavel pelo gerenciamento de memoria da matriz, impressao dela na tela e criacao de uma matriz
*/

#ifndef matriz_ligada
#define matriz_ligada

/* Estrutura de um nó. */
typedef struct No {
	int linha;
	int coluna;
	float valor;
	struct No *prox_linha;
	struct No *prox_coluna;
} TipoNo, *PtrNo, **PPtrNo; /* Definindo tipos: struct No; ponteiro para struct No; 
								ponteiro para ponteiro para struct No */

/* FUNCOES REFERENTES A ESTRUTURA */
PtrNo novaMatriz(int,int); /* cria o nó inicio da nova matriz e retorna seu endereco */
void imprimeMatriz(PtrNo); /* imprime a matriz inicia no endereco passado por argumento */
int insereCasa(PtrNo,int,int,float); /* insere novo valor na matriz */
void freeMatriz(PtrNo); /* funcao que libera a memoria utilizada por toda a matriz */

/* FUNCOES AUXILIARES */
PtrNo novoNo(); /* aloca um novo nó e retorna o endereco */
PtrNo insereCabeca(PtrNo,int,int); /* insere nó cabeca para a coluna/linha e retorna o endereco dessa nova cabeca */
void freeNo(PtrNo); /* funcao que libera a memoria de um no */

#endif
