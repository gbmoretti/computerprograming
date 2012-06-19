/* Programa Raiz
    Descrição: Makefile .
    Programador: Valter Hugo Guandaline
    RGM: 017727
    Data da última modificação: 01/04/2010 */
#include <stdio.h>/*printf()*/
#include <stdlib.h>/*FILE, fopen, fclose,...*/
#include <string.h>/*strlen, strcpy, strcat, strupr*/

/*Funcionamento do programa: 
Primeiro ele verifica se o arquivo passado pelo usuario exite caso não exista ele fecha o programa, 
caso exista ele procura por bibliotecas "pessoais",  caso exitam  essas bibliotecas guarda todas em uma lista
Procura o caminho do compilador gcc, caso não exista ele insere o caminho na variavel path.
Procura pelo arquivo dirs.txt, caso não exita ele cria o arquivo dirs.txt cotendo os diretorio, cria as pastas e
move as bibliotecas para as mesmas, apos isso ele gera o executavel do programa*/

int pegalibs(char *);/*guarda  os nomes das blibioteca a parte  */
int busca_lib(char *, char *);/*le linha a linha do arquivo procurando "#includes ""  eu passaos para uma variavel auxiliar*/
int compara(char *, char *, int);/*começa a buscar o caminho na variavel path a partir da posição n passada por parametro*/
int dirs();/*verifica se o arquivo dirs.txt exite caso não exia ele cria o arquivo e as pasta */
void busca_gcc(char *);/*busca o caminho do gcc na variavel de ambiente path e envia para o SO*/
void move(char **, int);/*move as bibliotecas seus "cabeçalho" para as pasta libs_minhas e headers_meu respectivamente*/
void gera_linha(char **, char *,int );/*gera a linha a ser enviada para o prompt de comando para a geração de executaveis*/

int pegalibs(char *nome){
	char **libs;/*variavel para guarda os nomes das bibliotecas*/
	char linha[51], aux[20];/*variavel para ler uma linha do arquivo, e para pegar o nome da biblioteca caso haja, respectivamente*/
	int i,n;/*cantador para o numero de bibliotecas*/
	FILE *arq;
	if((arq=fopen(nome, "r"))==NULL){
		printf("\nArquivo nao encontrado!\n");
		return 1;/*encerra o programa casso não seja possivel ler o arquivo*/
	}
	libs=(char **)malloc(sizeof(char)*1);/*aloca espaço para as bibliotecas*/
	n=0;/*ZERA O CONTADOR*/
	do{
		fgets(linha,50,arq);/*pega linha a linha do arquivo...*/
		if(busca_lib(linha, aux)){/*caso a função encontre alguma biblioteca "particular" a mesma guarda seu nome em uma variavel auxiliar*/
			libs[n]=(char *)malloc(sizeof(char)*strlen(aux));/*aloca espaço para o nome na lista de bibliotecas*/
			strcpy(libs[n],aux);/*copia o nome na lista*/	
			n++;
			(char **)realloc((void*)libs,n*sizeof(char));
		}
	}while(!feof(arq));/*enquanto nao encontra o fim do arquivo*/
	fclose(arq);
		if(dirs())/*verifica se jah exitem  os diretorios, caso nao a função os cria*/
			move(libs,n);/*move  as biblioteca para os diretorios criados, caso estes tenha sido  recem criados */
	gera_linha(libs,nome,n);/*gera a linha de comando para o prompt e comando*/
	for(i=0;i<n;i++){
		free(libs[i]);
	}
	free(libs);
	return 0;
}

void busca_gcc(char *path){
	char *gcc={";C:\\DEV-CPP\\BIN"};/*caminho do gcc*/
	int i=0;/*Contador INICIALIZADO*/
	while(i<strlen(path) && compara(path,gcc,i)!=1)/*sai do laço se percorrer toda a variavel path ou se encontrar o caminho*/
		i++;
	if (i==strlen(path)){/*significa que nao encontrou pois percorreu toda a variavel  path*/
		strcat(path,gcc);/*adiciona o caminho do gcc no final da variavel path */
		putenv(path);/*envia a variavel para o so*/
	}
}

int compara(char *path, char *gcc, int n){
	int i=0;/*Declara e INICIALIZA O CONTADOR*/
	while(i<strlen(gcc)&& gcc[i]==path[i+n])/*sai do laço se percorrer toda a variavel ou se encontrar algum caracter diferente*/
		i++;
	if (i==strlen(gcc))/*significa que encontrou pois soh percorre toda a variavel caso nao encontre nenhum caracter diferente*/
		return 1;
	return 0;/*caso não encontre*/
}

int busca_lib(char *linha, char *aux){
	char *lib={"#include \""};
	int tam, i=0;/*Declara e INICIALIZA O CONTADOR*/
	tam=strlen(lib);
	while(i<tam && lib[i]==linha[i])/*sai do laço se percorrer toda a variavel ou se encontrar algum caracter diferente*/
		i++;
	if(i==tam){/*significa que encontrou pois soh percorre toda a variavel caso nao encontre nenhum caracter diferente*/
		i=0;/*ZERA O CONTADOR*/
		while ((linha[i+tam])!='\"'){/*começa a copiar uma posição apos o " e para quando encontra  outro " */
			aux[i]=linha[i+tam];/*copia o nome da biblioteca caracter  a caractere*/
			i++;
		}
		aux[i-1]='c';/*acrescenta um 'C' no luga do 'H'*/
		aux[i]='\0';/*encerra  o nome*/
		return 1;/* se encontrar alguma biblioteca*/
	}
	return 0;/*caso não encontre*/
}

