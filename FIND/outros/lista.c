#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct no {
   int chave;
   no *prox;  
};
typedef no *NoPointer;

NoPointer novoNo() {
   NoPointer novo;
   novo = (NoPointer)malloc(sizeof(no));
   return novo;
}

NoPointer buscaNo(NoPointer aux, int x) {
   int i = 0;
   bool achou = 0;
   NoPointer pai;
   printf("Buscando...\n");
   if(aux) {
      while(aux != NULL || achou != 1) {
         i++;
         //printf(" %d... ",aux->chave);
         if(aux->chave == x) {
            achou = 1;
            printf("\nAchei! Na posicao %d ",i);
         }
         pai = aux;
         if (aux->prox) { 
            aux = aux->prox;
            //printf("Tem proximo!\n");
         }
         if (!aux->prox) {
            aux = NULL;
            achou = 1;
            //printf("Nao tem proximo!\n");
         }
      }
      return pai;
   }   
}

void imprimeLista(NoPointer aux) {
   printf("Imprimindo...\n");
   while(aux) {
      printf("%d, ",aux->chave);
      aux = aux->prox;
   }
   printf("\n");
}

void insereNo(NoPointer aux, int chave) {
   NoPointer novo, aux2;
   if(aux) {
      aux2 = buscaNo(aux,chave);
      if(aux2->chave == chave) {
         printf("\nJa existe essa chave.\n");
      }
      else if(aux2->prox == NULL) {
         novo = novoNo();
         novo->chave = chave;
         novo->prox = NULL;
         aux->prox = novo;
         printf("\nInserido novo no (%d)\n",novo->chave);
      }
   }else {
      printf("Sem raiz...\n");
   }
}

int main() {
   int esc = 0;
   bool fim = 0;
   NoPointer inicio = NULL;
   while(!fim) {
      printf("Digite uma chave: ");scanf("%d",&esc);
      if(inicio) {
         printf("Inserindo %d\n",esc);
		 insereNo(inicio,esc);      
      }else {
         inicio = novoNo();
         inicio->chave = esc;
         inicio->prox = NULL;
         printf("\nRaiz Inserida\n");
      }
      imprimeLista(inicio);
   }
}
