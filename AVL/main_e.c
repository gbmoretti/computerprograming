#include <stdio.h>
#include "avl.h"

int main(int argc, char* argv[]) {
	PPNo tree;
	
	tree = novaArvore();
	setaRaiz(tree,10);
	
	insereNo(tree,15);
	imprime(*tree);
	printf("\n");
	insereNo(tree,5);
	imprime(*tree);
	printf("\n");
	insereNo(tree,1);
	imprime(*tree);
	printf("\n");
	insereNo(tree,-2);
	imprime(*tree);
	printf("\n");
	insereNo(tree,20);
	imprime(*tree);
	printf("\n");
	insereNo(tree,17);
	imprime(*tree);
	printf("\n");
	insereNo(tree,19);
	imprime(*tree);
	printf("\n");
	insereNo(tree,27);
	imprime(*tree);
	return 0;
}