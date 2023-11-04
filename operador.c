#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

// -------------- Var Globais --------------
int GLOBAL_tam_pont_dados_operadores = 1; //ja usado!

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
    dados.codigo = retorna_id(txt, bin, tam, GLOBAL_tam_pont_dados_operadores);
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

void menuOperadores(int tipoAquivo, operador *GLOBAL_dados_operadores) {
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
                } else if (tipoAquivo == 1) {
                    salva_cadastro_operadores_txt(dados);
                }
                else {
                    GLOBAL_dados_operadores = salva_cadastro_operadores_mem(dados, GLOBAL_dados_operadores);
                }
                break;
            case 2:
                le_todos_operadores(GLOBAL_dados_operadores);
                break;
            case 3:
                le_operador(GLOBAL_dados_operadores);
                break;
            case 4:
                alterar_operador(GLOBAL_dados_operadores);
                break;
            case 5:
                exclui_operador(GLOBAL_dados_operadores);
                break;
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
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

operador *salva_cadastro_operadores_mem(operador dados, operador *GLOBAL_dados_operadores) {
    //caso a variavel global GLOBAL_tam_pont_dados_acomodacao não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (GLOBAL_tam_pont_dados_operadores == 1) {
        GLOBAL_dados_operadores = malloc(sizeof(acomodacao));
        *GLOBAL_dados_operadores = dados;
    }
    //caso a variavel GLOBAL_tam_pont_dados_operadores tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        GLOBAL_dados_operadores = realloc(GLOBAL_dados_operadores, (GLOBAL_tam_pont_dados_operadores)*sizeof(acomodacao));
        *(GLOBAL_dados_operadores + (GLOBAL_tam_pont_dados_operadores - 1)) = dados;
    }
    
    if (GLOBAL_dados_operadores == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    }
    
    //aumenta o valor da variavel global
    GLOBAL_tam_pont_dados_operadores++;
    
    return GLOBAL_dados_operadores;
}

void le_operador(operador *GLOBAL_dados_operadores) {
    FILE *arquivo;
    float codigo;
    operador dados;
    int encontrado = 0, tam_point = 0;
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
    
    //memoria
    if (encontrado == 0) {
        if (GLOBAL_dados_operadores != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_operadores; tam_point++) {
                if (GLOBAL_dados_operadores->delet == 0) {
                    if (GLOBAL_dados_operadores->codigo == codigo) {
                        printf("\nCódigo: %0.0f\n\tAcesso: %d\n\tNome: %s\n\tUser: %s\n\tSenha: %s \n",
                                GLOBAL_dados_operadores->codigo, GLOBAL_dados_operadores->acesso, GLOBAL_dados_operadores->nome, GLOBAL_dados_operadores->user, GLOBAL_dados_operadores->senha);
                        encontrado = 1;
                        break;
                    }
                }

                //avança 1 posição
                GLOBAL_dados_operadores++;
            }

            //retorna o ponteiro para a primeira posição
            GLOBAL_dados_operadores -= (tam_point -1);
        }
    }
    if(encontrado == 0){
        printf("Nenhum operador com esse código encontrado!");
    }
}

void le_todos_operadores(operador *GLOBAL_dados_operadores) {
    FILE *arquivo;
    operador dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof (operador))], *token;

    arquivo = fopen("operadores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de operadoreses!");
        exit(1);
    }

    while (fread(&dados, sizeof (operador), 1, arquivo)) {
        if (dados.delet == 0) {
            encontrado = 1;
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
            encontrado = 1;
            printf("\nCódigo: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Nivel de acesso: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Nome do operador: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Username: %s \n\t", token);
            token = strtok(NULL, ";");
            printf("Senha: %s \n", token);
            token = strtok(NULL, ";");
        }
    }

    fclose(arquivo);
    
    //memoria
    if (GLOBAL_dados_operadores != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_operadores; tam_point++) {
            if (GLOBAL_dados_operadores->delet == 0) {
                encontrado = 1;
                printf("\nCódigo: %0.0f\n\tAcesso: %d\n\tNome: %s\n\tUser: %s\n\tSenha: %s \n",
                    GLOBAL_dados_operadores->codigo, GLOBAL_dados_operadores->acesso, GLOBAL_dados_operadores->nome, GLOBAL_dados_operadores->user, GLOBAL_dados_operadores->senha);
            }
            
            //avança 1 posição
            GLOBAL_dados_operadores++;
        }
        
        //retorna o ponteiro para a primeira posição
        GLOBAL_dados_operadores -= (tam_point -1);
    }
    if(encontrado == 0){
        printf("\nNenhum operador cadastrado!");
    }
}

void alterar_operador(operador *GLOBAL_dados_operadores) {
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
    
    //memoria
    if (encontrado == 0) {
        if (GLOBAL_dados_operadores != NULL) {
            for (i = 1; i < GLOBAL_tam_pont_dados_operadores; i++) {
                if (GLOBAL_dados_operadores->delet == 0) {
                    if (GLOBAL_dados_operadores->codigo == codigo) {
                        dados = le_dados_operador();
                        dados.codigo = codigo;
                        *(GLOBAL_dados_operadores) = dados;
                        encontrado = 1;
                        break;
                    }
                }

                //avança 1 posição
                GLOBAL_dados_operadores++;
            }

            //retorna o ponteiro para a primeira posição
            GLOBAL_dados_operadores -= (i - 1);
        }
    }

    if (encontrado == 0) {
        printf("Operador não encontrado!\n");
    } else {
        printf("Dados Alterados com sucesso!\n");
    }
}

void exclui_operador(operador *GLOBAL_dados_operadores) {
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
    
    //memoria
    if (encontrado == 0) {
        if (GLOBAL_dados_operadores != NULL) {
            for (i = 1; i < GLOBAL_tam_pont_dados_operadores; i++) {
                if (GLOBAL_dados_operadores->delet == 0) {
                    if (GLOBAL_dados_operadores->codigo == codigo) {
                        GLOBAL_dados_operadores->delet = 1;
                        encontrado = 1;
                        break;
                    }
                }

                //avança 1 posição
                GLOBAL_dados_operadores++;
            }

            //retorna o ponteiro para a primeira posição
            GLOBAL_dados_operadores -= (i - 1);
        }
    }

    if (encontrado == 0) {
        printf("Operador não encontrado!\n");
    } else {
        printf("Dados excluídos com sucesso!\n");
    }
}
