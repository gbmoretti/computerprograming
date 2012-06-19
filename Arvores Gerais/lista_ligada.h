#ifndef lista_ligada
#define lista_ligada

typedef struct _Listano {
	int valor;
	int nivel;
	int linha;
	int coluna;
	void* pai;
	struct _Listano* prox;
} ListaNo;

/* FUNCOES DE MANIPULACAO DA LISTA */
int Lista_novoNo(ListaNo**,int); /* Funcao que insere o um no na primeira posicao da lista (menor custo) */
int Lista_inserePos(ListaNo**,int,int); /* Insere no em uma posicao especifica (custo maior) */
int Lista_tamLista(ListaNo**);  /* Retorna o tamanho da lista */
void Lista_imprimeLista(ListaNo**); /* Imprime todos os valores armazenados na lista */
void Lista_ordena_asc(ListaNo**); /* Ordena a lista crescentemente */
void Lista_ordena_dec(ListaNo**); /* Ordena a lista decrescentemente */
void Lista_excluiValor(ListaNo**,int); /* Exclui algum valor da lista */
void Lista_excluiLista(ListaNo**); /* Libera memoria de toda a lista */
ListaNo* Lista_buscaValor(ListaNo**,int); /* Busca um determinado valor na lista */

#endif
