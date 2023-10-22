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

int tam_produto() {
    int tamanho = 0;
    
    tamanho = sizeof(produto) - sizeof(float);
    
    return tamanho;
}

int tam_fornecedor() {
    int tamanho = 0;
    
    tamanho = sizeof(fornecedor) - sizeof(float);
    
    return tamanho;
}

int tam_operador() {
    int tamanho = 0;
    
    tamanho = sizeof(operador) - sizeof(float);
    
    return tamanho;
}

int tam_reserva() {
    int tamanho = 0;
    
    tamanho = sizeof(reserva) - sizeof(float);
    
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
    char bin[30] = "cliente.bin", txt[30] = "cliente.txt";

    cad_clie dados;

    dados.delet = 0;

    dados.codigo = retorna_id(txt, bin, tam_clientes());

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

cate_aco le_dados_categ_acomod() {
    //variaveis
    cate_aco dados;
    char bin[30] = "categoria_acomo.bin", txt[30] = "categoria_acomo.txt";

    //coleta de dados
    dados.delet = 0;
    dados.codigo = retorna_id(txt, bin, tam_categ_acomod());
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
    char txt[30] = "acomodacoes.txt", bin[30] = "acomodacoes.bin";
    acomodacao dados;

    //coleta de dados
    dados.codigo = retorna_id(txt, bin, tam_acomodacao());
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

produto le_dados_produto() {
    // variaveis
    produto dados;
    char txt[30] = "produtos.txt", bin[30] = "produtos.bin";

    //coleta dados
    dados.codigo = retorna_id(txt, bin, tam_produto());
    setbuf(stdin, NULL);
    printf("Digite a descrição do produto: \n");
    scanf("%[a-z A-Z][^\n]s", dados.descricao);
    setbuf(stdin, NULL);
    printf("Digite o estoque do produto: \n");
    scanf("%d", &dados.estoque);
    setbuf(stdin, NULL);
    printf("Digite o estoque minimo do produto: \n");
    scanf("%d", &dados.estoque_min);
    setbuf(stdin, NULL);
    printf("Digite o preço de custo do produto: \n");
    scanf("%f", &dados.custo);
    setbuf(stdin, NULL);
    printf("Digite o preço de venda do produto: \n");
    scanf("%f", &dados.venda);
    dados.delet = 0;
    return dados;
}

fornecedor le_dados_fornecedor() {
    //variaveis
    fornecedor dados;
    char txt[30] = "fornecedores.txt", bin[30] = "fornecedores.bin";
    
    //coleta dados
    dados.codigo = retorna_id(txt, bin, tam_fornecedor());
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
    scanf("%f", &dados.telefone);
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
    scanf("%f", &dados.local.cep);
    setbuf(stdin, NULL);
    printf("Digite o bairro do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.bairro);
    setbuf(stdin, NULL);
    printf("Digite a rua do fornecedor: \n");
    scanf("%[a-z A-Z][^\n]s", dados.local.rua);
    setbuf(stdin, NULL);
    printf("Digite o número do fornecedor: \n");
    scanf("%f", &dados.local.numero);
    dados.delet = 0;
    return dados;
}

operador le_dados_operador() {
    //variaveis
    operador dados;
    char txt[30] = "operadores.txt", bin[30] = "operadores.bin";

    //coleta dados
    dados.codigo = retorna_id(txt, bin, tam_operador());
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

    dados.delet = 0;
    dados.codigo = retorna_id(txt, bin, tam_reserva());
    
    printf("Digite o código do quarto: ");
    scanf("%f", &dados.codQuarto);
    printf("\nDigite a data de entrada:\n");
    dados.inicio = le_dados_data();
    printf("\nDigite a data de saída:\n");
    dados.fim = le_dados_data();

    return dados;
}
//MENUS:

void menuPrincipal() {
    int opcao = 99, binOUtxt = 0;

    setbuf(stdin, NULL);
    while (opcao != 0) {
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tHotel - 1\n");
        printf("\tClientes - 2\n");
        printf("\tReservas - 3\n");
        printf("\tAcomodações - 4\n");
        printf("\tProdutos - 5\n");
        printf("\tFornecedores - 6\n");
        printf("\tOperadores - 7\n");
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
            case 5:
                menuProdutos(binOUtxt);
                break;
            case 6:
                menuFornecedores(binOUtxt);
                break;
            case 7:
                menuOperadores(binOUtxt);
                break;
            case 9:
                binOUtxt = selecionarTipoArquivo();
                break;
            default:
                printf("Opcao invalida, digite novamente: ");
                scanf("%d", &opcao);
                break;
        }
    }
    printf("Fechando programa...");
    exit(1);
}

void menuHotel() {
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
    menuPrincipal();
}

void menuCliente(int tipoArquivo) {
    int opcao = 0;
    cad_clie dados;
    while (opcao != 6) {
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
                if (tipoArquivo == 0) {
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
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        printf("\nPRESSIONE QUALQUER TECLA PARA CONTINUAR...");
        getchar();
    }
    menuPrincipal();
}

void menuReserva(int tipoArquivo) {
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
    menuPrincipal();
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

void menuProdutos(int tipoAquivo) {
    int opcao = 0;
    produto dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de produtos - 1\n");
        printf("\tListar todos os produtos - 2\n");
        printf("\tListar um dos produtos - 3\n");
        printf("\tAlterar produtos - 4\n");
        printf("\tExcluir produtos - 5\n");
        printf("\tVoltar ao menu principal - 6\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_produto();
                if (tipoAquivo == 0) {
                    salva_cadastro_produtos_bin(dados);
                } else {
                    salva_cadastro_produtos_txt(dados);
                }
                break;
            case 2:
                le_todos_produtos();
                break;
            case 3:
                le_produtos();
                break;
            case 4:
                altera_produto();
                break;
            case 5:
                exclui_produto();
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        getchar();
    }
    menuPrincipal();
}

void menuFornecedores(int tipoAquivo) {
    int opcao = 0;
    fornecedor dados;
    while (opcao != 6) {

        setbuf(stdin, NULL);

        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tCadastro de fornecedores - 1\n");
        printf("\tListar todos os fornecedores - 2\n");
        printf("\tListar um dos fornecedores - 3\n");
        printf("\tAlterar fornecedores - 4\n");
        printf("\tExcluir fornecedores - 5\n");
        printf("\tVoltar ao menu principal - 6\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dados = le_dados_fornecedor();
                if (tipoAquivo == 0) {
                    salva_cadastro_fornecedores_bin(dados);
                } else {
                    salva_cadastro_fornecedores_txt(dados);
                }
                break;
            case 2:
                le_todos_fonecedores();
                break;
            case 3:
                le_fonecedor();
                break;
            case 4:
                altera_fonecedor();
                break;
            case 5:
                exclui_fonecedor();
                break;
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
        getchar();
    }
    menuPrincipal();
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
    menuPrincipal();
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
    FILE *arquivoBin, *le, *altera;
    cad_clie cliente, novo;
    int encontrado = 0;
    float codigo;
    char linha[(sizeof(cad_clie))], *token;

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
                cliente.delet = atoi(token);
                token = strtok(NULL, ";");
                cliente.codigo = atoff(token);

                //se o código foi igual ao digitado ele altera
                if (cliente.codigo == codigo) {
                    cliente = le_dados_cad();
                    cliente.codigo = codigo;
                    encontrado = 1;
                }//caso o código digitado seja diferente
                else {
                    token = strtok(NULL, ";");
                    strcpy(cliente.nome, token);
                    token = strtok(NULL, ";");
                    cliente.cpf = atoff(token);
                    token = strtok(NULL, ";");
                    cliente.telefone = atoff(token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.email, token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.sexo, token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.estado_civil, token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.nascimento, token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.local.estado, token);
                    token = strtok(NULL, ";");
                    cliente.local.cep = atoff(token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.local.cidade, token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.local.bairro, token);
                    token = strtok(NULL, ";");
                    strcpy(cliente.local.rua, token);
                    token = strtok(NULL, ";");
                    cliente.local.numero = atoff(token);
                }
            }//caso os dados já tenham sido deletados
            else {
                cliente.delet = atoi(token);
                token = strtok(NULL, ";");
                cliente.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(cliente.nome, token);
                token = strtok(NULL, ";");
                cliente.cpf = atoff(token);
                token = strtok(NULL, ";");
                cliente.telefone = atoff(token);
                token = strtok(NULL, ";");
                strcpy(cliente.email, token);
                token = strtok(NULL, ";");
                strcpy(cliente.sexo, token);
                token = strtok(NULL, ";");
                strcpy(cliente.estado_civil, token);
                token = strtok(NULL, ";");
                strcpy(cliente.nascimento, token);
                token = strtok(NULL, ";");
                strcpy(cliente.local.estado, token);
                token = strtok(NULL, ";");
                cliente.local.cep = atoff(token);
                token = strtok(NULL, ";");
                strcpy(cliente.local.cidade, token);
                token = strtok(NULL, ";");
                strcpy(cliente.local.bairro, token);
                token = strtok(NULL, ";");
                strcpy(cliente.local.rua, token);
                token = strtok(NULL, ";");
                cliente.local.numero = atoff(token);
            }

            //salva os dados no arquivo temporario altera 
            fprintf(altera, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", cliente.delet, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
            fprintf(altera, "%s;%0.0f;%s;%s;%s;%0.0f;\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
        }

        fclose(altera);
        fclose(le);
        remove("cliente.txt");
        rename("temp.txt", "cliente.txt");
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
            cliente.delet = atoi(token);
            token = strtok(NULL, ";");
            cliente.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(cliente.nome, token);
            token = strtok(NULL, ";");
            cliente.cpf = atoff(token);
            token = strtok(NULL, ";");
            cliente.telefone = atoff(token);
            token = strtok(NULL, ";");
            strcpy(cliente.email, token);
            token = strtok(NULL, ";");
            strcpy(cliente.sexo, token);
            token = strtok(NULL, ";");
            strcpy(cliente.estado_civil, token);
            token = strtok(NULL, ";");
            strcpy(cliente.nascimento, token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.estado, token);
            token = strtok(NULL, ";");
            cliente.local.cep = atoff(token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.cidade, token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.bairro, token);
            token = strtok(NULL, ";");
            strcpy(cliente.local.rua, token);
            token = strtok(NULL, ";");
            cliente.local.numero = atoff(token);

            if (cliente.codigo == codigo) {
                cliente.delet = 1;
                fprintf(remover, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", cliente.delet, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
                fprintf(remover, "%s;%0.0f;%s;%s;%s;%0.0f;\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
                encontrado = 1;
            } else {
                fprintf(remover, "%d;%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", cliente.delet, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefone, cliente.email, cliente.sexo, cliente.estado_civil, cliente.nascimento);
                fprintf(remover, "%s;%0.0f;%s;%s;%s;%0.0f;\n", cliente.local.estado, cliente.local.cep, cliente.local.cidade, cliente.local.bairro, cliente.local.rua, cliente.local.numero);
            }
        }

        fclose(remover);
        fclose(le);

        remove("cliente.txt");
        rename("temp.txt", "cliente.txt");
    }
    
    if (encontrado == 0) {
        printf("Cliente não encontrado!\n");
    } else {
        printf("Cliente excluido com sucesso!\n");
    }
}

//  Hotel

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
        printf("Categoria de acomodação salva com sucesso!\n");
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

    if (ler == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }

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

    if (ler == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }

    while (fread(&acomodacao, sizeof (cate_aco), 1, ler)) {
        if (acomodacao.delet == 0 && acomodacao.codigo == codigo) {
            printf("\n\tCódigo categoria: %.0f\n\tDescrição: %s\n\tValor diária: %.2f\n\tNúmero de pessoas: %d",
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
                    printf("\nCódigo: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Descrição: %s\n\t", token);
                    token = strtok(NULL, ";");
                    printf("Diária: R$%s\n\t", token);
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

    if (le == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }

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

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le) != NULL) {
            token = strtok(linha, ";");

            if (strcmp(token, "0") == 0) {
                acomodacao.delet = atoi(token);
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);

                if (acomodacao.codigo == codigo) {
                    acomodacao = le_dados_categ_acomod();
                    acomodacao.codigo = codigo;
                    encontrado = 1;
                } else {
                    token = strtok(NULL, ";");
                    strcpy(acomodacao.descri, token);
                    token = strtok(NULL, ";");
                    acomodacao.diaria = atoff(token);
                    token = strtok(NULL, ";");
                    acomodacao.qnt_pessoas = atoi(token);
                }
            } else {
                acomodacao.delet = atoi(token);
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomodacao.descri, token);
                token = strtok(NULL, ";");
                acomodacao.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomodacao.qnt_pessoas = atoi(token);
            }

            fprintf(altera, "%d;%0.0f;%s;%0.2f;%d", acomodacao.delet, acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
        }
        fclose(altera);
        fclose(le);

        remove("categoria_acomo.txt");
        rename("temp.txt", "categoria_acomo.txt");
    }
    
    if (encontrado == 1) {
        printf("Dados alterados com sucesso!\n");
    } else {
        printf("Código digitado não encontrado!\n");
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

    if (le == NULL) {
        printf("Erro ao abrir arquivo de categorias!");
        exit(1);
    }
    
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

        remover = fopen("temp.txt", "a");
        if (remover == NULL) {
            printf("Erro na abertura do arquivo das categorias de acomodações! \n");
            exit(1);
        }

        while (fgets(linha, sizeof (cate_aco), le) != NULL) {
            token = strtok(linha, ";");
            acomodacao.delet = atoi(token);

            if (strcmp(token, "0") == 0) {
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomodacao.descri, token);
                token = strtok(NULL, ";");
                acomodacao.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomodacao.qnt_pessoas = atoi(token);

                if (acomodacao.codigo == codigo) {
                    acomodacao.delet = 1;
                    encontrado = 1;
                }
            } else {
                token = strtok(NULL, ";");
                acomodacao.codigo = atoff(token);
                token = strtok(NULL, ";");
                strcpy(acomodacao.descri, token);
                token = strtok(NULL, ";");
                acomodacao.diaria = atoff(token);
                token = strtok(NULL, ";");
                acomodacao.qnt_pessoas = atoi(token);
            }

            fprintf(remover, "%d;%0.0f;%s;%0.2f;%d", acomodacao.delet, acomodacao.codigo, acomodacao.descri, acomodacao.diaria, acomodacao.qnt_pessoas);
        }

        fclose(remover);
        fclose(le);
        
        remove("categoria_acomo.txt");
        rename("temp.txt", "categoria_acomo.txt");
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

//Produtos

void salva_cadastro_produtos_bin(produto dados) {
    FILE *arquivo;

    arquivo = fopen("produtos.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }
    printf("Codigo do prod: %0.0f", dados.codigo);
    fwrite(&dados, sizeof (produto), 1, arquivo);
    printf("\nProduto cadastrado com sucesso!");
    fclose(arquivo);
}

void salva_cadastro_produtos_txt(produto dados) {
    FILE *salva;
    int salvar;

    salva = fopen("produtos.txt", "a");
    if (salva == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
    if (salvar < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        printf("Salvo com sucesso!\n");
    }

    fclose(salva);
}

void le_produtos() {
    FILE *arquivo;
    float codigo;
    int encontrado = 0;
    produto dados;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja ler: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: %.2f\n\tVenda: %.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de Leitura de arquivo texto!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (produto), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Descrição: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estoque mínimo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estoque atual: %s \n", token);
                token = strtok(NULL, ";");
                printf("Custo do produto: R$%s \n", token);
                token = strtok(NULL, ";");
                printf("Preço de venda: R$%s \n", token);
            }
        }

        fclose(arquivo);
    }
}

void le_todos_produtos() {
    FILE *arquivo;
    produto dados;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0) {
            printf("\nCódigo: %0.0f\n\tDescrição: %s\n\tEstoque mínimo: %d\n\tEstoque atual: %d\n\tCusto: %.2f\n\tVenda: %.2f",
                    dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
        }
    }

    arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro de Leitura de arquivo texto!\n");
        exit(1);
    }

    while (fgets(linha, sizeof (produto), arquivo)) {
        token = strtok(linha, ";");
        if (strcmp(token, "0") == 0) {
            token = strtok(NULL, ";");
            printf("\nCódigo: %s \n", token);
            token = strtok(NULL, ";");
            printf("Descrição: %s \n", token);
            token = strtok(NULL, ";");
            printf("Estoque mínimo: %s \n", token);
            token = strtok(NULL, ";");
            printf("Estoque atual: %s \n", token);
            token = strtok(NULL, ";");
            printf("Custo do produto: R$%s \n", token);
            token = strtok(NULL, ";");
            printf("Preço de venda: R$%s \n", token);
        }
    }

    fclose(arquivo);
}

void altera_produto() {
    FILE *altera, *le;
    float codigo;
    produto dados;
    int encontrado = 0, tam = 0, i = 0, salvar;
    char linha[(sizeof (produto))], *token;

    altera = fopen("produtos.bin", "rb+wb");

    if (altera == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (produto), 1, altera)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados = le_dados_produto();
            fseek(altera, -sizeof (produto), 1);
            fwrite(&dados, sizeof (produto), 1, altera);
            encontrado = 1;
        }
    }

    fclose(altera);

    if (encontrado == 0) {
        le = fopen("produtos.txt", "r");
        if (le == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (altera == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (produto), le)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados = le_dados_produto();
                dados.codigo = codigo;
            } else {
                token = strtok(NULL, ";");
                strcpy(dados.descricao, token);
                token = strtok(NULL, ";");
                dados.estoque_min = atoi(token);
                token = strtok(NULL, ";");
                dados.estoque = atoi(token);
                token = strtok(NULL, ";");
                dados.custo = atoff(token);
                token = strtok(NULL, ";");
                dados.venda = atoff(token);
            }

            salvar = fprintf(altera, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            if (salvar < 0) {
                printf("Erro de salvamento de arquivo texto!\n");
            }
        }

        fclose(le);
        fclose(altera);

        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
    }

    if (encontrado == 0) {
        printf("Produto não encontrado!\n");
    } else {
        printf("Dados alterados com sucesso!\n");
    }
}

