/* Estrutra do n� */
typedef struct _no {
	int valor;
	struct _no* prox;
	struct _no* maiores; /* campo que aponta para uma lista contendo os numeros que foram comparadas com esse n� e s�o maior que ele */
} No, *PNo, **PPNo;

PNo novoNo(int); /* aloca um novo n� */
void insereValor(PPNo,int); /* insere um valor no inicio da lista ligada */
int maxComps(int); /* retorna o numero de compara��es m�ximas que o programa pode fazer */
void imprime(PPNo); /* imprime uma lista ligada */
PNo menorElemento(PPNo); /* retorna o endere�o para um n� que contem o menor valor da lista ligada passada por parametro */

int comps; /* variavel global usada para contar o n�mero de compara��es */
