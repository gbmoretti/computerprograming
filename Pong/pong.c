/* Programa Raiz
    Descrição: Simulador do jogo PONG do Atari
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da última modificação: 18/03/2010 
*/

#include <stdio.h> //printf();
#include "conio_v3.h" //clrscr(); gotoxy();
#include <conio.h> //getch(); kbhit();
#include <time.h> //time();
#include <stdlib.h> //srand(); rand();

#define CIMA 1
#define DIR 2
#define BAIXO 3
#define ESQ 4
#define DIAG_SUP_DIR 5
#define DIAG_INF_DIR 6
#define DIAG_INF_ESQ 7
#define DIAG_SUP_ESQ 8

void desenhaArena(); //funcao que desenha as bordas da arena
void desenhaBarra(int pos, int pos_a, int jogador); //funcao que desenha as barras (raquetes)
void desenhaBola(int x, int y, int x_a, int y_a); //funcao que desenha a bola
int calculaColisao(int dir_bola, int bola_posx, int bola_posy); //funcao que retorna a direcao da bola depois de uma colisao com uma parede
int existeColisao(int bola_x, int bola_y, int bola_dir, int pos_j1, int pos_j2); //funcao que retorna 1 - se existir colisao com o jogador 1; 2 - se existir colisao com o jogador 2; 0 - se nao houver colisao com nenhum jogador
int colisaoJogador(int x, int y, int dir, int pos_j); //funcao que retorna a direcao da bola depois de uma colisao com um dos jogadores

