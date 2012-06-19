#ifndef ARVORE
#define ARVORE

typedef struct _no {
	int chave; /* valor do nó */
	int n_filhos; /* numero de filhos q esse nó tem */
	int tamanho_total; /* largura total do nó (soma das larguras dos filhos */
	struct _no* filho; /* ponteiro para o primeiro filho do nó */
	struct _no* irmao; /* ponteiro para o irmão do nó */
} No, *PNo, **PPNo;

PPNo novaArvore(); /* Aloca um ponteiro de ponteiro que vai apontar para a raiz da arvore*/
PNo novoNo(int); /* Aloca novo nó e retorna o endereço */
PNo busca(PNo,int, PNo); /* Busca um nó e caso esse nó existe retorna o endereço dele */
void insereFilho(PNo,int,int); /* Insere um filho no nó especificado */
void setaRaiz(PPNo,int); /* Seta valor de raiz */
void imprime(PNo); /* Imprime árvore usando metodo pre-ordem */
int alturaArvore(PNo); /* Retorna a altura da arvore */

#endif
