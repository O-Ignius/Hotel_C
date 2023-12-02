#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

int tam_reserva() {
    int tamanho = 0;
    
    tamanho = sizeof(reserva) - sizeof(float);
    
    return tamanho;
}

data le_dados_data() {
    data dados;
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("Digite o mes(1-12): ");
    scanf("%d", &dados.mes);

    while (dados.mes <= 0 || dados.mes >= 13) {
        printf("\nMes inválido, digite outro no intervalo de 1 a 12: ");
        scanf("%d", &dados.mes);
    }

    printf("\nDigite o dia(1-%d): ", diasNoMes[dados.mes]);
    scanf("%d", &dados.dia);

    while (dados.dia <= 0 || dados.dia > diasNoMes[dados.mes]) {
        printf("\nDia inválido, digite outro no intervalo de 1 a %d: ", diasNoMes[dados.mes]);
        scanf("%d", &dados.dia);
    }


    printf("Digite o ano(2023 - 2024 - 2025...)");
    scanf("%d", &dados.ano);

    while (dados.ano <= 2022) {
        printf("\nAno inválido, digite outro: ");
        scanf("%d", &dados.ano);
    }

    return dados;
}

int Vdata(data inicio, data fim){
    int valida = 0;
    if(inicio.ano == fim.ano){
        if(inicio.mes == fim.mes){
            if(inicio.dia >= fim.dia){
                valida = 1;
            }
        } else if(inicio.mes > fim.mes){
            valida = 1;
        }
    } else if(inicio.ano > fim.ano){
        valida = 1;
    }

    return valida;
}

reserva le_dados_reserva(int GLOBAL_tam_pont_dados_reservas) {
    reserva dados;
    char txt[30] = "reservas.txt", bin[30] = "reservas.bin";
    int tam = sizeof(reserva);

    dados.delet = 0;
    dados.codigo = retorna_id(txt, bin, tam, GLOBAL_tam_pont_dados_reservas);

    printf("Digite o código do quarto: ");
    scanf("%f", &dados.codQuarto);
    printf("\nDigite a data de entrada:\n");
    dados.inicio = le_dados_data();
    printf("\nDigite a data de saída:\n");
    dados.fim = le_dados_data();

    while(Vdata(dados.inicio, dados.fim) == 1){
        printf("\nData inválida!!");
        printf("\nDigite a data de entrada:\n");
        dados.inicio = le_dados_data();
        printf("\nDigite a data de saída:\n");
        dados.fim = le_dados_data();
    }
    return dados;
}

