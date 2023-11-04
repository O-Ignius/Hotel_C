#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

hotel le_dados_hotel() {
    // variaveis
    hotel dados;

    //coleta de dados
    printf("////////// Cadastre seu HOTEL \\\\\\\\\\");
    
    setbuf(stdin, NULL);
    printf("\n\nDigite o nome do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome_hot);
    setbuf(stdin, NULL);
    printf("Digite a razão social: \n");
    scanf("%[a-z A-Z][^\n]s", dados.raz_soci);
    setbuf(stdin, NULL);
    printf("Digite a inscrição estadual do hotel: \n");
    scanf("%[^\n]s", dados.inscri_estad);
    setbuf(stdin, NULL);
    printf("Digite o CNPJ do hotel: \n");
    scanf("%[0-9.-][^\n]s", dados.cnpj);
    setbuf(stdin, NULL);
    printf("Digite o email do hotel: \n");
    scanf("%s", dados.email);
    setbuf(stdin, NULL);
    printf("Digite o número de telefone do hotel: \n");
    scanf("%f", &dados.telefone_hot);
    setbuf(stdin, NULL);
    printf("Digite a sigla do estado em que se encontra o hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.estado);
    setbuf(stdin, NULL);
    printf("Digite a cidade do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.cidade);
    setbuf(stdin, NULL);
    printf("Digite o CEP da cidade do hotel: \n");
    scanf("%f", &dados.local.cep);
    setbuf(stdin, NULL);
    printf("Digite o bairro do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);
    setbuf(stdin, NULL);
    printf("Digite a rua do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.rua);
    setbuf(stdin, NULL);
    printf("Digite o número do hotel: \n");
    scanf("%f", &dados.local.numero);
    setbuf(stdin, NULL);
    printf("Digite o nome do gerente do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome_respo);
    setbuf(stdin, NULL);
    printf("Digite o telefone do gerente do hotel: \n");
    scanf("%f", &dados.telefone_respo);
    setbuf(stdin, NULL);
    printf("Digite o horario de check-in do hotel: \n");
    printf("horas: ");
    scanf("%d", &dados.in.hora);
    setbuf(stdin, NULL);
    printf("\nminutos: ");
    scanf("%d", &dados.in.min);
    setbuf(stdin, NULL);
    printf("Digite o horario de check-out do hotel: \n");
    printf("horas: ");
    scanf("%d", &dados.out.hora);
    setbuf(stdin, NULL);
    printf("\nminutos: ");
    scanf("%d", &dados.out.min);
    setbuf(stdin, NULL);
    printf("Digite a margem de lucro dos produtos vendidos pelo hotel: ");
    scanf("%f", &dados.lucro);
    dados.delet = 0;
    return dados;
}

void menuHotel(int tipoArquivo, hotel *GLOBAL_dados_hotel) {
    int opcao = 0;
    hotel dados;
    while (opcao != 5) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tListar dados do Hotel - 1\n");
        printf("\tAlterar dados do Hotel - 2\n");
        printf("\tExcluir dados do Hotel - 3\n");
        printf("\tSalvar dados do Hotel - 4\n");
        printf("\tVoltar ao menu inicial - 5\n");

        printf("Opc�o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                le_cadastro_hotel();
                break;
            case 2:
                exclui_hotel();
                dados = le_dados_hotel();
                salva_cadastro_hotel(dados);
                break;
            case 3:
                exclui_hotel();
                break;
            case 4:
                if (verifica_Hotel() == 0) {
                    dados = le_dados_hotel();
                    salva_cadastro_hotel(dados);
                } else {
                    printf("Hotel já cadastrado! Exclua o atual ou faça alteração.");
                }
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPressione qualquer tecla para continuar... ");
        getchar();
    }
}

int verifica_Hotel() {
    FILE *salva;
    hotel hotel1;
    int tam = 0;

    salva = fopen("hotel.bin", "rb");

    if (salva == NULL) {
        printf("Erro ao abrir aquivo do hotel!");
        exit(1);
    }
    while (fread(&hotel1, sizeof (hotel), 1, salva)) {
        if (hotel1.delet == 0) {
            tam = 1;
            break;
        }
    }
    fclose(salva);

    return tam;
}

void salva_cadastro_hotel(hotel dados) {
    FILE *salva;

    salva = fopen("hotel.bin", "ab");

    //Salvando em binário
    fwrite(&dados, sizeof (hotel), 1, salva);
    fclose(salva);

    //Salvando em txt

    int end, hot, chek;

    //      abrir arquivo
    fclose(salva);

    salva = fopen("hotel.txt", "a");

    if (salva == NULL) {

        printf("\n\t!! Erro de salvamento de Cadasto !! \n");

        exit(1);
    }

    //      Escrever no arquivo

    hot = fprintf(salva, "%d;%s;%s;%s;%s;%s;%0.0f;%s;%0.0f;%0.0f;", dados.delet, dados.nome_hot, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone_hot, dados.nome_respo, dados.telefone_respo, dados.lucro);

    if (hot < 0) {
        printf("!! Erro em salvar os dados do hotel!!");
        exit(1);
    } else {
        printf("Dados do hotel salvos com sucesso!\n");
    }

    //      Endereço

    end = fprintf(salva, "%0.0f;%s;%s;%s;%0.0f;", dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);

    if (end < 0) {
        printf("!! Erro em salvar o endereço do hotel !!");
        exit(1);
    } else {
        printf("Endereço salvo com sucesso!\n");
    }

    chek = fprintf(salva, "%d;%d;%d;%d;\n", dados.in.hora, dados.in.min, dados.out.hora, dados.out.min);

    if (chek < 0) {
        printf("!! Erro em salvar os dados de check-in e check-out do hotel !!");
        exit(1);
    } else {
        printf("Check-in e check-out salvos com sucesso!\n");
    }

    //      Fechar arquivo
    fclose(salva);
}

void le_cadastro_hotel() {
    FILE *le;
    hotel dados;

    le = fopen("hotel.bin", "rb");

    while (fread(&dados, sizeof (hotel), 1, le)) {
        if (dados.delet == 0) {
            printf("\nNome: %s\n\tRazão Social: %s\n\tInscrição Estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone do Hotel: %.0f\n\tGerente: %s\n\tTelefone do Gerente: %.0f\n\tPorcentagem de lucro do hotel: %.2f%%\n\tCep: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero do hotel: %.0f\n\tCheck-in: %d:%d\n\tCheck-out: %d:%d",
                    dados.nome_hot, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone_hot,
                    dados.nome_respo, dados.telefone_respo, dados.lucro, dados.local.cep, dados.local.cidade,
                    dados.local.bairro, dados.local.rua, dados.local.numero, dados.in.hora, dados.in.min, dados.out.hora, dados.out.min);
        }
    }
}

void exclui_hotel() {
    FILE *deletar, *altera;
    hotel dados;
    int hot, end, chek;
    char linha[sizeof (hotel)], *token;

    //BIN

    deletar = fopen("hotel.bin", "rb+wb");

    if (deletar == NULL) {
        printf("Erro na abertura do arquivo hotel!\n");
        exit(1);
    }

    while (fread(&dados, sizeof (hotel), 1, deletar)) {
        if (dados.delet == 0) {
            dados.delet = 1;
            fseek(deletar, -sizeof (hotel), SEEK_CUR);
            fwrite(&dados, sizeof (hotel), 1, deletar);
            printf("Hotel excluido com sucesso!");
        }
    }
    fclose(deletar);

    //TXT
    deletar = fopen("hotel.txt", "r");

    altera = fopen("temp.txt", "a");
    if (altera == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }

    // lê linha a linha do arquivo, armazenando os dados antigos, fazendo exclusão lógica
    while (fgets(linha, sizeof (hotel), deletar) != NULL) {
        // exclui logicamente os dados
        dados.delet = 1;
        //pega cada dado e adiciona a um campo da struct o transformando para o tipo do dado
        token = strtok(linha, ";");
        strcpy(dados.nome_hot, token);
        token = strtok(NULL, ";");
        strcpy(dados.raz_soci, token);
        token = strtok(NULL, ";");
        strcpy(dados.inscri_estad, token);
        token = strtok(NULL, ";");
        strcpy(dados.cnpj, token);
        token = strtok(NULL, ";");
        strcpy(dados.email, token);
        token = strtok(NULL, ";");
        dados.telefone_hot = atoff(token);
        token = strtok(NULL, ";");
        strcpy(dados.nome_respo, token);
        token = strtok(NULL, ";");
        dados.telefone_respo = atoff(token);
        token = strtok(NULL, ";");
        dados.lucro = atoff(token);
        token = strtok(NULL, ";");
        dados.local.cep = atoff(token);
        token = strtok(NULL, ";");
        strcpy(dados.local.cidade, token);
        token = strtok(NULL, ";");
        strcpy(dados.local.bairro, token);
        token = strtok(NULL, ";");
        strcpy(dados.local.rua, token);
        token = strtok(NULL, ";");
        dados.local.numero = atoff(token);
        token = strtok(NULL, ";");
        dados.in.hora = atoi(token);
        token = strtok(NULL, ";");
        dados.in.min = atoi(token);
        token = strtok(NULL, ";");
        dados.out.hora = atoi(token);
        token = strtok(NULL, ";");
        dados.out.hora = atoi(token);

        // salva os dados antigos com exclusão lógica
        hot = fprintf(altera, "%d;%s;%s;%s;%s;%s;%0.0f;%s;%0.0f;%0.0f;", dados.delet, dados.nome_hot, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone_hot, dados.nome_respo, dados.telefone_respo, dados.lucro);

        if (hot < 0) {

            printf("!! Erro em salvar os dados do hotel!!");

            exit(1);
        }

        //      Endereço

        end = fprintf(altera, "%0.0f;%s;%s;%s;%0.0f;", dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);

        if (end < 0) {

            printf("!! Erro em salvar o endereço do hotel !!");

            exit(1);
        }

        chek = fprintf(altera, "%d;%d;%d;%d;\n", dados.in.hora, dados.in.min, dados.out.hora, dados.out.min);

        if (chek < 0) {

            printf("!! Erro em salvar os dados de check-in e check-out do hotel !!");

            exit(1);
        }
    }

    fclose(altera);
    fclose(deletar);

    //remove arquivo antigo
    remove("hotel.txt");
    //renomeia o arquivo temporário
    rename("temp.txt", "hotel.txt");
    
}