int main(int argc, char *argv[]) {
	int j1, j1_a, j2, j2_a; //variaveis que irao guardar as posicoes das barras  do jogador 1 e do jogador 2
	int bola_posx, bola_posy, bola_posx_a, bola_posy_a, bola_dir; //variaveis que irao guardar a posicao da bola e a direcao
	int tempo, tempomax; //controla o tempo de atualizaçao da bola
	int termina = 0; //variavel que quando setada como 1 define o fim do jogo
	int existecolisao; //variavel que recebe o retorno da funcao existeColisao()
	char tecla; //guarda a tecla pressionada pelo usuario	
	
	clrscr();
	desenhaArena();
	
	//setando posicao inicial das barras e desenhando-as
	j1 = 9;
	j2 = 9;
	desenhaBarra(j1,j1,1);
	desenhaBarra(j2,j1,2);
	//////////////////////
	
	//setando posicao inicial e direcao incial da bola e desenhando-a
	srand(time(NULL));
	do {
		bola_dir = (rand()%8)+1;
	} while(bola_dir == 1 || bola_dir == 3); //a bola nao pode começar nem pra cima e nem pra baixo, se nao não há jogo
	bola_posx = 20;
	bola_posy = 10;
	desenhaBola(bola_posx,bola_posy,bola_posx,bola_posy);
	/////////////////////
	
	tempomax = 800; //tempo da bola, quanto menor o valor, mais rapido ela ficara 
	
	while(!termina) {
		tempo = 0;
		while(tempo<=tempomax)  {
			_sleep(1);
			tempo++;
			if(kbhit()) {
				tecla = getch();
				if(tecla != 'x') {
					if(tecla == 'a') {
						if(j1-1 > 1) {
							j1_a = j1;
							j1--;
							desenhaBarra(j1,j1_a,1);
						}
					}
					if(tecla == 'z') {
						if(j1+3 < 20) {
						j1_a = j1;
						j1++;
						desenhaBarra(j1,j1_a,1);
						}
					}
					if(tecla == 72) {
						if(j2-1 > 1) {
							j2_a = j2;
							j2--;
							desenhaBarra(j2,j2_a,2);
						}
					}
					if(tecla == 80) {
						if(j2+3 < 20) {
							j2_a = j2;
							j2++;
							desenhaBarra(j2,j2_a,2);
						}
					}
				}else {
					termina = 3;
				}
			}
		}
	
		gotoxy(45,6);
		printf("Direcao da bola: %d",bola_dir);
		gotoxy(45,7);
		printf("Velocidade da bola: %d    ",tempomax);
		
		//VERIFICANDO SE HOUVE GOL EM ALGUM DOS LADOS OU BATEU NA "TRAVE"
		if((bola_posx == 2) && bola_posy > 6 && bola_posy < 15) {
			if(bola_dir == DIAG_SUP_ESQ && bola_posy-1 == 6) {
				bola_dir = DIAG_INF_DIR;
			}else {
				if(bola_dir == DIAG_INF_ESQ && bola_posy+1 == 15) {
					bola_dir = DIAG_SUP_DIR;
				}else {
					termina = 2;
				}
			}
		}
		if((bola_posx == 39) && bola_posy > 6 && bola_posy < 15) {
			if(bola_dir == DIAG_SUP_DIR && bola_posy-1 == 6) {
				bola_dir = DIAG_INF_ESQ;
			}else {
				if(bola_dir == DIAG_INF_DIR && bola_posy+1 == 15) {
					bola_dir = DIAG_SUP_ESQ;
				}else {
					termina = 1;
				}
			}
		}
		////////////////////////////////////////////////////
		
		//VERIFICANDO SE EXISTE COLISAO COM AS BARRAS
		existecolisao = existeColisao(bola_posx,bola_posy,bola_dir,j1,j2);
		if(existecolisao == 1) {
			if(tempomax > 100) tempomax = tempomax/2;
			bola_dir = colisaoJogador(bola_posx,bola_posy,bola_dir,j1);
		}
		if(existecolisao == 2) {
			if(tempomax > 100) tempomax = tempomax/2;
			bola_dir = colisaoJogador(bola_posx,bola_posy,bola_dir,j2);
		}
		////////////////////////////////////////////////////
		
		if(bola_dir == CIMA) {
			if(bola_posy-1 == 1) { //COLISAO
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posy_a = bola_posy;
				desenhaBola(bola_posx,--bola_posy,bola_posx_a,bola_posy_a);
			}
		}
		if(bola_dir == BAIXO) {
			if(bola_posy+1 == 20) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posy_a = bola_posy;
				desenhaBola(bola_posx,++bola_posy,bola_posx_a,bola_posy_a);
			}
		}
		if(bola_dir == DIR) {
			if(bola_posx+1 == 40) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {			
				bola_posx_a = bola_posx;
				bola_posy_a = bola_posy;
				desenhaBola(++bola_posx,bola_posy,bola_posx_a,bola_posy_a);
			}	
		}
		if(bola_dir == ESQ) {
			if(bola_posx-1 == 1) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posx_a = bola_posx;
				bola_posy_a = bola_posy;
				desenhaBola(--bola_posx,bola_posy,bola_posx_a,bola_posy_a);
			}
		}
		if(bola_dir == DIAG_SUP_DIR) {
			if(bola_posx+1 == 40 || bola_posy-1 == 1) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posy_a = bola_posy;
				bola_posx_a = bola_posx;
				desenhaBola(++bola_posx,--bola_posy,bola_posx_a,bola_posy_a);
			}
		}
		if(bola_dir == DIAG_INF_DIR) {
			if(bola_posx+1 == 40 || bola_posy+1 == 20) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posy_a = bola_posy;
				bola_posx_a = bola_posx;
				desenhaBola(++bola_posx,++bola_posy,bola_posx_a,bola_posy_a);
			}
		}
		if(bola_dir == DIAG_SUP_ESQ) {
			if(bola_posx-1 == 1 || bola_posy-1 == 1) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posy_a = bola_posy;
				bola_posx_a = bola_posx;
				desenhaBola(--bola_posx,--bola_posy,bola_posx_a,bola_posy_a);
			}
		}
		if(bola_dir == DIAG_INF_ESQ) {
			if(bola_posx-1 == 1 || bola_posy+1 == 20) {
				bola_dir = calculaColisao(bola_dir, bola_posx, bola_posy);
			}else {
				bola_posy_a = bola_posy;
				bola_posx_a = bola_posx;
				desenhaBola(--bola_posx,++bola_posy,bola_posx_a,bola_posy_a);
			}
		}

	}
	clrscr();
	
	if(termina == 1) {
		printf("JOGADOR 1 VENCEU!");
		getch();
	}
	if(termina == 2) {
		printf("JOGADOR 2 VENCEU!");
		getch();
	}
	
	return 0;
}