void menuReserva(int tipoArquivo, reserva **GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int *GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao) {
    reserva dados;
    int opcao = 99, variavel = 0;

    while (opcao != 6) {
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de reserva - 1\n");
        printf("\tListar reservas - 2\n");
        printf("\tAlterar dados reserva - 3\n");
        printf("\tExcluir dados de reserva - 4\n");
        printf("\tPesquisar reservas - 5\n");
        printf("\tVoltar ao menu inicial - 6\n");

        printf("Opc�o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_reserva(*GLOBAL_tam_pont_dados_reservas);
                if (tipoArquivo == 0) {
                    salva_cadastro_reserva_bin(dados, *GLOBAL_dados_reservas, *GLOBAL_tam_pont_dados_reservas);
                } else if (tipoArquivo == 1) {
                    salva_cadastro_reserva_txt(dados, *GLOBAL_dados_reservas, *GLOBAL_tam_pont_dados_reservas);
                }
                else {
                    salva_cadastro_reserva_mem(dados, &GLOBAL_dados_reservas, &(*GLOBAL_tam_pont_dados_reservas));
                }
                break;
            case 2:
                le_todas_reservas(*GLOBAL_dados_reservas, *GLOBAL_tam_pont_dados_reservas);
                break;
            case 3:
                altera_reserva(*GLOBAL_dados_reservas, *GLOBAL_tam_pont_dados_reservas);
                break;
            case 4:
                exclui_reservas(*GLOBAL_dados_reservas, *GLOBAL_tam_pont_dados_reservas);
                break;
            case 5:
                pesquisa_reserva(*GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, *GLOBAL_tam_pont_dados_reservas, GLOBAL_tam_pont_dados_acomodacao);
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}

//Menu de pesquisa
void pesquisa_reserva(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao) {

    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    float codigo;
    int encontrado_bin = 0, encontrado_txt = 0, op = 0;
    char linha_rese[(sizeof(reserva))], linha_aco[(sizeof(acomodacao))], *token, *facilidade;
    
    printf("Digite a maneira a qual procurar uma acomodação livre: \n1- Data \n2- Id da categoria de acomodação \n3- Quantia de pessoas \n4- Facilidades \n5- Todas as opções\n");
    scanf("%d", &op);
    
    switch (op) {
        case 1:
            pesquisa_reserva_data(GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_reservas, GLOBAL_tam_pont_dados_acomodacao);
            break;
        case 2:
            pesquisa_reserva_Categoria(GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_reservas, GLOBAL_tam_pont_dados_acomodacao);
            break;
        case 3:
            pesquisa_reserva_quantPessoas(GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_reservas, GLOBAL_tam_pont_dados_acomodacao);
            break;
        case 4:
            pesquisa_reserva_facilidade(GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_reservas, GLOBAL_tam_pont_dados_acomodacao);
            break;
        case 5:
        pesquisa_reserva_porTudo(GLOBAL_dados_reservas, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_reservas, GLOBAL_tam_pont_dados_acomodacao);
            break;
        default :
            printf("Opção inválida!\n");
            break;
    }
}

//Reserva

void salva_cadastro_reserva_bin(reserva dados, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *arquivo;

    arquivo = fopen("reservas.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    if (valida_data(dados.inicio, dados.fim, dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
        if(valida_id_acomodacao(dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas)){
            fwrite(&dados, sizeof (reserva), 1, arquivo);
            printf("\nReserva cadastrada com sucesso!");
        } else
            printf("Código do quarto inválido!");
    } else {
        printf("\nData inválida!");
    }
    fclose(arquivo);
}

void salva_cadastro_reserva_txt(reserva dados, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *txt;
    int salva;
    
    
    if (valida_data(dados.inicio, dados.fim, dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
        if (valida_id_acomodacao(dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
            txt = fopen("reservas.txt", "a");
            if (txt == NULL) {
                printf("Erro de abertura reservas.txt!\n");
                exit(1);
            }

            salva = fprintf(txt, "%d;%0.0f;%0.0f;%d;%d;%d;%d;%d;%d;\n", dados.delet, dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);  
            if (salva < 0) {
                printf("Erro de salvamento de reserva!\n");
            }
            else {
                printf("Salvo com sucesso!\n");
            }
            fclose(txt);
        }
        else {
            printf("Código do quarto inválido!\n");
        }
    }
    else {
        printf("Data Inválida!\n");
    }
    
    getchar();
}

void salva_cadastro_reserva_mem(reserva dados, reserva ***GLOBAL_dados_reservas, int *GLOBAL_tam_pont_dados_reservas) {
    //caso a variavel global GLOBAL_tam_pont_dados_acomodacao não tenha mudado, ele aloca memoria com malloc pro ponteiro global e guarda o valor dos dados na posição apontada pelo ponteiro 
    if (*GLOBAL_tam_pont_dados_reservas == 1) {
        **GLOBAL_dados_reservas = malloc(sizeof(acomodacao));
        ***GLOBAL_dados_reservas = dados;
        
    }
    //caso a variavel GLOBAL_tam_pont_dados_reservas tenha mudado, ele irá realocar a alocação dinâmica como o que ja foi alocado +1
    //depois, ele vai guardar o valor dos dados na próxima porção de memoria apontada pelo ponteiro
    else {
        **GLOBAL_dados_reservas = realloc(GLOBAL_dados_reservas, (*GLOBAL_tam_pont_dados_reservas)*sizeof(acomodacao));
        ***(GLOBAL_dados_reservas + (*GLOBAL_tam_pont_dados_reservas - 1)) = dados;
    }
    
    if (**GLOBAL_dados_reservas == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    } else 
        printf("Reserva cadastrada com sucesso!");
    
    //aumenta o valor da variavel global
    (*GLOBAL_tam_pont_dados_reservas)++;
}

int valida_data(data inicio, data fim, float id, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *arquivo;
    reserva dados;
    int valido = 1, tam_point = 0;
    char linha[(sizeof(reserva))], *token;

    arquivo = fopen("reservas.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    while (fread(&dados, sizeof (reserva), 1, arquivo)) {
        //tomemos por base que seja inviavel alguem ficar mais de 12 meses em um hotel
        if (dados.delet == 0) {
            if (dados.codQuarto == id) {
                //ano
                if (dados.inicio.ano >= inicio.ano && dados.inicio.ano <= fim.ano) {
                    //caso não haja mudança de mes ex: 25/07 - 30/07
                    if ((dados.fim.mes - dados.inicio.mes == 0) == (fim.mes - inicio.mes == 0)) {
                        //logo, caso seja o mesmo mes em ambos
                        if (dados.inicio.mes == inicio.mes) {
                            //caso o dia salvo não esteja no intervalo passado pelo usuário ou seja igual a esse intervalo:
                            if (((dados.inicio.dia >= inicio.dia) && (dados.inicio.dia <= fim.dia)) || ((dados.fim.dia >= inicio.dia) && (dados.fim.dia <= fim.dia)) || (inicio.dia >= dados.inicio.dia) && (inicio.dia <= dados.fim.dia) || ((fim.dia >= dados.inicio.dia) && (fim.dia <= dados.fim.dia))){valido = 0;}
                        }
                    }
                    //caso o mes se altere ex: 29/07 - 01/08
                    else if (((dados.inicio.mes >= inicio.mes) && (dados.inicio.mes <= fim.mes)) || ((dados.fim.mes >= inicio.mes) && (dados.fim.mes <= fim.mes))) {
                        //caso o dia salvo não esteja no intervalo passado pelo usuário ou seja igual a esse intervalo:
                        if (((dados.inicio.dia >= inicio.dia) && (dados.inicio.dia <= fim.dia)) || ((dados.fim.dia >= inicio.dia) && (dados.fim.dia <= fim.dia)) || (inicio.dia >= dados.inicio.dia) && (inicio.dia <= dados.fim.dia) || ((fim.dia >= dados.inicio.dia) && (fim.dia <= dados.fim.dia))){valido = 0;}
                    }
                }
            }
        }
    }
    fclose(arquivo);
    
    if (valido == 1) {
        arquivo = fopen("reservas.txt", "r");
        if (arquivo == NULL) {
            printf("\nErro ao abrir arquivo de reservas!");
            exit(1);
        }
        
        while(fgets(linha, sizeof(reserva), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            if (dados.delet == 0) {
                token = strtok(NULL, ";");
                dados.codigo = atoff(token);
                token = strtok(NULL, ";");
                dados.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                dados.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                dados.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                dados.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                dados.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                dados.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                dados.fim.ano = atoi(token);
                
                //tomemos por base que seja inviavel alguem ficar mais de 12 meses em um hotel
                if (dados.codQuarto == id) {
                    //ano
                    if (dados.inicio.ano >= inicio.ano && dados.inicio.ano <= fim.ano) {
                        //caso não haja mudança de mes ex: 25/07 - 30/07
                        if ((dados.fim.mes - dados.inicio.mes == 0) == (fim.mes - inicio.mes == 0)) {
                            //logo, caso seja o mesmo mes em ambos
                            if (dados.inicio.mes == inicio.mes) {
                                //caso o dia salvo não esteja no intervalo passado pelo usuário ou seja igual a esse intervalo:
                                if (((dados.inicio.dia >= inicio.dia) && (dados.inicio.dia <= fim.dia)) || ((dados.fim.dia >= inicio.dia) && (dados.fim.dia <= fim.dia)) || (dados.inicio.dia == inicio.dia && dados.fim.dia == fim.dia)) {
                                    valido = 0;
                                }
                                else if (((inicio.dia >= dados.inicio.dia) && (inicio.dia <= dados.fim.dia)) || ((fim.dia <= dados.inicio.dia) && (fim.dia >= dados.fim.dia))) {
                                    valido = 0;
                                }
                            }
                        }
                        //caso o mes se altere ex: 29/07 - 01/08
                        else if (((dados.inicio.mes >= inicio.mes) && (dados.inicio.mes <= fim.mes)) || ((dados.fim.mes >= inicio.mes) && (dados.fim.mes <= fim.mes))) {
                            //caso o dia salvo não esteja no intervalo passado pelo usuário ou seja igual a esse intervalo:
                            if (((dados.inicio.dia >= inicio.dia) && (dados.inicio.dia <= fim.dia)) || ((dados.fim.dia >= inicio.dia) && (dados.fim.dia <= fim.dia)) || (dados.inicio.dia == inicio.dia && dados.fim.dia == fim.dia)) {
                                valido = 0;
                            }
                            else if (((inicio.dia >= dados.inicio.dia) && (inicio.dia <= dados.fim.dia)) || ((fim.dia <= dados.inicio.dia) && (fim.dia >= dados.fim.dia))) {
                                    valido = 0;
                            }
                        }
                    }
                }
            }
        }
        
        fclose(arquivo);
    }
    
    if (valido == 1) {
        if (GLOBAL_dados_reservas != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
                //tomemos por base que seja inviavel alguem ficar mais de 12 meses em um hotel
                if (GLOBAL_dados_reservas->delet == 0) {
                    if (GLOBAL_dados_reservas->codQuarto == id) {
                        //ano
                        if (GLOBAL_dados_reservas->inicio.ano >= inicio.ano && GLOBAL_dados_reservas->inicio.ano <= fim.ano) {
                            //caso não haja mudança de mes ex: 25/07 - 30/07
                            if ((GLOBAL_dados_reservas->fim.mes - GLOBAL_dados_reservas->inicio.mes == 0) == (fim.mes - inicio.mes == 0)) {
                                //logo, caso seja o mesmo mes em ambos
                                if (GLOBAL_dados_reservas->inicio.mes == inicio.mes) {
                                    //caso o dia salvo não esteja no intervalo passado pelo usuário ou seja igual a esse intervalo:
                                    if (((GLOBAL_dados_reservas->inicio.dia >= inicio.dia) && (GLOBAL_dados_reservas->inicio.dia <= fim.dia)) || ((GLOBAL_dados_reservas->fim.dia >= inicio.dia) && (GLOBAL_dados_reservas->fim.dia <= fim.dia)) || (GLOBAL_dados_reservas->inicio.dia == inicio.dia && GLOBAL_dados_reservas->fim.dia == fim.dia)) {
                                        valido = 0;
                                    }
                                }
                            }
                            //caso o mes se altere ex: 29/07 - 01/08
                            else if (((GLOBAL_dados_reservas->inicio.mes >= inicio.mes) && (GLOBAL_dados_reservas->inicio.mes <= fim.mes)) || ((GLOBAL_dados_reservas->fim.mes >= inicio.mes) && (GLOBAL_dados_reservas->fim.mes <= fim.mes))) {
                                //caso o dia salvo não esteja no intervalo passado pelo usuário ou seja igual a esse intervalo:
                                if (((GLOBAL_dados_reservas->inicio.dia >= inicio.dia) && (GLOBAL_dados_reservas->inicio.dia <= fim.dia)) || ((GLOBAL_dados_reservas->fim.dia >= inicio.dia) && (GLOBAL_dados_reservas->fim.dia <= fim.dia)) || (GLOBAL_dados_reservas->inicio.dia == inicio.dia && GLOBAL_dados_reservas->fim.dia == fim.dia)) {
                                    valido = 0;
                                }
                            }
                        }
                    }
                }

                GLOBAL_dados_reservas++;
            }
        
            GLOBAL_dados_reservas -= (tam_point - 1);
        }
    }
    
    return valido;
}

int valida_id_acomodacao(float id, reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *txt, *bin;
    acomodacao dados;
    int valido = 0, tam_point = 0;
    char linha[(sizeof(acomodacao))], *token;
    
    bin = fopen("acomodacoes.bin", "rb");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo acomodacoes.bin!\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(acomodacao), 1, bin)) {
        if (dados.delet == 0 && dados.codigo == id) {
            valido = 1;
            break;
        }
    }
    
    fclose(bin);
    
    if (valido == 0) {
        txt = fopen("acomodacoes.txt", "r");
        if (txt == NULL) {
            printf("Erro de abertura de arquivo acomodacoes.txt!\n");
            exit(1);
        }

        while(fgets(linha, sizeof(acomodacao), txt)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == id) {
                valido = 1;
                break;
            }
        }

        fclose(txt);
    }
    
    if (valido == 0) {
        if (GLOBAL_dados_reservas != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
                if (GLOBAL_dados_reservas->delet == 0) {
                    if (GLOBAL_dados_reservas->codigo == id) {
                        valido = 1;
                        break;
                    }
                }
                
                GLOBAL_dados_reservas++;
            }
            
            GLOBAL_dados_reservas -= (tam_point - 1);
        }
    }
    
    return valido;
}

