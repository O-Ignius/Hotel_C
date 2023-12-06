#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\

//Verifica se já foi realizado check-in para aquela reserva
int verificaCheckIn(float codReserva, checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks){
    FILE *arquivo;
    int existe = 0;
    checkInOut dados;

    arquivo = fopen("checkInOut.bin", "rb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo de Check-in bin");
        exit(1);
    }

    while (fread(&dados, sizeof(checkInOut), 1, arquivo)){
        if(dados.delet == 0){
            if(dados.codigoReserva == codReserva){
                existe = 1;
                break;
            }
        }
    }
    
    fclose(arquivo);

    if(existe == 0){
        arquivo = fopen("checkInOut.txt", "r");

        if(arquivo == NULL){
            printf("Erro ao abrir arquivo de Check-in txt");
            exit(1);
        }

        char linha[(sizeof(checkInOut))], *token;
        while (fgets(linha, sizeof(checkInOut), arquivo)){
            token = strtok(linha, ";");
            //atoi passa string para int 
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            //atoff passa string para float
            dados.codigoReserva = atoff(token);
            token = strtok(NULL, ";");
            dados.consumoHospede = atoff(token);
            token = strtok(NULL, ";");
            dados.DiariasPagas = atoi(token);
            token = strtok(NULL, ";");
            dados.valorDiarias = atoff(token);

            if(dados.delet == 0){
                if(dados.codigoReserva == codReserva){
                    existe = 1;
                    break;
                }
            }
        }
        
        fclose(arquivo);
    }

    if(existe == 0){
        if(GLOBAL_dados_checkInOut != NULL){
            int i;
            for(i = 1; i < GLOBAL_tam_pont_dados_checks; i++){
                if(GLOBAL_dados_checkInOut->delet == 0){
                    if(GLOBAL_dados_checkInOut->codigoReserva == codReserva){
                        existe = 1;
                        break;
                    }
                }
                //Aritimetica para passar para a próxima posição do ponteiro
                GLOBAL_dados_checkInOut++;
            }
            //Retorna o ponteiro para a posição inicial
            GLOBAL_dados_checkInOut -= (i -1);
        }
    }
    return existe;
}

int verificaHospede(float codigo, cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente){
    FILE *arquivoBin, *arquivoTxt;
    cad_clie cliente;
    int tam_point = 0;
    int encontrado = 0;

    //      abrir arquivo
    arquivoBin = fopen("cliente.bin", "rb");
    arquivoTxt = fopen("cliente.txt", "r");

    if (arquivoBin == NULL || arquivoTxt == NULL) {
        printf("\n\t!! Erro de leitura do Cadastro !! \n");
        exit(1);
    }

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.codigo == codigo && cliente.delet == 0) {
            encontrado = 1;
            break;
        }
    }
    if (encontrado == 0) {

        char linha[(sizeof (cad_clie))], *token, cod[10];
        //Passa o cod de float para string
        sprintf(cod, "%.0f", codigo);

        while (fgets(linha, sizeof (cad_clie), arquivoTxt)) {
            // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
            token = strtok(linha, ";");
            // compara e caso o arquivo não tenha sido excluido ele verifica se o código escrito pela pessoa realmente existe
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                if (strcmp(cod, token) == 0) {
                    encontrado = 1;
                    break;
                }
            }
        }
    }
    fclose(arquivoBin);
    fclose(arquivoTxt);

    if (encontrado == 0) {
        for (tam_point = 1; tam_point < GLOBAL_tam_pont_dados_cliente; tam_point++) {
            if (GLOBAL_dados_cliente->delet == 0) {
                if (GLOBAL_dados_cliente->codigo == codigo) {
                    //caso seja achado, quebra o loop finito
                    encontrado = 1;
                    break;
                }
            }
            //pula o ponteiro para a próxima posição;
            GLOBAL_dados_cliente += 1;
        }
        //retorna o ponteiro para a posição inicial do bloco que foi alocado
        GLOBAL_dados_cliente -= (tam_point - 1);
    }
    
    if (encontrado == 0) {
        printf("Cliente não encontrado!");
    }
    return encontrado;
}

void pagamentoCheck(int BinOuTxt, checkInOut dados){
    contaHotel dadosConta;
    CaixaHotel dadosCaixa;
    
    dadosCaixa = verificaCaixa();
    
    printf("\nTotal a ser pago: %.2f", dados.consumoHospede);

    dadosConta = retornaVenda(dados.consumoHospede);
    if(dadosConta.tipo == 0){
        dadosCaixa.valorEmCaixa += dados.consumoHospede; 
    } else {
        dadosCaixa.contasAReceber += dados.consumoHospede;
    }

    //Salva nos três tipos de memória
    adicionaCaixa(dadosCaixa);

    if(BinOuTxt == 0)
        adicionaContas_Bin(dadosConta);
        else if(BinOuTxt == 1)
            adicionaContas_Txt(dadosConta);

    printf("Pagamento realizado com sucesso!");
}

