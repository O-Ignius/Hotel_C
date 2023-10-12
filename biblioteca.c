#include "biblioteca.h"

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\
//    Variadas

int tam_clientes() {
    int tamanho = 0;

    tamanho = sizeof (cad_clie) - sizeof (float);

    return tamanho;
}

int tam_categ_acomod() {
    int tamanho = 0;

    tamanho = sizeof (cate_aco) - sizeof (float);

    return tamanho;
}

int tam_acomodacao() {
    int tamanho = 0;

    tamanho = sizeof (acomodacao) - sizeof (float);

    return tamanho;
}

int selecionarTipoArquivo() {
    int tipoArquivo = 0;

    printf("\nDigite 0 para salvar as informações em arquivos binários e 1 para arquivos txt: ");
    scanf("%d", &tipoArquivo);

    while (tipoArquivo != 0 && tipoArquivo != 1) {
        printf("Número inválido, digite novamente: ");
        scanf("%d", &tipoArquivo);
    }
    if (tipoArquivo == 0) {
        printf("Tipo de arquivo alterado para BINARIO!");
    } else
        printf("Tipo de arquivo alterado para TXT!");
    getchar();
    return tipoArquivo;
}

float retorna_id(char *nome_txt, char *nome_bin, int tam) {
    FILE *txt, *bin;
    // cria variaveis so pra ver se o número é diferente ou não do ID
    int dif_txt = 0, dif_bin = 0;
    //variaveis para guardar os ID's
    float id_livre = 0, id_bin = 0, id_txt = 0;
    char linha[300], *token;

    txt = fopen(nome_txt, "r");
    if (txt == NULL) {
        printf("Erro de abertura de arquivo txt!");
        exit(1);
    }

    bin = fopen(nome_bin, "rb");
    if (bin == NULL) {
        printf("Erro de abertura de arquivo bin!");
        exit(1);
    }

    /* posiciona o cursor dentro do arquivo binário 1 posição (int) a frente com relação ao inicio, já que a primeira posição somente
    diz se o arquivo foi ou não excluido lógicamente */
    fseek(bin, sizeof (int), SEEK_CUR);

    // pega linha a linha do arquivo txt e a coloca em uma string
    while (fgets(linha, sizeof (linha), txt) != NULL) {
        dif_bin = 0;
        dif_txt = 0;

        //corta a string até achar um ";" e adereça o resultado a uma variavel do tipo ponteiro, esse primeiro endereço seria o delet da struct
        token = strtok(linha, ";");
        //corta a string novamente para coletar o valor do id
        token = strtok(NULL, ";");
        //transforma o tipo da string cortada pra um tipo inteiro e salva ele em uma variavel
        id_txt = atoff(token);
        //caso não tenha diferença entre o id_txt e o id_livre (basicamente pra iniciar)
        //inicia verificação no arquivo txt
        while (dif_txt == 0) {
            if (id_livre != id_txt) {
                //inicia a verifição no arquivo binário
                if (id_livre != id_bin) {
                    if (id_bin > id_txt) {
                        /* Enquanto não houver diferença, ele tentará comparar se há diferença entre o id_bin e o id_livre
                         caso ache a diferença ele define a variavel dif_bin = 1 e quebra o loop.
                         Caso não ache, quer dizer que é igual, logo, ele aumenta em 1 o id_livre e verifica novamente
                         Avançando a posição do cursor com relação ao tamanho da struct e parando antes do float de ID*/
                        while (dif_bin == 0) {
                            if ((id_livre != id_bin)) {
                                dif_bin = 1;
                                break;
                            } else {
                                id_livre++;
                                fseek(bin, tam, SEEK_CUR);
                                break;
                            }
                        }
                    }//se o id_bin for menor que o id_txt
                    else {
                        while (fread(&id_bin, sizeof (float), 1, bin)) {
                            while (dif_bin == 0) {
                                if ((id_livre != id_bin)) {
                                    dif_bin = 1;
                                    break;
                                } else {
                                    id_livre++;
                                    fseek(bin, tam, SEEK_CUR);
                                    break;
                                }
                            }

                            if (dif_bin == 1) {
                                break;
                            }
                        }
                    }

                    if (id_txt == id_livre) {
                        id_livre++;
                    } else {
                        dif_txt = 1;
                    }
                }//se o id_bin for igual ao id_livre, id_livre aumenta em 1 e a posição do cursor avança com relação ao tamanho da struct
                else {
                    id_livre++;
                    fseek(bin, tam, SEEK_CUR);
                }
            }//caso o id_livre é igual ao txt
            else {
                id_livre++;
            }
        }
    }

    //fecha binario
    fclose(bin);

    //fecha txt
    fclose(txt);

    return id_livre;
}

//    Coleta dados:

cad_clie le_dados_cad() {

    cad_clie dados;

    dados.delet = 0;

    setbuf(stdin, NULL);

    printf("\nDigite o id: ");

    scanf("%f", &dados.codigo);

    setbuf(stdin, NULL);

    printf("\nDigite o seu nome completo: ");

    scanf("%[a-z A-Z][^\n]s", dados.nome);

    setbuf(stdin, NULL);

    /*

    printf("Digite o seu cpf: \n");

    scanf("%f", &dados.cpf);

    setbuf(stdin, NULL);

    
    printf("Digite seu estado: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.estado);

    setbuf(stdin, NULL); 
    
    printf("Digite sua cidade: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.cidade);

    setbuf(stdin, NULL);

    printf("Digite seu bairro: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);

    setbuf(stdin, NULL);

    printf("Digite sua rua: \n");

    scanf("%[a-z A-Z][^\n]s", dados.local.rua);

    setbuf(stdin, NULL);

    printf("Digite o número de sua casa: \n");

    scanf("%f", &dados.local.numero);

    setbuf(stdin, NULL);



    printf("Digite seu cpf: \n");

    scanf("%f", &dados.cpf);

    setbuf(stdin, NULL);

    printf("Digite seu telefone: \n");

    scanf("%f", &dados.telefone);

    setbuf(stdin, NULL);

    printf("Digite seu email: \n");

    scanf("%[^\n]s", dados.email);

    setbuf(stdin, NULL);

    printf("Digite seu sexo: \n");

    scanf("%[a-z A-Z][^\n]s", dados.sexo);

    setbuf(stdin, NULL);

    printf("Digite seu estado civil: \n");

    scanf("%[a-z A-Z][^\n]s", dados.estado_civil);

    setbuf(stdin, NULL);

    printf("Digite sua data de nascimento: \n");

    scanf("%[0-9/-][^\n]s", &dados.nascimento);

    setbuf(stdin, NULL);
     */
    return dados;
}

