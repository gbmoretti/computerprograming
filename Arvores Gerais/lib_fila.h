#ifndef lib_fila#define lib_filatypedef struct _Fila {	void *dados;	struct _Fila *prox;} Fila;Fila* novaFila();Fila* fila_novoNo();int Insere(Fila*,void*);void* Retira(Fila*);Fila* percorre(Fila*); /* funcao que percorre toda a fila e retorna o endereco do ultimo no */int estaVazia(Fila*);

#endif

