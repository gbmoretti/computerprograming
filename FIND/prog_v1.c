/* Programa Raiz
    Descrição: Programa que procura recursivamente por um arquivo no computador. Ele pode receber até 3 argumentos. 
	O primeiro, com o diretório inicial da busca (argumento obrigatório). O segundo contendo o nome do arquivo (esse argumento suporta o uso de
	caracteres coringa (? e *). E o terceiro contendo uma string que deve ser encontrada dentro do arquivo.
	O programa primeiro varre recursivamente todas as subpastas contidas no diretorio inicial da pesquisa, depois procura por arquivos 
	que se encaixem no filtro setado no 2o argumento, e quando encontra um arquivo ele varre esse arquivo procurando pela string setada 
	no 3o argumento, quando encontra a string no arquivo o programa imprime a linha. Depois de todo o processo concluído é mostrada a quantidade
	de arquivos analisadas e de pastas percorridas.
	
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da última modificação: 21/05/2010 
*/

#include <stdlib.h> /* exit() */
#include <stdio.h>  /* printf() */
#include <io.h>     /* _findfirst(), _findnext(), estrutura _finddata  */
#include <strings.h> /* strcpy(), strlen(), strcpy() */
#include "conio_v3.1.h" /* wherey(), gotoxy() */

void find(char *, char *, char *,int *, int *); /* Funcao recursiva que percorre o diretorio (e os subdiretorios) */
void printPalavra(char *, char *); /* Funcao que procura por uma string dentro de um arquivo e imprime a linha onde existe aquela string */
int contaPalavra(char *, char *); /* Funcao que conta quantas linhas a string existe dentro do arquivo */
void dir_raiz(char *); /* Funcao para saber qual o diretorio raiz do programa */
void trataArgs(int, char *) /* Funcao que trata os argumentos recebidos pelo programa e chama a funcao find() de maneira correta */

int main (int argc, char *argv[]) {
	int conta_arqs = 0, conta_pastas = 0; /* Variaveis que guardarao a quantidade de arquivos e pastas analisadas */
	char diretorio[200]; /* Variavel que guardara o diretorio em que a pesquisa deve iniciar */

	system("cls");
	
	/* Se o diretorio em que a pesquisa for iniciar for igual a '.', guarda em diretorio o diretorio raiz do programa */
	if(strcmp(argv[1],".") == 0) {
		dir_raiz(diretorio);
	}else {
		strcpy(diretorio,argv[1]);
	}
	
	trataArgs(argc,argv); /* chama função para tratar argumentos */ 
	
	if(conta_arqs > 0) {
		printf("Foram analisados %d arquivos em %d pastas",conta_arqs,conta_pastas);
	}else {
		printf("Foram analisadas %d pastas e nenhum arquivo foi encontrado.\n",conta_pastas);
	}
	return 0;
}

/* Funcao que trata os argumentos recebidos pelo programa e chama a funcao find() de maneira correta */
void trataArgs(int argc,char *argv[]) {
	/* Tratando os argumentos */
	switch (argc) {
		case 2:
			printf("Procurando em %s\n\n",diretorio);
			find(diretorio,"*.*","",&conta_arqs,&conta_pastas);
			break;
		case 3:
			printf("Procurando em %s, utilizando o filtro %s\n\n",diretorio,argv[2]);
			find(diretorio,argv[2],"",&conta_arqs,&conta_pastas);
			break;
		case 4:
			printf("Procurando em %s arquivos contendo \"%s\", utilizando o filtro %s\n\n",diretorio,argv[3],argv[2]);
			find(diretorio,argv[2],argv[3],&conta_arqs,&conta_pastas);
			break;
		default:
			printf("Erro nos argumentos (%d). Maneira correta: find [diretorio inicial] <filtro de arquivo> <palavra que deve conter o arquivo>\n",argc);
			exit(1);
	}
}

/* Imprime no arquivo temp o diretorio raiz do programa, depois le o arquivo temp e salva o conteudo na string apontada por dir */
void dir_raiz(char dir[]) {
	FILE *arq;
	int tam;
	
	system("cd > temp");
	
	arq = fopen("temp","r");
	fgets(dir,99,arq);
	fclose(arq);
	system("del temp");

	tam = strlen(dir);
	dir[tam-1] = '\0'; /*apagando o \n do final da string*/

}

/* Percorre o arquivo passada por argumento procurando pela string contida na string palavra. 
	Quando encontra a string, imprime a linha toda do arquivo */