//Realiza o checkOut
void checkOut(int binOuTxt){
    FILE *arquivo;
    int encontrado = 0;
    checkInOut dados;
    float codReserva;

    printf("Digite o código da reserva que deseja buscar: ");
    scanf("%f", &codReserva);

    arquivo = fopen("checkInOut.bin", "rb + wb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo de Check-in bin");
        exit(1);
    }

    while (fread(&dados, sizeof(checkInOut), 1, arquivo)){
        if(dados.delet == 0){
            if(dados.codigoReserva == codReserva){
                encontrado = 1;
                pagamentoCheck(binOuTxt, dados);
                dados.delet = 1;
                fseek(arquivo, -sizeof(checkInOut), 1);
                fwrite(&dados, sizeof(checkInOut), 1, arquivo);
                break;
            }
        }
    }
    
    fclose(arquivo);

    if(encontrado == 0){
        FILE *altera;
        arquivo = fopen("checkInOut.txt", "r");

        if(arquivo == NULL){
            printf("Erro ao abrir arquivo de Check-in txt");
            exit(1);
        }

        altera = fopen("checkInOut.txt", "a");

        if(altera == NULL){
            printf("Erro ao abrir arquivo de Check-in txt");
            exit(1);
        }

        char linha[(sizeof(checkInOut))], *token;
        while (fgets(linha, 1, arquivo)){
            token = strtok(linha, ";");
            //atoi passa string para int 
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            //atoff passa string para float
            dados.codigoReserva = atoff(token);
            token = strtok(NULL, ";");
            dados.consumoHospede = atoff(token);
            token = strtok(NULL, ";");
            dados.DiariasPagas = atoi(token);
            token = strtok(NULL, ";");
            dados.valorDiarias = atoff(token);

            //Caso o seja a reserva correta é adicionado o valor do consumo
            if(dados.delet == 0){
                if(dados.codigoReserva == codReserva){
                    pagamentoCheck(binOuTxt, dados);
                    dados.delet = 1;
                    encontrado = 1;
                }
            }
            //Todos os checkIns são passados para um novo arquivo
            int teste = fprintf(altera,"%d;%.0f;%.2f;%d;%.2f",dados.delet, dados.codigoReserva, dados.consumoHospede, dados.DiariasPagas, dados.valorDiarias);

            if(teste < 0)
                printf("\nFalha ao altera consumo!");
            else
                printf("\nConsumo alterado com sucesso!");
        }
        
        fclose(arquivo);
    }

    //Memória
    /*
        if(encontrado == 0){
        if(GLOBAL_dados_checkInOut != NULL){
            int i;
            for(i = 1; i < GLOBAL_tam_pont_dados_checks; i++){
                if(GLOBAL_dados_checkInOut->delet == 0){
                    if(GLOBAL_dados_checkInOut->codigoReserva == codReserva){
                        pagamentoCheck(binOuTxt, dados);
                        GLOBAL_dados_checkInOut->delet = 1;
                        encontrado = 1;
                        break;
                    }
                }
                //Aritimetica para passar para a próxima posição do ponteiro
                GLOBAL_dados_checkInOut++;
            }
            //Retorna o ponteiro para a posição inicial
            GLOBAL_dados_checkInOut -= (i -1);
        }
    }
    */

    if(encontrado == 0){
        printf("Check-in não realizado para essa reserva!");
    }
}