void le_todas_reservas(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *txt, *bin;
    reserva dados;
    int tam_point = 0, encontrado = 0;
    char linha[(sizeof(reserva))], *token;
    
    bin = fopen("reservas.bin", "rb");
    if (bin == NULL) {
        printf("Erro de leitura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(reserva), 1, bin)) {
        if (dados.delet == 0) {
            encontrado = 1;
            printf("Código da reserva: %0.0f \n\tCódigo do quarto: %0.0f \n\tData Inicial: %d/%d/%d \n\tData Final: %d/%d/%d\n\n", dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);
        }
    }
    
    fclose(bin);
    
    txt = fopen("reservas.txt", "r");
    if (txt == NULL) {
        printf("Erro de leitura de arquivo reservas.txt!\n");
        exit(1);
    }
    
    while(fgets(linha, sizeof(reserva), txt)) {
        token = strtok(linha, ";");
        
        if (strcmp(token, "0") == 0) {
            encontrado = 1;
            token = strtok(NULL, ";");
            printf("Código da reserva: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Código do quarto: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Data inicial: %s/", token);
            token = strtok(NULL, ";");
            printf("%s/", token);
            token = strtok(NULL, ";");
            printf("%s\n\t", token);
            token = strtok(NULL, ";");
            printf("Data final: %s/", token);
            token = strtok(NULL, ";");
            printf("%s/", token);
            token = strtok(NULL, ";");
            printf("%s\n\n", token);
        }
    }
    
    fclose(txt);
    
    //memoria
    if (GLOBAL_dados_reservas != NULL) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
            if (GLOBAL_dados_reservas->delet == 0) {
                encontrado = 1;
                printf("Código da reserva: %0.0f \n\tCódigo do quarto: %0.0f \n\tData Inicial: %d/%d/%d \n\tData Final: %d/%d/%d\n\n", GLOBAL_dados_reservas->codigo, GLOBAL_dados_reservas->codQuarto, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);
            }
            
            GLOBAL_dados_reservas++;
        }
        
        GLOBAL_dados_reservas -= (tam_point - 1);
    }

    if(encontrado == 0){
        printf("\nNenhuma reserva cadastrada!");
    }
    getchar();
}

reserva le_uma_reserva(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas){
    FILE *txt, *bin, *alt;
    float codigo = 0;
    int encontrado = 0, tam_point = 0;
    char linha[(sizeof(reserva))], *token;
    reserva dados, retorna;

    retorna.delet = 1;
    
    printf("Digite o código da reserva que deseja buscar: \n");
    scanf("%f", &codigo);
    
    //bin
    bin = fopen("reservas.bin", "rb+wb");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(reserva), 1, bin)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            encontrado++;
            retorna = dados;
            break;
        }
    }
    
    fclose(bin);
    
    //txt
    if (encontrado == 0) {
        txt = fopen("reservas.txt", "r");
        if (txt == NULL) {
            printf("Erro de abertura de arquivo reservas.txt!\n");
            exit(1);
        }
        alt = fopen("temp.txt", "a");
        if (alt == NULL) {
            printf("Erro ao criar arquivo temporário!\n");
            exit(1);
        }

        while(fgets(linha, sizeof(reserva), txt)) {
            //Passa os dados para a varável dados

            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            dados.codQuarto = atoff(token);
            token = strtok(NULL, ";");
            dados.inicio.dia = atoi(token);
            token = strtok(NULL, ";");
            dados.inicio.mes = atoi(token);
            token = strtok(NULL, ";");
            dados.inicio.ano = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.dia = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.mes = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.ano = atoi(token);

            if (dados.delet == 0 && dados.codigo == codigo) {
                encontrado++;
                retorna = dados;
            }
        }


        fclose(alt);
        fclose(txt);
        
        remove("reservas.txt");
        rename("temp.txt", "reservas.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        if (GLOBAL_dados_reservas != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
                if (GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_reservas->codigo == codigo) {
                    encontrado++;
                    retorna.codigo = GLOBAL_dados_reservas->codigo;
                    retorna.codQuarto = GLOBAL_dados_reservas->codQuarto;
                    retorna.delet = GLOBAL_dados_reservas->delet;
                    retorna.fim = GLOBAL_dados_reservas->fim;
                    retorna.inicio = GLOBAL_dados_reservas->inicio;
                    break;
                }
                
                GLOBAL_dados_reservas++;
            }
            
            GLOBAL_dados_reservas -= (tam_point - 1);
        }
    }
    
    if (encontrado == 0) {
        printf("Reserva não consta na base de dados! \n");
        return retorna;
    }
}

void altera_reserva(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *txt, *bin, *alt;
    float codigo = 0;
    int encontrado = 0, tam_point = 0;
    char linha[(sizeof(reserva))], *token;
    reserva dados;
    
    printf("Digite o código da reserva que deseja alterar: \n");
    scanf("%f", &codigo);
    
    //bin
    bin = fopen("reservas.bin", "rb+wb");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(reserva), 1, bin)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados = le_dados_reserva(GLOBAL_tam_pont_dados_reservas);
            dados.codigo = codigo;
            if (valida_data(dados.inicio, dados.fim, dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                fseek(bin, -sizeof(reserva), SEEK_CUR);
                fwrite(&dados, sizeof (reserva), 1, bin);
                encontrado = 1;
                break;
            }
            else {
                printf("Data digitada é inválida!!\n");
            }
        }
    }
    
    fclose(bin);
    
    //txt
    if (encontrado == 0) {
        txt = fopen("reservas.txt", "r");
        if (txt == NULL) {
            printf("Erro de abertura de arquivo reservas.txt!\n");
            exit(1);
        }
        alt = fopen("temp.txt", "a");
        if (alt == NULL) {
            printf("Erro ao criar arquivo temporário!\n");
            exit(1);
        }

        while(fgets(linha, sizeof(reserva), txt)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados = le_dados_reserva(GLOBAL_tam_pont_dados_reservas);
                dados.codigo = codigo;
                
                if (valida_data(dados.inicio, dados.fim, dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                    encontrado = 1;
                }
                else{
                    printf("data invalida!\n");
                }
            }
            else {
                token = strtok(NULL, ";");
                dados.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                dados.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                dados.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                dados.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                dados.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                dados.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                dados.fim.ano = atoi(token);
            }
            
            fprintf(alt, "%d;%0.0f;%0.0f;%d;%d;%d;%d;%d;%d;\n", dados.delet, dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);
        }


        fclose(alt);
        fclose(txt);
        
        remove("reservas.txt");
        rename("temp.txt", "reservas.txt");
    }
    
    //memoria
    if (encontrado == 0) {
        if (GLOBAL_dados_reservas != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
                if (GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_reservas->codigo == codigo) {
                    dados = le_dados_reserva(GLOBAL_tam_pont_dados_reservas);
                    dados.codigo = codigo;
                    if (valida_data(dados.inicio, dados.fim, dados.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                        *(GLOBAL_dados_reservas) = dados;
                        encontrado = 1;
                        break;
                    }
                }
                
                GLOBAL_dados_reservas++;
            }
            
            GLOBAL_dados_reservas -= (tam_point - 1);
        }
    }
    
    if (encontrado == 0) {
        printf("Reserva não consta na base de dados! \n");
    }
    else {
        printf("Reserva alterada com sucesso! \n");
    }
}

