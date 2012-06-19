#ifndef ARVORE
#define ARVORE

typedef struct _no {
	int chave; /* valor do nó */
	int n_filhos; /* numero de filhos q esse nó tem */
	int balanc; /* valor usado para fazer o balanceamento da avl */
	int tamanho_total; /* largura total do nó (soma das larguras dos filhos */
	struct _no* esq; /* ponteiro para o primeiro filho do nó */
	struct _no* dir; /* ponteiro para o irmão do nó */
} No, *PNo, **PPNo;

PPNo novaArvore(); /* Aloca um ponteiro de ponteiro que vai apontar para a raiz da arvore*/
PNo novoNo(int); /* Aloca novo nó e retorna o endereço */
PNo busca(PNo,int, PNo); /* Busca um nó e caso esse nó existe retorna o endereço dele */
void insereNo(PPNo,int); /* Insere um filho no nó especificado */
void setaRaiz(PPNo,int); /* Seta valor de raiz */
void imprime(PNo); /* Imprime árvore usando metodo pre-ordem */
int alturaArvore(PNo); /* retorna a altura do nó passado por argumento */
void freeArvore(PPNo); /* libera memória ocupada pela árvore */
void freeNos(PNo); /* libera memória ocupada por um nó da árvore */
void rotacionaDir(PPNo); /* rotaciona o nó recebido por argumento para a direita */
void rotacionaEsq(PPNo); /* rotaciona nó recebido por argumento para a esquerda */
void rotacionaDirEsq(PPNo); /* faz rotação dupla direita-esquerda */
void rotacionaEsqDir(PPNo); /* faz rotação dupla esquerda-direta */
int balanceamento(PPNo); /* recalcula o fator balanceamento de todos os nós a partir do nó recebido por argumento */
#endif
