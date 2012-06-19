#ifndef _DESENHO_
#define _DESENHO_

 
int nDigitos(int); /* Retorna o numero de digitos de n */
int geraLarguras(PNo); /* Função recursiva que calcula o tamanho ocupado por cada nó. Necessário para o calculo do posicionamento de todos os nós das arvores */
void desenha(PNo,int,int,int); /* Função que desenha as caixas dos nós e as linhas de ligação entre os pais e os filhos */
void desenhaArvore(PNo,int); /* Função que chama a função recursiva de desenho */
void desenhaCor(PNo,int,int,int,int); /* desenha as caixas e as linhas colorindo de vermelho o nó com valor recebido pelo ultimo argumento */
void desenhaArvoreCor(PNo,int,int); /* chama a função para desenhar a arvore com destaque em vermelho */

#endif
