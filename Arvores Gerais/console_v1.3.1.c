/* Esta diretiva foi colocada para que o programa que utilizar esta biblioteca possa ser compilado corretamente. 
     Isso porque a função GetConsoleWindow precisa disso.
     A partir deste momento só rodará para Windows 2000 ou superior pois desabilitará todas as outras funções que 
	  sejam específicas de versões anteriores (Ex. win95, win98)	 
	 Observações: 
	 1) ao invés do código 0x0500 poderia-se usar a macro Windows2000 definida em w32api.h pelo gcc para windows.
	     Contudo, essa macro pode estar definida com um nome em outros compiladores (borland, visual studio, etc). 
	     Portanto, para garantir maior compatibilidade, manteve-se a escrita do valor em hexadecimal, mesmo perdendo
	     na legibilidade final 
	 2) Os códigos e significado dessa macro podem ser consultados em:
	      http://msdn.microsoft.com/en-us/library/aa383745.aspx */
#if (_WIN32_WINNT < 0x0500)
    #undef _WIN32_WINNT 
    #define _WIN32_WINNT 0x0500 /* 0x0500 corresponde a versão do Windows 2000 */
#endif

#include <windows.h> /* GetKeyState() */
#include <stdio.h>  /* printf() */
#include <conio.h>  /* getch() */
#include "console_v1.3.1.h"


/* C avan‡ado */
/* Usa chamadas a API do windows */
/* maiores informa‡äes podem ser consultadas no link:
http://msdn2.microsoft.com/en-us/libray/ms686311(VS.85).aspx */




/* Retorna uma estrutura contendo o tamanho da janela de console atual:
   typedef struct _COORD{
                        SHORT X;   -> Largura da janela
                        SHORT Y;   -> Altura da janela
                        } COORD;
                        (
*/
COORD tamanhoJanelaConsole(void)
{
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    SMALL_RECT srWindow;
    COORD dimJanela;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if(! GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
         printf("GetConsoleScreenBufferInfo(%ld)\n", GetLastError());

    srWindow = csbiInfo.srWindow;
    dimJanela.Y = srWindow.Bottom - srWindow.Top + 1;
    dimJanela.X = srWindow.Right - srWindow.Left + 1;

    return dimJanela;
}

COORD MaxDimensaoJanela(void)
{
    HANDLE hStdout;
    
    /* armazenar o controlador da janela atual */
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    
    return(GetLargestConsoleWindowSize(hStdout));    
      
}

COORD posicaoJanela(void)
{
    HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	COORD canto_superior_esquerdo; /* canto_superior_esquerdo.Y = linha superior da janela ;
                                                                                             canto_superior_esquerdo.X = = coluna mais a esquerda da janela */
	    
    /* armazenar o controlador da janela atual */
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	/* armazenar as coordenadas da janela atual */
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	
    canto_superior_esquerdo.Y = csbiInfo.srWindow.Top;
    canto_superior_esquerdo.X = csbiInfo.srWindow.Left;	
	
	return (canto_superior_esquerdo);
}

void setPosicaoJanela(int top, int left)
{
     HWND janela; /* variável responsável por armazenar o identificador da janela de console */

     /* Obter o identificador da janela de console */
	 janela = GetConsoleWindow(); 
	 
	 /* Posicionar a janela nas coordenadas passadas como parâmetro. Para detalhes da função SetWindowPos
                  consultar: http://msdn.microsoft.com/en-us/library/ms633545%28VS.85%29.aspx	 */
	 SetWindowPos(janela,
	              HWND_TOP,
				  left,
				  top, 
				  0, 0, 
				  SWP_NOSIZE);
}

void setDimensaoJanela(int largura, int altura)
{
    HANDLE hStdout;
    SMALL_RECT srWindow;
    COORD dimMaxJanela, novoBufferSize;
    
    /* armazenar o controlador da janela atual */
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	dimMaxJanela = MaxDimensaoJanela();
	if (dimMaxJanela.X < largura) printf("\nLargura fora do limite permitido. Valor máximo possível: %hi", dimMaxJanela.X);
    else if (dimMaxJanela.Y < altura) printf("\nAltura fora do limite permitido. Valor máximo possível: %hi", dimMaxJanela.Y);
    else
    {	
	     /* ajustar o buffer para a nova dimensão da janela. Caso contrário a janela não será redimensionada */
           novoBufferSize.X = 10 * largura;
		   novoBufferSize.Y = 20 * altura;
		   SetConsoleScreenBufferSize(hStdout, novoBufferSize);
		   
		 /* armazenar as novas altura e largura para a janela do console */           
           srWindow.Top = 0;
           srWindow.Bottom = altura - 1;
           srWindow.Left = 0;
           srWindow.Right = largura - 1;
    
         /* modificar a janela atual para as novas altura e largura */
           if ( ! SetConsoleWindowInfo(hStdout, TRUE, &srWindow))
           {
                printf("SetConsoleWindowInfo(%ld) \n", GetLastError());
           }
    } 
}


void setCursorStatus(status s)
{
    CONSOLE_CURSOR_INFO info;
    HANDLE hOutput = GetStdHandle (STD_OUTPUT_HANDLE);
    char buf[255];
    DWORD dwError;
    static DWORD dwSizeCursor; /* variável que armazenará o tamanho atual do cursor para quando for ligá-lo */

    /* armazenar as informações sobre o cursor atualmente */
    GetConsoleCursorInfo(hOutput, &info);
    switch (s)
    {
            case LIGAR:
                 info.bVisible = TRUE; /* turn the cursor on */
                 info.dwSize = dwSizeCursor;

                 break;
            case DESLIGAR:
                 info.bVisible = FALSE; /* turn the cursor off */
                 dwSizeCursor = info.dwSize; /* armazenar o tamanho do cursor */
                 break;
    }
       if( SetConsoleCursorInfo(hOutput,&info) == 0 )
       {
           dwError = GetLastError();
           printf("SetConsoleCurInfo failed(%ld)", dwError);
           FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, dwError,0,buf,sizeof(buf),0);
           printf("%s", buf);
       }
}



