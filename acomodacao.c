#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

#include <ctype.h>

int tam_acomodacao() {
    int tamanho = 0;

    tamanho = sizeof (acomodacao) - sizeof (float);

    return tamanho;
}

acomodacao le_dados_acomod(int GLOBAL_tam_pont_dados_acomodacao) {
    //variaveis
    char txt[30] = "acomodacoes.txt", bin[30] = "acomodacoes.bin";
    int tam = sizeof(acomodacao), aux = 0;
    acomodacao dados;

    //coleta de dados
    dados.codigo = retorna_id(txt, bin, tam, GLOBAL_tam_pont_dados_acomodacao);
    setbuf(stdin, NULL);
    printf("Digite a descrição da acomodação: \n");
    scanf("%[^\n]s", dados.descri);
    setbuf(stdin, NULL);
    printf("Digite as facilidades da acomodação (como ar condicionado, TV, ...): \n");
    scanf("%[^\n]s", dados.facilidades);
    setbuf(stdin, NULL);
    dados.delet = 0;
    
    //Torna todos os caracteres da string minúsculos para facilitar busca posterior
    for (aux = 0; aux < strlen(dados.facilidades); aux++) {
       dados.facilidades[aux] = tolower((unsigned char) dados.facilidades[aux]);
    }
    
    return dados;
}

acomodacao *menuAcomodacoes(int tipoArquivo, cate_aco *GLOBAL_dados_categ_acomodacao, acomodacao *GLOBAL_dados_acomodacao, int *GLOBAL_tam_pont_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_acomodacao) {
    int opcao = 0;
    acomodacao dados;
    while (opcao != 5) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de acomodação - 1\n");
        printf("\tListar todas acomodações - 2\n");
        printf("\tAlterar acomodação - 3\n");
        printf("\tExcluir acomodação - 4\n");
        printf("\tVoltar ao menu principal - 5\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_acomod(*GLOBAL_tam_pont_dados_acomodacao);
                if (tipoArquivo == 0) {
                    salva_cadastro_acomodacao_bin(dados, GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao);
                } else if (tipoArquivo == 1) {
                    salva_cadastro_acomodacao_txt(dados, GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao);
                }
                else {
                    GLOBAL_dados_acomodacao = salva_cadastro_acomodacao_mem(dados, GLOBAL_dados_acomodacao, GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao, &(*GLOBAL_tam_pont_dados_acomodacao));
                }
                break;
            case 2:
                le_todas_acomodacoes(GLOBAL_dados_acomodacao, GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 3:
                altera_acomodacoes(GLOBAL_dados_acomodacao, GLOBAL_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_categ_acomodacao, *GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 4:
                exclui_acomodacoes(GLOBAL_dados_acomodacao, *GLOBAL_tam_pont_dados_acomodacao);
                break;
            case 5:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPressione ENTER para continuar... ");
        getchar();
    }
    
    return GLOBAL_dados_acomodacao;
}

cate_aco retorna_tipo_acomodacao(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *tipo;
    int valido = 0, tam_poin = 0;
    float codigo = 0;
    char linha[(sizeof(cate_aco))], *token;
    cate_aco dados_tipo;
    
    while(valido == 0) {
        le_todos_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
        setbuf(stdin, NULL);
        printf("\nDigite o código do tipo de acomodação:\n");
        scanf("%f", &codigo);
        setbuf(stdin, NULL);
        
        //verifica txt
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
                    break;
                }
            }
        }

        fclose(tipo);
        
        //verifica binario
        if (valido == 0) {
            tipo = fopen("categoria_acomo.bin", "rb");
            if (tipo == NULL) {
                printf("Erro ao abrir arquivo!\n");
                exit(1);
            }

            while (fread(&dados_tipo, sizeof (cate_aco), 1, tipo)) {
                if (dados_tipo.delet == 0 && dados_tipo.codigo == codigo) {
                    valido = 1;
                    break;
                }
            }

            fclose(tipo);
        }
        
        //verifica na memória
        if (valido == 0) {
            if (GLOBAL_dados_categ_acomodacao != NULL) {
                for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_categ_acomodacao; tam_poin++) {
                    if (GLOBAL_dados_categ_acomodacao->codigo == codigo) {
                        valido = 2;
                        dados_tipo = *(GLOBAL_dados_categ_acomodacao);
                        break;
                    }
                    
                    GLOBAL_dados_categ_acomodacao++;
                }
                
                GLOBAL_dados_categ_acomodacao -= (tam_poin - 1);
            }
        }
        
        if (valido == 1) {
            return dados_tipo;
        }
        else if (valido == 2) {
            printf("\nO Tipo digitado está salvo em mémoria, sendo uma informação volátil, é impossível salvá-la em arquivos!! \nEscolha outro tipo ou troque o local de salvamento! \n");
        }
        else {
            printf("\nTipo digitado inválido, Tente Novamente!!\n");
        }
    }
}