void exclui_produto() {

    FILE *arquivo, *exclui;
    float codigo;
    produto dados;
    int encontrado = 0, tam = 0, i = 0, salvar;
    char linha[(sizeof (produto))], *token;

    arquivo = fopen("produtos.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de produtos!");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja excluir: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (produto), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.delet = 1;
            fseek(arquivo, -sizeof (produto), 1);
            fwrite(&dados, sizeof (produto), 1, arquivo);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        exclui = fopen("temp.txt", "a");
        if (exclui == NULL) {
            printf("Erro em abrir produto txt!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (produto), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(dados.descricao, token);
            token = strtok(NULL, ";");
            dados.estoque_min = atoi(token);
            token = strtok(NULL, ";");
            dados.estoque = atoi(token);
            token = strtok(NULL, ";");
            dados.custo = atoff(token);
            token = strtok(NULL, ";");
            dados.venda = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.delet = 1;
                encontrado = 1;
            }

            salvar = fprintf(exclui, "%d;%0.0f;%s;%d;%d;%0.2f;%0.2f;\n", dados.delet, dados.codigo, dados.descricao, dados.estoque_min, dados.estoque, dados.custo, dados.venda);
            if (salvar < 0) {
                printf("Erro de salvamento de arquivo texto!\n");
            }
        }

        fclose(arquivo);
        fclose(exclui);

        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
    }

    if (encontrado == 0) {
        printf("Produto não encontrado!\n");
    } else {
        printf("Dados excluidos com sucesso!\n");
    }
}

