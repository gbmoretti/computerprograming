#ifndef _DESENHO_
#define _DESENHO_

 
int nDigitos(int); /* Retorna o numero de digitos de n */
int geraLarguras(PNo); /* Fun��o recursiva que calcula o tamanho ocupado por cada n�. Necess�rio para o calculo do posicionamento de todos os n�s das arvores */
void desenha(PNo,int,int,int); /* Fun��o que desenha as caixas dos n�s e as linhas de liga��o entre os pais e os filhos */
void desenhaArvore(PNo,int); /* Fun��o que chama a fun��o recursiva de desenho */

#endif


