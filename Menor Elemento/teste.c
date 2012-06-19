#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Global que armazena quantidade de comparações feitas pelo algoritmo */
int comps;

/* calcula maximo de comparações de acordo com a formula passada */
int maxComps(int n) { 
	return n + ceil(log10(n)/log10(2)) -2;
}

void heapsort(int* a, int n)
{
   int i = n/2, pai, filho;
   int t;
 
   for (;;)
   {
      if (i > 0)
      {
          i--;
          t = a[i];
      }
      else
      {
          n--;
          if (n == 0)
             return;
          t = a[n];
          a[n] = a[0];
      }
 
      pai = i;
      filho = i*2 + 1;
 
      while (filho < n)
      {
 		  if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          comps++;
		  if (a[filho] > t)
          {
             a[pai] = a[filho];
             pai = filho;
             filho = pai*2 + 1;
          }
          else
             break;
      }
      a[pai] = t;
   }
}



int main(int argc,char* argv[]) {
	int *vetor, i;
	
	vetor = malloc(sizeof(int)*argc);
	
	for(i=1;i<argc;i++)
		vetor[i-1] = atoi(argv[i]);
		
	comps = 0;
	heapsort(vetor,argc-2);
	
	for(i=0;i<argc-1;i++)
		printf("%d ",vetor[i]);
	printf("\nComparacoes feitas: %d -- Ideal: %d",comps,maxComps(argc-1));
		
	return 0;
}
