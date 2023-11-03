#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

// -------------- Var Globais --------------
int GLOBAL_tam_pont_dados_reservas = 1; //ja usado!

int tam_reserva() {
    int tamanho = 0;
    
    tamanho = sizeof(reserva) - sizeof(float);
    
    return tamanho;
}

data le_dados_data() {
    data dados;

    printf("\nDigite o dia(1-30): ");
    scanf("%d", &dados.dia);

    while (dados.dia <= 0 || dados.dia >= 31) {
        printf("\nDia inválido, digite outro no intervalo de 1 a 30: ");
        scanf("%d", &dados.dia);
    }

    printf("Digite o mes(1-12): ");
    scanf("%d", &dados.mes);

    while (dados.mes <= 0 || dados.mes >= 13) {
        printf("\nMes inválido, digite outro no intervalo de 1 a 12: ");
        scanf("%d", &dados.mes);
    }

    printf("Digite o ano(2023 - 2024 - 2025...)");
    scanf("%d", &dados.ano);

    while (dados.ano <= 2022) {
        printf("\nAno inválido, digite outro: ");
        scanf("%d", &dados.ano);
    }

    return dados;
}

reserva le_dados_reserva() {
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

    return dados;
}

void menuReserva(int tipoArquivo, reserva *GLOBAL_dados_reservas) {
    reserva dados;
    int opcao = 99;

    while (opcao != 6) {
        system("clear");
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
                dados = le_dados_reserva();
                if (tipoArquivo == 0) {
                    salva_cadastro_reserva_bin(dados);
                } else {
                    salva_cadastro_reserva_txt(dados);
                }
                break;
            case 2:
                le_todas_reservas();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                pesquisa_reserva();
            case 6:
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPRESSIONE QUALQUER TECLA PARA CONTINUAR...");
        getchar();
    }
}

//Menu de pesquisa
void pesquisa_reserva() {

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
            pesquisa_reserva_data();
            break;
        case 2:
            pesquisa_reserva_Categoria();
            break;
        case 3:
            pesquisa_reserva_quantPessoas();
            break;
        case 4:
            pesquisa_reserva_facilidade();
            break;
        case 5:
            break;
        default :
            printf("Opção inválida!\n");
            break;
    }
    getchar();
}

//Reserva

void salva_cadastro_reserva_bin(reserva dados) {
    FILE *arquivo;

    arquivo = fopen("reservas.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de reservas!");
        exit(1);
    }

    if (valida_data(dados.inicio, dados.fim, dados.codQuarto) == 1) {
        fwrite(&dados, sizeof (reserva), 1, arquivo);
        printf("\nReserva cadastrada com sucesso!");
    } else {
        printf("\nData inválida!");
    }
    fclose(arquivo);
}

