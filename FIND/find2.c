#include <stdlib.h> /* exit() */
#include <stdio.h>  /* printf() */
#include <dirent.h>  /* struct DIR, struct dirent  */ 
#include <strings.h> /* strcpy(), strlen() */

void find(char *dir);

int main (int argc, char *argv[])
{
  /*char *lista_nomes_de_um_diretorio = "H:\\pcii";*/

  find(argv[1]);

  return 0;
}

void find(char *dir_const) {
	DIR *id_pasta; /* ponteiro para o fluxo correspondente a pasta a ser analisada */
	struct dirent *id_nome; /* ponteiro para um dos nomes da pasta */
	char dir_find[200], dir[200]; /*string q sera usada na funcao _findfirst e _findnext*/
	
	strcpy(dir,dir_const);
	
	
	printf("----- iniciando find(%s) ------\n",dir);
	dir_find[0] = '\0';
	strcpy(dir_find,dir);
	strcat(dir_find,"\\*.*");
	
	id_pasta = opendir(dir); /* abrir o fluxo para a pasta desejada e retornar um ponteiro para esse fluxo */
	
	if (id_pasta == NULL) exit(1);
	
	printf("Procurando em %s...\n",dir_find);
	do {
		id_nome = readdir(id_pasta); /* ler um nome da pasta sendo varrida. Uma vez lido, automaticamente, a próxima leitura será do próximo nome na pasta */
		
		if(id_pasta->dd_dta.attrib & _A_SUBDIR) {
			dir_find[0] = '\0';
			strcpy(dir_find,dir);
			strcat(dir_find,"\\");
			strcat(dir_find,id_pasta->dd_dta.name);
			
			if(dir_find[strlen(dir_find)-1] != '.') { 
				printf("find(%s)\n",dir_find);
				find(dir_find);				
			}
		}else {
			printf("   Arquivo: %s\n",id_pasta->dd_dta.name);
		}
	}while(id_nome != NULL);/* repetir enquanto houver nomes não lidos no fluxo corresponde a pasta sendo varrida */
	
	closedir(id_pasta);  /* desalocar todos os recursos alocados em id_pasta */
	printf("----- terminando find(%s) -----\n",dir);
}	