int colisaoJogador(int x, int y, int dir, int pos_j) {
	if(dir == ESQ) {
		if(pos_j == y) return DIAG_SUP_DIR;
		if(pos_j+1 == y) return DIR;
		if(pos_j+2 == y) return DIAG_INF_DIR;
		return DIR;
	}
	if(dir == DIR) {
		if(pos_j == y) return DIAG_SUP_ESQ;
		if(pos_j+1 == y) return ESQ;
		if(pos_j+2 == y) return DIAG_INF_ESQ;
		return ESQ;
	}
	if(dir == DIAG_SUP_DIR) {
		if(pos_j+2 == y) {
			return ESQ;
		}else {
			return DIAG_SUP_ESQ;
		}
	}
	if(dir == DIAG_SUP_ESQ) {
		if(pos_j+2 == y)  { 
			return DIR;
		}else {
			return DIAG_SUP_DIR;
		}
	}
	if(dir == DIAG_INF_DIR) {
		if(pos_j == y) { 
			return ESQ;
		}else {
			return DIAG_INF_ESQ;
		}
	}
	if(dir == DIAG_INF_ESQ) {
		if(pos_j == y) { 
			return DIR;
		}else {
			return DIAG_INF_DIR;
		}	
	}
	return 0;
}


int existeColisao(int bola_x, int bola_y, int bola_dir, int j1, int j2) {
	if(bola_dir == DIR) {
		if((bola_x+1 == 10) && (bola_y == j1 || bola_y == j1+1 || bola_y == j1+2)) {
			return 1;
		}else {
			if((bola_x+1 == 30) && (bola_y == j2 || bola_y == j2+1 || bola_y == j2+2)) {
				return 2;
			}else {
				return 0;
			}
		}
	}
	if(bola_dir == ESQ) {
		if((bola_x-1 == 10) && (bola_y == j1 || bola_y == j1+1 || bola_y == j1+2)) {
			return 1;
		}else {
			if((bola_x-1 == 30) && (bola_y == j2 || bola_y == j2+1 || bola_y == j2+2)) {
				return 2;
			}else {
				return 0;
			}
		}
	}
	if(bola_dir == DIAG_SUP_DIR) {
		if((bola_x+1 == 10) && (bola_y-1 == j1 || bola_y-1 == j1+1 || bola_y-1 == j1+2)) {
			return 1;
		}else {
			if((bola_x+1 == 30) && (bola_y-1 == j2 || bola_y-1 == j2+1 || bola_y-1 == j2+2)) {
				return 2;
			}else {
				return 0;
			}
		}
	}
	if(bola_dir == DIAG_INF_DIR) {
		if((bola_x+1 == 10) && (bola_y+1 == j1 || bola_y+1 == j1+1 || bola_y+1 == j1+2)) {
			return 1;
		}else {
			if((bola_x+1 == 30) && (bola_y+1 == j2 || bola_y+1 == j2+1 || bola_y+1 == j2+2)) {
				return 2;
			}else {
				return 0;
			}
		}
	}
	if(bola_dir == DIAG_INF_ESQ) {
		if((bola_x-1 == 10) && (bola_y+1 == j1 || bola_y+1 == j1+1 || bola_y+1 == j1+2)) {
			return 1;
		}else {
			if((bola_x-1 == 30) && (bola_y+1 == j2 || bola_y+1 == j2+1 || bola_y+1 == j2+2)) {
				return 2;
			}else {
				return 0;
			}
		}
	}
	if(bola_dir == DIAG_SUP_ESQ) {
		if((bola_x-1 == 10) && (bola_y-1 == j1 || bola_y-1 == j1+1 || bola_y-1 == j1+2)) {
			return 1;
		}else {
			if((bola_x-1 == 30) && (bola_y-1 == j2 || bola_y-1 == j2+1 || bola_y-1 == j2+2)) {
				return 2;
			}else {
				return 0;
			}
		}
	}
	return -1;
}

