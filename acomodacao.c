#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

int tam_acomodacao() {
    int tamanho = 0;

    tamanho = sizeof (acomodacao) - sizeof (float);

    return tamanho;
}

acomodacao le_dados_acomod() {
    //variaveis
    char txt[30] = "acomodacoes.txt", bin[30] = "acomodacoes.bin";
    int tam = sizeof(acomodacao);
    acomodacao dados;

    //coleta de dados
    dados.codigo = retorna_id(txt, bin, tam);
    setbuf(stdin, NULL);
    printf("Digite a descrição da acomodação: \n");
    scanf("%[^\n]s", dados.descri);
    setbuf(stdin, NULL);
    printf("Digite as facilidades da acomodação (como ar condicionado, TV, ...): \n");
    scanf("%[^\n]s", dados.facilidades);
    setbuf(stdin, NULL);
    dados.delet = 0;
    return dados;
}

void menuAcomodacoes(int tipoArquivo) {
    int opcao = 0;
    cate_aco categ;
    acomodacao dados;
    while (opcao != 9) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de acomodação - 1\n");
        printf("\tListar todas acomodações - 2\n");
        printf("\tAlterar acomodação - 3\n");
        printf("\tExcluir acomodação - 4\n");
        printf("\tCadastro de um tipo de acomodação - 5\n");
        printf("\tListar tipos de acomodação - 6\n");
        printf("\tAlterar um tipo de acomodação - 7\n");
        printf("\tExcluir um tipo de acomodação - 8\n");
        printf("\tVoltar ao menu principal - 9\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_acomod();
                if (tipoArquivo == 0) {
                    salva_cadastro_acomodacao_bin(dados);
                } else {
                    salva_cadastro_acomodacao_txt(dados);
                }
                break;
            case 2:
                le_todas_acomodacoes();
                break;
            case 3:
                altera_acomodacoes();
                break;
            case 4:
                exclui_acomodacoes();
                break;
            case 5:
                categ = le_dados_categ_acomod();
                if (tipoArquivo == 0) {
                    salva_cadastro_tipo_acomodacao_bin(categ);
                } else {
                    salva_cadastro_tipo_acomodacao_txt(categ);
                }
                break;
            case 6:
                le_todos_tipo_acomodacao();
                break;
            case 7:
                altera_tipo_acomodacao();
                break;
            case 8:
                remover_tipo_acomodacao();
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPressione qualquer tecla para continuar... ");
        getchar();
    }
    menuPrincipal();
}

