#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int tam_operador() {
    int tamanho = 0;
    
    tamanho = sizeof(operador) - sizeof(float);
    
    return tamanho;
}

operador le_dados_operador() {
    //variaveis
    operador dados;
    char txt[30] = "operadores.txt", bin[30] = "operadores.bin";
    int tam = sizeof(operador);

    //coleta dados
    dados.codigo = retorna_id(txt, bin, tam);
    setbuf(stdin, NULL);
    printf("Digite o nome do operador: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome);
    setbuf(stdin, NULL);
    printf("Digite o usuário do operador: \n");
    scanf("%[^\n]s", dados.user);
    setbuf(stdin, NULL);
    printf("Digite a senha do operador: \n");
    scanf("%[^\n]s", dados.senha);
    setbuf(stdin, NULL);
    printf("Digite qual a permissão de acesso do fornecedor: \n");
    scanf("%d", &dados.acesso);
    dados.delet = 0;
    return dados;
}

void menuOperadores(int tipoAquivo) {
    int opcao = 0;
    operador dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de operadores - 1\n");
        printf("\tListar todos os operadores - 2\n");
        printf("\tListar um dos operadores - 3\n");
        printf("\tAlterar operadores - 4\n");
        printf("\tExcluir operadores - 5\n");
        printf("\tVoltar ao menu principal - 6\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_operador();
                if (tipoAquivo == 0) {
                    salva_cadastro_operadores_bin(dados);
                } else {
                    salva_cadastro_operadores_txt(dados);
                }
                break;
            case 2:
                le_todos_operadores();
                break;
            case 3:
                le_operador();
                break;
            case 4:
                alterar_operador();
                break;
            case 5:
                exclui_operador();
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        getchar();
    }
}

void salva_cadastro_operadores_bin(operador dados) {
    FILE *arquivo;

    arquivo = fopen("operadores.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadores!");
        exit(1);
    }
    fwrite(&dados, sizeof (operador), 1, arquivo);
    printf("\nOperador salvo com sucesso!");
    fclose(arquivo);
}

void salva_cadastro_operadores_txt(operador dados) {
    FILE *salva;
    int salvar;

    salva = fopen("operadores.txt", "a");
    if (salva == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%d;%s;%s;%s;\n", dados.delet, dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
    if (salvar < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        printf("Salvo com sucesso!\n");
    }

    fclose(salva);
}

void le_operador() {
    FILE *arquivo;
    float codigo;
    operador dados;
    int encontrado = 0;
    char linha[(sizeof (operador))], *token;

    arquivo = fopen("operadores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadores!");
        exit(1);
    }

    printf("Digite o codigo do operador que deseja ler: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (operador), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            printf("\nCódigo: %0.0f\n\tAcesso: %d\n\tNome: %s\n\tUser: %s\n\tSenha: %s",
                    dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("operadores.txt", "r");
        if (arquivo == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        while (fgets(linha, sizeof (operador), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Nivel de acesso: %s \n", token);
                token = strtok(NULL, ";");
                printf("Nome do operador: %s \n", token);
                token = strtok(NULL, ";");
                printf("Username: %s \n", token);
                token = strtok(NULL, ";");
                printf("Senha: %s \n", token);
                token = strtok(NULL, ";");
                encontrado = 1;
            }
        }

        fclose(arquivo);
    }
}

void le_todos_operadores() {
    FILE *arquivo;
    operador dados;
    char linha[(sizeof (operador))], *token;

    arquivo = fopen("operadores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadoreses!");
        exit(1);
    }

    while (fread(&dados, sizeof (operador), 1, arquivo)) {
        if (dados.delet == 0) {
            printf("\nCódigo: %0.0f\n\tAcesso: %d\n\tNome: %s\n\tUser: %s\n\tSenha: %s",
                    dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
        }
    }

    fclose(arquivo);

    arquivo = fopen("operadores.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadores.txt!");
        exit(1);
    }

    while (fgets(linha, sizeof (operador), arquivo)) {
        token = strtok(linha, ";");
        dados.delet = atoi(token);
        token = strtok(NULL, ";");
        if (dados.delet == 0) {
            printf("\nCódigo: %s \n", token);
            token = strtok(NULL, ";");
            printf("Nivel de acesso: %s \n", token);
            token = strtok(NULL, ";");
            printf("Nome do operador: %s \n", token);
            token = strtok(NULL, ";");
            printf("Username: %s \n", token);
            token = strtok(NULL, ";");
            printf("Senha: %s \n", token);
            token = strtok(NULL, ";");
        }
    }

    fclose(arquivo);
}

