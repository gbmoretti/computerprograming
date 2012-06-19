/* Programa Raiz
    Descrição: Makefile
    Programador: Guilherme Burille Moretti
    RGM: 17710
    Data da última modificação: 06/04/2010 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>

/*
Função que compara duas strings e retorna a posição (na string de maior tamanho) em que a string (menor) foi encontrada. Ou retorna -1 caso não haja ocorrencia da string menor na string menor.
*/
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

/*
Funcao que transforma todas as letras maiusculas da string em minusculas
*/
char* paraminusculo(char string[]) {
	int i;

	for(i=0;i<strlen(string);i++) {
		if(string[i] >= 'A' && string[i] <= 'Z') {
			string[i] = string[i] + ('a' - 'A');
		}
	}

	return string;
}

/*
Função que retorna um vetor de ponteiros, onde se encontram todas as bibliotecas não-padrão encontradas no arquivo
*/
char** localiza_libs(char arquivo[]) {
	char linha[9999], lib[100], **libs;
	int j, k, l, enc, qnt_libs, bib_existe, tam;
	FILE *arq;
	
	arq = fopen(arquivo,"r");
	
	if(!arq) {
		printf("Certifique-se de que o arquivo existe e pode ser lido\n");
		exit(1);
	}
	
	qnt_libs = 0;
	//alocando um vetor de ponteiro, que armazenara as strings com os nomes das bibliotecas
	libs=(char **)malloc(sizeof(char)*20);

	while(!feof(arq)) {
		fgets(linha, 9998, arq);
		
		if(compara_string(linha,"#include \"") != -1) {
			j = 0;
			enc = 0;
			k = 0;
			
			//laço que percorre a string linha, procura pela biblioteca e salva em lib
			while(j<strlen(linha)) {
				if(linha[j] == '"' && enc == 0) { //se o caracter for igual a " e a biblioteca nao foi encontrada ainda (enc = 0), entao o nome da biblioteca começa no proximo caracter
					enc = 1; //biblioteca foi encontrada
				}
				if(enc == 1 && linha[j] != '"') { //se a biblioteca ja foi encontrada e o caracter nao é igual a " entao salva caracter na string lib
					if(lib[k] != '"') { 
						if(linha[j] != '\n') { //condicao pra nao salvar o \n no final da string
							lib[k] = linha[j];
						}
						k++;
					}else {
						enc = 0;
					}
				}
				j++;
			}
			lib[k-1] = '\0'; //caracter NULL no final da string para delimitar seu final
			//////////////////////////////////////
			
			//laço que percorre a libs para verificar se a biblioteca nao é repetida
			bib_existe = 0;
			for(l = 0;l<qnt_libs;l++) {
				if(strcmp(libs[l],lib) == 0) { //BIBLIOTECA JA EXISTE!
					bib_existe = 1;
				}
			}
			//////////////////////////////////////////
			
			//se biblioteca nao for repetida, adiciona na libs
			if(bib_existe == 0) {
				tam = strlen(lib);
				libs[qnt_libs] = (char *)malloc(sizeof(char)*tam);
				strcpy(libs[qnt_libs],lib);
				qnt_libs++;
			}				
			///////////////////////////////////////////
		}
	}
	fclose(arq);
	
	libs[qnt_libs] = '\0'; //ultima posicao do vetor tem valor NULL, para o programa saber quando ela termina
	
	return libs;
}

/*
Funcao que salva no endereço do ponteiro linha a string com o caminho para os .c lidos de dirs.txt
*/
void caminho_c(char* linha) {
	FILE *arq;
	int i;
	
	arq = fopen("dirs.txt","r");
	
	fgets(linha,199,arq); //1a linha é o diretorio dos headers, nao interessa para esse funcao
	fgets(linha,199,arq); //2a linha é o diretorio dos .c
	
	i = strlen(linha);
	linha[i] = '\0'; //adicionando valor NULL ao final da string
	
	fclose(arq);
}

/*
Funcao que salva no endereço do ponteiro linha a string com o caminho para os .h lidos de dirs.txt
*/
void caminho_h(char* linha) {
	int i;
	FILE *arq;
	
	arq = fopen("dirs.txt","r");
	
	fgets(linha,199,arq); //1a linha é o diretorio dos headers
	
	i = strlen(linha);
	linha[i] = '\0'; //adicionando valor NULL ao final da string
	
	fclose(arq);
	
}

/*
Funcao que tira a extensão do arquivo
*/
char* tira_extensao(char *arquivo) {
	int i;
	char *retorno;
	
	retorno = malloc(sizeof(char)*100);
	for(i = 0;arquivo[i] != '.';i++) {
		retorno[i] = arquivo[i];
	}
	retorno[i] = '\0'; //adicionando valor NULL ao final da string
	return retorno;
}

