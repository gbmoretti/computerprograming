#ifndef _CONSOLE
#define _CONSOLE

#include<windows.h> /* Estrutura COORD */

#define TECLA_FUNCAO           1    /* F1 a F12 */
#define LETRA_ALFABETO         2    /* 'a' a 'z' e 'A' a 'Z' */
#define TECLA_ESPECIAL_1       4    /* ESC, ENTER, ESPACO, TAB, BACKSPACE */
#define TECLA_ESPECIAL_2       8    /* SETAS DE DIRECAO, PAGE_UP, PAGE_DOWN, DELETE, INSERT, HOME, END */
#define ACENTO                 16   /* ~, ^, ', `  */
#define PONTUACAO              32   /* , . : ; ? !   */
#define SIMBOLO_ESPECIAL_1     64   /* @, ", #, $, %, &, ', ¨, _, |, \  */
#define TECLA_MODIFICADORA_1   128  /* SHIFT_ESQUERDO, SHIFT_DIREITO */
#define CTRL_ESQUERDO          256  /* CTRL_ESQUERDO */
#define CTRL_DIREITO           512  /* CTRL_DIREITO, */ 
#define QUALQUER_CTRL          1024  /* CTRL_DIREITO OU CTRL_ESQUERDO */
#define ALT_ESQUERDO           2048  /* ALT_ESQUERDO */
#define ALT_GR                 4096  /* ALT GR */
#define DIGITO                 8192  /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
#define OPERADORES_MATEMATICOS 16384 /* +, -, *, /, <, >   */
#define CAPS_LOCK              32768 /* CAPS_LOCK */
#define SIMBOLO_ESPECIAL_2     65536 /* (, ), }, ], {, [ */
#define TECLAS_ESPECIAIS       131072  /* ESC, ENTER, ESPACO, TAB, BACKSPACE, SETAS DE DIRECAO, PAGE_UP, PAGE_DOWN, DELETE, INSERT, HOME, END */
#define SIMBOLOS_MATEMATICOS   262144  /* +, -, *, /, <, >, (, ), }, ], {, [  */
#define LETRA_MAIUSCULA        524288  /* 'A' a 'Z' */
#define LETRA_MINUSCULA        1048576 /* 'a' a 'z' */
#define CARACTERES_1           2097152 /* 'a' a 'z', 'A' a 'Z' e , . : ; ? !   */
#define CARACTERES_2           4194304 /* 'a' a 'z', 'A' a 'Z' e 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
#define CARACTERES_3           8388608 /* 'a' a 'z', 'A' a 'Z' e 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 e   , . : ; ? ! */
#define CARACTERES_4           16777216 /* 'a' a 'z', 'A' a 'Z' e 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 e   , . : ; ? !   e   +, -, *, /, <, > */
#define CARACTERES_5           33554432 /* 'a' a 'z', 'A' a 'Z' e 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 e   , . : ; ? !   e   +, -, *, /, <, > *   e   , ), }, ], {, [   */
#define CARACTERES_6           67108864 /* 'a' a 'z', 'A' a 'Z' e 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 e   , . : ; ? !   e   +, -, *, /, <, > *   e   , ), }, ], {, [     e   @, ", #, $, %, &, ', ¨, _, |, \  */
#define CARACTERES_7           134217728 /* 'a' a 'z', 'A' a 'Z' e 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 e   , . : ; ? !   e   +, -, *, /, <, > *   e   , ), }, ], {, [     e   @, ", #, $, %, &, ', ¨, _, |, \    e    ~, ^, ', `  */

#define ARROBA 64
#define ASPAS_DUPLAS 34
#define CERQUINHA 35
#define CIFRAO 36
#define PERCENTAGEM 37
#define E_COMERCIAL 38
#define APOSTROFE 39
#define TREMA 249
#define SUBLINHADO 95
#define BARRA_VERTICAL 124
#define BARRA_INVERTIDA 92

#define ABRE_PARENTESES 40
#define FECHA_PARENTESES 41
#define ABRE_CHAVES 123
#define FECHA_CHAVES 125
#define ABRE_COLCHETES 91
#define FECHA_COLCHETES 93

#define SINAL_ADICAO 43
#define SINAL_DIVISAO 47
#define SINAL_MULTIPLICACAO 42
#define SINAL_SUBTRACAO 45
#define SINAL_MAIOR 62
#define SINAL_MENOR 60
#define SINAL_IGUAL 61

