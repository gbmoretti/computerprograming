#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>


void busca(const char *, const char *, const char *, int *, int *);
int comparaCoringas(char *, char *);
int compara_string(char *, char *);

int compara_string(char *string1, char *string2) {
	int i, maior, j, igual;
	char s_maior[10000],s_menor[10000];

	maior = strlen(string1);
	strcpy(s_maior,string1);
	strcpy(s_menor,string2);

	if(maior < strlen(string2)) {
		maior = strlen(string2);
		strcpy(s_maior,string2);
		strcpy(s_menor,string1);
	}
	for(i = 0;i<maior;i++) {
		igual = 0;
		if(s_maior[i] == s_menor[0]) {
			j = 1;
			while(j<strlen(s_menor) && igual == 0) {
				if(s_menor[j] != s_maior[i+j]) {
					igual = 1;
				}
				j++;
			}
			if(igual == 0) {
				return i;
			}
		}
	}
	return -1;
}

int comparaCoringa(const char *str1, char *str2) {
	int i, tam, pos_asterisco;

	
	pos_asterisco = compara_string(str1,"*");
	
	return pos_asterisco;
}

int main(int argc,char *argv[])
{ //find “.” “teste.c” “include” 
	int conta_arqs = 0, conta_pastas = 0;
		
	if (argc == 1) 
		busca(argv[1],"","",&conta_arqs,&conta_pastas);
	if (argc == 2)
		busca(argv[1],argv[2],"",&conta_arqs,&conta_pastas);
	if (argc == 3) 
		busca(argv[1],argv[2],argv[3],&conta_arqs,&conta_pastas);
	if (argc > 3 || argc < 1) {
		printf("Erro nos argumentos (%d)\n",argc);
		exit(1);
	}
	
	printf("Foram analisados %d arquivos em %d pastas",conta_arqs,conta_pastas);
	
	return 0;
}

void busca(const char *diretorio, const char *arquivo, const char *palavra, int *carqs, int *cpastas)
{
	DIR *pasta; /* ponteiro para a pasta */
	struct dirent *dir;
	char vai_para_frente[500], valor[500]; /* para ir a proxima pasta */
	
	strcpy(valor,diretorio);
		
	sprintf(valor,"%s\\",valor);
	
	pasta = opendir(valor);  /* busca nomes em diretório */
	
	if(pasta == NULL) { 
		printf(">>finalizou?!\n");
		return; /* ocorreu um erro fatal */
	}
	
	dir = readdir(pasta); /* ler nome e sair varrendo */
	while(dir != NULL){		
		if(!(pasta->dd_dta.attrib & _A_SUBDIR))
		{/* verifica se é subdiretorio */
			sprintf(vai_para_frente,"%s\\%s",valor,pasta->dd_dta.name);
			(*carqs)++;
			printf("Comparacoringa: %d\n",comparaCoringa(arquivo,pasta->dd_dta.name));
			/*if(!strcmp(arquivo,pasta->dd_dta.name)) {
				printf("Arquivo: %s, encontrado em %s\n",pasta->dd_dta.name,vai_para_frente);
				/* mostrar o nome do arquivo
			}*/			
		}
		else if(!((!strcmp(pasta->dd_dta.name,".")) || (!strcmp(pasta->dd_dta.name,".."))))
		{
			sprintf(vai_para_frente,"%s\\%s",valor,pasta->dd_dta.name);
			(*cpastas)++;
			busca(vai_para_frente,arquivo,palavra,carqs,cpastas);
		}
		dir = readdir(pasta); /* ler nome e sair varrendo */
	}
	closedir(pasta);
	return;
}
