/* Estrutra do nó */
typedef struct _no {
	int valor;
	struct _no* prox;
	struct _no* maiores; /* campo que aponta para uma lista contendo os numeros que foram comparadas com esse nó e são maior que ele */
} No, *PNo, **PPNo;

PNo novoNo(int); /* aloca um novo nó */
void insereValor(PPNo,int); /* insere um valor no inicio da lista ligada */
int maxComps(int); /* retorna o numero de comparações máximas que o programa pode fazer */
void imprime(PPNo); /* imprime uma lista ligada */
PNo menorElemento(PPNo); /* retorna o endereço para um nó que contem o menor valor da lista ligada passada por parametro */

int comps; /* variavel global usada para contar o número de comparações */