cate_aco retorna_tipo_acomodacao_memoria(cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *tipo;
    int valido = 0, tam_poin = 0;
    float codigo = 0;
    char linha[(sizeof(cate_aco))], *token;
    cate_aco dados_tipo;
    
    while(valido == 0) {
        le_todos_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
        setbuf(stdin, NULL);
        printf("\nDigite o código do tipo de acomodação:\n");
        scanf("%f", &codigo);
        setbuf(stdin, NULL);
        
        //verifica txt
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
                    break;
                }
            }
        }

        fclose(tipo);
        
        //verifica binario
        if (valido == 0) {
            tipo = fopen("categoria_acomo.bin", "rb");
            if (tipo == NULL) {
                printf("Erro ao abrir arquivo!\n");
                exit(1);
            }

            while (fread(&dados_tipo, sizeof (cate_aco), 1, tipo)) {
                if (dados_tipo.delet == 0 && dados_tipo.codigo == codigo) {
                    valido = 1;
                    break;
                }
            }

            fclose(tipo);
        }
        
        //verifica na memória
        if (valido == 0) {
            if (GLOBAL_dados_categ_acomodacao != NULL) {
                for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_categ_acomodacao; tam_poin++) {
                    if (GLOBAL_dados_categ_acomodacao->codigo == codigo) {
                        valido = 2;
                        dados_tipo = *(GLOBAL_dados_categ_acomodacao);
                        break;
                    }
                    
                    GLOBAL_dados_categ_acomodacao++;
                }
                
                GLOBAL_dados_categ_acomodacao -= (tam_poin - 1);
            }
        }
        
        if (valido == 1) {
            return dados_tipo;
        }
        else {
            printf("\nTipo digitado inválido, Tente Novamente!!\n");
        }
    }
}

void salva_cadastro_acomodacao_txt(acomodacao dados, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *salva;
    int salvar;
    acomodacao dados_geral = dados;
    
    dados_geral.tipo = retorna_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
    
    salva = fopen("acomodacoes.txt", "a");
    
    salvar = fprintf(salva, "%d;%0.0f;%s;%s;%d;%0.0f;%s;%0.2f;%d;\n", dados_geral.delet, dados_geral.codigo, dados_geral.descri, dados_geral.facilidades, dados_geral.tipo.delet, dados_geral.tipo.codigo, dados_geral.tipo.descri, dados_geral.tipo.diaria, dados_geral.tipo.qnt_pessoas);
    if (salvar < 0) {
        printf("Erro no salvamento do arquivo!\n");
        exit(1);
    } else {
        printf("Salvo com sucesso!\n");
    }
    
    fclose(salva);
}

void salva_cadastro_acomodacao_bin(acomodacao dados, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao) {
    FILE *arquivo;
    acomodacao dados_geral = dados;
    
    dados_geral.tipo = retorna_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
    
    arquivo = fopen("acomodacoes.bin", "ab");
    
    fwrite(&dados_geral, sizeof (acomodacao), 1, arquivo);
    printf("Acomodação cadastrada com sucesso!");
    
    fclose(arquivo);
}

