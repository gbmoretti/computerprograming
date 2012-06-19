#ifndef ARVORE
#define ARVORE

typedef struct _no {
	int chave; /* valor do n� */
	int n_filhos; /* numero de filhos q esse n� tem */
	int balanc; /* valor usado para fazer o balanceamento da avl */
	int tamanho_total; /* largura total do n� (soma das larguras dos filhos */
	struct _no* esq; /* ponteiro para o primeiro filho do n� */
	struct _no* dir; /* ponteiro para o irm�o do n� */
} No, *PNo, **PPNo;

PPNo novaArvore(); /* Aloca um ponteiro de ponteiro que vai apontar para a raiz da arvore*/
PNo novoNo(int); /* Aloca novo n� e retorna o endere�o */
PNo busca(PNo,int, PNo); /* Busca um n� e caso esse n� existe retorna o endere�o dele */
void insereNo(PPNo,int); /* Insere um filho no n� especificado */
void setaRaiz(PPNo,int); /* Seta valor de raiz */
void imprime(PNo); /* Imprime �rvore usando metodo pre-ordem */
int alturaArvore(PNo); /* retorna a altura do n� passado por argumento */
void freeArvore(PPNo); /* libera mem�ria ocupada pela �rvore */
void freeNos(PNo); /* libera mem�ria ocupada por um n� da �rvore */
void rotacionaDir(PPNo); /* rotaciona o n� recebido por argumento para a direita */
void rotacionaEsq(PPNo); /* rotaciona n� recebido por argumento para a esquerda */
void rotacionaDirEsq(PPNo); /* faz rota��o dupla direita-esquerda */
void rotacionaEsqDir(PPNo); /* faz rota��o dupla esquerda-direta */
int balanceamento(PPNo); /* recalcula o fator balanceamento de todos os n�s a partir do n� recebido por argumento */
#endif