hotel le_dados_hotel() {
    // variaveis
    hotel dados;

    //coleta de dados
    dados.delet = 0;
    setbuf(stdin, NULL);
    printf("Digite o nome do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome_hot);
    setbuf(stdin, NULL);
    printf("Digite a razão social: \n");
    scanf("%[a-z A-Z][^\n]s", dados.raz_soci);
    setbuf(stdin, NULL);
    printf("Digite a inscrição estadual do hotel: \n");
    scanf("%[^\n]s", dados.inscri_estad);
    setbuf(stdin, NULL);
    printf("Digite o CNPJ do hotel: \n");
    scanf("%[0-9.-][^\n]s", dados.nome_hot);
    setbuf(stdin, NULL);
    printf("Digite o email do hotel: \n");
    scanf("%s", dados.email);
    setbuf(stdin, NULL);
    printf("Digite o número de telefone do hotel: \n");
    scanf("%[0-9][^\n]s", dados.telefone_hot);
    setbuf(stdin, NULL);
    printf("Digite a sigla do estado em que se encontra o hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.estado);
    setbuf(stdin, NULL);
    printf("Digite a cidade do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.cidade);
    setbuf(stdin, NULL);
    printf("Digite o CEP da cidade do hotel: \n");
    scanf("%f", dados.local.cep);
    setbuf(stdin, NULL);
    printf("Digite o bairro do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);
    setbuf(stdin, NULL);
    printf("Digite a rua do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.rua);
    setbuf(stdin, NULL);
    printf("Digite o número do hotel: \n");
    scanf("%f", dados.local.numero);
    setbuf(stdin, NULL);
    printf("Digite o nome do gerente do hotel: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome_respo);
    setbuf(stdin, NULL);
    printf("Digite o telefone do gerente do hotel: \n");
    scanf("%f", dados.telefone_respo);
    setbuf(stdin, NULL);
    printf("Digite o horario de check-in do hotel: \n");
    printf("horas: ");
    scanf("%d", dados.in.hora);
    setbuf(stdin, NULL);
    printf("\nminutos: ");
    scanf("%d", dados.in.min);
    setbuf(stdin, NULL);
    printf("Digite o horario de check-out do hotel: \n");
    printf("horas: ");
    scanf("%d", dados.out.hora);
    setbuf(stdin, NULL);
    printf("\nminutos: ");
    scanf("%d", dados.out.min);
    setbuf(stdin, NULL);
    printf("Digite a margem de lucro dos produtos vendidos pelo hotel: ");
    scanf("%f", dados.lucro);

    return dados;
}

cate_aco le_dados_categ_acomod() {
    //variaveis
    cate_aco dados;

    //coleta de dados
    dados.delet = 0;
    setbuf(stdin, NULL);
    printf("Digite o código da categoria da acomodação: \n");
    scanf("%f", &dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite a descrição da acomodação: \n");
    scanf("%[^\n]s", dados.descri);
    setbuf(stdin, NULL);
    printf("Digite o valor da diária: \n");
    scanf("%f", &dados.diaria);
    setbuf(stdin, NULL);
    printf("Digite a quantia de pessoas que a acomodação comporta: \n");
    scanf("%d", &dados.qnt_pessoas);
    setbuf(stdin, NULL);

    return dados;
}

acomodacao le_dados_acomod() {
    //variaveis

    acomodacao dados;

    //coleta de dados
    dados.delet = 0;
    setbuf(stdin, NULL);
    printf("Digite o código do quarto: \n");
    scanf("%f", &dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite a descrição da acomodação: \n");
    scanf("%[^\n]s", dados.descri);
    setbuf(stdin, NULL);
    printf("Digite as facilidades da acomodação (como ar condicionado, TV, ...): \n");
    scanf("%[^\n]s", dados.facilidades);
    setbuf(stdin, NULL);

    return dados;
}

produto le_dados_produto() {
    // variaveis
    produto dados;

    //coleta dados
    setbuf(stdin, NULL);
    printf("Digite o código do produto: \n");
    scanf("%d", dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite a descrição do produto: \n");
    scanf("%[a-z A-Z][^\n]s", dados.descricao);
    setbuf(stdin, NULL);
    printf("Digite o estoque do produto: \n");
    scanf("%d", dados.estoque);
    setbuf(stdin, NULL);
    printf("Digite o estoque minimo do produto: \n");
    scanf("%d", dados.estoque_min);
    setbuf(stdin, NULL);
    printf("Digite o preço de custo do produto: \n");
    scanf("%f", dados.custo);
    setbuf(stdin, NULL);
    printf("Digite o preço de venda do produto: \n");
    scanf("%f", dados.venda);

    return dados;
}

fornecedor le_dados_fornecedor() {
    //variaveis
    fornecedor dados;

    //coleta dados
    setbuf(stdin, NULL);
    printf("Digite o código do fornecedor: \n");
    scanf("%f", dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite o nome do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.nome);
    setbuf(stdin, NULL);
    printf("Digite a razão social do fornecedor: \n");
    scanf("%[^\n]s", dados.raz_soci);
    setbuf(stdin, NULL);
    printf("Digite a inscrição estadual do fornecedor: \n");
    scanf("%[^\n]s", dados.inscri_estad);
    setbuf(stdin, NULL);
    printf("Digite o CNPJ do fornecedor: \n");
    scanf("%[^\n]s", dados.cnpj);
    setbuf(stdin, NULL);
    printf("Digite o telefone do fornecedor: \n");
    scanf("%f", dados.telefone);
    setbuf(stdin, NULL);
    printf("Digite o email do fornecedor: \n");
    scanf("%[^\n]s", dados.email);
    setbuf(stdin, NULL);
    printf("Digite a sigla do estado do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.estado);
    setbuf(stdin, NULL);
    printf("Digite a cidade do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.cidade);
    setbuf(stdin, NULL);
    printf("Digite o CEP da cidade do fornecedor: \n");
    scanf("%f", dados.local.cep);
    setbuf(stdin, NULL);
    printf("Digite o bairro do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);
    setbuf(stdin, NULL);
    printf("Digite a rua do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.rua);
    setbuf(stdin, NULL);
    printf("Digite o número do fornecedor: \n");
    scanf("%f", dados.local.numero);

    return dados;
}

operador le_dados_operador() {
    //variaveis
    operador dados;

    //coleta dados
    setbuf(stdin, NULL);
    printf("Digite o código do operador: \n");
    scanf("%f", dados.codigo);
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
    scanf("%f", dados.acesso);

    return dados;
}

//MENUS:

void menuPrincipal() {
    int opcao = -1, binOUtxt = 0;

    while (opcao != 0) {
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tHotel - 1\n");
        printf("\tClientes - 2\n");
        printf("\tReservas - 3\n");
        printf("\tAcomodações - 4\n");
        printf("\tConfigurações de salvamento - 9\n");
        printf("\tEncerrar - 0\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuHotel(binOUtxt);
                break;
            case 2:
                menuCliente(binOUtxt);
                break;
            case 3:
                menuReserva(binOUtxt);
                break;
            case 4:
                menuAcomodacoes(binOUtxt);
                break;
            case 9:
                binOUtxt = selecionarTipoArquivo();
                break;
            case 0:
                printf("Fechando programa...");
                exit(1);
            default:
                printf("Opcao invalida, digite novamente: ");
                scanf("%d", &opcao);
                break;
        }
    }

}

void menuHotel(int tipoArquivo) {
    int opcao = 0, binOUtxt = tipoArquivo;
    hotel dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastrar Hotel - 1\n");
        printf("\tListar dados do Hotel - 2\n");
        printf("\tAlterar dados do Hotel - 3\n");
        printf("\tExcluir dados do Hotel - 4\n");
        printf("\tVoltar ao menu inicial - 5\n");

        printf("Opc�o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_hotel();
                if (binOUtxt == 0) {
                    //salva_cadastro_hotel_bin(dados);
                } else {
                    salva_cadastro_hotel_txt(dados);
                }
                break;
            case 2:
                if (binOUtxt == 0) {
                    //le_cadastro_hotel_bin();
                } else
                    le_cadastro_hotel_txt();
                break;
            case 3:
                if (binOUtxt == 0) {
                    //altera_hotel_bin();
                } else {
                    //altera_hotel_txt();
                }
                break;
            case 4:
                if (binOUtxt == 0) {
                    //exclui_hotel_bin();
                } else {
                    //exclui_hotel_txt();
                }
                break;
            case 5:
                menuPrincipal();
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        getchar();
    }
}

void menuCliente(int tipoArquivo) {
    int opcao = 0, binOUtxt = tipoArquivo;
    cad_clie dados;
    while (opcao != 5) {
        setbuf(stdin, NULL);
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de cliente - 1\n");
        printf("\tListar todos os cliente - 2\n");
        printf("\tLista dados de um cliente - 3\n");
        printf("\tAlterar dados cliente - 4\n");
        printf("\tExcluir dados de cliente - 5\n");
        printf("\tVoltar ao menu inicial - 6\n");

        printf("Opc�o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_cad();
                if (binOUtxt == 0) {
                    salva_cadastro_pessoa_bin(dados);
                } else {
                    salva_cadastro_pessoa_txt(dados);
                }
                break;
            case 2:
                le_todos_cadastro_pessoa();
                break;
            case 3:
                le_cadastro_pessoa();
                break;
            case 4:
                alteraCliente();
                break;
            case 5:
                removeCliente();
                break;
            case 6:
                menuPrincipal();
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPRESSIONE QUALQUER TECLA PARA CONTINUAR...");
        getchar();
    }
}

void menuReserva(int tipoArquivo) {
    int opcao, binOUtxt = tipoArquivo;
    cad_clie dados;


    while (opcao != 5) {
        getchar();
        system("clear");
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de reserva - 1\n");
        printf("\tListar reservas - 2\n");
        printf("\tAlterar dados reserva - 3\n");
        printf("\tExcluir dados de reserva - 4\n");
        printf("\tVoltar ao menu inicial - 5\n");

        printf("Opc�o: ");
        scanf("%d", &opcao);
    }
    menuPrincipal();
}

void menuAcomodacoes(int tipoArquivo) {
    int opcao = 0, binOUtxt = tipoArquivo;
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
                if (binOUtxt == 0) {
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
                //remove
                break;
            case 5:
                categ = le_dados_categ_acomod();
                if (binOUtxt == 0) {
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
            case 9:
                menuPrincipal();
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        getchar();
    }
}

//  Clientes

void salva_cadastro_pessoa_bin(cad_clie saves) {

    FILE *salva;
    //      abrir arquivo
    salva = fopen("cliente.bin", "ab");

    if (salva == NULL) {
        printf("\n\t!! Erro de salvamento de Cadastro !! \n");
        return;
    }

    //      Escrever no arquivo
    fwrite(&saves, sizeof (cad_clie), 1, salva);
    
    printf("\nCadastro realizado com sucesso!\n\n");
    fclose(salva);
}

void salva_cadastro_pessoa_txt(cad_clie saves) {

    FILE *salva;

    int end, pessoa;

    //      abrir arquivo

    salva = fopen("cliente.txt", "a");

    if (salva == NULL) {

        printf("\n\t!! Erro de salvamento de Cadasto !! \n");

        exit(1);
    }

    //      Escrever no arquivo

    pessoa = fprintf(salva, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", saves.delet, saves.codigo, saves.nome, saves.cpf, saves.telefone, saves.email, saves.sexo, saves.estado_civil, saves.nascimento);

    if (pessoa < 0) {

        printf("!! Erro em salvar os dados !!\n");

        exit(1);
    } else {
        printf("Dados do cliente salvos com sucesso! \n");
    }

    //      Endereço

    end = fprintf(salva, "%s;%0.0f;%s;%s;%s;%0.0f;\n", saves.local.estado, saves.local.cep, saves.local.cidade, saves.local.bairro, saves.local.rua, saves.local.numero);

    if (end < 0) {

        printf("!! Erro em salvar o endereço !!\n");

        exit(1);
    } else {
        printf("Dados do endereço salvos com sucesso! \n");
    }

    //      Fechar arquivo
    fclose(salva);
}

void le_cadastro_pessoa() {
    //      Variáveis
    FILE *arquivoBin, *arquivoTxt;
    cad_clie cliente;

    float codigo;
    int encontrado = 0;

    printf("Digite o codigo do cliente que deseja ler: ");
    scanf("%f", &codigo);

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
            printf("\nCódigo: %.0f\n\tNome: %s\n\tCPF: %.0f\n\tTelefone: %.0f\n\tEmail: %s\n\tSexo: %s\n\tEstad civil: %s\n\tNascimento: %s\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNumero: %.0f\n\tCEP: %.0f",
                    cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil,
                    cliente.nascimento, cliente.local.estado, cliente.local.cidade, cliente.local.bairro, cliente.local.rua,
                    cliente.local.numero, cliente.local.cep);
            break;
        }
    }
    if (encontrado == 0) {

        char linha[(sizeof (cad_clie))], *token, cod[10];
        //Passa o cod de float para string
        sprintf(cod, "%.0f", codigo);

        while (fgets(linha, sizeof (cad_clie), arquivoTxt) != NULL) {
            // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
            token = strtok(linha, ";");

            // compara e caso o arquivo não tenha sido excluido ele verifica se o código escrito pela pessoa realmente existe
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                if (strcmp(cod, token) == 0) {
                    encontrado = 1;

                    printf("\nCódigo: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Nome: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("CPF: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Telefone: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Email: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Sexo: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Estado Civil: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Nascimento: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Estado: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("CEP: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Cidade: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Bairro: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Rua: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Número da casa: %s\n", token);
                    token = strtok(NULL, ";");
                }
            }
        }
    }

    if (encontrado == 0) {
        printf("Cliente não encontrado!");
    }
    fclose(arquivoBin);
    fclose(arquivoTxt);
}

void le_todos_cadastro_pessoa() {
    FILE *arquivoBin, *arquivoTxt;
    cad_clie cliente;

    arquivoBin = fopen("cliente.bin", "rb");
    arquivoTxt = fopen("cliente.txt", "r");

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.delet == 0) {
            printf("\nCódigo: %.0f\n\tNome: %s\n\tCPF: %.0f\n\tTelefone: %.0f\n\tEmail: %s\n\tSexo: %s\n\tEstad civil: %s\n\tNascimento: %s\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNumero: %.0f\n\tCEP: %.0f",
                    cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil,
                    cliente.nascimento, cliente.local.estado, cliente.local.cidade, cliente.local.bairro, cliente.local.rua,
                    cliente.local.numero, cliente.local.cep);
        }
    }

    char linha[(sizeof (cad_clie))], *token;
    while (fgets(linha, sizeof (cad_clie), arquivoTxt) != NULL) {
        // pega o primeiro dado (se o arquivo foi ou não excluido logicamente)
        token = strtok(linha, ";");

        // compara e caso o arquivo não tenha sido excluido ele mostra
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            printf("\nCódigo: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Nome: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("CPF: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Telefone: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Email: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Sexo: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Estado Civil: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Nascimento: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Estado: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("CEP: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Cidade: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Bairro: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Rua: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Número da casa: %s\n", token);
            token = strtok(NULL, ";");
        }
    }
    fclose(arquivoBin);
    fclose(arquivoTxt);
    getchar();
}

void alteraCliente() {
    FILE *arquivoBin;
    cad_clie cliente, novo;
    int encontrado = 0;
    float codigo;

    //      abrir arquivo
    arquivoBin = fopen("cliente.bin", "rb+wb");

    if (arquivoBin == NULL) {
        printf("\n\t!! Erro de leitura do Cadastro !! \n");
        exit(1);
    }

    printf("Digite o codigo do cliente que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.codigo == codigo && cliente.delet == 0) {
            encontrado = 1;
            printf("\nAntigos dados:\nCod: %.0f\nNome: %s\n", cliente.codigo, cliente.nome);

            printf("\nNovos dados:");

            novo.codigo = cliente.codigo;
            novo = le_dados_cad();

            //Volta para o inicio da linha de cadastro desse cliente, permitindo que se altere o cliente correto
            fseek(arquivoBin, -sizeof (cad_clie), SEEK_CUR);
            //Com o ponteiro no local correto, salva-se os novos dados, substituindo os antigos
            fwrite(&novo, sizeof (cad_clie), 1, arquivoBin);
            break;
        }

    }

    fclose(arquivoBin);

    if (encontrado == 0) {
        FILE *le, *altera;

        int tam = 0, i = 0;

        char linha[(sizeof (cad_clie))], *token;

        le = fopen("cliente.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        //verificar quantas linhas:
        while (fgets(linha, sizeof (cad_clie), le) != NULL) {
            tam++;
        }

        //cria um vetor de struct do tipo cad_clie variante a quantia de linha do arquivo
        cad_clie txt[tam];

        le = fopen("cliente.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        //lê linha a linha do arquivo
        while (fgets(linha, sizeof (cad_clie), le) != NULL) {
            //pega o primeiro dado guardado (se o arquivo foi ou não excluido) e o separa dos demais
            token = strtok(linha, ";");
            //compara o primeiro dado, caso ele seja 0, o arquivo não foi excluido
            if (strcmp(token, "0") == 0) {
                txt[i].delet = atoi(token);
                token = strtok(NULL, ";");
                txt[i].codigo = atoff(token);

                //se o código foi igual ao digitado ele altera
                if (txt[i].codigo == codigo) {
                    txt[i] = le_dados_cad();
                    txt[i].codigo = codigo;
                    encontrado = 1;
                }//caso o código digitado seja diferente
                else {
                    token = strtok(NULL, ";");
                    strcpy(txt[i].nome, token);
                    token = strtok(NULL, ";");
                    txt[i].cpf = atoff(token);
                    token = strtok(NULL, ";");
                    txt[i].telefone = atoff(token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].email, token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].sexo, token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].estado_civil, token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].nascimento, token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].local.estado, token);
                    token = strtok(NULL, ";");
                    txt[i].local.cep = atoff(token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].local.cidade, token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].local.bairro, token);
                    token = strtok(NULL, ";");
                    strcpy(txt[i].local.rua, token);
                    token = strtok(NULL, ";");
                    txt[i].local.numero = atoff(token);
                }
            }//caso os dados já tenham sido deletados
            else {
                txt[i].delet = atoi(token);
                token = strtok(NULL, ";");
                txt[i].codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(txt[i].nome, token);
                token = strtok(NULL, ";");
                txt[i].cpf = atoff(token);
                token = strtok(NULL, ";");
                txt[i].telefone = atoff(token);
                token = strtok(NULL, ";");
                strcpy(txt[i].email, token);
                token = strtok(NULL, ";");
                strcpy(txt[i].sexo, token);
                token = strtok(NULL, ";");
                strcpy(txt[i].estado_civil, token);
                token = strtok(NULL, ";");
                strcpy(txt[i].nascimento, token);
                token = strtok(NULL, ";");
                strcpy(txt[i].local.estado, token);
                token = strtok(NULL, ";");
                txt[i].local.cep = atoff(token);
                token = strtok(NULL, ";");
                strcpy(txt[i].local.cidade, token);
                token = strtok(NULL, ";");
                strcpy(txt[i].local.bairro, token);
                token = strtok(NULL, ";");
                strcpy(txt[i].local.rua, token);
                token = strtok(NULL, ";");
                txt[i].local.numero = atoff(token);
            }

            //salva os dados no arquivo temporario altera 
            fprintf(altera, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", txt[i].delet, txt[i].codigo, txt[i].nome, txt[i].cpf, txt[i].telefone, txt[i].email, txt[i].sexo, txt[i].estado_civil, txt[i].nascimento);
            fprintf(altera, "%s;%0.0f;%s;%s;%s;%0.0f;\n", txt[i].local.estado, txt[i].local.cep, txt[i].local.cidade, txt[i].local.bairro, txt[i].local.rua, txt[i].local.numero);

            i++;
        }

        fclose(altera);
        fclose(le);
        if (remove("cliente.txt") == 0 && rename("temp.txt", "cliente.txt")) {
            printf("\nDeu\n");
        }
    }

    if (encontrado == 1) {
        printf("Dados alterados com sucesso!");
    } else {
        printf("Cliente não encontrado!");
    }

}

void removeCliente() {
    //      Variáveis
    FILE *arquivoBin;
    cad_clie cliente;

    float codigo;
    int encontrado = 0;

    printf("Digite o codigo do cliente que deseja excluir: ");
    scanf("%f", &codigo);

    //      abrir arquivo
    arquivoBin = fopen("cliente.bin", "rb+wb");

    if (arquivoBin == NULL) {
        printf("\n\t!! Erro de abertura de arquivo !! \n");
        exit(1);
    }
    while (fread(&cliente, sizeof (cad_clie), 1, arquivoBin)) {
        if (cliente.codigo == codigo && cliente.delet == 0) {
            encontrado = 1;
            //Salva-se os dados na va, substituindo o valor do campo delet de 0 para 1
            cliente.delet = 1;
            //Volta para o inicio da linha de cadastro desse cliente, permitindo que se altere o cliente correto
            fseek(arquivoBin, -sizeof (cad_clie), SEEK_CUR);
            //Com o ponteiro no local correto, 
            fwrite(&cliente, sizeof (cad_clie), 1, arquivoBin);
            printf("\n\ta");
            break;
        }
    }
    fclose(arquivoBin);

    if (encontrado == 0) {
        FILE *remover, *le;
        char linha[(sizeof (cad_clie))], *token;
        int tam = 0, i = 0, encontrado = 0;

        le = fopen("cliente.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        //verificar quantas linhas:
        while (fgets(linha, sizeof (cad_clie), le) != NULL) {
            tam++;
        }

        fclose(le);

        cad_clie txt[tam];

        le = fopen("cliente.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        remover = fopen("temp.txt", "a");
        if (remover == NULL) {
            printf("Erro de abertura de arquivo!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (cad_clie), le) != NULL) {
            token = strtok(linha, ";");
            txt[i].delet = atoi(token);
            token = strtok(NULL, ";");
            txt[i].codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(txt[i].nome, token);
            token = strtok(NULL, ";");
            txt[i].cpf = atoff(token);
            token = strtok(NULL, ";");
            txt[i].telefone = atoff(token);
            token = strtok(NULL, ";");
            strcpy(txt[i].email, token);
            token = strtok(NULL, ";");
            strcpy(txt[i].sexo, token);
            token = strtok(NULL, ";");
            strcpy(txt[i].estado_civil, token);
            token = strtok(NULL, ";");
            strcpy(txt[i].nascimento, token);
            token = strtok(NULL, ";");
            strcpy(txt[i].local.estado, token);
            token = strtok(NULL, ";");
            txt[i].local.cep = atoff(token);
            token = strtok(NULL, ";");
            strcpy(txt[i].local.cidade, token);
            token = strtok(NULL, ";");
            strcpy(txt[i].local.bairro, token);
            token = strtok(NULL, ";");
            strcpy(txt[i].local.rua, token);
            token = strtok(NULL, ";");
            txt[i].local.numero = atoff(token);

            if (txt[i].codigo == codigo) {
                txt[i].delet = 1;
                fprintf(remover, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", txt[i].delet, txt[i].codigo, txt[i].nome, txt[i].cpf, txt[i].telefone, txt[i].email, txt[i].sexo, txt[i].estado_civil, txt[i].nascimento);
                fprintf(remover, "%s;%0.0f;%s;%s;%s;%0.0f;\n", txt[i].local.estado, txt[i].local.cep, txt[i].local.cidade, txt[i].local.bairro, txt[i].local.rua, txt[i].local.numero);
                encontrado = 1;
            } else {
                fprintf(remover, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", txt[i].delet, txt[i].codigo, txt[i].nome, txt[i].cpf, txt[i].telefone, txt[i].email, txt[i].sexo, txt[i].estado_civil, txt[i].nascimento);
                fprintf(remover, "%s;%0.0f;%s;%s;%s;%0.0f;\n", txt[i].local.estado, txt[i].local.cep, txt[i].local.cidade, txt[i].local.bairro, txt[i].local.rua, txt[i].local.numero);
            }

            i++;
        }

        fclose(remover);
        fclose(le);

        if (encontrado == 0) {
            printf("Cliente não encontrado!\n");
        } else {
            printf("Cliente excluido com sucesso!\n");
        }

        remove("cliente.txt");
        rename("temp.txt", "cliente.txt");
    }
}

//  Hotel

void salva_cadastro_hotel_txt(hotel saves) {
    FILE *salva;

    int end, hot, chek;

    //      abrir arquivo

    salva = fopen("hotel.txt", "a");

    if (salva == NULL) {

        printf("\n\t!! Erro de salvamento de Cadasto !! \n");

        exit(1);
    }

    //      Escrever no arquivo

    hot = fprintf(salva, "%d;%s;%s;%s;%s;%s;%0.0f;%s;%0.0f;%0.0f;", saves.delet, saves.nome_hot, saves.raz_soci, saves.inscri_estad, saves.cnpj, saves.email, saves.telefone_hot, saves.nome_respo, saves.telefone_respo, saves.lucro);

    if (hot < 0) {
        printf("!! Erro em salvar os dados do hotel!!");
        exit(1);
    } else {
        printf("Dados do hotel salvos com sucesso!\n");
    }

    //      Endereço

    end = fprintf(salva, "%0.0f;%s;%s;%s;%0.0f;", saves.local.cep, saves.local.cidade, saves.local.bairro, saves.local.rua, saves.local.numero);

    if (end < 0) {
        printf("!! Erro em salvar o endereço do hotel !!");
        exit(1);
    } else {
        printf("Endereço salvo com sucesso!\n");
    }

    chek = fprintf(salva, "%d;%d;%d;%d;\n", saves.in.hora, saves.in.min, saves.out.hora, saves.out.min);

    if (chek < 0) {
        printf("!! Erro em salvar os dados de check-in e check-out do hotel !!");
        exit(1);
    } else {
        printf("Check-in e check-out salvos com sucesso!\n");
    }

    //      Fechar arquivo
    fclose(salva);
}

void le_cadastro_hotel_txt() {
    FILE *le;
    char linha[(sizeof (hotel))], *token;

    //      abrir arquivo
    le = fopen("hotel.txt", "r");
    if (le == NULL) {

        printf("\n\t!! Erro de leitura de Cadastro !! \n");

        exit(1);
    }

    while (fgets(linha, sizeof (hotel), le) != NULL) {
        token = strtok(linha, ";");
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            printf("Nome: %s\n", token);
            token = strtok(NULL, ";");
            printf("Razão Social: %s\n", token);
            token = strtok(NULL, ";");
            printf("Inscrição Estadual: %s\n", token);
            token = strtok(NULL, ";");
            printf("CNPJ: %s\n", token);
            token = strtok(NULL, ";");
            printf("Email: %s\n", token);
            token = strtok(NULL, ";");
            printf("Telefone do Hotel: %s\n", token);
            token = strtok(NULL, ";");
            printf("Gerente: %s\n", token);
            token = strtok(NULL, ";");
            printf("Telefone do Gerente: %s\n", token);
            token = strtok(NULL, ";");
            printf("Porcentagem de lucro do hotel: %s%%\n", token);
            token = strtok(NULL, ";");
            printf("Cep: %s\n", token);
            token = strtok(NULL, ";");
            printf("Cidade: %s\n", token);
            token = strtok(NULL, ";");
            printf("Bairro: %s\n", token);
            token = strtok(NULL, ";");
            printf("Rua: %s\n", token);
            token = strtok(NULL, ";");
            printf("Número do hotel: %s\n", token);
            token = strtok(NULL, ";");
            printf("Check-in: %s:", token);
            token = strtok(NULL, ";");
            printf("%s\n", token);
            token = strtok(NULL, ";");
            printf("Check-out: %s:", token);
            token = strtok(NULL, ";");
            printf("%s\n", token);
        }
    }

    //      Fechar arquivo
    fclose(le);

    getchar();
}

void altera_hotel_txt() {
    FILE *le, *altera;
    char linha[(sizeof (hotel))], *token;
    hotel txt;
    int hot, end, chek;

    le = fopen("hotel.txt", "r");
    if (le == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }

    altera = fopen("temp.txt", "a");
    if (altera == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }

    // lê linha a linha do arquivo, armazenando os dados antigos, fazendo exclusão lógica
    while (fgets(linha, sizeof (hotel), le) != NULL) {
        // exclui logicamente os dados
        txt.delet = 1;
        //pega cada dado e adiciona a um campo da struct o transformando para o tipo do dado
        token = strtok(linha, ";");
        token = strtok(NULL, ";");
        strcpy(txt.nome_hot, token);
        token = strtok(NULL, ";");
        strcpy(txt.raz_soci, token);
        token = strtok(NULL, ";");
        strcpy(txt.inscri_estad, token);
        token = strtok(NULL, ";");
        strcpy(txt.cnpj, token);
        token = strtok(NULL, ";");
        strcpy(txt.email, token);
        token = strtok(NULL, ";");
        txt.telefone_hot = atoff(token);
        token = strtok(NULL, ";");
        strcpy(txt.nome_respo, token);
        token = strtok(NULL, ";");
        txt.telefone_respo = atoff(token);
        token = strtok(NULL, ";");
        txt.lucro = atoff(token);
        token = strtok(NULL, ";");
        txt.local.cep = atoff(token);
        token = strtok(NULL, ";");
        strcpy(txt.local.cidade, token);
        token = strtok(NULL, ";");
        strcpy(txt.local.bairro, token);
        token = strtok(NULL, ";");
        strcpy(txt.local.rua, token);
        token = strtok(NULL, ";");
        txt.local.numero = atoff(token);
        token = strtok(NULL, ";");
        txt.in.hora = atoi(token);
        token = strtok(NULL, ";");
        txt.in.min = atoi(token);
        token = strtok(NULL, ";");
        txt.out.hora = atoi(token);
        token = strtok(NULL, ";");
        txt.out.hora = atoi(token);

        // salva os dados antigos com exclusão lógica
        hot = fprintf(altera, "%d;%s;%s;%s;%s;%s;%0.0f;%s;%0.0f;%0.0f;", txt.delet, txt.nome_hot, txt.raz_soci, txt.inscri_estad, txt.cnpj, txt.email, txt.telefone_hot, txt.nome_respo, txt.telefone_respo, txt.lucro);

        if (hot < 0) {

            printf("!! Erro em salvar os dados do hotel!!");

            exit(1);
        }

        //      Endereço

        end = fprintf(altera, "%0.0f;%s;%s;%s;%0.0f;", txt.local.cep, txt.local.cidade, txt.local.bairro, txt.local.rua, txt.local.numero);

        if (end < 0) {

            printf("!! Erro em salvar o endereço do hotel !!");

            exit(1);
        }

        chek = fprintf(altera, "%d;%d;%d;%d;\n", txt.in.hora, txt.in.min, txt.out.hora, txt.out.min);

        if (chek < 0) {

            printf("!! Erro em salvar os dados de check-in e check-out do hotel !!");

            exit(1);
        }
    }

    fclose(le);

    //coleta os novos dados
    txt = le_dados_hotel();

    //salva os novos dados no arquivo txt
    hot = fprintf(altera, "%s;%s;%s;%s;%s;%0.0f;%s;%0.0f;%0.0f;", txt.nome_hot, txt.raz_soci, txt.inscri_estad, txt.cnpj, txt.email, txt.telefone_hot, txt.nome_respo, txt.telefone_respo, txt.lucro);

    if (hot < 0) {

        printf("!! Erro em salvar os dados do hotel!!");

        exit(1);
    }

    //      Endereço

    end = fprintf(altera, "%0.0f;%s;%s;%s;%0.0f;", txt.local.cep, txt.local.cidade, txt.local.bairro, txt.local.rua, txt.local.numero);

    if (end < 0) {

        printf("!! Erro em salvar o endereço do hotel !!");

        exit(1);
    }

    chek = fprintf(altera, "%d;%d;%d;%d;\n", txt.in.hora, txt.in.min, txt.out.hora, txt.out.min);

    if (chek < 0) {

        printf("!! Erro em salvar os dados de check-in e check-out do hotel !!");

        exit(1);
    }

    fclose(altera);

    //remove arquivo antigo
    remove("hotel.txt");
    //renomeia o arquivo temporário
    rename("temp.txt", "hotel.txt");
}

void exclui_hotel_txt() {
    FILE *deletar, *altera;
    hotel txt;
    int hot, end, chek;
    char linha[sizeof (hotel)], *token;

    deletar = fopen("hotel.txt", "r");

    altera = fopen("temp.txt", "a");
    if (altera == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }

    // lê linha a linha do arquivo, armazenando os dados antigos, fazendo exclusão lógica
    while (fgets(linha, sizeof (hotel), deletar) != NULL) {
        // exclui logicamente os dados
        txt.delet = 1;
        //pega cada dado e adiciona a um campo da struct o transformando para o tipo do dado
        token = strtok(linha, ";");
        strcpy(txt.nome_hot, token);
        token = strtok(NULL, ";");
        strcpy(txt.raz_soci, token);
        token = strtok(NULL, ";");
        strcpy(txt.inscri_estad, token);
        token = strtok(NULL, ";");
        strcpy(txt.cnpj, token);
        token = strtok(NULL, ";");
        strcpy(txt.email, token);
        token = strtok(NULL, ";");
        txt.telefone_hot = atoff(token);
        token = strtok(NULL, ";");
        strcpy(txt.nome_respo, token);
        token = strtok(NULL, ";");
        txt.telefone_respo = atoff(token);
        token = strtok(NULL, ";");
        txt.lucro = atoff(token);
        token = strtok(NULL, ";");
        txt.local.cep = atoff(token);
        token = strtok(NULL, ";");
        strcpy(txt.local.cidade, token);
        token = strtok(NULL, ";");
        strcpy(txt.local.bairro, token);
        token = strtok(NULL, ";");
        strcpy(txt.local.rua, token);
        token = strtok(NULL, ";");
        txt.local.numero = atoff(token);
        token = strtok(NULL, ";");
        txt.in.hora = atoi(token);
        token = strtok(NULL, ";");
        txt.in.min = atoi(token);
        token = strtok(NULL, ";");
        txt.out.hora = atoi(token);
        token = strtok(NULL, ";");
        txt.out.hora = atoi(token);

        // salva os dados antigos com exclusão lógica
        hot = fprintf(altera, "%d;%s;%s;%s;%s;%s;%0.0f;%s;%0.0f;%0.0f;", txt.delet, txt.nome_hot, txt.raz_soci, txt.inscri_estad, txt.cnpj, txt.email, txt.telefone_hot, txt.nome_respo, txt.telefone_respo, txt.lucro);

        if (hot < 0) {

            printf("!! Erro em salvar os dados do hotel!!");

            exit(1);
        }

        //      Endereço

        end = fprintf(altera, "%0.0f;%s;%s;%s;%0.0f;", txt.local.cep, txt.local.cidade, txt.local.bairro, txt.local.rua, txt.local.numero);

        if (end < 0) {

            printf("!! Erro em salvar o endereço do hotel !!");

            exit(1);
        }

        chek = fprintf(altera, "%d;%d;%d;%d;\n", txt.in.hora, txt.in.min, txt.out.hora, txt.out.min);

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


//  Acomodação

//tipo:

void salva_cadastro_tipo_acomodacao_txt(cate_aco dados) {
    FILE *salva;
    int salvar;

    salva = fopen("categoria_acomo.txt", "a");
    if (salva == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%s;%0.2f;%d;\n", dados.delet, dados.codigo, dados.descri, dados.diaria, dados.qnt_pessoas);
    if (salvar < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        printf("Salvo com sucesso!\n");
    }

    fclose(salva);
}

void salva_cadastro_tipo_acomodacao_bin(cate_aco dados) {
    FILE *arquivo;

    arquivo = fopen("categoria_acomo.bin", "ab");

    if (arquivo == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    fwrite(&dados, sizeof (cate_aco), 1, arquivo);

    printf("Tipo de acomodação salvo com sucesso");

    fclose(arquivo);
}

void le_todos_tipo_acomodacao() {
    FILE *ler;
    cate_aco acomodacao;
    char linha[(sizeof (cate_aco))], *token;

    ler = fopen("categoria_acomo.bin", "rb");

    while (fread(&acomodacao, sizeof (cate_aco), 1, ler)) {
        if (acomodacao.delet == 0) {
            printf("\nCódigo: %.0f\n\tDescrição: %s\n\tValor diária: %.2f\n\tNúmero de pessoas: %d",
                    acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
        }
    }

    fclose(ler);

    ler = fopen("categoria_acomo.txt", "r");
    if (ler == NULL) {
        printf("Erro de abertura de arquivo !\n");
        exit(1);
    }

    while (fgets(linha, sizeof (cate_aco), ler)) {
        token = strtok(linha, ";");

        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            printf("\nCódigo: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Descrição: %s\n\t", token);
            token = strtok(NULL, ";");
            printf("Diária: R$%s\n\t", token);
            token = strtok(NULL, ";");
            printf("Quantia de pessoas que suporta: %s\n", token);
        }
    }

    fclose(ler);
}

void le_tipo_acomodacao(float codigo) {
    FILE *ler;
    cate_aco acomodacao;
    char linha[(sizeof (cate_aco))], *token;
    int encontrado = 0;

    ler = fopen("categoria_acomo.bin", "rb");

    while (fread(&acomodacao, sizeof (cate_aco), 1, ler)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            printf("\nCódigo: %.0f\nDescrição: %s\nValor diária: %.2f\nNúmero de pessoas: %d",
                    acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
            encontrado = 1;
        }
    }

    fclose(ler);

    //Testar se essa comparação esta funcionando

    if (encontrado == 0) {
        char cod;
        ler = fopen("categoria_acomo.txt", "r");
        if (ler == NULL) {
            printf("Erro de abertura de arquivo !\n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), ler)) {
            token = strtok(linha, ";");

            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                cod = atoff(token);

                //se o código foi igual ao digitado ele altera
                if (cod == codigo) {
                    printf("\nCódigo: %s\n", token);
                    token = strtok(NULL, ";");
                    printf("Descrição: %s\n", token);
                    token = strtok(NULL, ";");
                    printf("Diária: R$%s\n", token);
                    token = strtok(NULL, ";");
                    printf("Quantia de pessoas que suporta: %s\n", token);
                }
            }
        }

        fclose(ler);
    }
}

void altera_tipo_acomodacao() {
    FILE *le, *altera;
    cate_aco acomodacao, novo;
    char linha[(sizeof (cate_aco))], *token;
    int tam = 0, encontrado = 0, i = 0;
    float codigo;

    printf("Digite o código do tipo da acomodação que deseja alterar: \n");
    scanf("%f", &codigo);

    le = fopen("categoria_acomo.bin", "rb+wb");

    while (fread(&acomodacao, sizeof (cate_aco), 1, le)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            acomodacao = le_dados_categ_acomod();
            acomodacao.codigo = codigo;
            fseek(le, -sizeof (cate_aco), SEEK_CUR);
            fwrite(&acomodacao, sizeof (cate_aco), 1, le);
            encontrado = 1;
            printf("Tipo de acomodação alterado com sucesso!");
            break;
        }
    }

    fclose(le);
    
    if (encontrado == 0) {
        le = fopen("categoria_acomo.txt", "r");
        if (le == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le) != NULL) {
            tam++;
        }

        fclose(le);

        cate_aco dados[tam];

        le = fopen("categoria_acomo.txt", "r");
        if (le == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le) != NULL) {
            token = strtok(linha, ";");

            if (strcmp(token, "0") == 0) {
                dados[i].delet = atoi(token);
                token = strtok(NULL, ";");
                dados[i].codigo = atoff(token);

                if (dados[i].codigo == codigo) {
                    dados[i] = le_dados_categ_acomod();
                    dados[i].codigo = codigo;
                    encontrado = 1;
                } else {
                    token = strtok(NULL, ";");
                    strcpy(dados[i].descri, token);
                    token = strtok(NULL, ";");
                    dados[i].diaria = atoff(token);
                    token = strtok(NULL, ";");
                    dados[i].qnt_pessoas = atoi(token);
                }
            } else {
                dados[i].delet = atoi(token);
                token = strtok(NULL, ";");
                dados[i].codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(dados[i].descri, token);
                token = strtok(NULL, ";");
                dados[i].diaria = atoff(token);
                token = strtok(NULL, ";");
                dados[i].qnt_pessoas = atoi(token);
            }

            fprintf(altera, "%d;%0.0f;%s;%0.2f;%d", dados[i].delet, dados[i].codigo, dados[i].descri, dados[i].diaria, dados[i].qnt_pessoas);
            i++;
        }
        fclose(altera);
        fclose(le);

        if (encontrado == 1) {
            printf("Dados alterados com sucesso!\n");
        } else {
            printf("Código digitado não encontrado!\n");
        }

        remove("categoria_acomo.txt");
        rename("temp.txt", "categoria_acomo.txt");
    }
}

void remover_tipo_acomodacao() {
    FILE *remover, *le;
    cate_aco acomodacao;
    char linha[(sizeof (cad_clie))], *token;
    int tam = 0, i = 0, encontrado = 0;
    float codigo;

    printf("Digite o código do cliente a ser excluido:\n");
    scanf("%f", &codigo);

    le = fopen("categoria_acomo.bin", "rb+wb");

    while (fread(&acomodacao, sizeof (cate_aco), 1, le)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            acomodacao.delet = 1;
            fseek(le, -sizeof (cate_aco), 1);
            fwrite(&acomodacao, sizeof (cate_aco), 1, le);
            encontrado = 1;
            break;
        }
    }

    fclose(le);

    if (encontrado == 0) {
        le = fopen("categoria_acomo.txt", "r");
        if (le == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le) != NULL) {
            tam++;
        }

        fclose(le);

        cate_aco dados[tam];

        le = fopen("categoria_acomo.txt", "r");
        if (le == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        remover = fopen("temp.txt", "r+w");
        if (remover == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le) != NULL) {
            token = strtok(linha, ";");

            if (strcmp(token, "0") == 0) {
                dados[i].delet = atoi(token);
                token = strtok(NULL, ";");
                dados[i].codigo = atoff(token);

                if (dados[i].codigo == codigo) {
                    dados[i].delet = 1;
                    token = strtok(NULL, ";");
                    strcpy(dados[i].descri, token);
                    token = strtok(NULL, ";");
                    dados[i].diaria = atoff(token);
                    token = strtok(NULL, ";");
                    dados[i].qnt_pessoas = atoi(token);
                    encontrado = 1;
                } else {
                    token = strtok(NULL, ";");
                    strcpy(dados[i].descri, token);
                    token = strtok(NULL, ";");
                    dados[i].diaria = atoff(token);
                    token = strtok(NULL, ";");
                    dados[i].qnt_pessoas = atoi(token);
                }
            } else {
                dados[i].delet = atoi(token);
                token = strtok(NULL, ";");
                dados[i].codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(dados[i].descri, token);
                token = strtok(NULL, ";");
                dados[i].diaria = atoff(token);
                token = strtok(NULL, ";");
                dados[i].qnt_pessoas = atoi(token);
            }

            fprintf(remover, "%d;%0.0f;%s;%0.2f;%d", dados[i].delet, dados[i].codigo, dados[i].descri, dados[i].diaria, dados[i].qnt_pessoas);
            i++;
        }

        fclose(remover);
        fclose(le);
    }

    if (encontrado == 1) {
        printf("Dados deletados com sucesso!\n");
    } else {
        printf("Código digitado não encontrado!\n");
    }
}

//geral:

void salva_cadastro_acomodacao_txt(acomodacao dados) {
    FILE *salva, *tipo;
    char linha[(sizeof (cate_aco))], *token;
    float codigo;
    int valido = 0, op = 0, salvar;
    acomodacao dados_geral = dados;
    cate_aco dados_tipo;

    while (valido == 0) {
        le_todos_tipo_acomodacao();
        
        setbuf(stdin, NULL);
        printf("Digite o código do tipo de acomodação:\n");
        scanf("%f", &codigo);
        setbuf(stdin, NULL);

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
            
            while(fread(&dados_tipo, sizeof(cate_aco), 1, tipo)){
                if (dados_tipo.delet == 0 && dados_tipo.codigo == codigo) {
                    dados_geral.tipo.delet = dados_tipo.delet;
                    dados_geral.tipo.codigo = dados_tipo.codigo;
                    strcpy(dados_geral.tipo.descri, dados_tipo.descri);
                    dados_geral.tipo.diaria = dados_tipo.diaria;
                    dados_geral.tipo.qnt_pessoas = dados_tipo.qnt_pessoas;
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
            }
            else {
                printf("Salvo com sucesso!\n");
            }
        }
        else {
            printf("Código da acomodação é inválido!\n");
        }

        fclose(salva);
    }
}

void salva_cadastro_acomodacao_bin(acomodacao dados) {
    FILE *arquivo;

    arquivo = fopen("acomodacoes.bin", "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomodações!");
    } else {
        fwrite(&dados, sizeof (acomodacao), 1, arquivo);
        printf("Acomodação cadastrada com sucesso!");
    }
}

void le_todas_acomodacoes() {
    FILE *arquivo;
    char linha[(sizeof(acomodacao))], *token;
    float codigo;
    acomodacao acomod;
    
    arquivo = fopen("acomodacoes.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de acomofações!");
    } else {
        while (fread(&acomod, sizeof (acomodacao), 1, arquivo)) {
            if (acomod.delet == 0) {
                printf("\nCódigo: %.0f\n\tDescrição: %s\n\tFacilidades: %s",
                        acomod.codigo, acomod.descri, acomod.facilidades);
                printf("\nTipo acomodação:\n");
                le_tipo_acomodacao(acomod.tipo.codigo);
            }
        }
    }
    
    fclose(arquivo);
        
    arquivo = fopen("acomodacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo txt!\n");
        exit(1);
    }
    else {
        while (fgets(linha, sizeof(acomodacao), arquivo)) {
            //separa o primeiro elemento que diz se foi excluido ou não
            token = strtok(linha, ";");
            //caso não tenha sido excluido
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                printf("Código do quarto: %s\n", token);
                token = strtok(NULL, ";");
                printf("Descrição: %s\n", token);
                token = strtok(NULL, ";");
                printf("Facilidades: %s\n", token);
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
    char linha[(sizeof (acomodacao))], linha_tipo[(sizeof(cate_aco))], *token, cod_str[(sizeof(float))];
    int tam = 0, encontrado = 0, i = 0, op = 0, alterado = 0, salvar;
    float codigo, tipo_cod;

    printf("Digite o código da acomodação que deseja alterar: \n");
    scanf("%f", &codigo);
    
    le = fopen("acomodacoes.bin", "rb+wb");
    if (le == NULL) {
        printf("Erro de abertura de arquivo acomodacoes.bin!\n");
        exit(1);
    }
    
    /*
     Senhor André refaz ou conserta essa buceta aqui pra mim? c quiser usar o txt de base, acho q ta funfando ksakasks
    */
    
    while (fread(&acomod, sizeof(acomodacao), 1, le)) {
        if (acomod.delet == 0 && acomod.codigo == codigo) {
            encontrado = 1;
            acomod = le_dados_acomod();
            acomod.codigo = codigo;
            fseek(le, -sizeof(acomodacao), SEEK_CUR);
            fwrite(&acomod, sizeof(acomodacao), 1, le);
            printf("Acomodação alterada com sucesso!");
        }
    }
    
    fclose(le);
    
    if (encontrado == 0) {
        le = fopen("acomodacoes.txt", "r");
        if (le == NULL) {
            printf("Erro de abertura de arquivo acomodacoes.txt!\n");
            exit(1);
        }
        
        while(fgets(linha, sizeof(acomodacao), le)) {
            tam++;
        }
        
        fclose(le);
        
        acomodacao dados[tam];
        
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
        
        while(fgets(linha, sizeof(acomodacao), le)) {
            token = strtok(linha, ";");
            dados[i].delet == atoi(token);
            
            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                dados[i].codigo = atoff(token);
                if (dados[i].codigo == codigo) {
                    token = strtok(NULL, ";");
                    strcpy(dados[i].descri, token);
                    token = strtok(NULL, ";");
                    strcpy(dados[i].facilidades, token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.delet = atoi(token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.codigo = atoff(token);
                    token = strtok(NULL, ";");
                    strcpy(dados[i].tipo.descri, token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.diaria = atoff(token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.qnt_pessoas = atoi(token);
                    tipo_aco = dados[i].tipo;
                    dados[i] = le_dados_acomod();
                    dados[i].codigo = codigo;
                    dados[i].tipo = tipo_aco;

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

                            while(fgets(linha_tipo, sizeof(cate_aco), tipo)) {
                                token = strtok(linha_tipo, ";");

                                if (strcmp(token, "0") == 0) {
                                    token = strtok(NULL, ";");

                                    if (strcmp(token, cod_str) == 0) {
                                        dados[i].tipo.delet = 0;
                                        dados[i].tipo.codigo = atoff(token);
                                        token = strtok(NULL, ";");
                                        strcpy(dados[i].tipo.descri, token);
                                        token = strtok(NULL, ";");
                                        dados[i].tipo.diaria = atoff(token);
                                        token = strtok(NULL, ";");
                                        dados[i].tipo.diaria = atoi(token);
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

                                while(fread(&tipo_aco, sizeof(cate_aco), 1, tipo)){
                                    if (tipo_aco.delet == 0 && tipo_aco.codigo == tipo_cod) {
                                        dados[i].tipo.delet = tipo_aco.delet;
                                        dados[i].tipo.codigo = tipo_aco.codigo;
                                        strcpy(dados[i].tipo.descri, tipo_aco.descri);
                                        dados[i].tipo.diaria = tipo_aco.diaria;
                                        dados[i].tipo.qnt_pessoas = tipo_aco.qnt_pessoas;
                                        alterado = 1;
                                    }
                                }

                                fclose(tipo);
                            }

                            break;
                        case 2:
                            dados[i].tipo = tipo_aco;
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                }
                else {
                    token = strtok(NULL, ";");
                    strcpy(dados[i].descri, token);
                    token = strtok(NULL, ";");
                    strcpy(dados[i].facilidades, token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.delet = atoi(token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.codigo = atoff(token);
                    token = strtok(NULL, ";");
                    strcpy(dados[i].tipo.descri, token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.diaria = atoff(token);
                    token = strtok(NULL, ";");
                    dados[i].tipo.qnt_pessoas = atoi(token);
                }
            }
            
            salvar = fprintf(altera, "%d;%0.0f;%s;%s;%d;%0.0f;%s;%0.2f;%d;\n", dados[i].delet, dados[i].codigo, dados[i].descri, dados[i].facilidades, dados[i].tipo.delet, dados[i].tipo.codigo, dados[i].tipo.descri, dados[i].tipo.diaria, dados[i].tipo.qnt_pessoas);
            if (salvar < 0) {
                printf("Erro no salvamento do arquivo!\n");
                exit(1);
            }
            
            i++;
        }
        
        fclose(le);
        fclose(altera);
        
        remove("acomodacoes.txt");
        rename("temp.txt", "acomodacoes.txt");
    }
    
    if (encontrado == 0) {
        printf("Código digitado não encontrado!\n");
    }
    else {
        printf("Alterado com sucesso!\n");
    }
}