acomodacao *salva_cadastro_acomodacao_mem(acomodacao dados, acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int *GLOBAL_tam_pont_dados_acomodacao) {
    acomodacao dados_geral = dados;
    
    printf("\nSalvando dados na memoria!! ...\n");
    
    dados_geral.tipo = retorna_tipo_acomodacao_memoria(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
    
    //caso a variavel global GLOBAL_tam_pont_dados_acomodacao não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (*GLOBAL_tam_pont_dados_acomodacao == 1) {
        GLOBAL_dados_acomodacao = malloc(sizeof(acomodacao));
        *GLOBAL_dados_acomodacao = dados_geral;
    }
    //caso a variavel GLOBAL_tam_pont_dados_acomodacao tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        GLOBAL_dados_acomodacao = realloc(GLOBAL_dados_acomodacao, (*GLOBAL_tam_pont_dados_acomodacao+1)*sizeof(acomodacao));
        *(GLOBAL_dados_acomodacao + (*GLOBAL_tam_pont_dados_acomodacao - 1)) = dados_geral;
    }
    
    if (GLOBAL_dados_acomodacao == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    }
    
    //aumenta o valor da variavel global
    (*GLOBAL_tam_pont_dados_acomodacao)++;
    
    return GLOBAL_dados_acomodacao;
    
}

void le_todas_acomodacoes(acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_acomodacao) {
    FILE *arquivo;
    char linha[(sizeof (acomodacao))], *token;
    float codigo;
    int tam_poin = 0, encontrado = 0;
    acomodacao acomod;

    arquivo = fopen("acomodacoes.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomodações!");
        exit(1);
    }

    //bin
    while (fread(&acomod, sizeof (acomodacao), 1, arquivo)) {
        if (acomod.delet == 0) {
            printf("\nCódigo quarto: %.0f\n\tDescrição: %s\n\tFacilidades: %s",
                    acomod.codigo, acomod.descri, acomod.facilidades);
            printf("\nTipo da acomodação:");
            codigo = acomod.tipo.codigo;
            le_tipo_acomodacao(codigo, GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
            printf("\n");
            encontrado =1;
        }
    }
    fclose(arquivo);

    //txt
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
                encontrado =1;
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
                le_tipo_acomodacao(codigo, GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
                printf("\n");
            }
        }
    }

    fclose(arquivo);
    
    //memoria
    for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_acomodacao; tam_poin++) {
        if (GLOBAL_dados_acomodacao->delet == 0) {
            encontrado =1;
            printf("\nCódigo quarto: %.0f\n\tDescrição: %s\n\tFacilidades: %s",
                    GLOBAL_dados_acomodacao->codigo, GLOBAL_dados_acomodacao->descri, GLOBAL_dados_acomodacao->facilidades);
            printf("\nTipo da acomodação:");
            codigo = GLOBAL_dados_acomodacao->tipo.codigo;
            le_tipo_acomodacao(codigo, GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
            printf("\n");
        }
        
        GLOBAL_dados_acomodacao += 1;
    }
    
    //retorna o ponteiro para a posição inicial do bloco que foi alocado
    GLOBAL_dados_acomodacao -= (tam_poin - 1);

    if(encontrado == 0){
        printf("\nNenhuma acomodação cadastrada!");
    }
}

acomodacao le_uma_acomodacao(float codigo, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao){
    FILE *le, *altera;
    acomodacao acomod, retorna;

    retorna.delet == 1;

    char linha[(sizeof (acomodacao))], *token;
    int  encontrado = 0, tam_poin = 0;

    le = fopen("acomodacoes.bin", "rb+wb");
    if (le == NULL) {
        printf("Erro de abertura de arquivo acomodacoes.bin!\n");
        exit(1);
    }

    while (fread(&acomod, sizeof (acomodacao), 1, le)) {
        if (acomod.delet == 0 && acomod.codigo == codigo) {
            encontrado++;
            retorna = acomod;
            break;
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
                    encontrado++;
                    retorna = acomod;
                    break;
                }
            }
        }

        fclose(le);
        fclose(altera);

        remove("acomodacoes.txt");
        rename("temp.txt", "acomodacoes.txt");
    }
    
    if (encontrado == 0) {
        //memoria
        for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_acomodacao; tam_poin++) {
            if (GLOBAL_dados_acomodacao->delet == 0) {
                if (GLOBAL_dados_acomodacao->codigo == codigo) {
                    encontrado++;
                    retorna.codigo = GLOBAL_dados_acomodacao->codigo;
                    retorna.delet = GLOBAL_dados_acomodacao->delet;
                    strcpy(retorna.descri, GLOBAL_dados_acomodacao->descri);
                    strcpy(retorna.facilidades, GLOBAL_dados_acomodacao->facilidades);
                    retorna.tipo = GLOBAL_dados_acomodacao->tipo;
                    break;
                }
            }

            GLOBAL_dados_acomodacao += 1;
        }

        //retorna o ponteiro para a posição inicial do bloco que foi alocado
        GLOBAL_dados_acomodacao -= (tam_poin - 1);
    }

    if (encontrado == 0) {
        printf("Acomodacao da reserva não encontrada na base de dados!\n");
    }
    return retorna;
}