void exclui_reservas(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas) {
    FILE *txt, *bin, *altera;
    reserva dados;
    float codigo;
    int encontrado = 0, tam_point = 0, salvar;
    char linha[(sizeof(reserva))], *token;
    
    printf("Digite o código da reserva que deseja excluir: \n");
    scanf("%f", &codigo);
    
    bin = fopen("reservas.bin", "rb+wb");
    if (bin == NULL) {
        printf("Erro de leitura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(reserva), 1, bin)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.delet = 1;
            fseek(bin, -sizeof(reserva), SEEK_CUR);
            fwrite(&dados, sizeof(reserva), 1, bin);
            encontrado = 1;
        }
    }
    
    fclose(bin);
    
    if (encontrado == 0) {
        txt = fopen("reservas.txt", "r");
        if (txt == NULL) {
            printf("Erro de leitura de arquivo reservas.txt!\n");
            exit(1);
        }
        
        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro de leitura de arquivo reservas.txt!\n");
            exit(1);
        }

        while(fgets(linha, sizeof(reserva), txt)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            dados.codQuarto = atoff(token);
            token = strtok(NULL, ";");
            dados.inicio.dia = atoi(token);
            token = strtok(NULL, ";");
            dados.inicio.mes = atoi(token);
            token = strtok(NULL, ";");
            dados.inicio.ano = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.dia = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.mes = atoi(token);
            token = strtok(NULL, ";");
            dados.fim.ano = atoi(token);
            
            
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.delet = 1;
                encontrado = 1;
            }

            salvar = fprintf(altera, "%d;%0.0f;%0.0f;%d;%d;%d;%d;%d;%d;\n", dados.delet, dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);
            if (salvar < 0) {
                printf("Erro na exclusão!\n");
            }
        }

        fclose(txt);
        fclose(altera);
        
        remove("reservas.txt");
        rename("temp.txt", "reservas.txt");
    }
    
    if (encontrado == 0) {
        //memoria
        if (GLOBAL_dados_reservas != NULL) {
            for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_reservas; tam_point++) {
                if (GLOBAL_dados_reservas->delet == 0) {
                    if (GLOBAL_dados_reservas->codigo == codigo) {
                        GLOBAL_dados_reservas->delet = 1;
                        encontrado = 1;
                        break;
                    }
                }

                GLOBAL_dados_reservas++;
            }

            GLOBAL_dados_reservas -= (tam_point - 1);
        }
    }
    
    if (encontrado == 0) {
        printf("Reserva não encontrada!\n");
    } else {
        printf("Dados excluídos com sucesso!\n");
    }
}

int retornaDias(data inicio, data fim){
        int dias = 0;
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(inicio.ano == fim.ano){
        if(inicio.mes == fim.mes){
            //Caso seja mesmo ano e mês, dias recebe apenas o dia final - inicial + 1
            dias += (fim.dia - inicio.dia + 1);
        } else {
            for(int i = inicio.mes; i <= fim.mes; i++){
                if(i < fim.mes){
                    //Caso sejam meses diferentes, subtrai-se do mes de inicio o dia de inicio e soma 1
                    dias += (diasNoMes[i] - inicio.dia + 1);
                    //Define o dia de início para 0 pois passa para o próximo mês
                    inicio.dia = 1;
                } else{
                    //Caso chegue ao último mês, apenas soma-se o dia final
                    dias+= fim.dia;
                }
            }
        }
    } else{
        for(int i = inicio.ano; i <= fim.ano; i++){
            if(i < fim.ano){
                //Seta uma data auxiliar até o fim do ano
                data aux;
                aux.dia = 31;
                aux.mes = 12;
                aux.ano = i;

                //Calcula os dias até o fim do ano de inicio
                if(inicio.mes == aux.mes){
                    //Caso seja mesmo ano e mês, dias recebe apenas o dia final - inicial + 1
                    dias += (aux.dia - inicio.dia + 1);
                } else{
                    for(int j = inicio.mes; j <= aux.mes; j++){
                        if(j < aux.mes){
                            //Caso sejam meses diferentes, subtrai-se do mes de inicio o dia de inicio e soma 1
                            dias += (diasNoMes[j] - inicio.dia + 1);
                            //Define o dia de início para 0 pois passa para o próximo mês
                            inicio.dia = 1;
                        } else{
                            //Caso chegue ao último mês, apenas soma-se o dia final
                            dias+= aux.dia;
                        }
                    }
                }
                
                inicio.dia = 1;
                inicio.mes = 1;
                inicio.ano = i + 1;
            }
            //Quando o ano de inicio se tornar igual é só calcular novamente; 
            else {
                if(inicio.mes == fim.mes){
                    //Caso seja mesmo ano e mês, dias recebe apenas o dia final - inicial + 1
                    dias += (fim.dia - inicio.dia + 1);
                } else {
                    for(int i = inicio.mes; i <= fim.mes; i++){
                        if(i < fim.mes){
                            //Caso sejam meses diferentes, subtrai-se do mes de inicio o dia de inicio e soma 1
                            dias += (diasNoMes[i] - inicio.dia + 1);
                            //Define o dia de início para 0 pois passa para o próximo mês
                            inicio.dia = 1;
                        } else{
                            //Caso chegue ao último mês, apenas soma-se o dia final
                            dias+= fim.dia;
                        }
                    }
                }
            }
        }
    }
    return dias;
}