//Fornecedor

void salva_cadastro_fornecedores_bin(fornecedor dados) {
    FILE *arquivo;

    arquivo = fopen("fornecedores.bin", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fonecedores!");
        exit(1);
    }
    fwrite(&dados, sizeof (fornecedor), 1, arquivo);

    fclose(arquivo);
}

void salva_cadastro_fornecedores_txt(fornecedor dados) {
    FILE *salva;
    int salvar, local, salvou = 0;

    salva = fopen("fornecedores.txt", "a");
    if (salva == NULL) {
        printf("Erro de criação de arquivo !\n");
        exit(1);
    }

    salvar = fprintf(salva, "%d;%0.0f;%s;%s;%s;%s;%s;%0.0f;", dados.delet, dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
    if (salvar < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        salvou++;
    }

    local = fprintf(salva, "%s;%0.0f;%s;%s;%s;%0.0f;\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
    if (local < 0) {
        printf("Erro no salvamento do tipo de acomodação !\n");
    } else {
        salvou++;
    }

    if (salvou == 2) {
        printf("Salvo com Sucesso!");
    }

    fclose(salva);
}

void le_fonecedor() {
    FILE *arquivo;
    float codigo;
    fornecedor dados;
    int encontrado = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    printf("Digite o codigo do fornecedor que deseja ler: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f",
                    dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone, dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("fornecedores.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (fornecedor), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                printf("\nCódigo: %s \n", token);
                token = strtok(NULL, ";");
                printf("Nome: %s \n", token);
                token = strtok(NULL, ";");
                printf("Razão social: %s \n", token);
                token = strtok(NULL, ";");
                printf("Inscrição estadual: %s \n", token);
                token = strtok(NULL, ";");
                printf("CNPJ: %s \n", token);
                token = strtok(NULL, ";");
                printf("Email: %s \n", token);
                token = strtok(NULL, ";");
                printf("Telefone: %s \n", token);
                token = strtok(NULL, ";");
                printf("Estado: %s \n", token);
                token = strtok(NULL, ";");
                printf("CEP: %s \n", token);
                token = strtok(NULL, ";");
                printf("Cidade: %s \n", token);
                token = strtok(NULL, ";");
                printf("Bairro: %s \n", token);
                token = strtok(NULL, ";");
                printf("Rua: %s \n", token);
                token = strtok(NULL, ";");
                printf("Número: %s \n", token);
                encontrado = 1;
            }
        }

        fclose(arquivo);
    }

    if (encontrado == 0) {
        printf("Nenhum fornecedor encontrado com esse código");
    }
}

void le_todos_fonecedores() {
    FILE *arquivo;
    fornecedor dados;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0) {
            printf("\nCódigo: %0.0f\n\tNome: %s\n\tRazão social: %s\n\tInscrição estadual: %s\n\tCNPJ: %s\n\tEmail: %s\n\tTelefone: %.0f\nDados do local:\n\tEstado: %s\n\tCEP: %.0f\n\tCidade: %s\n\tBairro: %s\n\tRua: %s\n\tNúmero: %.0f",
                    dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone, dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }
    }

    fclose(arquivo);

    arquivo = fopen("fornecedores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro de abertura de arquivo TXT!\n");
        exit(1);
    }

    while (fgets(linha, sizeof (fornecedor), arquivo)) {
        token = strtok(linha, ";");
        dados.delet = atoi(token);

        if (dados.delet == 0) {
            token = strtok(NULL, ";");
            printf("\nCódigo: %s \n", token);
            token = strtok(NULL, ";");
            printf("Nome: %s \n", token);
            token = strtok(NULL, ";");
            printf("Razão social: %s \n", token);
            token = strtok(NULL, ";");
            printf("Inscrição estadual: %s \n", token);
            token = strtok(NULL, ";");
            printf("CNPJ: %s \n", token);
            token = strtok(NULL, ";");
            printf("Email: %s \n", token);
            token = strtok(NULL, ";");
            printf("Telefone: %s \n", token);
            token = strtok(NULL, ";");
            printf("Estado: %s \n", token);
            token = strtok(NULL, ";");
            printf("CEP: %s \n", token);
            token = strtok(NULL, ";");
            printf("Cidade: %s \n", token);
            token = strtok(NULL, ";");
            printf("Bairro: %s \n", token);
            token = strtok(NULL, ";");
            printf("Rua: %s \n", token);
            token = strtok(NULL, ";");
            printf("Número: %s \n", token);
        }
    }

    fclose(arquivo);
}

