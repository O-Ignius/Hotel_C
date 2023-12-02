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

//Realiza o checkOut
void checkOut(checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks){
    FILE *arquivo;
    checkInOut dados;
    float codReserva, valorFinal = 0;
    int achou = 0;

    printf("\nDigite o código da reserva que deseja realizar o checkOut: ");
    scanf("%f", &codReserva);

    arquivo = fopen("checkInOut.bin", "rb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo de Check-in bin");
        exit(1);
    }

    while (fread(&dados, sizeof(checkInOut), 1, arquivo)){
        if(dados.delet == 0){
            if(dados.codigoReserva == codReserva){
                //Caso as diárias não tenham sido pagas o valor é adicionado ao vaor total
                if(dados.DiariasPagas == 0){
                    valorFinal += dados.valorDiarias;
                }
                valorFinal += dados.consumoHospede;
                achou = 1;
                break;
            }
        }
    }
    
    fclose(arquivo);

    if(achou == 0){
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
                    //Caso as diárias não tenham sido pagas o valor é adicionado ao vaor total
                    if(dados.DiariasPagas == 0){
                        valorFinal += dados.valorDiarias;
                    }
                    valorFinal += dados.consumoHospede;
                    achou = 1;
                    break;
                }
            }
        }
        
        fclose(arquivo);
    }

    if(achou == 0){
        if(GLOBAL_dados_checkInOut != NULL){
            int i;
            for(i = 1; i < GLOBAL_tam_pont_dados_checks; i++){
                if(GLOBAL_dados_checkInOut->delet == 0){
                    if(GLOBAL_dados_checkInOut->codigoReserva == codReserva){
                        //Caso as diárias não tenham sido pagas o valor é adicionado ao vaor total
                        if(dados.DiariasPagas == 0){
                            valorFinal += dados.valorDiarias;
                        }
                        valorFinal += dados.consumoHospede;
                        achou = 1;
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
    //CHAMAR FUNÇÃO DE PAGAMENTO

    if(achou == 0){
        printf("\nCheck-in não encontrado!");
    }
}

//Leitura de dados
checkInOut le_dados_checkIn(reserva *GLOBAL_dados_reservas, int GLOBAL_tam_pont_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_acomodacao, checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks){
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

                int dias = retornaDias(reser.inicio, reser.fim);

                check.valorDiarias = dias * acomod.tipo.diaria;

                printf("Data inicio: %d/%d/%d\tFim: %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);

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
                    //realizar pagamento
                    check.DiariasPagas = 1;
                    check.consumoHospede = 0;
                } else{
                    check.DiariasPagas = 0;
                    check.consumoHospede = check.valorDiarias;
                    //contas a receber
                }
                return check;
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
void salva_check_bin(checkInOut dados){
    FILE *arquivo;

    arquivo = fopen("checkInOut.bin","ab");
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo de Check-in!");
        exit(1);
    }

    fwrite(&dados, sizeof(checkInOut), 1, arquivo);
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

    teste = fprintf(arquivo,"%d;%.0f;%.2f;%d;%.2f",dados.delet, dados.codigoReserva, dados.consumoHospede, dados.DiariasPagas, dados.valorDiarias);

    fclose(arquivo);

    if(teste < 0)
        printf("\nFalha ao salvar check-In");
        else
        printf("\nCheck-in realizado com sucesso!");
    
}

void salva_check_memoria(checkInOut dados, checkInOut ***GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks){
    //Realloca o o ponteiro para o tamanho necessário
    **GLOBAL_dados_checkInOut = realloc(GLOBAL_dados_checkInOut, (*GLOBAL_tam_pont_dados_checks)*sizeof(checkInOut));

    //Aritimética para salvar os dados na última posição, como o tam começa em 1 e as posições em 0 é necessário o -1
    ***(GLOBAL_dados_checkInOut + ((*GLOBAL_tam_pont_dados_checks) - 1)) = dados;
        
    //Verifica se foi possível alocar a memória necessária
    if (GLOBAL_dados_checkInOut == NULL) {
        printf("!! ERRO !! \nNão há memória suficiente disponível!! \n");
        exit(1);
    } else
        printf("\nCheck-in realizado com sucesso!");

    //Aumenta o valor do tamanho
    (*GLOBAL_tam_pont_dados_checks)++;
}

void leCheckIn(checkInOut *GLOBAL_dados_checkInOut,int GLOBAL_tam_pont_dados_checks){
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
                printf("Entrou?");
                if(dados.DiariasPagas == 1){
                    printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: SIM\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.consumoHospede);
                } else
                    printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: Não\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.consumoHospede);
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
                        printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: SIM\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.consumoHospede);
                    } else
                        printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: Não\n\tConsumo atual: %.2f", dados.codigoReserva, dados.valorDiarias, dados.consumoHospede);
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
                        if(dados.DiariasPagas == 1){
                            printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: SIM\n\tConsumo atual: %.2f", GLOBAL_dados_checkInOut->codigoReserva, GLOBAL_dados_checkInOut->valorDiarias, GLOBAL_dados_checkInOut->consumoHospede);
                        } else
                            printf("\nCódigo da reserva: %.0f\n\tValor das diárias: %.2f\n\tDiárias pagas: Não\n\tConsumo atual: %.2f", GLOBAL_dados_checkInOut->codigoReserva, GLOBAL_dados_checkInOut->valorDiarias, GLOBAL_dados_checkInOut->consumoHospede);
                        
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
void menu_checkInOut(int tipoArquivo, reserva *GLOBAL_dados_reservas, acomodacao *GLOBAL_dados_acomodacao, int GLOBAL_tam_pont_dados_reservas, int GLOBAL_tam_pont_dados_acomodacao, checkInOut **GLOBAL_dados_checkInOut, int *GLOBAL_tam_pont_dados_checks){
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
                dados = le_dados_checkIn(GLOBAL_dados_reservas, GLOBAL_tam_pont_dados_reservas,GLOBAL_dados_acomodacao, GLOBAL_tam_pont_dados_acomodacao, *GLOBAL_dados_checkInOut, *GLOBAL_tam_pont_dados_checks);
                //Verifica se houve algum problema na leitura do check-in
                if(dados.delet != 2){
                    if (tipoArquivo == 0) {
                        salva_check_bin(dados);
                    } else if (tipoArquivo == 1) {
                        salva_check_txt(dados);
                    }
                    else {
                        salva_check_memoria(dados, &GLOBAL_dados_checkInOut, &(*GLOBAL_tam_pont_dados_checks));
                    }
                }
                break;
            case 2:
                leCheckIn(*GLOBAL_dados_checkInOut, *GLOBAL_tam_pont_dados_checks);
                break;
            case 3:
                checkOut(*GLOBAL_dados_checkInOut, *GLOBAL_tam_pont_dados_checks);
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
    }
}