void altera_acomodacoes(acomodacao *GLOBAL_dados_acomodacao, cate_aco *GLOBAL_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_categ_acomodacao, int GLOBAL_tam_pont_dados_acomodacao) {
    FILE *le, *altera, *tipo;
    cate_aco tipo_aco;
    acomodacao acomod, novo;
    char linha[(sizeof (acomodacao))], linha_tipo[(sizeof (cate_aco))], *token, cod_str[(sizeof (float))];
    int tam = 0, encontrado = 0, i = 0, op = 0, alterado = 0, salvar, tam_poin = 0;
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
            acomod = le_dados_acomod(GLOBAL_tam_pont_dados_acomodacao);
            acomod.codigo = codigo;
            
            printf("Deseja editar o tipo de acomodação?\n    1- Sim    2- Não\n");
            scanf("%d", &op);

            switch (op) {
                case 1:
                    acomod.tipo = retorna_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
                    break;
                case 2:
                    acomod.tipo = tipo_aco;
                    break;
                default:
                    printf("Opção inválida!\n");
            }
            
            fseek(le, -sizeof (acomodacao), SEEK_CUR);
            fwrite(&acomod, sizeof (acomodacao), 1, le);
            break;
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
                    acomod = le_dados_acomod(GLOBAL_tam_pont_dados_acomodacao);
                    acomod.codigo = codigo;
                    acomod.tipo = tipo_aco;
                    encontrado = 1;

                    printf("Deseja editar o tipo de acomodação?\n    1- Sim    2- Não\n");
                    scanf("%d", &op);

                    switch (op) {
                        case 1:
                            acomod.tipo = retorna_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
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
        //memoria
        for (tam_poin = 1; tam_poin < GLOBAL_tam_pont_dados_acomodacao; tam_poin++) {
            if (GLOBAL_dados_acomodacao->delet == 0) {
                if (GLOBAL_dados_acomodacao->codigo == codigo) {
                    acomod = le_dados_acomod(GLOBAL_tam_pont_dados_acomodacao);
                    acomod.codigo = codigo;
                    
                    printf("Deseja editar o tipo de acomodação?\n    1- Sim    2- Não\n");
                    scanf("%d", &op);

                    switch (op) {
                        case 1:
                            acomod.tipo = retorna_tipo_acomodacao(GLOBAL_dados_categ_acomodacao, GLOBAL_tam_pont_dados_categ_acomodacao);
                            break;
                        case 2:
                            acomod.tipo = tipo_aco;
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                    
                    *(GLOBAL_dados_acomodacao) = acomod;
                    encontrado = 1;
                    
                    break;
                }
            }

            GLOBAL_dados_acomodacao += 1;
        }

        //retorna o ponteiro para a posição inicial do bloco que foi alocado
        GLOBAL_dados_acomodacao -= (tam_poin - 1);
    }

    if (encontrado == 0) {
        printf("Código digitado não encontrado!\n");
    } else {
        printf("Alterado com sucesso!\n");
    }
}

void exclui_acomodacoes(acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao) {
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
        if (GLOBAL_dados_acomodacao != NULL) {
            for (i = 1; i < GLOBAL_tam_pont_dados_acomodacao; i++) {
                if (GLOBAL_dados_acomodacao->delet == 0) {
                    if (GLOBAL_dados_acomodacao->codigo == codigo) {
                        GLOBAL_dados_acomodacao->delet = 1;
                        encontrado = 1;
                        break;
                    }
                }
                
                GLOBAL_dados_acomodacao++;
            }
            
            GLOBAL_dados_acomodacao -= (i - 1);
        }
    }

    if (encontrado == 0) {
        printf("Código não encontrado!\n");
    } else {
        printf("Dados Excluídos com sucesso!\n");
    }
}