void pesquisa_reserva_quantPessoas(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao){
    FILE *arquivo1, *arquivo2;
    int quant, encontrado = 0, encontrado1 = 0, encontrado2 = 0, encontrado3 = 0, tam_point_rese = 0, tam_point_acomod = 0;
    acomodacao acomod;
    reserva reser;

    printf("\nDigite a quantidade de pessoas que deseja pesquisar: ");
    scanf("%d", &quant);

    arquivo1 = fopen("acomodacoes.bin", "rb");
    arquivo2 = fopen("reservas.bin", "rb");

    if(arquivo1 == NULL){
        printf("\nErro ao abrir arquivo de acomodações!");
        exit(1);
    }

    if(arquivo2 == NULL){
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    //Lendo acomodações(quartos) binários e comparando com as reservas binárias, txt e memoria respectivamente 
    while (fread(&acomod, sizeof(acomodacao), 1 ,arquivo1)){
        if(acomod.delet == 0 && acomod.tipo.qnt_pessoas == quant){
            //Reservas BIN
            while (fread(&reser, sizeof(reserva), 1 ,arquivo2)){
                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado1 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);

            //Reservas TXT
            arquivo2 = fopen("reservas.txt", "r");
            char linha[(sizeof(reserva))], *token;

            if(arquivo2 == NULL){
                printf("\nErro ao abrir arquivo de reservas!");
                exit(1);
            }

            while (fgets(linha, sizeof(reserva), arquivo2)){
                token = strtok(linha, ";");
                reser.delet = atoi(token);
                token = strtok(NULL, ";");
                reser.codigo = atoff(token);
                token = strtok(NULL, ";");
                reser.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                reser.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.ano = atoi(token);

                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado1 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);
            
            if(encontrado1 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
            }
        }
    }
    fclose(arquivo1);
    
    
    //Lendo acomodações(quartos) txts e comparando com as reservas binárias, txt e memoria respectivamente

    arquivo1 = fopen("acomodacoes.txt", "r");
    arquivo2 = fopen("reservas.bin", "rb");

    if(arquivo1 == NULL){
        printf("\nErro ao abrir arquivo de acomodações!");
        exit(1);
    }

    if(arquivo2 == NULL){
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    char linha[(sizeof(acomodacao))], *token;

    while (fgets(linha, sizeof(acomodacao) ,arquivo1)){
        //Recebe os dados de delet, código da acomodação
        token = strtok(linha, ";");
        acomod.delet = atoi(token);
        token = strtok(NULL, ";");
        acomod.codigo = atoff(token);
        //pula para sua quantidade de pessoas
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        acomod.tipo.qnt_pessoas = atoi(token);

        if(acomod.delet == 0 && acomod.tipo.qnt_pessoas == quant){
            //Reservas BIN
            while (fread(&reser, sizeof(reserva), 1 ,arquivo2)){
                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado2 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);

            //Reservas TXT
            arquivo2 = fopen("reservas.txt", "r");
            char linha[(sizeof(reserva))], *token;

            if(arquivo2 == NULL){
                printf("\nErro ao abrir arquivo de reservas!");
                exit(1);
            }

            while (fgets(linha, sizeof(reserva), arquivo2)){
                token = strtok(linha, ";");
                reser.delet = atoi(token);
                token = strtok(NULL, ";");
                reser.codigo = atoff(token);
                token = strtok(NULL, ";");
                reser.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                reser.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.ano = atoi(token);

                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado2 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);
            
            if(encontrado2 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
            }
        }
    }
    fclose(arquivo1);
    
    
    //verifica nas acomodações salvas na memória:
    for(tam_point_acomod = 1; tam_point_acomod < GLOBAL_tam_pont_dados_acomodacao; tam_point_acomod++) {        
        if(GLOBAL_dados_acomodacao->delet == 0 && GLOBAL_dados_acomodacao->tipo.qnt_pessoas == quant){
            //Reservas BIN
            while (fread(&reser, sizeof(reserva), 1 ,arquivo2)){
                if(reser.delet == 0 && GLOBAL_dados_acomodacao->codigo == reser.codQuarto){
                    encontrado3 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        GLOBAL_dados_acomodacao->codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);

            //Reservas TXT
            arquivo2 = fopen("reservas.txt", "r");
            char linha[(sizeof(reserva))], *token;

            if(arquivo2 == NULL){
                printf("\nErro ao abrir arquivo de reservas!");
                exit(1);
            }

            while (fgets(linha, sizeof(reserva), arquivo2)){
                token = strtok(linha, ";");
                reser.delet = atoi(token);
                token = strtok(NULL, ";");
                reser.codigo = atoff(token);
                token = strtok(NULL, ";");
                reser.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                reser.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.ano = atoi(token);

                if(reser.delet == 0 && GLOBAL_dados_acomodacao->codigo == reser.codQuarto){
                    encontrado3 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        GLOBAL_dados_acomodacao->codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);
            
            //reserva memoria
            for(tam_point_rese = 1; tam_point_rese < GLOBAL_tam_pont_dados_reservas; tam_point_rese++) {
                if(GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_acomodacao->codigo == GLOBAL_dados_reservas->codQuarto){
                    encontrado3 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        GLOBAL_dados_acomodacao->codigo, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);
                }
                //aumenta o valor do ponteiro
                GLOBAL_dados_reservas++;
            }
            
            GLOBAL_dados_reservas -= (tam_point_rese - 1);
            
            if(encontrado3 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
            }
        }
        
        //aumenta o valor do ponteiro
        GLOBAL_dados_acomodacao++;
    }
    
    GLOBAL_dados_acomodacao -= (tam_point_acomod - 1);

    if(encontrado == 0){
        printf("\nNenhum quarto para %d pessoa(s) encontrado!", quant);
    } else {
        printf("\nForam encontrados %d quarto(s)!", encontrado);
    }
}

void pesquisa_reserva_Categoria(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao) {
    FILE *arquivo1, *arquivo2;
    int cate, encontrado = 0, encontrado1 = 0, encontrado2 = 0, encontrado3 = 0, tam_point_rese = 0, tam_point_acomod = 0;
    acomodacao acomod;
    reserva reser;

    printf("\nDigite o código da categoria que deseja pesquisar: ");
    scanf("%d", &cate);

    arquivo1 = fopen("acomodacoes.bin", "rb");
    arquivo2 = fopen("reservas.bin", "rb");

    if(arquivo1 == NULL){
        printf("\nErro ao abrir arquivo de acomodações!");
        exit(1);
    }

    if(arquivo2 == NULL){
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    //Lendo acomodações(quartos) binários e comparando com as reservas binárias e txts respectivamente 
    while (fread(&acomod, sizeof(acomodacao), 1 ,arquivo1)){
        if(acomod.delet == 0 && acomod.tipo.codigo == cate){
            //Reservas BIN
            while (fread(&reser, sizeof(reserva), 1 ,arquivo2)){
                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado1 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                    acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);

            //Reservas TXT
            arquivo2 = fopen("reservas.txt", "r");
            char linha[(sizeof(reserva))], *token;

            if(arquivo2 == NULL){
                printf("\nErro ao abrir arquivo de reservas!");
                exit(1);
            }

            while (fgets(linha, sizeof(reserva), arquivo2)){
                token = strtok(linha, ";");
                reser.delet = atoi(token);
                token = strtok(NULL, ";");
                reser.codigo = atoff(token);
                token = strtok(NULL, ";");
                reser.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                reser.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.ano = atoi(token);

                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado1 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                    acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            if(encontrado1 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
            }
            fclose(arquivo2);
        }
    }
    fclose(arquivo1);
    
    //Lendo acomodações(quartos) txts e comparando com as reservas binárias e txts respectivamente 

    arquivo1 = fopen("acomodacoes.txt", "r");
    arquivo2 = fopen("reservas.bin", "rb");

    if(arquivo1 == NULL){
        printf("\nErro ao abrir arquivo de acomodações!");
        exit(1);
    }

    if(arquivo2 == NULL){
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    char linha[(sizeof(acomodacao))], *token;

    while (fgets(linha, sizeof(acomodacao) ,arquivo1)){
        //Recebe os dados de delet, código do tipo acomodação
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
        

        if(acomod.delet == 0 && acomod.tipo.codigo == cate){
            //Reservas BIN
            while (fread(&reser, sizeof(reserva), 1 ,arquivo2)){
                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado2 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                    acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            fclose(arquivo2);

            //Reservas TXT
            arquivo2 = fopen("reservas.txt", "r");
            char linha[(sizeof(reserva))], *token;

            if(arquivo2 == NULL){
                printf("\nErro ao abrir arquivo de reservas!");
                exit(1);
            }

            while (fgets(linha, sizeof(reserva), arquivo2)){
                token = strtok(linha, ";");
                reser.delet = atoi(token);
                token = strtok(NULL, ";");
                reser.codigo = atoff(token);
                token = strtok(NULL, ";");
                reser.codQuarto = atoff(token);
                token = strtok(NULL, ";");
                reser.inicio.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.inicio.ano = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.dia = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.mes = atoi(token);
                token = strtok(NULL, ";");
                reser.fim.ano = atoi(token);

                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado2 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            
            //reserva memoria
            for(tam_point_rese = 1; tam_point_rese < GLOBAL_tam_pont_dados_reservas; tam_point_rese++) {
                //tentando fazer uma condição de parada
                if ((GLOBAL_dados_reservas->delet < 0 || GLOBAL_dados_reservas->delet > 1)) {
                    break;
                }
                
                if(GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_acomodacao->codigo == GLOBAL_dados_reservas->codQuarto){
                    encontrado2 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        GLOBAL_dados_acomodacao->codigo, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);
                }
                //aumenta o valor do ponteiro
                GLOBAL_dados_reservas++;
            }
            
            GLOBAL_dados_reservas -= (tam_point_rese - 1);
            
            if(encontrado2 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
            }
            fclose(arquivo2);
        }
    }
    fclose(arquivo1);
    
    if(encontrado == 0){
        printf("\nNenhum quarto com a categoria %d encontrado!", cate);
    } else 
        printf("\nForam encontrados %d quarto(s)!", encontrado);
}

void pesquisa_reserva_facilidade(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao) {
    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    float salva_cod = -1;
    int encontrado_bin = 0, encontrado_txt = 0, encontrado_mem = 0, aux;
    char linha_rese[(sizeof(reserva))], linha_aco[(sizeof(acomodacao))], *token, facilidade[100];
    
    printf("Digite a facilidade a ser pesquisada: \n");
    scanf("%s", facilidade);
    //Torna todos os caracteres da string minúsculos para facilitar busca posterior
    for (aux = 0; aux < strlen(facilidade); aux++) {
       facilidade[aux] = tolower((unsigned char) facilidade[aux]);
    }

    //verifica no bin
    rese_bin = fopen("reservas.bin", "rb");
    if (rese_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //abre acomodacoes tanto txt quanto bin
    acomo_bin = fopen("acomodacoes.bin", "rb");
    if (acomo_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verificar na acomodação binaria
    while(fread(&reser, sizeof(reserva), 1, rese_bin)) {
        encontrado_bin = 0;

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        
        while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se dentro da string facilidade do quarto há a facilidade escrita pela pessoa (pode dar erro por diferenciar maiuscula e minuscula, a ordem importa caso hajá mais de 1 palavra)
                        if (strstr(acomod.facilidades, facilidade) != NULL) {
                            encontrado_bin = 1;
                            
                            if (encontrado_bin == 1) {
                                if (salva_cod == reser.codQuarto) {
                                    printf("Ocupado de: %d/%d/%d até %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                                else {
                                    salva_cod = reser.codQuarto;
                                    printf("Código do quarto: %0.0f \nOcupado de: %d/%d/%d até %d/%d/%d\n", reser.codQuarto, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    fclose(rese_bin);
    
    fclose(acomo_bin);
    
    rese_bin = fopen("reservas.bin", "rb");
    if (rese_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    acomo_txt = fopen("acomodacoes.txt", "r");
    if (acomo_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verificar na acomodação txt
    while(fread(&reser, sizeof(reserva), 1, rese_bin)) {
        encontrado_bin = 0;

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_txt, 0, SEEK_SET);
        
        while(fgets(linha_aco, sizeof(acomodacao), acomo_txt)) {
            // passa os dados do txt pra variavel para facilitar comparação
            token = strtok(linha_aco, ";");
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

            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se dentro da string facilidade do quarto há a facilidade escrita pela pessoa (pode dar erro por diferenciar maiuscula e minuscula, a ordem importa caso hajá mais de 1 palavra)
                        if (strstr(acomod.facilidades, facilidade) != NULL) {
                            encontrado_bin = 1;
                            
                            if (encontrado_bin == 1) {
                                if (salva_cod == reser.codQuarto) {
                                    printf("Ocupado de: %d/%d/%d até %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                                else {
                                    salva_cod = reser.codQuarto;
                                    printf("Código do quarto: %0.0f \nOcupado de: %d/%d/%d até %d/%d/%d\n", reser.codQuarto, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_txt);

    fclose(rese_bin);

    //verifica no txt
    rese_txt = fopen("reservas.txt", "r");
    if (rese_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }


    //abre acomodacoes bin
    acomo_bin = fopen("acomodacoes.bin", "rb");
    if (acomo_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verifica no acomodacoes.bin
    while(fgets(linha_rese, sizeof(reserva), rese_txt)) {
        //coleta dados do reservas.txt e o coloca em uma struct
        token = strtok(linha_rese, ";");
        reser.delet = atoi(token);
        token = strtok(NULL, ";");
        reser.codigo = atoff(token);
        token = strtok(NULL, ";");
        reser.codQuarto = atoff(token);
        token = strtok(NULL, ";");
        reser.inicio.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.ano = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.ano = atoi(token);

        encontrado_txt = 0;
        
        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);

        while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se dentro da string facilidade do quarto há a facilidade escrita pela pessoa (pode dar erro por diferenciar maiuscula e minuscula, a ordem importa caso hajá mais de 1 palavra)
                        if (strstr(acomod.facilidades, facilidade) != NULL) {
                            encontrado_txt = 1;
                            
                            if (encontrado_bin == 1) {
                                if (salva_cod == reser.codQuarto) {
                                    printf("Ocupado de: %d/%d/%d até %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                                else {
                                    salva_cod = reser.codQuarto;
                                    printf("Código do quarto: %0.0f \nOcupado de: %d/%d/%d até %d/%d/%d\n", reser.codQuarto, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_bin);
    
    fclose(rese_txt);
    
    rese_txt = fopen("reservas.txt", "r");
    if (rese_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    acomo_txt = fopen("acomodacoes.txt", "r");
    if (acomo_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verifica no acomodacoes.txt
    while(fgets(linha_rese, sizeof(reserva), rese_txt)) {
        //coleta dados do reservas.txt e o coloca em uma struct
        token = strtok(linha_rese, ";");
        reser.delet = atoi(token);
        token = strtok(NULL, ";");
        reser.codigo = atoff(token);
        token = strtok(NULL, ";");
        reser.codQuarto = atoff(token);
        token = strtok(NULL, ";");
        reser.inicio.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.ano = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.ano = atoi(token);

        encontrado_txt = 0;
        
        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_txt, 0, SEEK_SET);

        while(fgets(linha_aco, sizeof(acomodacao), acomo_txt)) {
            // passa os dados do txt pra variavel para facilitar comparação
            token = strtok(linha_aco, ";");
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

            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se dentro da string facilidade do quarto há a facilidade escrita pela pessoa (pode dar erro por diferenciar maiuscula e minuscula, a ordem importa caso hajá mais de 1 palavra)
                        if (strstr(acomod.facilidades, facilidade) != NULL) {
                            encontrado_txt = 1;
                            
                            if (encontrado_bin == 1) {
                                if (salva_cod == reser.codQuarto) {
                                    printf("Ocupado de: %d/%d/%d até %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                                else {
                                    salva_cod = reser.codQuarto;
                                    printf("Código do quarto: %0.0f \nOcupado de: %d/%d/%d até %d/%d/%d\n", reser.codQuarto, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_txt);

    fclose(rese_txt);

    acomo_bin = fopen("acomodacoes.bin", "rb");
    if(acomo_bin == NULL){
        printf("Erro ao abrir arquivo de acomodacoes BIN!");
        exit(1);
    }

    encontrado_mem = 0;

    //Ler acomodações BIN e verificar nas reservas memória
    while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
        if(acomod.delet == 0){
            if(strstr(acomod.facilidades, facilidade) != NULL){
                int k;
                for(k = 1; k < GLOBAL_tam_pont_dados_reservas; k++) {        
                    if(GLOBAL_dados_reservas->codQuarto == acomod.codigo){
                        encontrado_mem = 1;
                        printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                            acomod.codigo, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);  
                    }
                    //aumenta o valor do ponteiro
                    GLOBAL_dados_reservas++;
                }
                GLOBAL_dados_reservas-= k - 1;
                if(encontrado_mem == 0){
                    printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                }
            }
        }
        
    }

    fclose(acomo_bin);
    
    acomo_txt = fopen("acomodacoes.txt", "rb");
    if(acomo_txt == NULL){
        printf("Erro ao abrir arquivo de acomodacoes TXT!");
        exit(1);
    }
    
    char linha[(sizeof(acomodacao))];
    
    encontrado_mem = 0;
    //Ler acomodações TXT e verificar nas reservas memória
    while(fgets(linha, sizeof(acomodacao), acomo_txt)) {
        encontrado_mem = 0;
        // passa os dados do txt pra variavel para facilitar comparação
        token = strtok(linha, ";");
        acomod.delet = atoi(token);
        token = strtok(NULL, ";");
        acomod.codigo = atoff(token);
        token = strtok(NULL, ";");
        strcpy(acomod.descri, token);
        token = strtok(NULL, ";");
        strcpy(acomod.facilidades, token);
        token = strtok(NULL, ";");

        if(acomod.delet == 0){
            if(strstr(acomod.facilidades, facilidade) != NULL){
                int i;
                for(i = 1; i < GLOBAL_tam_pont_dados_reservas; i++) {        
                    if(GLOBAL_dados_reservas->codQuarto == acomod.codigo){
                        encontrado_mem = 1;
                        printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                            acomod.codigo, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);  
                    }
                    //aumenta o valor do ponteiro
                    GLOBAL_dados_reservas++;
                }
                GLOBAL_dados_reservas-= i - 1;
                if(encontrado_mem == 0){
                    printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                }
            }
        }
    }

    fclose(acomo_txt);

    encontrado_mem = 0;
    int i;
    //verifica nas acomodações salvas na memória:
    for(i = 1; i < GLOBAL_tam_pont_dados_acomodacao; i++) {        
        if(GLOBAL_dados_acomodacao->delet == 0 && strstr(GLOBAL_dados_acomodacao->facilidades, facilidade) != NULL){

            //Só é possível fazer uma reserva em mémoria quando a acomodação está salva em memória, logo não é necessário buscar nos arquivos bin e txt.
            //reserva memoria
            int j;
            for(j = 1; j < GLOBAL_tam_pont_dados_reservas; j++) {
                if(GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_acomodacao->codigo == GLOBAL_dados_reservas->codQuarto){
                    encontrado_mem = 1;

                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        GLOBAL_dados_acomodacao->codigo, GLOBAL_dados_reservas->inicio.dia, GLOBAL_dados_reservas->inicio.mes, GLOBAL_dados_reservas->inicio.ano, GLOBAL_dados_reservas->fim.dia, GLOBAL_dados_reservas->fim.mes, GLOBAL_dados_reservas->fim.ano);
                }
                //aumenta o valor do ponteiro
                GLOBAL_dados_reservas++;
            }
            
            GLOBAL_dados_reservas -= (j - 1);
            
            if(encontrado_mem == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", GLOBAL_dados_acomodacao->codigo);
            }
        }
        
        //aumenta o valor do ponteiro
        GLOBAL_dados_acomodacao++;
    }
    GLOBAL_dados_acomodacao-= i - 1;
}

void pesquisa_reserva_data(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao) {
    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    data inicio, fim;
    float salva_cod = -1;
    int encontrado_bin = 0, encontrado_txt = 0, encontrado_mem = 0, livres = 0, tam_point_reserv = 0, tam_point_acomod = 0;
    char linha_rese[(sizeof(reserva))], linha_aco[(sizeof(acomodacao))], *token;
    
    printf("Data Inicial: \n");
    inicio = le_dados_data();
    printf("Data Final: \n");
    fim = le_dados_data();
    
    rese_bin = fopen("reservas.bin", "rb");
    if (rese_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    acomo_bin = fopen("acomodacoes.bin", "rb");
    if (acomo_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    //verificar na acomodação binaria
    while(fread(&reser, sizeof(reserva), 1, rese_bin)) {
        encontrado_bin = 0;

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        if (reser.delet == 0) {
            while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_bin = 1;
                            livres++;

                            if (encontrado_bin == 1) {
                                if (salva_cod != acomod.codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                                    salva_cod = acomod.codigo;
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    fclose(acomo_bin);
    
    fclose(rese_bin);

    rese_bin = fopen("reservas.bin", "rb");
    if (rese_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    acomo_txt = fopen("acomodacoes.txt", "r");
    if (acomo_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verificar na acomodação txt
    while(fread(&reser, sizeof(reserva), 1, rese_bin)) {
        encontrado_bin = 0;

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_txt, 0, SEEK_SET);
        
        while(fgets(linha_aco, sizeof(acomodacao), acomo_txt)) {
            // passa os dados do txt pra variavel para facilitar comparação
            token = strtok(linha_aco, ";");
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

            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_bin = 1;
                            livres++;
                            
                            if (encontrado_bin == 1) {
                                if (salva_cod != acomod.codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                                    salva_cod = acomod.codigo;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_txt);

    fclose(rese_bin);

    //verifica no txt
    rese_txt = fopen("reservas.txt", "r");
    if (rese_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }


    //abre acomodacoes tanto txt quanto bin
    acomo_bin = fopen("acomodacoes.bin", "rb");
    if (acomo_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verifica no acomodacoes.bin
    while(fgets(linha_rese, sizeof(reserva), rese_txt)) {
        //coleta dados do reservas.txt e o coloca em uma struct
        token = strtok(linha_rese, ";");
        reser.delet = atoi(token);
        token = strtok(NULL, ";");
        reser.codigo = atoff(token);
        token = strtok(NULL, ";");
        reser.codQuarto = atoff(token);
        token = strtok(NULL, ";");
        reser.inicio.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.ano = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.ano = atoi(token);

        encontrado_txt = 0;
        
        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        if (reser.delet == 0) {
            while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_bin = 1;
                            livres++;

                            if (encontrado_bin == 1) {
                                if (salva_cod != acomod.codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                                    salva_cod = acomod.codigo;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_bin);
    
    fclose(rese_txt);
    
    rese_txt = fopen("reservas.txt", "r");
    if (rese_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    acomo_txt = fopen("acomodacoes.txt", "r");
    if (acomo_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verifica no acomodacoes.txt
    while(fgets(linha_rese, sizeof(reserva), rese_txt)) {
        //coleta dados do reservas.txt e o coloca em uma struct
        token = strtok(linha_rese, ";");
        reser.delet = atoi(token);
        token = strtok(NULL, ";");
        reser.codigo = atoff(token);
        token = strtok(NULL, ";");
        reser.codQuarto = atoff(token);
        token = strtok(NULL, ";");
        reser.inicio.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.inicio.ano = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.dia = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.mes = atoi(token);
        token = strtok(NULL, ";");
        reser.fim.ano = atoi(token);

        encontrado_txt = 0;
        
        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_txt, 0, SEEK_SET);

        while(fgets(linha_aco, sizeof(acomodacao), acomo_txt)) {
            // passa os dados do txt pra variavel para facilitar comparação
            token = strtok(linha_aco, ";");
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

            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_bin = 1;
                            livres++;
                            
                            if (encontrado_bin == 1) {
                                if (salva_cod != acomod.codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                                    salva_cod = acomod.codigo;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_txt);

    fclose(rese_txt);
    
    //parte memoria
    //verifica no binario
    acomo_bin = fopen("acomodacoes.bin", "rb");
    if (acomo_bin == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    for (tam_point_reserv = 1; tam_point_reserv < GLOBAL_tam_pont_dados_reservas; tam_point_reserv++) {
        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        if (GLOBAL_dados_reservas->delet == 0) {
            while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
                if (acomod.delet == 0) {
                    if (GLOBAL_dados_reservas->codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, GLOBAL_dados_reservas->codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_mem = 1;
                            livres++;

                            if (encontrado_mem == 1) {
                                if (salva_cod != acomod.codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                                    salva_cod = acomod.codigo;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //avança ponteiro uma posição
        GLOBAL_dados_reservas++;
    }
    //retorna ponteiro posição inicial
    GLOBAL_dados_reservas -= (tam_point_reserv - 1);
    
    fclose(acomo_bin);
    
    acomo_txt = fopen("acomodacoes.txt", "r");
    if (acomo_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    //verifica no txt
    for (tam_point_reserv = 1; tam_point_reserv < GLOBAL_tam_pont_dados_reservas; tam_point_reserv++) {
        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_txt, 0, SEEK_SET);
        
        while(fgets(linha_aco, sizeof(acomodacao), acomo_txt)) {
            // passa os dados do txt pra variavel para facilitar comparação
            token = strtok(linha_aco, ";");
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

            if (GLOBAL_dados_reservas->delet == 0) {
                if (acomod.delet == 0) {
                    if (GLOBAL_dados_reservas->codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, GLOBAL_dados_reservas->codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_mem = 1;
                            livres++;
                            
                            if (encontrado_mem == 1) {
                                if (salva_cod != acomod.codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                                    salva_cod = acomod.codigo;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //avança ponteiro uma posição
        GLOBAL_dados_reservas++;
    }
    //retorna ponteiro posição inicial
    GLOBAL_dados_reservas -= (tam_point_reserv - 1);
    
    fclose(acomo_txt);
    
    //verifica na memória
    for (tam_point_reserv = 1; tam_point_reserv < GLOBAL_tam_pont_dados_reservas; tam_point_reserv++) {
        if (GLOBAL_dados_reservas->delet == 0) {
            for (tam_point_acomod = 1; tam_point_acomod < GLOBAL_tam_pont_dados_acomodacao; tam_point_acomod++) {
                if (GLOBAL_dados_acomodacao->delet == 0) {
                    if (GLOBAL_dados_reservas->codQuarto == GLOBAL_dados_acomodacao->codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, GLOBAL_dados_reservas->codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1) {
                            encontrado_mem = 1;
                            livres++;

                            if (encontrado_mem == 1) {
                                if (salva_cod != GLOBAL_dados_acomodacao->codigo) {
                                    printf("Código do quarto: %0.0f \nDescrição: %s \nFacilidades: %s \nCódigo do tipo da acomodação: %0.0f \nDescrição do tipo de acomodação: %s \nQuantia de pessoas que comporta: %d \nValor da diária: R$%0.2f \n", GLOBAL_dados_acomodacao->codigo, GLOBAL_dados_acomodacao->descri, GLOBAL_dados_acomodacao->facilidades, GLOBAL_dados_acomodacao->tipo.codigo, GLOBAL_dados_acomodacao->tipo.descri, GLOBAL_dados_acomodacao->tipo.qnt_pessoas, GLOBAL_dados_acomodacao->tipo.diaria);
                                    salva_cod = GLOBAL_dados_acomodacao->codigo;
                                }
                            }
                        }
                    }
                }
                
                //avança ponteiro uma posição
                GLOBAL_dados_acomodacao++;
            }
            
            //retorna ponteiro posição inicial
            GLOBAL_dados_acomodacao -= (tam_point_acomod - 1); 
        }
        
        //avança ponteiro uma posição
        GLOBAL_dados_reservas++;
    }
    //retorna ponteiro posição inicial
    GLOBAL_dados_reservas -= (tam_point_reserv - 1);
    
    getchar();
    
    if (livres == 0) {
        printf("Não há quartos vagos nessa data!\n");
    }
}

void pesquisa_reserva_porTudo(reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao){
    FILE *arquivo1, *arquivo2;
    acomodacao acomod;
    reserva reser;

    data inicio, fim;
    float codigoCategoria;
    char facilidade[100];
    int quantidade, encontrado = 0, encontrado1 = 0, encontrado2 = 0, encontrado3 = 0;
    int tam = 0;
    
    char linhaReser[(sizeof(reserva))], *token;
    char linhaAcomod[(sizeof(acomodacao))];

    printf("Digite o código da categoria de acomodação que deseja filtrar: ");
    scanf("%f", &codigoCategoria);

    printf("Digite o número de pessoas: ");
    scanf("%d", &quantidade);

    printf("Digite a facilidade a ser pesquisada: \n");
    scanf("%s", facilidade);

    printf("Data Inicial: \n");
    inicio = le_dados_data();
    printf("Data Final: \n");
    fim = le_dados_data();

    arquivo1 = fopen("acomodacoes.bin", "rb");
    arquivo2 = fopen("reservas.bin", "rb");

    if(arquivo1 == NULL){
        printf("\nErro ao abrir arquivo de acomodações!");
        exit(1);
    }

    if(arquivo2 == NULL){
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    //Lendo acomodações(quartos) binários e comparando com as reservas binárias, txts e memória respectivamente 
    while (fread(&acomod, sizeof(acomodacao), 1 ,arquivo1)){
        
        encontrado1 = 0;
        if(acomod.delet == 0 && acomod.codigo == codigoCategoria && acomod.tipo.qnt_pessoas == quantidade){
            if(strstr(acomod.facilidades, facilidade) != NULL){
                fseek(arquivo2, 0, SEEK_SET);
                while (fread(&reser, sizeof(reserva), 1, arquivo2)){
                    tam++;
                    if(reser.delet == 0){
                        if(valida_data(inicio,fim,reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1){
                            //Encontrado 1 verifica se o quarto binario ja foi encontrado
                            encontrado1 = 1;
                        } else
                            break;
                    }
                }
                
                fclose(arquivo2);
                arquivo2 = fopen("reservas.txt","r");

                if(arquivo2 == NULL){
                    printf("\nErro ao abrir arquivo de reservas!");
                    exit(1);
                }
                
                while (fgets(linhaReser, sizeof(reserva), arquivo2)){
                    // passa os dados do txt pra variavel para facilitar comparação
                    token = strtok(linhaReser, ";");
                    reser.delet = atoi(token);
                    token = strtok(NULL, ";");
                    reser.codigo = atoff(token);
                    token = strtok(NULL, ";");
                    reser.codQuarto = atoff(token);
                    
                    if(reser.delet == 0){
                        if(valida_data(inicio,fim,reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1){
                            encontrado1++;
                        }else
                            break;
                    }
                }
                fclose(arquivo2);
                
                //Memória
                //Caso tenha alguma reserva cadastrada em memoria:
                if(GLOBAL_tam_pont_dados_reservas > 1){
                    int j;
                    for(j = 1; j < GLOBAL_tam_pont_dados_reservas; j++) {
                        if(GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_acomodacao->codigo == GLOBAL_dados_reservas->codQuarto){
                            encontrado1++;
                        }
                        //aumenta o valor do ponteiro
                        GLOBAL_dados_reservas++;
                    }
                    
                    GLOBAL_dados_reservas -= (j - 1);
                } else
                    encontrado1++;
                                
                if(encontrado1 == 3){
                    encontrado = 1;
                    printf("\nQuarto %.0f", acomod.codigo);
                }
            }
        }
    }
    fclose(arquivo1);

    //Lendo acomodações(quartos) TXTs e comparando com as reservas binárias, txts e memória respectivamente 

    arquivo1 = fopen("acomodacoes.txt", "r");
    arquivo2 = fopen("reservas.bin", "rb");

    if(arquivo1 == NULL){
        printf("\nErro ao abrir arquivo de acomodações!");
        exit(1);
    }

    if(arquivo2 == NULL){
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    while (fgets(linhaAcomod, sizeof(acomodacao), arquivo1)){
        encontrado2 = 0;
        // passa os dados do txt pra variavel para facilitar comparação
        token = strtok(linhaAcomod, ";");
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

        //Verifica se o quarto entra nas exigências de pesquisa
       if(acomod.delet == 0 && acomod.codigo == codigoCategoria && acomod.tipo.qnt_pessoas == quantidade){
            if(strstr(acomod.facilidades, facilidade) != NULL){
                
                //Começa a comparar a data nas reservas
                //Binária

                fseek(arquivo2, 0, SEEK_SET);
                while (fread(&reser, sizeof(reserva), 1, arquivo2)){
                    if(reser.delet == 0){
                        if(valida_data(inicio,fim,reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1){
                            encontrado2 = 1;
                        }
                    }
                }
                fclose(arquivo2);
                arquivo2 = fopen("reservas.txt","r");

                if(arquivo2 == NULL){
                    printf("\nErro ao abrir arquivo de reservas!");
                    exit(1);
                }
                
                //TXT
                while (fgets(linhaReser, sizeof(reserva), arquivo2)){
                    // passa os dados do txt pra variavel para facilitar comparação
                    token = strtok(linhaReser, ";");
                    reser.delet = atoi(token);
                    token = strtok(NULL, ";");
                    reser.codigo = atoff(token);
                    token = strtok(NULL, ";");
                    reser.codQuarto = atoff(token);
                    
                    if(reser.delet == 0){
                        if(valida_data(inicio,fim,reser.codQuarto, GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas) == 1){
                            encontrado2++;
                            if(encontrado2 == 2){
                                printf("\n\nCódigo do quarto: %0.0f \n\tDescrição: %s \n\tFacilidades: %s \n\tCódigo do tipo da acomodação: %0.0f \n\tDescrição do tipo de acomodação: %s \n\tQuantia de pessoas que comporta: %d \n\tValor da diária: R$%0.2f \n", 
                                acomod.codigo, acomod.descri, acomod.facilidades, acomod.tipo.codigo, acomod.tipo.descri, acomod.tipo.qnt_pessoas, acomod.tipo.diaria);
                            }
                        }
                    }
                }
                fclose(arquivo2);

                //Memória
                //Caso tenha alguma reserva cadastrada em memoria:
                if(GLOBAL_tam_pont_dados_reservas > 1){
                    int j;
                    for(j = 1; j < GLOBAL_tam_pont_dados_reservas; j++) {
                        if(GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_acomodacao->codigo == GLOBAL_dados_reservas->codQuarto){
                            encontrado2++;
                        }
                        //aumenta o valor do ponteiro
                        GLOBAL_dados_reservas++;
                    }
                    
                    GLOBAL_dados_reservas -= (j - 1);
                } else
                    encontrado2++;
                                
                if(encontrado2 == 3){
                    encontrado++;
                    printf("\nQuarto %.0f", acomod.codigo);
                }
            }
        }
    }
    fclose(arquivo1);

    //Lendo acomodações(quartos) em memória e comparando com as em memória, já que não é possível criar reservas em bin ou txt para quartos em memória
    
    encontrado3 = 0;
    int i;
    for(i = 1; i < GLOBAL_tam_pont_dados_acomodacao; i++) {        
        if(GLOBAL_dados_acomodacao->delet == 0){
            if(GLOBAL_dados_acomodacao->tipo.codigo == codigoCategoria && GLOBAL_dados_acomodacao->tipo.qnt_pessoas == quantidade && strstr(GLOBAL_dados_acomodacao->facilidades, facilidade) != NULL){

            //Só é possível fazer uma reserva em mémoria quando a acomodação está salva em memória, logo não é necessário buscar nos arquivos bin e txt.
            //reserva memoria
            int j;
            for(j = 1; j < GLOBAL_tam_pont_dados_reservas; j++) {
                if(GLOBAL_dados_reservas->delet == 0 && GLOBAL_dados_reservas->codQuarto == GLOBAL_dados_acomodacao->codigo){
                    if(valida_data(inicio,fim,GLOBAL_dados_reservas->codQuarto,GLOBAL_dados_reservas,GLOBAL_tam_pont_dados_reservas) == 0){
                        encontrado3 = 1;
                    }
                }
                //aumenta o valor do ponteiro
                GLOBAL_dados_reservas++;
            }
            if(encontrado3 == 0){
                encontrado++;
                printf("\nQuarto %.0f ", GLOBAL_dados_acomodacao->codigo);
            }
            GLOBAL_dados_reservas -= (j - 1);
        }
    }  
        //aumenta o valor do ponteiro
        GLOBAL_dados_acomodacao++;
    }
    GLOBAL_dados_acomodacao-= i - 1;
    
    if(encontrado == 0)
        printf("\nNenhum quarto encontrado com essas informações!");
}