void salva_cadastro_acomodacao_txt(acomodacao dados) {
    FILE *salva, *tipo;
    char linha[(sizeof (cate_aco))], *token;
    float codigo;
    int valido = 0, op = 0, salvar;
    acomodacao dados_geral = dados;
    cate_aco dados_tipo;

    le_todos_tipo_acomodacao();
    setbuf(stdin, NULL);
    printf("Digite o código do tipo de acomodação:\n");
    scanf("%f", &codigo);
    setbuf(stdin, NULL);
    
    while (valido == 0) {
        salva = fopen("acomodacoes.txt", "a");
        if (salva == NULL) {
            printf("Erro ao abrir arquivo!\n");
            exit(1);
        }

        tipo = fopen("categoria_acomo.txt", "r");
        if (tipo == NULL) {
            printf("Erro ao abrir arquivo!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), tipo)) {
            token = strtok(linha, ";");
            dados_tipo.delet = atoi(token);

            if (dados_tipo.delet == 0) {
                token = strtok(NULL, ";");
                dados_tipo.codigo = atoff(token);
                if (dados_tipo.codigo == codigo) {
                    token = strtok(NULL, ";");
                    strcpy(dados_tipo.descri, token);
                    token = strtok(NULL, ";");
                    dados_tipo.diaria = atoff(token);
                    token = strtok(NULL, ";");
                    dados_tipo.qnt_pessoas = atoi(token);
                    valido = 1;

                    dados_geral.tipo = dados_tipo;
                }
            }
        }

        fclose(tipo);

        if (valido == 0) {
            tipo = fopen("categoria_acomo.bin", "rb");
            if (tipo == NULL) {
                printf("Erro ao abrir arquivo!\n");
                exit(1);
            }

            while (fread(&dados_tipo, sizeof (cate_aco), 1, tipo)) {
                if (dados_tipo.delet == 0 && dados_tipo.codigo == codigo) {
                    dados_geral.tipo = dados_tipo;
                    valido = 1;
                }
            }

            fclose(tipo);
        }

        if (valido == 1) {
            salvar = fprintf(salva, "%d;%0.0f;%s;%s;%d;%0.0f;%s;%0.2f;%d;\n", dados_geral.delet, dados_geral.codigo, dados_geral.descri, dados_geral.facilidades, dados_geral.tipo.delet, dados_geral.tipo.codigo, dados_geral.tipo.descri, dados_geral.tipo.diaria, dados_geral.tipo.qnt_pessoas);
            if (salvar < 0) {
                printf("Erro no salvamento do arquivo!\n");
                exit(1);
            } else {
                printf("Salvo com sucesso!\n");
            }
        } else {
            printf("Código da acomodação é inválido!\n");
        }

        fclose(salva);
    }
}

void salva_cadastro_acomodacao_bin(acomodacao dados) {
    FILE *arquivo, *tipo;
    float codigo;
    int valido = 0;
    char linha[(sizeof (cate_aco))], *token;
    acomodacao dados_geral = dados;
    cate_aco dados_tipo;
    
    le_todos_tipo_acomodacao();
    setbuf(stdin, NULL);
    printf("Digite o código do tipo de acomodação:\n");
    scanf("%f", &codigo);
    setbuf(stdin, NULL);
    
    arquivo = fopen("acomodacoes.bin", "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomodações!");
    } else {
        while(valido == 0) {
            tipo = fopen("categoria_acomo.txt", "r");
            if (tipo == NULL) {
                printf("Erro ao abrir arquivo!\n");
                exit(1);
            } 
            
            while (fgets(linha, sizeof (cate_aco), tipo)) {
                token = strtok(linha, ";");
                dados_tipo.delet = atoi(token);

                if (dados_tipo.delet == 0) {
                    token = strtok(NULL, ";");
                    dados_tipo.codigo = atoff(token);
                    if (dados_tipo.codigo == codigo) {
                        token = strtok(NULL, ";");
                        strcpy(dados_tipo.descri, token);
                        token = strtok(NULL, ";");
                        dados_tipo.diaria = atoff(token);
                        token = strtok(NULL, ";");
                        dados_tipo.qnt_pessoas = atoi(token);
                        valido = 1;

                        dados_geral.tipo = dados_tipo;
                    }
                }
            }

            fclose(tipo);

            if (valido == 0) {
                tipo = fopen("categoria_acomo.bin", "rb");
                if (tipo == NULL) {
                    printf("Erro ao abrir arquivo!\n");
                    exit(1);
                }

                while (fread(&dados_tipo, sizeof (cate_aco), 1, tipo)) {
                    if (dados_tipo.delet == 0 && dados_tipo.codigo == codigo) {
                        dados_geral.tipo = dados_tipo;
                        valido = 1;
                    }
                }

                fclose(tipo);
            }

            if (valido == 1) {
                fwrite(&dados_geral, sizeof (acomodacao), 1, arquivo);
                printf("Acomodação cadastrada com sucesso!");
            } else {
                printf("Código da acomodação é inválido!\n");
            }
        }
    }
    fclose(arquivo);
}

void le_todas_acomodacoes() {
    FILE *arquivo;
    char linha[(sizeof (acomodacao))], *token;
    float codigo;
    acomodacao acomod;

    arquivo = fopen("acomodacoes.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomodações!");
        exit(1);
    }

    while (fread(&acomod, sizeof (acomodacao), 1, arquivo)) {
        if (acomod.delet == 0) {
            printf("\nCódigo quarto: %.0f\n\tDescrição: %s\n\tFacilidades: %s",
                    acomod.codigo, acomod.descri, acomod.facilidades);
            printf("\nTipo da acomodação:");
            codigo = acomod.tipo.codigo;
            le_tipo_acomodacao(codigo);
            printf("\n");
        }
    }
    fclose(arquivo);

    arquivo = fopen("acomodacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo txt!\n");
        exit(1);
    } else {
        while (fgets(linha, sizeof (acomodacao), arquivo)) {
            //separa o primeiro elemento que diz se foi excluido ou não
            token = strtok(linha, ";");
            //caso não tenha sido excluido
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                printf("\nCódigo do quarto: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Descrição: %s\n\t", token);
                token = strtok(NULL, ";");
                printf("Facilidades: %s\n\t", token);
                printf("Dados do tipo de acomodação:");
                token = strtok(NULL, ";");
                token = strtok(NULL, ";");
                codigo = atoff(token);
                le_tipo_acomodacao(codigo);
                printf("\n");
            }
        }
    }

    fclose(arquivo);
}

