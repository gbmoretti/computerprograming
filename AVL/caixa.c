#include <stdio.h> /* printf() */
#include "avl.h"
#include "conio_v3.1.h"
#include "caixa.h"
#include "desenho.h"
#include <math.h>

#define QUINA_INFERIOR_DIREITA 217
#define QUINA_INFERIOR_ESQUERDA 192
#define QUINA_SUPERIOR_DIREITA 191
#define QUINA_SUPERIOR_ESQUERDA 218
#define LADO_VERTICAL 179
#define LADO_HORIZONTAL 196
#define LADO_HORIZONTAL_INFERIOR 194
#define LADO_HORIZONTAL_SUPERIOR 193

void box(int Lin, int Col, int Info, int tipo_no,int cor)
{
	int digitos, i;
	
	digitos = nDigitos(Info);
	  textcolor(cor);
	  
	  gotoxy(Col, Lin);
      cprintf("%d", Info); 

      gotoxy(Col + digitos, Lin + 1);
      cprintf("%c", QUINA_INFERIOR_DIREITA);

      gotoxy(Col - 1, Lin + 1);
      cprintf("%c", QUINA_INFERIOR_ESQUERDA);

      gotoxy(Col + digitos, Lin - 1);
      cprintf("%c", QUINA_SUPERIOR_DIREITA);

      gotoxy(Col - 1, Lin - 1);
      cprintf("%c", QUINA_SUPERIOR_ESQUERDA);

      gotoxy(Col - 1, Lin);
      cprintf("%c", LADO_VERTICAL);

      gotoxy(Col + digitos, Lin);
      cprintf("%c", LADO_VERTICAL);

      gotoxy(Col, Lin - 1);
      for(i=0;i<digitos;i++)
		cprintf("%c", LADO_HORIZONTAL);
	  
	  
      gotoxy(Col, Lin + 1);
       for(i=0;i<digitos;i++)
		cprintf("%c", LADO_HORIZONTAL);
		
	  textcolor(15);
}

/* Funcao que desenha uma linha ligando o ponto x1,y1 até o ponto x2,y2 */
void line(int x1, int y1, int x2, int y2) {
	int i;
	unsigned char buffer[4], c;
	
	if(y2>y1) { /* se o 2o ponto estiver abaixo do 1o ponto, inverte-se o pontos */
		i = x1;
		x1 = x2;
		x2 = i;
		i = y1;
		y1 = y2;
		y2 = i;
	}
	
	gotoxy(x1,y1);
	printf("%c",LADO_HORIZONTAL_SUPERIOR);
	gotoxy(x1,y1-1);
	
	if(x1==x2) { /* se os pontos que devem ser ligados estiverem um em cima do outro */		
		_gettext(x1,y1-1,x1+1,y1-1,buffer); /* armazena na string buffer o caracter que esta na posicao x1, y-1 do console */
		if(buffer[0] == QUINA_INFERIOR_DIREITA || buffer[0] == QUINA_INFERIOR_ESQUERDA) c = 197;
		else c = LADO_VERTICAL;
		printf("%c",c);
		gotoxy(x2,y2);
		printf("%c",LADO_HORIZONTAL_INFERIOR);
	}else {	
		if(x1 > x2) { /* se o 1o ponto estiver a direita do 2o ponto */
			_gettext(x1,y1-1,x1+1,y1-1,buffer);
			if(buffer[0] == LADO_HORIZONTAL || buffer[0] == 194) c = 194;
			else c = QUINA_SUPERIOR_DIREITA;
			printf("%c",c);
			for(i=x2+1;i<x1;i++) {
				_gettext(i,y1-1,i+1,y1-1,buffer);
				if(buffer[0] == QUINA_INFERIOR_ESQUERDA || buffer[0] == 193) c = 193;
				else if (buffer[0] == QUINA_SUPERIOR_DIREITA || buffer[0] == 194) c = 194; 
				else c = LADO_HORIZONTAL;
				gotoxy(i,y1-1);
				printf("%c",c);
			}
			_gettext(x2,y1-1,x2+1,y1-1,buffer);
			if(buffer[0] == QUINA_INFERIOR_DIREITA || buffer[0] == 193) c = 193;
			else if(buffer[0] == 197) c = 197;
			else c = QUINA_INFERIOR_ESQUERDA;
			gotoxy(x2,y1-1);
			printf("%c",c);
			gotoxy(x2,y2);
			printf("%c",LADO_HORIZONTAL_INFERIOR);
		}else { /* se o 1o ponto estiver a esquerda do 2o ponto */
			_gettext(x1,y1-1,x1+1,y1-1,buffer);
			if(buffer[0] == LADO_HORIZONTAL || buffer[0] == 194) c = 194;
			else c = QUINA_SUPERIOR_ESQUERDA;
			printf("%c",c);
			for(i=x1+1;i<x2;i++) {
				_gettext(i,y1-1,i+1,y1-1,buffer);
				if(buffer[0] == QUINA_SUPERIOR_ESQUERDA || buffer[0] == 194) c = 194;
				else c = LADO_HORIZONTAL;
				gotoxy(i,y1-1);
				printf("%c",c);
			}
			_gettext(x2,y1-1,x2+1,y1-1,buffer);
			if(buffer[0] == QUINA_INFERIOR_ESQUERDA || buffer[0] == 193) c = 193;
			else if(buffer[0] == QUINA_SUPERIOR_ESQUERDA) c = 197;
			else c = QUINA_INFERIOR_DIREITA;
			gotoxy(x2,y1-1);
			printf("%c",c);
			gotoxy(x2,y2);
			printf("%c",LADO_HORIZONTAL_INFERIOR);
		}
	}
}