int dirs(){
	FILE *arq;
	if((arq=fopen("dirs.txt", "r"))==NULL){/*abri o arquivo caso ele exista*/
		printf("\nArquivo dirs.txt nao encontrado!");
		printf("\nCriando o arquivo dirs.txt");
		if((arq=fopen("dirs.txt", "w"))==NULL){/*cria o arquivo caso ele não exista*/
			printf("\nO Arquivo nao pode ser criado!");
			return -1;/*se o arquivo não puder ser criado*/
		}
		fprintf(arq, "%s", "C:\\headers_meus\n");/*escreve os diretorios no arquivo*/
		fprintf(arq, "%s", "C:\\libs_minhas\n");
		printf("\nCriando as pastas!");
		system("md C:\\headers_meus");/*cria as pastas*/
		system("md C:\\libs_minhas");
		fclose(arq);
		return 1;/*caso o arquivo tenha sido criado*/
	}
	fclose(arq);
	return 0;/*caso o  arquivo ja exista*/
}

void move(char **libs, int n){
	char mova[100];
	char aux[100], head[100], bibli[100];
	int i=0;/*Declara e INICIALIZA O CONTADOR*/
	FILE *arq;
	if((arq=fopen("dirs.txt", "r"))==NULL){
		printf("Não foi possivel encontrar o diretorio pra mover os arquivos");
		exit(1);/*fecha o programa*/
	}
	fgets(head,50,arq);/*pega os endereços */
	fgets(bibli,50,arq);
	fclose(arq);
	if(n>0)
		printf("\nMovendo os arquivos!\n");
	while(i<n){/*percorre a lista  de bibliotecas ate ofim*/
		mova[0]='\0';/*zera a varivael para  não montar um comando no fim de outro*/
		strcat(mova,"move ");/*o comando "move"*/
		strcat(mova,libs[i]);/*adiciona a biblioteca a ser movida*/
		strcat(mova," ");/*espaço*/
		strcat(mova,bibli);/*adiciona o diretorio*/
		system(mova);/*move o arquivo*/
		strcpy(aux,libs[i]);/*copia a biblioteca em uma variavel auxiliar, para evitar perca de dados*/
		mova[0]='\0';/*zera para montar o comando para o arquivo .H  */
		aux[strlen(aux)-1]='h';/*coloca um H no luga do C*/
		strcat(mova,"move ");/*comando*/
		strcat(mova,aux);/*adiciona o header a ser movida*/
		strcat(mova," ");/*espaço*/
		strcat(mova,head);/*adiciona o diretorio*/
		system(mova);/*move o arquivo*/
		i++;
	}
}

void gera_linha(char **libs,char *nome, int n){/*monta a linha para gerar o executavel do arquivo*/
	char gcc[100];
	char c_head[100], caminho[100], aux[100], head[100], bibli[100];
	int i=0;/*Declara e INICIALIZA O CONTADOR*/
	FILE *arq;
	if((arq=fopen("dirs.txt", "r"))==NULL){
		printf("Não foi possivel encontrar o diretorio pra abrir os arquivos");
		exit(1);/*encerra o programa*/
	}
	fgets(head,50,arq);/*pega os diretorios*/
	fgets(bibli,50,arq);
	head[strlen(head)-1]='\0';/*tira o \n do fim da linha*/
	fclose(arq);
	/*gcc -o prog prog.c <caminho_do_c>/lib.c -I<caminho_do_h> -Wall*/
	strcpy(gcc,"gcc -o ");/*começa alinha de comando*/
	strcpy(aux,nome);/*utiliza-se uma fariavel auxiliar para evitar perca de dados*/
	aux[strlen(aux)-2]=' ';/*retira o  '.' do nome e acrescenta um espaço no lugar*/
	aux[strlen(aux)-1]='\0';/*retira o C e termina a variavel*/
	strcat(gcc,aux);/*acrescenta na linha de comando o nome do executavel*/
	strcat(gcc,nome);/*acrescenta o nome do arquivo .C*/
	while(i<n){/*vai ate o fim da lista de bibliotecas*/
		caminho[0]='\0';/*zera o caminho*/
		strcat(caminho, bibli);/*acrescenta o endereço das bibliotecas*/
		caminho[strlen(caminho)-1]='\\';
		strcat(caminho,libs[i]);/*acrescenta o nome*/
		strcat(gcc," ");
		strcat(gcc,caminho);/*acrescenta o caminho a linha de comando*/
		i++;
	}
	if (n>0){	/*caso exista alguma biblioteca*/
		strcpy(c_head," -I");
		strcat(c_head,head);
		strcat(gcc,c_head);
	}
	strcat(gcc," -Wall");	
	printf("\n%s\n\n", gcc);
	system(gcc);/*gera o executavel*/
}

int main(int argc, char **argv, char **env){
	char *nome=argv[1];	
	char *path;
	int i=0;/*Declara e INICIALIZA O CONTADOR*/
	FILE *arq;
	if(pegalibs(nome))
		return 1;
	while(env[i]){
		strupr(env[i]);/*passa toda a envi para caixa alta*/
		i++;
	}		
	path=getenv("PATH");
	busca_gcc(path);/*procura e acrescenta o caminho do gcc na variavel path caso nao tenha*/
	nome[strlen(nome)-1]='\0';
	strcat(nome,"exe");/*nome do executavel*/
	if((arq=fopen(nome, "r"))!=NULL){ 
		printf("\nArquivo gerado %s\n",nome);
		system(nome);/*executa o arquivo gerado pelo makefile*/
		fclose(arq);
	}
	else printf("\nO arquivo %s nao pode ser gerado!\n", nome);	
	return 0;
}