/* Esta função retorna o código da tecla pressionada.
   - Construída a partir da função getch().
   - Compile com a função getch() disponibilizada pelo próprio gcc e NÃO com a função
     getch() existente dentro do arquivo CONIO.C que foi disponibilizado. Abra o arquivo
     CONIO.C, localize a função getch() dentro dele e coloque todo o seu código como
     comentário. MOTIVO: a função getch() existente dentro do arquivo CONIO.C NÃO funciona
     corretamente!
*/
unsigned int Tecla(int *tecla)
{
    int codigo, tipo = 0;

    codigo = getch();

    switch (codigo)
    {
            case 0:  /* teclas especiais */
            case 224:
                 codigo = getch();
                 if ((codigo >= F1 && codigo <= F10) || (codigo >= F11 && codigo <= F12)) tipo += TECLA_FUNCAO;
                 else if (codigo == PAGE_UP || codigo == PAGE_DOWN || codigo == HOME || codigo == END || codigo == INSERT || codigo == DEL || codigo == SETA_PARA_CIMA || codigo == SETA_PARA_BAIXO || codigo == SETA_PARA_ESQUERDA || codigo == SETA_PARA_DIREITA) tipo += TECLA_ESPECIAL_2, tipo += TECLAS_ESPECIAIS;
                 break;
            default:
                 if ((codigo >= 'A' && codigo <= 'Z') || (codigo >= 'a' && codigo <= 'z')) tipo += LETRA_ALFABETO, (codigo >= 'A' && codigo <= 'Z')? (tipo += LETRA_MAIUSCULA) : (tipo += LETRA_MINUSCULA), tipo += CARACTERES_1, tipo += CARACTERES_2, tipo += CARACTERES_3, tipo += CARACTERES_4, tipo += CARACTERES_5, tipo += CARACTERES_6, tipo += CARACTERES_7;
                 else if (codigo >= '0' && codigo <= '9') tipo += DIGITO, tipo += CARACTERES_2, tipo += CARACTERES_3, tipo += CARACTERES_4, tipo += CARACTERES_5, tipo += CARACTERES_6, tipo += CARACTERES_7;
                 else if (codigo == ACENTO_CIRCUNFLEXO || codigo == TIL || codigo == ACENTO_AGUDO || codigo == ACENTO_GRAVE) tipo += ACENTO, tipo += CARACTERES_7;
                 else if (codigo == PONTO_FINAL || codigo == VIRGULA || codigo == DOIS_PONTOS || codigo == PONTO_E_VIRGULA || codigo == EXCLAMACAO || codigo == INTERROGACAO) tipo += PONTUACAO, tipo += CARACTERES_1, tipo += CARACTERES_3, tipo += CARACTERES_4, tipo += CARACTERES_5, tipo += CARACTERES_6, tipo += CARACTERES_7;
                 else if (codigo == ESC || codigo == ENTER || codigo == TAB || codigo == ESPACO) tipo += TECLA_ESPECIAL_1, tipo += TECLAS_ESPECIAIS;
                 else if (codigo == SINAL_ADICAO || codigo == SINAL_SUBTRACAO || codigo == SINAL_DIVISAO || codigo == SINAL_MULTIPLICACAO || codigo == SINAL_MAIOR || codigo == SINAL_MENOR) tipo += OPERADORES_MATEMATICOS, tipo += SIMBOLOS_MATEMATICOS, tipo += CARACTERES_4, tipo += CARACTERES_5, tipo += CARACTERES_6, tipo += CARACTERES_7;
                 else if (codigo == ARROBA || codigo == ASPAS_DUPLAS || codigo == CERQUINHA || codigo == CIFRAO || codigo == PERCENTAGEM || codigo == E_COMERCIAL || codigo == APOSTROFE || codigo == TREMA || codigo == SUBLINHADO || codigo == BARRA_VERTICAL || codigo == BARRA_INVERTIDA) tipo += SIMBOLO_ESPECIAL_1, tipo += CARACTERES_6, tipo += CARACTERES_7;
                 else if (codigo == ABRE_PARENTESES || codigo == FECHA_PARENTESES || codigo == ABRE_CHAVES || codigo == FECHA_CHAVES || codigo == ABRE_COLCHETES || codigo == FECHA_COLCHETES) tipo += SIMBOLO_ESPECIAL_2, tipo += SIMBOLOS_MATEMATICOS, tipo += CARACTERES_5, tipo += CARACTERES_6, tipo += CARACTERES_7;
    }

   
    if (GetKeyState(VK_LSHIFT) >> 7) tipo += TECLA_MODIFICADORA_1;
    if (GetKeyState(VK_RSHIFT) >> 7) tipo += TECLA_MODIFICADORA_1;
    if (GetKeyState(VK_LMENU) >> 7) tipo += ALT_ESQUERDO;
    if (GetKeyState(VK_RMENU) >> 7) tipo += ALT_GR; /* este nao ‚ o ALT e nao o ALT GR = CTRL_ESQUERDO + ALT DIREITO*/
    if (GetKeyState(VK_LCONTROL) >> 7) tipo += CTRL_ESQUERDO;
    if (GetKeyState(VK_RCONTROL) >> 7) tipo += CTRL_DIREITO;
	if ((tipo & CTRL_ESQUERDO) || (tipo & CTRL_DIREITO)) tipo += QUALQUER_CTRL;
    if ((GetKeyState(VK_CAPITAL) << 7) >> 7) tipo += CAPS_LOCK; /* CAPS LOCK key */

    *tecla = codigo;

    return tipo;
}