void altera_fonecedor() {
    FILE *arquivo, *altera;
    float codigo;
    fornecedor dados;
    int encontrado = 0, i = 0, tam = 0, salvar;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    printf("Digite o codigo do fornecedor que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados = le_dados_fornecedor();
            fseek(arquivo, -sizeof (fornecedor), 1);
            fwrite(&dados, sizeof (fornecedor), 1, arquivo);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("fornecedores.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        altera = fopen("temp.txt", "a");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (fornecedor), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados = le_dados_fornecedor();
                dados.codigo = codigo;

                encontrado = 1;
            } else {
                token = strtok(NULL, ";");
                strcpy(dados.nome, token);
                token = strtok(NULL, ";");
                strcpy(dados.raz_soci, token);
                token = strtok(NULL, ";");
                strcpy(dados.inscri_estad, token);
                token = strtok(NULL, ";");
                strcpy(dados.cnpj, token);
                token = strtok(NULL, ";");
                strcpy(dados.email, token);
                token = strtok(NULL, ";");
                dados.telefone = atoff(token);
                token = strtok(NULL, ";");
                strcpy(dados.local.estado, token);
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
            }

            fprintf(altera, "%d;%0.0f;%s;%s;%s;%s;%s;%0.0f;", dados.delet, dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
            fprintf(altera, "%s;%0.0f;%s;%s;%s;%0.0f;\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }

        fclose(arquivo);
        fclose(altera);

        remove("fornecedores.txt");
        rename("temp.txt", "fornecedores.txt");
    }

    if (encontrado == 0) {
        printf("Fornecedor não encontrado!\n");
    } else {
        printf("Dados alterados com sucesso!\n");
    }

}

void exclui_fonecedor() {
    FILE *arquivo, *exclui;
    float codigo;
    fornecedor dados;
    int encontrado = 0, i = 0, tam = 0;
    char linha[(sizeof (fornecedor))], *token;

    arquivo = fopen("fornecedores.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de fornecedores!");
        exit(1);
    }

    printf("Digite o codigo do fornecedor que deseja excluir: ");
    scanf("%f", &codigo);

    while (fread(&dados, sizeof (fornecedor), 1, arquivo)) {
        if (dados.delet == 0 && dados.codigo == codigo) {
            dados.delet = 1;
            fseek(arquivo, -sizeof (fornecedor), 1);
            fwrite(&dados, sizeof (fornecedor), 1, arquivo);
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        arquivo = fopen("fornecedores.txt", "r");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        exclui = fopen("temp.txt", "a");
        if (arquivo == NULL) {
            printf("Erro de abertura de arquivo TXT!\n");
            exit(1);
        }

        while (fgets(linha, sizeof (fornecedor), arquivo)) {
            token = strtok(linha, ";");
            dados.delet = atoi(token);
            token = strtok(NULL, ";");
            dados.codigo = atoff(token);
            token = strtok(NULL, ";");
            strcpy(dados.nome, token);
            token = strtok(NULL, ";");
            strcpy(dados.raz_soci, token);
            token = strtok(NULL, ";");
            strcpy(dados.inscri_estad, token);
            token = strtok(NULL, ";");
            strcpy(dados.cnpj, token);
            token = strtok(NULL, ";");
            strcpy(dados.email, token);
            token = strtok(NULL, ";");
            dados.telefone = atoff(token);
            token = strtok(NULL, ";");
            strcpy(dados.local.estado, token);
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
            if (dados.delet == 0 && dados.codigo == codigo) {
                dados.delet = 1;

                encontrado = 1;
            }

            fprintf(exclui, "%d;%0.0f;%s;%s;%s;%s;%s;%0.0f;", dados.delet, dados.codigo, dados.nome, dados.raz_soci, dados.inscri_estad, dados.cnpj, dados.email, dados.telefone);
            fprintf(exclui, "%s;%0.0f;%s;%s;%s;%0.0f;\n", dados.local.estado, dados.local.cep, dados.local.cidade, dados.local.bairro, dados.local.rua, dados.local.numero);
        }

        fclose(arquivo);
        fclose(exclui);

        remove("fornecedores.txt");
        rename("temp.txt", "fornecedores.txt");
    }

    if (encontrado == 0) {
        printf("Fornecedor não encontrado!\n");
    } else {
        printf("Dados excluídos com sucesso!\n");
    }

}

//Operador

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
    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    int quantPessoas, salva_cod = -1;
    int encontrado_bin = 0, encontrado_txt = 0;
    char linha_rese[(sizeof(reserva))], linha_aco[(sizeof(acomodacao))], *token;
    
    printf("Digite a quantidade de pessoas a ser pesquisada: ");
    scanf("%d", &quantPessoas);

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
            if (reser.delet == 0 && acomod.delet == 0) {
                if (reser.codQuarto == acomod.codigo) {
                    if (acomod.tipo.qnt_pessoas == quantPessoas) {
                        encontrado_bin = 1;
                            if (salva_cod == reser.codQuarto) {
                                printf("Ocupado de: %d/%d/%d até %d/%d/%d\n", reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                            }
                            else {
                                salva_cod = reser.codQuarto;
                                printf("Código do quarto: %0.0f \nOcupado de: %d/%d/%d até %d/%d/%d\n", reser.codQuarto, reser.inicio.dia, reser.inicio.mes, reser.inicio.ano, reser.fim.dia, reser.fim.mes, reser.fim.ano);
                            }
                    }
                } else {
                    if (acomod.tipo.qnt_pessoas == quantPessoas){
                        printf("\nNão existe reservas cadastradadas para o quarto: %0.0f com capacidade para %d pessoa(s)", 
                        acomod.codigo, acomod.tipo.qnt_pessoas);
                    }
                }
            }
        }
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

            if (reser.delet == 0 && acomod.delet == 0) {
                if (reser.codQuarto == acomod.codigo) {
                    // compara se dentro da string facilidade do quarto há a facilidade escrita pela pessoa (pode dar erro por diferenciar maiuscula e minuscula, a ordem importa caso hajá mais de 1 palavra)
                    if (acomod.tipo.qnt_pessoas == quantPessoas) {
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
                } else {
                            if (acomod.tipo.qnt_pessoas == quantPessoas){
                                printf("\nNão existe reservas cadastradadas para o quarto: %0.0f com capacidade para %d pessoa(s)", 
                                acomod.codigo, acomod.tipo.qnt_pessoas);
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
            if (reser.delet == 0 && acomod.delet == 0) {
                if (reser.codQuarto == acomod.codigo) {
                    if (acomod.tipo.qnt_pessoas == quantPessoas){
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
                } else {
                        if (acomod.tipo.qnt_pessoas == quantPessoas){
                            printf("\nNão existe reservas cadastradadas para o quarto: %0.0f com capacidade para %d pessoa(s)", 
                            acomod.codigo, acomod.tipo.qnt_pessoas);
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
                        if (acomod.tipo.qnt_pessoas == quantPessoas){
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
                    } else {
                            if (acomod.tipo.qnt_pessoas == quantPessoas){
                                printf("\nNão existe reservas cadastradadas para o quarto: %0.0f com capacidade para %d pessoa(s)", 
                                acomod.codigo, acomod.tipo.qnt_pessoas);
                            }
                        }
                }
            }
        }
    }

    fclose(acomo_txt);

    fclose(rese_txt);
}

void pesquisa_reserva_Categoria() {
    FILE *rese_txt, *rese_bin, *acomo_bin, *acomo_txt;
    reserva reser;
    acomodacao acomod;
    float codigoCategoria, salva_cod = -1;
    int encontrado_bin = 0, encontrado_txt = 0;
    char linha_rese[(sizeof(reserva))], linha_aco[(sizeof(acomodacao))], *token;
    
    printf("Digite a categoria a ser pesquisada: ");
    scanf("%f", &codigoCategoria);

    //abre reserva binario
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
    
    acomo_txt = fopen("acomodacoes.txt", "r");
    if (acomo_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }

    //verificar na acomodação binaria
    while(fread(&reser, sizeof(reserva), 1, rese_bin)) {
        encontrado_bin = 0;

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        fseek(acomo_txt, 0, SEEK_SET);
        
        //verifica na parte binaria
        while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
            if (reser.delet == 0 && acomod.delet == 0) {
                if (reser.codQuarto == acomod.codigo) {
                    encontrado_bin = 1;
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
        
        //verifica no txt
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
                        if (acomod.tipo.codigo == codigoCategoria){
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
                    } else{
                        if (acomod.tipo.codigo == codigoCategoria) {
                            printf("\nNão existe reservas cadastradadas para o quarto: %0.0f da categoria: %.0f", 
                            acomod.codigo, acomod.tipo.codigo);
                        }
                }
                }
            }
        }
    }

    fclose(rese_bin);
    
    //abre reserva txt
    rese_txt = fopen("reservas.txt", "r");
    if (rese_txt == NULL) {
        printf("Erro de abertura de arquivo reservas.bin!\n");
        exit(1);
    }
    
    //verificar na acomodação txt
    while(fgets(linha_rese, sizeof(reserva), rese_txt)) {
        encontrado_txt = 0;
        
        //passa dados do txt para variavel
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

        // reposiciona o cursor no inicio do arquivo
        fseek(acomo_bin, 0, SEEK_SET);
        fseek(acomo_txt, 0, SEEK_SET);
        
        //verifica na parte binaria
        while(fread(&acomod, sizeof(acomodacao), 1, acomo_bin)) {
            if (reser.delet == 0 && acomod.delet == 0) {
                if (reser.codQuarto == acomod.codigo) {
                    encontrado_bin = 1;
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
        
        //verifica no txt
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
                        if (acomod.tipo.codigo == codigoCategoria){
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
                    } else{
                        if (acomod.tipo.codigo == codigoCategoria) {
                            printf("\nNão existe reservas cadastradadas para o quarto: %0.0f da categoria: %.0f", 
                            acomod.codigo, acomod.tipo.codigo);
                        }
                    }
                }
            }
        }
    }

    fclose(acomo_txt);
    fclose(acomo_bin);
    fclose(rese_txt);
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