int calculaColisao(int dir_bola, int bola_posx, int bola_posy) {
	if (dir_bola == CIMA) {
		return BAIXO;
	}
	if (dir_bola == BAIXO) {
		return CIMA;
	}
	if (dir_bola == ESQ) {
		return DIR;
	}
	if (dir_bola == DIR) {
		return ESQ;
	}
	if(dir_bola == DIAG_SUP_DIR) {
		if(bola_posy == 2 && bola_posx != 39) {
			return DIAG_INF_DIR;
		}
		if(bola_posx == 39 && bola_posy != 2) {
			return DIAG_SUP_ESQ;
		}
		if(bola_posx == 39 && bola_posy == 2) {
			return DIAG_INF_ESQ;
		}
		
	}
	if(dir_bola == DIAG_SUP_ESQ) {
		if(bola_posy == 2 && bola_posx != 39) {
			return DIAG_INF_ESQ;
		}
		if(bola_posx == 2 && bola_posy != 2) {
			return DIAG_SUP_DIR;
		}
		if(bola_posx == 2 && bola_posy == 2) {
			return DIAG_INF_DIR;
		}
		
	}
	if(dir_bola == DIAG_INF_ESQ) {
		if(bola_posy == 19 && bola_posx != 39) {
			return DIAG_SUP_ESQ;
		}
		if(bola_posx == 2 && bola_posy != 19) {
			return DIAG_INF_DIR;
		}
		if(bola_posx == 2 && bola_posy == 19) {
			return DIAG_SUP_DIR;
		}
		
	}
	if(dir_bola == DIAG_INF_DIR) {
		if(bola_posy == 19 && bola_posx != 39) {
			return DIAG_SUP_DIR;
		}
		if(bola_posx == 39 && bola_posy != 19) {
			return DIAG_INF_ESQ;
		}
		if(bola_posx == 39 && bola_posy == 19) {
			return DIAG_SUP_ESQ;
		}
	}
	return -1;
}

void desenhaBola(int x, int y, int x_a, int y_a) {
	gotoxy(45,1);
	printf("coord: %d,%d    ",x,y);
	gotoxy(x_a,y_a);
	printf(" ");
	gotoxy(x,y);
	printf("O");
}

void desenhaBarra(int pos, int pos_a, int jogador) {
		if (jogador == 1) {
			//apaga barra na posicao antiga
			gotoxy(10,pos_a);
			printf(" ");
			gotoxy(10,pos_a+1);
			printf(" ");
			gotoxy(10,pos_a+2);
			printf(" ");
			////////////////
			
			gotoxy(10,pos);
			printf("%c",179);
			gotoxy(10,pos+1);
			printf("%c",179);
			gotoxy(10,pos+2);
			printf("%c",179);
		}	
	
		if (jogador == 2) {
			//apaga barra na posicao antiga
			gotoxy(30,pos_a);
			printf(" ");
			gotoxy(30,pos_a+1);
			printf(" ");
			gotoxy(30,pos_a+2);
			printf(" ");
			////////////////
			
			gotoxy(30,pos);
			printf("%c",179);
			gotoxy(30,pos+1);
			printf("%c",179);
			gotoxy(30,pos+2);
			printf("%c",179);
		}
}

void desenhaArena() {
	int i;
	
	//canto superior esquerdo
	gotoxy(1,1);
	printf("%c",201);
	///////////////////////
	
	//limite superior
	for(i=2;i<=39;i++) {
		gotoxy(i,1);
		printf("%c",205);
	}
	printf("%c",187);
	////////////////////
	
	//limite esquerdo
	for(i=2;i<=19;i++) {
		gotoxy(1,i);
		if(i < 7 || i > 14) {
			printf("%c",186);
		}
	}
	gotoxy(1,20);
	printf("%c",200);
	////////////////////////
	
	//limite inferior
	for(i=2;i<=39;i++) {
		gotoxy(i,20);
		printf("%c",205);
	}
	gotoxy(40,20);
	printf("%c",188);
	//////////////////////
	
	//limite direito
	for(i=2;i<=19;i++) {
		gotoxy(40,i);
		if(i < 7 || i > 14) {
			printf("%c",186);
		}
	}
}