void alterar_operador() {
    FILE *arquivo, *altera;
    float codigo;
    operador dados;
    int encontrado = 0, i = 0, tam = 0, salvar;
    char linha[(sizeof (operador))], *token;

    arquivo = fopen("operadores.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadores!");
        exit(1);
    }

    printf("Digite o codigo do operador que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (operador), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados = le_dados_operador();
            fseek(arquivo, -sizeof (operador), 1);
            fwrite(&dados, sizeof (operador), 1, arquivo);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("operadores.txt", "r");
        if (arquivo == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        while (fgets(linha, sizeof (operador), arquivo)) {
            tam++;
        }

        fclose(arquivo);

        operador txt[tam];

        arquivo = fopen("operadores.txt", "r");
        if (arquivo == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        while (fgets(linha, sizeof (operador), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados = le_dados_operador();
                dados.codigo = codigo;
                encontrado = 1;
            } else {
                token = strtok(NULL, ";");
                dados.acesso = atoi(token);
                token = strtok(NULL, ";");
                strcpy(dados.nome, token);
                token = strtok(NULL, ";");
                strcpy(dados.user, token);
                token = strtok(NULL, ";");
                strcpy(dados.senha, token);
            }

            salvar = fprintf(altera, "%d;%0.0f;%d;%s;%s;%s;\n", dados.delet, dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
            if (salvar < 0) {
                printf("Erro no salvamento do tipo de acomodação !\n");
            }

            i++;
        }

        fclose(altera);
        fclose(arquivo);

        remove("operadores.txt");
        rename("temp.txt", "operadores.txt");
    }

    if (encontrado == 0) {
        printf("Operador não encontrado!\n");
    } else {
        printf("Dados Alterados com sucesso!\n");
    }
}

void exclui_operador() {
    FILE *arquivo, *altera;
    float codigo;
    operador dados;
    int encontrado = 0, i = 0, tam = 0, salvar;
    char linha[(sizeof (operador))], *token;

    arquivo = fopen("operadores.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadores!");
        exit(1);
    }

    printf("Digite o codigo do operadores que deseja excluir: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (operador), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.delet = 1;
            fseek(arquivo, -sizeof (operador), 1);
            fwrite(&dados, sizeof (operador), 1, arquivo);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("operadores.txt", "r");
        if (arquivo == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        while (fgets(linha, sizeof (operador), arquivo)) {
            tam++;
        }

        fclose(arquivo);

        operador txt[tam];

        arquivo = fopen("operadores.txt", "r");
        if (arquivo == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("\nErro ao abrir arquivo de operadores.txt!");
            exit(1);
        }

        while (fgets(linha, sizeof (operador), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            dados.acesso = atoi(token);
            token = strtok(NULL, ";");
            strcpy(dados.nome, token);
            token = strtok(NULL, ";");
            strcpy(dados.user, token);
            token = strtok(NULL, ";");
            strcpy(dados.senha, token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.delet = 1;
                encontrado = 1;
            }

            salvar = fprintf(altera, "%d;%0.0f;%d;%s;%s;%s;\n", dados.delet, dados.codigo, dados.acesso, dados.nome, dados.user, dados.senha);
            if (salvar < 0) {
                printf("Erro no salvamento do tipo de acomodação !\n");
            }

            i++;
        }

        fclose(altera);
        fclose(arquivo);

        remove("operadores.txt");
        rename("temp.txt", "operadores.txt");
    }

    if (encontrado == 0) {
        printf("Operador não encontrado!\n");
    } else {
        printf("Dados excluídos com sucesso!\n");
    }
}