void salva_cadastro_reserva_txt(reserva dados) {
    FILE *txt;
    int salva;
    
    
    if (valida_data(dados.inicio, dados.fim, dados.codQuarto) == 1) {
        if (valida_id_acomodacao(dados.codQuarto) == 1) {
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

int valida_data(data inicio, data fim, float id) {
    FILE *arquivo;
    reserva dados;
    int valido = 1;
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
                            if (((dados.inicio.dia >= inicio.dia) && (dados.inicio.dia <= fim.dia)) || ((dados.fim.dia >= inicio.dia) && (dados.fim.dia <= fim.dia)) || (dados.inicio.dia == inicio.dia && dados.fim.dia == fim.dia)) {
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
    
    return valido;
}

int valida_id_acomodacao(float id) {
    FILE *txt, *bin;
    acomodacao dados;
    int valido = 0;
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

        while(fgets(linha, sizeof(acomodacao), txt) != NULL) {
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
    
    return valido;
}

void le_todas_reservas() {
    FILE *txt, *bin;
    reserva dados;
    char linha[(sizeof(reserva))], *token;
    
    bin = fopen("reservas.bin", "rb");
    if (bin == NULL) {
        printf("Erro de leitura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    while(fread(&dados, sizeof(reserva), 1, bin)) {
        if (dados.delet == 0) {
            printf("Código da reserva: %0.0f \nCódigo do quarto: %0.0f \nData Inicial: %d/%d/%d \nData Final: %d/%d/%d\n\n", dados.codigo, dados.codQuarto, dados.inicio.dia, dados.inicio.mes, dados.inicio.ano, dados.fim.dia, dados.fim.mes, dados.fim.ano);
        }
    }
    
    fclose(bin);
    
    txt = fopen("reservas.txt", "r");
    if (txt == NULL) {
        printf("Erro de leitura de arquivo reservas.txt!\n");
        exit(1);
    }
    
    while(fgets(linha, sizeof(reserva), txt) != NULL) {
        token = strtok(linha, ";");
        
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            printf("Código da reserva: %s\n", token);
            token = strtok(NULL, ";");
            printf("Código do quarto: %s\n", token);
            token = strtok(NULL, ";");
            printf("Data inicial: %s/", token);
            token = strtok(NULL, ";");
            printf("%s/", token);
            token = strtok(NULL, ";");
            printf("%s\n", token);
            token = strtok(NULL, ";");
            printf("Data final: %s/", token);
            token = strtok(NULL, ";");
            printf("%s/", token);
            token = strtok(NULL, ";");
            printf("%s\n\n", token);
        }
    }
    
    fclose(txt);
    getchar();
}

void exclui_reservas() {
    FILE *txt, *bin, *altera;
    reserva dados;
    float codigo;
    int encontrado = 0;
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

        while(fgets(linha, sizeof(reserva), txt) != NULL) {
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
        }

        fclose(txt);
        fclose(altera);
        
        remove("reservas.txt");
        rename("temp.txt", "reservas.txt");
    }
    
    if (encontrado == 0) {
        printf("Reserva não encontrada!\n");
    } else {
        printf("Dados Alterados com sucesso!\n");
    }
}

void pesquisa_reserva_quantPessoas(){
    FILE *arquivo1, *arquivo2;
    int quant, encontrado = 0, encontrado1 = 0, encontrado2 = 0, encontrado3 = 0, encontrado4 = 0;
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

    //Lendo acomodações(quartos) binários e comparando com as reservas binárias e txts respectivamente 
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
            if(encontrado1 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
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
            if(encontrado2 == 0){
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
                    encontrado3 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            if(encontrado3 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
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
                    encontrado4 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            if(encontrado4 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
            }
            fclose(arquivo2);
        }
    }
    fclose(arquivo1);

    if(encontrado == 0){
        printf("\nNenhum quarto para %d pessoa(s) encontrado!", quant);
    } else 
        printf("\nForam encontrados %d quarto(s)!", encontrado);
}

void pesquisa_reserva_Categoria() {
    FILE *arquivo1, *arquivo2;
    int cate, encontrado = 0, encontrado1 = 0, encontrado2 = 0, encontrado3 = 0, encontrado4 = 0;
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
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            if(encontrado1 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
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
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            if(encontrado2 == 0){
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
        //Recebe os dados de delet, código da acomodação
        token = strtok(linha, ";");
        acomod.delet = atoi(token);
        token = strtok(NULL, ";");
        acomod.codigo = atoff(token);

        if(acomod.delet == 0 && acomod.tipo.codigo == cate){
            //Reservas BIN
            while (fread(&reser, sizeof(reserva), 1 ,arquivo2)){
                if(reser.delet == 0 && acomod.codigo == reser.codQuarto){
                    encontrado3 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            if(encontrado3 == 0){
                printf("\nQuarto %.0f sem reservas cadastradas!", acomod.codigo);
                encontrado++;
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
                    encontrado4 = 1;
                    encontrado++;
                    printf("\nQuarto %.0f ocupado de: %d/%d/%d a %d/%d/%d!", 
                        acomod.codigo, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                }
            }
            if(encontrado4 == 0){
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

void pesquisa_reserva_facilidade() {
    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    float salva_cod = -1;
    int encontrado_bin = 0, encontrado_txt = 0;
    char linha_rese[(sizeof(reserva))], linha_aco[(sizeof(acomodacao))], *token, facilidade[100];
    
    printf("Digite a facilidade a ser pesquisada: \n");
    scanf("%s", facilidade);

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
}

//ok
void pesquisa_reserva_data() {
    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    data inicio, fim;
    float salva_cod = -1;
    int encontrado_bin = 0, encontrado_txt = 0, livres = 0;;
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
        
        while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, reser.codQuarto) == 1) {
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
                        if (valida_data(inicio, fim, reser.codQuarto) == 1) {
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

        while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se a data é valida, caso ela seja
                        if (valida_data(inicio, fim, reser.codQuarto) == 1) {
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
                        if (valida_data(inicio, fim, reser.codQuarto) == 1) {
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
    
    getchar();
    
    if (livres == 0) {
        printf("Não há quartos vagos nessa data!\n");
    }
}

/*
void pesquisa_reserva_porTudo(){
    FILE *ArquivoAcomoda, *ArquivoReser;
    acomodacao acomod;
    reserva reser;

    float codigoCategoria;
    char facilidade[100];
    int quantidade, encontrado = 0;
    data inicio, fim; 

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

    ArquivoAcomoda = fopen("acomodacoes.bin","rb");
    ArquivoReser = fopen("reservas.bin","rb");

    if (ArquivoAcomoda == NULL) {
        printf("Erro ao abrir acomod de acomodações!");
        exit(1);
    }

    
        
        while(fread(&reser, sizeof(reserva), 1, ArquivoReser)) {
        encontrado = 0;

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        
        while(fread(&acomod, sizeof(acomodacao), 1, ArquivoAcomoda)) {
            if (reser.delet == 0) {
                if (acomod.delet == 0) {
                    if (reser.codQuarto == acomod.codigo) {
                        // compara se dentro da string facilidade do quarto há a facilidade escrita pela pessoa (pode dar erro por diferenciar maiuscula e minuscula, a ordem importa caso hajá mais de 1 palavra)
                        if (strstr(acomod.facilidades, facilidade) != NULL) {
                            encontrado = 1;
                            
                            if (encontrado == 1) {
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
            if (acomod.delet == 0 && acomod.tipo.codigo == codigoCategoria && acomod.tipo.qnt_pessoas == quantidade) {
                printf("\nCódigo quarto: %.0f\n\tDescrição: %s\n\tFacilidades: %s",
                        acomod.codigo, acomod.descri, acomod.facilidades);
                printf("\nTipo da acomodação:");
                le_tipo_acomodacao(acomod.tipo.codigo);
                encontrado = 1;
            }
        }
    }

        
    }
*/