//Leitura de dados
checkInOut le_dados_checkIn(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao, checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks, cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente){
    checkInOut check;
    int erro = 0;

    reserva reser = le_uma_reserva(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas);
    //Caso nenhuma reserva ou acomodação com o código seja encontrada o .delet = 1
    if(reser.delet == 0){
        acomodacao acomod = le_uma_acomodacao(reser.codQuarto, GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_acomodacao);
        if(acomod.delet == 0){
            //Caso o check-in da reserva ainda n tenha sido feito 
            if(verificaCheckIn(reser.codigo,GLOBAL_dados_checkInOut, GLOBAL_tam_pont_dados_checks) == 0){
                check.delet = 0;
                check.codigoReserva = reser.codigo;
                
                printf("Digite o código do cliente: ");
                scanf("%f", &check.codHospede);
                    
                if(verificaHospede(check.codHospede, GLOBAL_dados_cliente, GLOBAL_tam_pont_dados_cliente) == 1){
                    int dias = retornaDias(reser.inicio, reser.fim);

                    check.valorDiarias = dias * acomod.tipo.diaria;

                    printf("\nData inicio: %d/%d/%d\tFim: %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);

                    printf("Dias: %d", dias);

                    printf("\nCusto: R$%.2f", check.valorDiarias);

                    int pagar;
                    printf("\nDeseja realizar o pagamento das diárias? (1 - sim, 2 - não): ");
                    scanf("%d", &pagar);

                    while (pagar != 1 && pagar != 2){
                        printf("\nNúmero inválido! Digite 1 para sim e 2 para não): ");
                        scanf("%d", &pagar);
                    }
                    
                    if(pagar == 1){
                        check.DiariasPagas = 1;
                        check.consumoHospede = 0;
                    } else{
                        check.DiariasPagas = 0;
                        check.consumoHospede = check.valorDiarias;
                    }
                    return check;
                } else
                    erro = 1;

            } else{
                printf("\nCheck-in da reserva %.0f já realizado!", reser.codigo);
                erro = 1;
            }
        }else
            erro = 1;
    } else
        erro = 1;

    if(erro == 1){
        check.delet = 2;
        return check;
    }
}

//Salvamento
void pagamentoDiarias(int BinOuTxt, float valor){
    contaHotel dadosConta;
    CaixaHotel dadosCaixa;
    
    dadosCaixa = verificaCaixa();
    
    printf("\nTotal a ser pago: %.2f", valor);

    dadosConta = retornaVenda(valor);
    if(dadosConta.tipo == 0){
        dadosCaixa.valorEmCaixa += valor; 
    } else {
        dadosCaixa.contasAReceber += valor;
    }

    //Salva nos três tipos de memória
    adicionaCaixa(dadosCaixa);

    if(BinOuTxt == 0)
        adicionaContas_Bin(dadosConta);
        else if(BinOuTxt == 1)
            adicionaContas_Txt(dadosConta);

    printf("Pagamento realizado com sucesso!");
}

void salva_check_bin(checkInOut dados){
    FILE *arquivo;

    arquivo = fopen("checkInOut.bin","ab");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de Check-in!");
        exit(1);
    }

    fwrite(&dados, sizeof(checkInOut), 1, arquivo);

    if(dados.DiariasPagas == 1)
        pagamentoDiarias(0, dados.valorDiarias);
    
    printf("\nCheck-in realizado com sucesso!");

    fclose(arquivo);
}

void salva_check_txt(checkInOut dados){
    FILE *arquivo;
    int teste;

    arquivo = fopen("checkInOut.txt","a");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo de Check-in!");
        exit(1);
    }

    teste = fprintf(arquivo,"%d;%.0f;%.0f;%.2f;%d;%.2f",dados.delet, dados.codigoReserva,dados.codHospede, dados.consumoHospede, dados.DiariasPagas, dados.valorDiarias);

    fclose(arquivo);
    
    if(dados.DiariasPagas == 1)
        pagamentoDiarias(1, dados.valorDiarias);

    if(teste < 0)
        printf("\nFalha ao salvar check-In");
        else
        printf("\nCheck-in realizado com sucesso!");
    
}

checkInOut *salva_check_memoria(checkInOut dados, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks){
    //Realloca o o ponteiro para o tamanho necessário
    GLOBAL_dados_checkInOut = realloc(GLOBAL_dados_checkInOut, (*GLOBAL_tam_pont_dados_checks)*sizeof(checkInOut));

    //Aritimética para salvar os dados na última posição, como o tam começa em 1 e as posições em 0 é necessário o -1
    *(GLOBAL_dados_checkInOut + ((*GLOBAL_tam_pont_dados_checks) - 1)) = dados;
        
    //Verifica se foi possível alocar a memória necessária
    if (GLOBAL_dados_checkInOut == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    } else
        printf("\nCheck-in realizado com sucesso!");

    //Aumenta o valor do tamanho
    (*GLOBAL_tam_pont_dados_checks)++;

    return GLOBAL_dados_checkInOut;
}