void altera_acomodacoes() {
    FILE *le, *altera, *tipo;
    cate_aco tipo_aco;
    acomodacao acomod, novo;
    char linha[(sizeof (acomodacao))], linha_tipo[(sizeof (cate_aco))], *token, cod_str[(sizeof (float))];
    int tam = 0, encontrado = 0, i = 0, op = 0, alterado = 0, salvar;
    float codigo, tipo_cod;

    printf("Digite o código do quarto da acomodação que deseja alterar: \n");
    scanf("%f", &codigo);

    le = fopen("acomodacoes.bin", "rb+wb");
    if (le == NULL) {
        printf("Erro de abertura de arquivo acomodacoes.bin!\n");
        exit(1);
    }

    while (fread(&acomod, sizeof (acomodacao), 1, le)) {
        if (acomod.delet == 0 && acomod.codigo == codigo) {
            encontrado = 1;
            acomod = le_dados_acomod();
            acomod.codigo = codigo;
            fseek(le, -sizeof (acomodacao), SEEK_CUR);
            fwrite(&acomod, sizeof (acomodacao), 1, le);
        }
    }

    fclose(le);

    if (encontrado == 0) {
        le = fopen("acomodacoes.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo acomodacoes.txt!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (le == NULL) {
            printf("Erro de criação de arquivo temp.txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (acomodacao), le)) {
            token = strtok(linha, ";");
            acomod.delet = atoi(token);
            token = strtok(NULL, ";");
            acomod.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(acomod.descri, token);
            token = strtok(NULL, ";");
            strcpy(acomod.facilidades, token);
            token = strtok(NULL, ";");
            acomod.tipo.delet = atoi(token);
            token = strtok(NULL, ";");
            acomod.tipo.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(acomod.tipo.descri, token);
            token = strtok(NULL, ";");
            acomod.tipo.diaria = atoff(token);
            token = strtok(NULL, ";");
            acomod.tipo.qnt_pessoas = atoi(token);

            if (acomod.delet == 0) {
                if (acomod.codigo == codigo) {
                    tipo_aco = acomod.tipo;
                    acomod = le_dados_acomod();
                    acomod.codigo = codigo;
                    acomod.tipo = tipo_aco;
                    encontrado = 1;

                    printf("Deseja editar o tipo de acomodação?\n    1- Sim    2- Não\n");
                    scanf("%d", &op);

                    switch (op) {
                        case 1:
                            le_todos_tipo_acomodacao();

                            printf("Digite o código do tipo de acomodação que deseja alterar: \n");
                            scanf("%f", &tipo_cod);

                            sprintf(cod_str, "%0.0f", tipo_cod);

                            tipo = fopen("categoria_acomo.txt", "r");
                            if (tipo == NULL) {
                                printf("Erro ao abrir arquivo!\n");
                                exit(1);
                            }

                            while (fgets(linha_tipo, sizeof (cate_aco), tipo)) {
                                token = strtok(linha_tipo, ";");

                                if (strcmp(token, "0") == 0) {
                                    token = strtok(NULL, ";");

                                    if (strcmp(token, cod_str) == 0) {
                                        acomod.tipo.delet = 0;
                                        acomod.tipo.codigo = atoff(token);
                                        token = strtok(NULL, ";");
                                        strcpy(acomod.tipo.descri, token);
                                        token = strtok(NULL, ";");
                                        acomod.tipo.diaria = atoff(token);
                                        token = strtok(NULL, ";");
                                        acomod.tipo.diaria = atoi(token);
                                        alterado = 1;
                                    }
                                }
                            }

                            fclose(tipo);

                            if (alterado == 0) {
                                tipo = fopen("categoria_acomo.bin", "rb");
                                if (tipo == NULL) {
                                    printf("Erro ao abrir arquivo!\n");
                                    exit(1);
                                }

                                while (fread(&tipo_aco, sizeof (cate_aco), 1, tipo)) {
                                    if (tipo_aco.delet == 0 && tipo_aco.codigo == tipo_cod) {
                                        acomod.tipo.delet = tipo_aco.delet;
                                        acomod.tipo.codigo = tipo_aco.codigo;
                                        strcpy(acomod.tipo.descri, tipo_aco.descri);
                                        acomod.tipo.diaria = tipo_aco.diaria;
                                        acomod.tipo.qnt_pessoas = tipo_aco.qnt_pessoas;
                                        alterado = 1;
                                    }
                                }

                                fclose(tipo);
                            }

                            break;
                        case 2:
                            acomod.tipo = tipo_aco;
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                }
            }

            salvar = fprintf(altera, "%d;%0.0f;%s;%s;%d;%0.0f;%s;%0.2f;%d;\n", acomod.delet, acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.delet, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.diaria, acomod.tipo.qnt_pessoas);
            if (salvar < 0) {
                printf("Erro no salvamento do arquivo!\n");
                exit(1);
            }
        }

        fclose(le);
        fclose(altera);

        remove("acomodacoes.txt");
        rename("temp.txt", "acomodacoes.txt");
    }

    if (encontrado == 0) {
        printf("Código digitado não encontrado!\n");
    } else {
        printf("Alterado com sucesso!\n");
    }
}

void exclui_acomodacoes() {
    FILE *le, *exclui;
    acomodacao acomod;
    char linha[(sizeof (acomodacao))], *token;
    int tam = 0, encontrado = 0, i = 0, salvar;
    float codigo;

    printf("Digite o código da acomodação a ser deletada: \n");
    scanf("%f", &codigo);

    le = fopen("acomodacoes.bin", "rb+wb");
    if (le == NULL) {
        printf("Erro de abertura de arquivo acomodacoes.bin!\n");
        exit(1);
    }

    while (fread(&acomod, sizeof (acomodacao), 1, le)) {
        if (acomod.delet == 0 && acomod.codigo == codigo) {
            acomod.delet = 1;
            fseek(le, -sizeof (acomodacao), SEEK_CUR);
            fwrite(&acomod, sizeof (acomodacao), 1, le);
            encontrado = 1;
        }
    }

    fclose(le);

    if (encontrado == 0) {
        le = fopen("acomodacoes.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo acomodacoes.txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (acomodacao), le)) {
            tam++;
        }

        fclose(le);

        acomodacao dados[tam];

        le = fopen("acomodacoes.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo acomodacoes.bin!\n");
            exit(1);
        }

        exclui = fopen("temp.txt", "a");
        if (exclui == NULL) {
            printf("Erro de abertura de arquivo acomodacoes.bin!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (acomodacao), le)) {
            token = strtok(linha, ";");
            acomod.delet = atoi(token);
            token = strtok(NULL, ";");
            acomod.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(acomod.descri, token);
            token = strtok(NULL, ";");
            strcpy(acomod.facilidades, token);
            token = strtok(NULL, ";");
            acomod.tipo.delet = atoi(token);
            token = strtok(NULL, ";");
            acomod.tipo.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(acomod.tipo.descri, token);
            token = strtok(NULL, ";");
            acomod.tipo.diaria = atoff(token);
            token = strtok(NULL, ";");
            acomod.tipo.qnt_pessoas = atoi(token);

            if (acomod.delet == 0) {
                if (acomod.codigo == codigo) {
                    acomod.delet = 1;
                    encontrado = 1;
                }
            }

            salvar = fprintf(exclui, "%d;%0.0f;%s;%s;%d;%0.0f;%s;%0.2f;%d;\n", acomod.delet, acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.delet, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.diaria, acomod.tipo.qnt_pessoas);
            if (salvar < 0) {
                printf("Erro no salvamento do arquivo!\n");
                exit(1);
            }
        }

        fclose(exclui);
        fclose(le);

        remove("acomodacoes.txt");
        rename("temp.txt", "acomodacoes.txt");
    }

    if (encontrado == 0) {
        printf("Código não encontrado!\n");
    } else {
        printf("Dados Excluídos com sucesso!\n");
    }
}
