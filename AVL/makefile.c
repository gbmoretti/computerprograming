#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define TAM_MAX 500

void monta_cabecalhos(char*, char*, char*, char*, int, int);
void monta_linha_de_compilacao(char*, char*, char*, char*, int);
void compila_prog(char*, char*, int);

char *converte_para_maiusculo(char *aux_path){ /* Converte para miúsculo o parâmetro passado*/
    int i;

    while(aux_path[i] != '\0'){
        if (aux_path[i] >= 'a' && aux_path[i] <= 'z'){
            aux_path[i] = 'A' + (aux_path[i] - 'a');
        }

         i++;
    }

    return aux_path;
}

int identifica(char *aux, char *verifica){ /* Função generica que executa várias operações de comparação*/
    int i=0, j=0, cont=0, tam_aux;

    tam_aux = strlen(verifica);

    while(aux[i] != '\0'){
        while(verifica[j] == aux[i] && verifica[j] != '\0'){
            cont++;
            i++;
            j++;
        }
        if(cont == tam_aux){
            return 1;
        }

        cont = 0;
        i++;
        j=0;
    }

    return 0;
}

char *lista_pastas(char *nome_pasta){ /* Lista as pastas no diretorio especificado pelo parâmetro */
    DIR *id_pasta;
    static char guarda_nomes[TAM_MAX];
	struct dirent *id_nome;

    guarda_nomes[0] = '\0';

	id_pasta = opendir(nome_pasta);

    if(id_pasta != NULL){
		do{
			id_nome = readdir(id_pasta);

			sprintf(guarda_nomes + strlen(guarda_nomes), "%-30s", id_pasta->dd_dta.name);

			if(id_pasta->dd_dta.attrib & _A_SUBDIR){
			    sprintf(guarda_nomes + strlen(guarda_nomes), "%s", "<DIR>");
			}

			sprintf(guarda_nomes + strlen(guarda_nomes), "\n");

        }while(id_nome != NULL);

    }

    closedir(id_pasta);

    return guarda_nomes;
}

void linka_compilador(char *nome_caminho){ /* Linka o compilador caso não esteja linkado */
    char caminho_compilador[TAM_MAX];

    caminho_compilador[0] = '\0';

    printf("Linkando Compilador...\n");

    sprintf(caminho_compilador + strlen(caminho_compilador), "%s", "path=%path%;");
    sprintf(caminho_compilador + strlen(caminho_compilador), "%s", nome_caminho);

    if(putenv(caminho_compilador) == 0){
        printf("Compilador Linkado com sucesso!!!\n\n");
    }

    else{
        printf("Erro ao tentar linkar o compilador.");
        printf("Precione qualquer tecla para finalizar...\n");

        system("pause >nul");

        exit(0);
    }
}

void acha_include(char *nome_compilador, char *nome_arquivo, char *nome_extensao, int deslocamento){ /* Acha todos os .h dentro do codigo principal */
    FILE *arquivo;
    char caracter, aux_cabecalho[TAM_MAX], aux_include[] = "#include";
    int i=0, cont=0, conta_cabecalho=0, tam_include;

    aux_cabecalho[0] = '\0';

    tam_include = strlen(aux_include);

    arquivo = fopen(nome_arquivo, "r");

    if(arquivo != NULL){

    while(!feof(arquivo)){
        fscanf(arquivo, "%c", &caracter);

        while(caracter == aux_include[i] && aux_include[i] != '\0'){
                cont++;
                i++;
                fscanf(arquivo, "%c", &caracter);
        }

        if(cont == tam_include){
            fscanf(arquivo, "%c", &caracter);

            if(caracter == '"'){
                fscanf(arquivo, "%c", &caracter);
                while(caracter != '"'){
                    sprintf(aux_cabecalho + strlen(aux_cabecalho), "%c", caracter);

                    fscanf(arquivo, "%c", &caracter);
                }
                sprintf(aux_cabecalho + strlen(aux_cabecalho), " ");

                conta_cabecalho++;
            }
        }

        cont=0;
        i=0;
    }

    fclose(arquivo);

    monta_cabecalhos(nome_compilador, nome_arquivo, nome_extensao, aux_cabecalho, conta_cabecalho, deslocamento);

    }

    else{
        printf("\nErro ao abrir arquivo.\n\n");
    }
}

void monta_cabecalhos(char *nome_compilador, char *nome_arquivo, char *nome_extensao, char *aux_cabecalho, int conta_cabecalho, int deslocamento){ /* Monta parte da linha de compilação somente com as bibliotecas criadas pelo programador */
    char aux[TAM_MAX], cabecalho_montado[TAM_MAX];
    int i=0, j=0, k=0;

    aux[0] = '\0';
    cabecalho_montado[0] = '\0';

    while(i < conta_cabecalho){
        while(aux_cabecalho[k] != ' ' && aux_cabecalho != '\0'){
            aux[j] = aux_cabecalho[k];
            j++;
            k++;
        }
        k++;

        aux[j] = '\0';

        sprintf(cabecalho_montado + strlen(cabecalho_montado), "%s", aux);
        sprintf(cabecalho_montado + strlen(cabecalho_montado) - deslocamento, "%s", nome_extensao);
        sprintf(cabecalho_montado + strlen(cabecalho_montado), " ");

        j=0;
        i++;
    }

    monta_linha_de_compilacao(nome_compilador, nome_arquivo, nome_extensao, cabecalho_montado, deslocamento);
}