void printPalavra(char arquivo[], char palavra[]) {
	int c_linha;
	char linha[1000];
	FILE *arq;
	
	c_linha = 0;
	
	arq = fopen(arquivo,"r");
	if(!arq) {
		return;
	}
	
	/* Laço que percorre por todo o arquivo procurando pela palavra passada por argumento. Quando encontra uma linha com a palavra, ele imprime */
	while(!feof(arq)) {
		fgets(linha, 999, arq);
		c_linha++;
		if(strstr(linha,palavra)) {
			printf("    \tLinha %d: %s",c_linha,linha);
		}
	}
}

/* Retorna quantas linhas do arquivo, passado por argumento, a string, apontada pelo ponteiro palavra, é encontrada */
int contaPalavra(char arquivo[], char palavra[]) {
	int conta_linha; /* conta_linha conta a quantidade de linhas em que a string palavra ocorre */ 
	char linha[1000];
	FILE *arq;
	
	conta_linha = 0;
	
	arq = fopen(arquivo,"r");
	if(!arq) {
		return -1;
	}
	
	/* Laço que percorre por todo o arquivo procurando pela palavra passada por argumento. Quando encontra uma linha com a palavra, 
	ele soma 1 na variavel conta_linha */
	while(!feof(arq)) {
		fgets(linha, 999, arq);
		if(strstr(linha,palavra)) {
			conta_linha++;
		}
	}
	return conta_linha;
}

/* Funcao recursiva que percorre o diretorio "dir_const" e chama a propria find() quando encontra um subdiretorio. 
	Depois de percorrer o diretorio pela primeira vez, percorre novamente mas agora procurando por arquivos que se encaixam no filtro "arquivo" */
void find(char dir_const[], char arquivo[], char palavra[], int *arqs, int *pastas) {
	long int id, id_arqs;
	struct _finddata_t dados_dir; /* estrutura para percorrer o diretorio procurando por subdiretorios */
	struct _finddata_t dados_arqs; /* estrutura para percorrer o diretorio procurando por arquivos que se encaixam no filtro "arquivo" */
	char dir_find[400], arqs_find[400], caminho_arquivo[400];
	
	/* constrói uma string "<diretorio>\*" para listar todos os arquivos e subdiretorios contidos no diretorio */
	strcpy(dir_find,dir_const);
	sprintf(dir_find,"%s\\*",dir_find);
	
	id = _findfirst(dir_find,&dados_dir); 
	if (id == -1) {
		return;
	}
	
	/* laço que percorre todo o diretorio */
	while(!_findnext(id, &dados_dir)) {
		if(dados_dir.attrib & _A_SUBDIR) { /* se o arquivo for um diretorio... */
			sprintf(dir_find,"%s\\%s",dir_const,dados_dir.name); /* adiciona ao final do diretorio o nome do subdiretorio encontrado, 
																		p/ poder percorrer esse subdiretorio */				
			if(dir_find[strlen(dir_find)-1] != '.') { /* condicao para nao entrar no diretorio "." e nem no ".." */ 
				(*pastas)++; /* conta mais uma pasta percorrida */
				find(dir_find,arquivo,palavra,arqs,pastas); /* chamando ela mesma para percorrer o subdiretorio encontrado */ 
				
				sprintf(arqs_find,"%s\\%s",dir_find,arquivo); /* adicionando o filtro "arquivo" para listar somente os arquivos */
				id_arqs = _findfirst(arqs_find,&dados_arqs);
				
				/* laço que percorre todo o diretorio */
				while(!_findnext(id_arqs, &dados_arqs)) {
					if(!(dados_arqs.attrib & _A_SUBDIR)) { /* se o arquivo não for um diretorio... */
						(*arqs)++; /* conta como mais um arquivo analisado */
						if(strcmp(palavra,"") != 0) {
							sprintf(caminho_arquivo,"%s\\%s",dir_find,dados_arqs.name); /* cria o caminho completo para o arquivo, 
																							p/ poder chamar a funcao que vai percorrer esse arquivo */
							printf("Analisando: %-20s em %s\n",dados_arqs.name,dir_find);
							if(contaPalavra(caminho_arquivo,palavra) > 0) { /* se a quantidade de linhas contendo a string "palavra" for > 0... */
								gotoxy(1,wherey()-1); /* sobe o cursor uma linha, para escrever em cima de "Analisando..." */
								printf("Encontrado: %-30s em %s\n",dados_arqs.name,dir_find); 
								printPalavra(caminho_arquivo,palavra); /* chama funcao que imprime todas as linhas contendo a string "palavra" */
								printf("\n");
							}
						}else {
							printf("%-30s em %s\n",dados_arqs.name,dir_find);
						}
					}
				}
			}				
		}
	}
		
	_findclose(id);

}
