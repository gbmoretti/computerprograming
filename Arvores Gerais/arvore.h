#ifndef ARVORE
#define ARVORE

typedef struct _no {
	int chave; /* valor do n� */
	int n_filhos; /* numero de filhos q esse n� tem */
	int tamanho_total; /* largura total do n� (soma das larguras dos filhos */
	struct _no* filho; /* ponteiro para o primeiro filho do n� */
	struct _no* irmao; /* ponteiro para o irm�o do n� */
} No, *PNo, **PPNo;

PPNo novaArvore(); /* Aloca um ponteiro de ponteiro que vai apontar para a raiz da arvore*/
PNo novoNo(int); /* Aloca novo n� e retorna o endere�o */
PNo busca(PNo,int, PNo); /* Busca um n� e caso esse n� existe retorna o endere�o dele */
void insereFilho(PNo,int,int); /* Insere um filho no n� especificado */
void setaRaiz(PPNo,int); /* Seta valor de raiz */
void imprime(PNo); /* Imprime �rvore usando metodo pre-ordem */
int alturaArvore(PNo); /* Retorna a altura da arvore */

#endif