void monta_linha_de_compilacao(char *nome_compilador, char *nome_arquivo, char *nome_extensao, char *cabecalho_montado, int deslocamento){ /* Monta linha de compilação */
    char linha[TAM_MAX];

    linha[0] = '\0';

    sprintf(linha + strlen(linha), "%s", nome_compilador);
    sprintf(linha + strlen(linha), " ");
    sprintf(linha + strlen(linha), "%s", "-o");
    sprintf(linha + strlen(linha), " ");

    sprintf(linha + strlen(linha), "%s", nome_arquivo);
    sprintf(linha + strlen(linha) - deslocamento, " ");

    sprintf(linha + strlen(linha), "%s", nome_arquivo);
    sprintf(linha + strlen(linha), " ");

    if(cabecalho_montado[0] != '\0'){
        sprintf(linha + strlen(linha), "%s", cabecalho_montado);
        sprintf(linha + strlen(linha), " ");
    }

    sprintf(linha + strlen(linha), "%s", "-Wall");
    sprintf(linha + strlen(linha), " ");

    sprintf(linha + strlen(linha), "%s", "-pedantic");

    compila_prog(linha, nome_arquivo, deslocamento);
}

void compila_prog(char *linha, char *nome_arquivo, int deslocamento){ /* Compila e executa o programa */

    if(deslocamento == 2){
        printf("\nCompilando codigo fonte C...\n\n");
    }

    else{
        printf("\nCompilando codigo fonte C++...\n\n");
    }

    printf("%s\n\n", linha);

    system(linha);

    printf("\n");

    sprintf(nome_arquivo + strlen(nome_arquivo) - deslocamento, "%s", ".exe");

    system(nome_arquivo);

    printf("\n\n");
}

int main(int argc, char **argv, char **env){
    char *aux_path, *nome_compilador, *nome_extensao, nome_arquivo[TAM_MAX];
    char compilador_c[] = "gcc", compilador_cpp[] = "g++", aux_c[] = ".c", aux_cpp[] = ".cpp";
    char gcc_code_blocks_win_32[] = "C:\\Program Files\\CodeBlocks\\MinGW\\bin", gcc_code_blocks_win_64[] = "C:\\Program Files (x86)\\CodeBlocks\\MinGW\\bin";
    char gcc_dev[] = "C:\\dev-cpp\\bin", gcc_c[] = "C:\\MinGW\\bin";
    int deslocamento;

    aux_path = converte_para_maiusculo(getenv("Path"));

    if(identifica("C:", lista_pastas("Program Files (x86)"))){
        printf("Sistema operacional de 64 bits.\n\n");

        if(!identifica(aux_path, "MINGW\\BIN")){
            printf("Compilador Nao linkado.\n\n");

            if(identifica(lista_pastas("C:\\"), "MinGW")){
                printf("Compilador localizado em: C:\\MinGW\\bin\n\n");

                linka_compilador(gcc_c);
            }

            else if(identifica(lista_pastas("C:\\dev-cpp\\"), "bin")){
                printf("Compilador localizado em: C:\\dev-cpp\\bin\n\n");

                linka_compilador(gcc_dev);
            }

            else if(identifica(lista_pastas("C:\\Program Files (x86)\\CodeBlocks\\"), "MinGW")){
                printf("Compilador localizado em: C:\\Program Files (x86)\\CodeBlocks\\MinGW\\bin\n\n");

                linka_compilador(gcc_code_blocks_win_64);
            }

            else{
                printf("Compilador não encontrado neste computador.\n\n");

                system("pause >nul");

                return 0;
            }
        }
    }

    else{
        printf("Sistema operacional de 32 bits.\n\n");

        if(!identifica(aux_path, "MINGW\\BIN")){
            printf("Compilador Nao linkado.\n\n");

            if(identifica(lista_pastas("C:\\"), "MinGW")){
                printf("Compilador localizado em: C:\\MinGW\\bin\n\n");

                linka_compilador(gcc_c);
            }

            else if(identifica(lista_pastas("C:\\dev-cpp\\"), "bin")){
                printf("Compilador localizado em: C:\\dev-cpp\\bin\n\n");

                linka_compilador(gcc_dev);
            }

            else if(identifica(lista_pastas("C:\\Program Files\\CodeBlocks\\"), "MinGW")){
                printf("Compilador localizado em: C:\\Program Files\\CodeBlocks\\MinGW\\bin\n\n");

                linka_compilador(gcc_code_blocks_win_32);

            }

            else{
                printf("Compilador não encontrado neste computador.\n\n");
                printf("Precione qualquer tecla para finalizar...\n");

                system("pause >nul");

                return 0;
            }
        }
    }

    do{

        printf("Entre com o nome e a extensao do arquivo que deseja compilar. (Para encerrar tecle enter)\n");

        gets(nome_arquivo);

        if(nome_arquivo[0] != '\0'){

            if(identifica(nome_arquivo, aux_cpp)){
                nome_compilador = compilador_cpp;
            }

            else{
                nome_compilador = compilador_c;
            }

            if(identifica(nome_arquivo, aux_cpp)){
                nome_extensao = aux_cpp;
            }

            else{
                nome_extensao = aux_c;
            }

            if(identifica(nome_arquivo, aux_cpp)){
                deslocamento = 4;
            }

            else{
                deslocamento = 2;
            }

            acha_include(nome_compilador, nome_arquivo, nome_extensao, deslocamento);
        }

    }while(nome_arquivo[0] != '\0');

    printf("Programa finalizado pelo usuario.\n");

    system("pause >nul");

    return 0;
}