/*
Função que verifica se o programa foi compilado com sucesso e pergunta ao usuario se ele deseja rodar
*/
void executa_prog(char *nome) {
	char tecla;
	FILE *arq;
	
	strcat(nome,".exe");
	
	if((arq = fopen(nome,"r"))) {
		printf("Arquivo compilado com sucesso! Deseja roda-lo? (s/n) ");
		tecla = getch();
		if(tecla == 's' || tecla == 'S') {
			system("cls");
			system(nome);
		}
	}else {
		printf("Programa nao foi compilado.");
	}
}

int main(int argc, char *argv[], char *env[]) {
	char **libs, arquivo[100], *path, dir_c[200], dir_h[200], *nome_prog, *lib, move[900], gcc[900];
	int i;
	FILE *dirs;

	strcpy(arquivo,argv[1]);

	libs = localiza_libs(arquivo); //pegando todas as bibliotecas que o programa usara para compilar
    nome_prog = tira_extensao(arquivo); //salvando o nome do programa (sem o .c)
	
	//laço para passar toda a variavel env para minuscula
	i = 0;
	while(env[i] != '\0') {
		env[i] = paraminusculo(env[i]);
		i++;
	}
	//////////////////////////////////////////////
	path = getenv("path"); //pegando conteudo da variavel path
	
	//se GCC nao estiver na path, adiciona
	if(compara_string(path,"c:\\dev-cpp\\bin") == -1) {
		printf("GCC nao configurado. Configurando...\n");
		putenv("path=%path%;C:\\Dev-cpp\\bin\\");
	}
	
	//se não há libs não-padrão para compilar, programa termina aqui
	if(libs[0] == '\0') {
		gcc[0] = '\0';
		strcat(gcc,"gcc -o ");
		strcat(gcc,nome_prog);
		strcat(gcc," ");
		strcat(gcc,arquivo);
		
		printf("%s",gcc);
		system(gcc);
		
		exit(0);
	}
	//////////////////////////////////////////////////////////
	
	//verificando a existencia do dirs.txt e se existir pegando os caminhos dos .c e dos .h
	dirs = fopen("dirs.txt","r");

	if(dirs) {
		caminho_c(dir_c);
		caminho_h(dir_h);
	}else {
		printf("dirs.txt nao encontrado. Bibliotecas estao no mesmo diretorio que o programa.\n");
		
		//CRIA DIRETORIOS E MOVER ARQUIVOS AQUI
		printf("Criando subdiretorios...\n");
		system("md C:\\headers_meus");
		system("md C:\\libs_minhas");
		
		printf("Movendo arquivos...\n");
		
		//MOVENDO HEADERS
		for(i=0;libs[i] != '\0';i++) {
			move[0] = '\0';
			strcat(move,"move ");
			strcat(move,libs[i]);
			strcat(move," C:\\headers_meus");
			system(move);
		}
		
		//MOVENDO LIBS
		for(i=0;libs[i] != '\0';i++) {
			move[0] = '\0';
			strcat(move,"move ");
			lib = tira_extensao(libs[i]);
			strcat(move,lib);
			strcat(move,".c C:\\libs_minhas");
			system(move);
		}
		//////////////////////////////////////////////

		//setando valores padroes para dir_c e dir_h
		dir_c[0] = '\0';
		strcat(dir_c,"C:\\libs_minhas\\");
		dir_h[0] = '\0';
		strcat(dir_h,"C:\\headers_meus");
		///////////////////////////////
		
		//CRIANDO ARQUIVO dirs.txt
		printf("Criando dirs.txt\n");
		dirs = fopen("dirs.txt","w");
		fprintf(dirs,"C:\\headers_meus\n");
		fprintf(dirs,"C:\\libs_minhas\\");
		fclose(dirs);
		//////////////////////////////////////////
	}
	//////////////////////////////////////////
	
	//construindo string gcc
	gcc[0] = '\0';
	
	strcat(gcc,"gcc -o ");
	strcat(gcc,nome_prog);
	strcat(gcc," ");
	strcat(gcc,arquivo);
	strcat(gcc," ");
	
	//adicionando as strings <caminho><lib>.c à string gcc
	for(i=0;libs[i] != '\0';i++) {
		lib = tira_extensao(libs[i]);
		if(dir_c[0] != '\0') {
			strcat(gcc,dir_c);
		}
		strcat(gcc,lib);
		strcat(gcc,".c ");
	}
	
	//adicionando -I<caminho_dos_headers>
	if(dir_h[0] != '\0') {
		strcat(gcc,"-I");
		strcat(gcc,dir_h);
	}
	
	strcat(gcc," -Wall");
	////////////////////////////////////////////
	
	printf("Compilando...\n");
	system(gcc);
	
	//roda funcao que rodara (ou nao) o programa compilado
	executa_prog(nome_prog);
	
	//DESALOCANDO PONTEIROS USADOS
	for(i=0;libs[i] != '\0';i++) {
		free(libs[i]);
	}
	free(libs);
	
	/////////////////////////////////////
	
	
	return 0;
}