#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define F7 65
#define F8 66
#define F9 67
#define F10 68
#define F11 133
#define F12 134

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define ESPACO 32
#define TAB 9

#define PAGE_UP 73
#define PAGE_DOWN 81
#define INSERT 82
#define DEL 83
#define HOME 71
#define END 79
#define SETA_PARA_CIMA 72
#define SETA_PARA_BAIXO 80
#define SETA_PARA_DIREITA 77
#define SETA_PARA_ESQUERDA 75

#define ACENTO_AGUDO 239
#define ACENTO_GRAVE 96
#define TIL 126
#define ACENTO_CIRCUNFLEXO 94

#define VIRGULA 44
#define PONTO_FINAL 46
#define PONTO_E_VIRGULA 59
#define EXCLAMACAO 33
#define INTERROGACAO 63
#define DOIS_PONTOS 58

#define CTRL_A 1
#define CTRL_B 2
#define CTRL_C 3
#define CTRL_D 4
#define CTRL_E 5
#define CTRL_F 6
#define CTRL_G 7
#define CTRL_H 8
#define CTRL_I 9
#define CTRL_J 10
#define CTRL_K 11
#define CTRL_L 12
#define CTRL_M 13
#define CTRL_N 14
#define CTRL_O 15
#define CTRL_P 16
#define CTRL_Q 17
#define CTRL_R 18
#define CTRL_S 19
#define CTRL_T 20
#define CTRL_U 21
#define CTRL_V 22
#define CTRL_W 23
#define CTRL_X 24
#define CTRL_Y 25
#define CTRL_Z 26
#define CTRL_ABRE_COLCHETES 27
#define CTRL_BARRA_INVERTIDA 28
#define CTRL_FECHA_COLCHETES 28
#define CTRL_C_CEDILHA 29
#define CTRL_F1 94
#define CTRL_F2 95
#define CTRL_F3 96
#define CTRL_F4 97
#define CTRL_F5 98
#define CTRL_F6 99
#define CTRL_F7 100
#define CTRL_F8 101
#define CTRL_F9 102
#define CTRL_F10 103
#define CTRL_F11 137
#define CTRL_F12 138
#define CTRL_ENTER 10
#define CTRL_INSERT 146
#define CTRL_DELETE 147
#define CTRL_END 117
#define CTRL_PAGE_DOWN 118
#define CTRL_HOME 119
#define CTRL_PAGE_UP 134
#define CTRL_SETA_ESQUERDA 115
#define CTRL_SETA_DIREITA 116
#define CTRL_SETA_PARA_CIMA 141
#define CTRL_SETA_PARA_BAIXO 145
#define CTRL_TAB 148
#define CTRL_BACKSPACE 127

#define CTRL_ALT_ENTER 28
#define CTRL_ALT_BACKSPACE 14


typedef enum{DESLIGAR, LIGAR} status;

/* Retorna uma estrutura contendo o tamanho da janela de console atual:
   typedef struct _COORD{
                        SHORT X;   -> Largura da janela 
                        SHORT Y;   -> Altura da janela  
                        } COORD;
                        (
*/
COORD tamanhoJanelaConsole(void);

/* Retorna as dimensões máximas possíveis de uma janela na resolução atual do monitor */
COORD MaxDimensaoJanela(void);

/* Definir as novas dimensões da janela atual */
void setDimensaoJanela(int largura, int altura);

/* Retorna as coordenadas do canto superior esquerdo da janela: COORD campo X = linha superior; COORD campo Y = coluna esquerda */
COORD posicaoJanela(void);

/* Definir a nova posição da janela atual */
void setPosicaoJanela(int top, int left);

/* Esta função retorna o código da tecla pressionada.
   DETALHES:
   - Construída a partir da função getch().
   - Compile com a função getch() disponibilizada pelo próprio gcc e NÃO com a função
     getch() existente dentro do arquivo CONIO.C que foi disponibilizado. Abra o arquivo
     CONIO.C, localize a função getch() dentro dele e coloque todo o seu código como
     comentário. MOTIVO: a função getch() existente dentro do arquivo CONIO.C NÃO funciona 
     corretamente!
*/
unsigned int Tecla(int *);
#endif