void leCheckIn(checkInOut *GLOBAL_dados_checkInOut, int GLOBAL_tam_pont_dados_checks){
    FILE *arquivo;
    checkInOut dados;
    int encontrado = 0;
    float codReserva;

    printf("Digite o código da reserva que deseja buscar: ");
    scanf("%f", &codReserva);

    arquivo = fopen("checkInOut.bin", "rb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo de Check-in bin");
        exit(1);
    }

    while (fread(&dados, sizeof(checkInOut), 1, arquivo)){
        if(dados.delet == 0){
            if(dados.codigoReserva == codReserva){
                if(dados.DiariasPagas == 1){
                    printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: SIM\n\tHospede cadastrado: %.0f\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.codHospede, dados.consumoHospede);
                } else
                    printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: Não\n\tHospede cadastrado: %.0f\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.codHospede, dados.consumoHospede);
                encontrado = 1;
                break;
            }
        }
    }
    
    fclose(arquivo);

    if(encontrado == 0){
        arquivo = fopen("checkInOut.txt", "r");

        if(arquivo == NULL){
            printf("Erro ao abrir arquivo de Check-in txt");
            exit(1);
        }

        char linha[(sizeof(checkInOut))], *token;
        while (fgets(linha, sizeof(checkInOut), arquivo)){
            token = strtok(linha, ";");
            //atoi passa string para int 
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            //atoff passa string para float
            dados.codigoReserva = atoff(token);
            token = strtok(NULL, ";");
            dados.consumoHospede = atoff(token);
            token = strtok(NULL, ";");
            dados.DiariasPagas = atoi(token);
            token = strtok(NULL, ";");
            dados.valorDiarias = atoff(token);
            if(dados.delet == 0){
                if(dados.codigoReserva == codReserva){
                    if(dados.DiariasPagas == 1){
                        printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: SIM\n\tHospede cadastrado: %.0f\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.codHospede, dados.consumoHospede);
                    } else
                        printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: Não\n\tHospede cadastrado: %.0f\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.codHospede, dados.consumoHospede);
                    encontrado = 1;
                    break;
                }
            }
        }
        
        fclose(arquivo);
    }

    if(encontrado == 0){
        if(GLOBAL_dados_checkInOut != NULL){
            int i;
            for(i = 1; i < GLOBAL_tam_pont_dados_checks; i++){
                if(GLOBAL_dados_checkInOut->delet == 0){
                    if(GLOBAL_dados_checkInOut->codigoReserva == codReserva){
                        if(GLOBAL_dados_checkInOut->DiariasPagas == 1){
                            printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: SIM\n\tHospede cadastrado: %.0f\n\tConsumo atual: %.2f", GLOBAL_dados_checkInOut->codigoReserva, GLOBAL_dados_checkInOut->valorDiarias, GLOBAL_dados_checkInOut->codHospede, GLOBAL_dados_checkInOut->consumoHospede);
                        } else
                            printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: Não\n\tHospede cadastrado: %.0f\n\tConsumo atual: %.2f", GLOBAL_dados_checkInOut->codigoReserva, GLOBAL_dados_checkInOut->valorDiarias, GLOBAL_dados_checkInOut->codHospede, GLOBAL_dados_checkInOut->consumoHospede);
                        encontrado = 1;
                        break;
                    }
                }
                //Aritimetica para passar para a próxima posição do ponteiro
                GLOBAL_dados_checkInOut++;
            }
            //Retorna o ponteiro para a posição inicial
            GLOBAL_dados_checkInOut -= (i -1);
        }
    }
    if(encontrado == 0){
        printf("Nenhum Check-In encontrado para essa reserva!");
    }
}

//Menu
checkInOut* menu_checkInOut(int tipoArquivo, reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao, checkInOut *GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks, cad_clie *GLOBAL_dados_cliente, int GLOBAL_tam_pont_dados_cliente){
    int opcao = 0;
    checkInOut dados;

    while (opcao != 4) {
        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tRealizar Check-In - 1\n");
        printf("\tLer Check-In - 2\n");
        printf("\tRealizar Check-Out - 3\n");
        printf("\tVoltar ao menu principal - 4\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_checkIn(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas,GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_acomodacao, GLOBAL_dados_checkInOut, *GLOBAL_tam_pont_dados_checks, GLOBAL_dados_cliente, GLOBAL_tam_pont_dados_cliente);
                //Verifica se houve algum problema na leitura do check-in
                if(dados.delet != 2){
                    if (tipoArquivo == 0) {
                        salva_check_bin(dados);
                    } else if (tipoArquivo == 1) {
                        salva_check_txt(dados);
                    }
                    else {
                        GLOBAL_dados_checkInOut = salva_check_memoria(dados, GLOBAL_dados_checkInOut, &(*GLOBAL_tam_pont_dados_checks));
                    }
                }
                break;
            case 2:
                leCheckIn(GLOBAL_dados_checkInOut, *GLOBAL_tam_pont_dados_checks);
                break;
            case 3:
                checkOut(tipoArquivo);
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
    return GLOBAL_dados_checkInOut;
}

