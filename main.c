/////////////////////////////   Bibliotecas  \\\\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

/////////////////////////////   Structs  \\\\\\\\\\\\\\\\\\\\\\\\\

//struct moradia
typedef struct {
    char rua[150], bairro[100], cidade[100], estado[2];
    float numero, cep;

} endereco;

//struct check
typedef struct {
    int hora, min;
}check;

//struct cadastro hotel
typedef struct {
    char nome_hot[100], nome_respo[100], raz_soci[150], inscri_estad[100], cnpj[50], email[150];
    endereco local;
    float telefone_hot, telefone_respo, lucro;
    check in, out;
    
}hotel;

// struct cadastro cliente
typedef struct {
    float codigo, cpf, telefone;
    char nome[100], email[150], sexo[50], estado_civil[50], nascimento[15];
    endereco local;

} cad_clie;

//struct categoria acomodações
typedef struct {
    char descri[300];
    float diaria;
    int codigo, qnt_pessoas;
    
}cate_aco;

//struct acomodações
typedef struct {
    float codigo;
    char descri[300], facilidades[300];
    cate_aco tipo;
    
}acomodacao;

//struct produtos
typedef struct {
    int codigo, estoque, estoque_min;
    float custo, venda;
    char descricao[300];
    
}produto;

//struct fornecedores
typedef struct {
    int codigo;
    char nome[100], raz_soci[150], inscri_estad[100], cnpj[50], email[150];
    float telefone;
    endereco local;
    
}fornecedor;

//struct operadores sistema
typedef struct {
    int codigo, acesso;
    char nome[100], user[100], senha[100];
    
}operador;

/////////////////////////////   Indicar subrotinas  \\\\\\\\\\\\\\\\\\\\\\\\\\\\

//Coleta dados

cad_clie le_dados_cad();

hotel le_dados_hotel();

acomodacao le_dados_acomod();

produto le_dados_produto();

fornecedor le_dados_fornecedor();

operador le_dados_operador();

//Variadas

int tamanhoArquivoBin();

int tamanhoArquivoTXT();

int selecionarTipoArquivo();

//Menus

void menuPrincipal();

void menuCliente(int tipoArquivo);

void menuReserva(int tipoArquivo);

//BIN
void salva_cadastro_pessoa_bin(cad_clie saves);

void le_cadastro_pessoa_bin();

void le_todos_cadastro_pessoa_bin();

void alteraBinario();

void removeBinario();

//TXT 

void salva_cadastro_pessoa_txt(cad_clie saves);

void le_cadastro_pessoa_txt();

void le_todos_cadastro_pessoa_txt();

void altera_txt();

void remover_txt();


/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\\\
\
\

//    Variadas

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

//    Coleta dados:
cad_clie le_dados_cad() {

    cad_clie dados;

    setbuf(stdin, NULL);

    printf("\nDigite o seu nome completo: ");

    scanf("%[a-z A-Z][^\n]s", dados.nome);

    setbuf(stdin, NULL);

    /*

    printf("Digite o seu cpf: \n");

    scanf("%f", &dados.cpf);

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

acomodacao le_dados_acomod(cate_aco tipo){
    //variaveis
    acomodacao dados;
    
    //coleta de dados
    setbuf(stdin, NULL);
    printf("Digite o código do quarto: \n");
    scanf("%f", dados.codigo);
    setbuf(stdin, NULL);
    printf("Digite a descrição da acomodação: \n");
    scanf("%[a-z A-Z]s", dados.descri);
    setbuf(stdin, NULL);
    printf("Digite as facilidades da acomodação (como ar condicionado, TV, ...): \n");
    scanf("%[a-z A-Z]s", dados.facilidades);
    
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
    scanf("%[a-z A-Z]s", dados.descricao);
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
    scanf("%[a-z A-Z]%s", dados.nome);
    setbuf(stdin, NULL);
    printf("Digite a razão social do fornecedor: \n");
    scanf("%s", dados.raz_soci);
    setbuf(stdin, NULL);
    printf("Digite a inscrição estadual do fornecedor: \n");
    scanf("%s", dados.inscri_estad);
    setbuf(stdin, NULL);
    printf("Digite o CNPJ do fornecedor: \n");
    scanf("%s", dados.cnpj);
    setbuf(stdin, NULL);
    printf("Digite o telefone do fornecedor: \n");
    scanf("%f", dados.telefone);
    setbuf(stdin, NULL);
    printf("Digite o email do fornecedor: \n");
    scanf("%s", dados.email);
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
    scanf("%[a-z A-Z]", dados.nome);
    setbuf(stdin, NULL);
    printf("Digite o usuário do operador: \n");
    scanf("%s", dados.user);
    setbuf(stdin, NULL);
    printf("Digite a senha do operador: \n");
    scanf("%s", dados.senha);
    setbuf(stdin, NULL);
    printf("Digite qual a permissão de acesso do fornecedor: \n");
    scanf("%f", dados.acesso);
    
    return dados;
}

//MENUS:

void menuPrincipal() {
    int opcao = -1, binOUtxt = 0;

    while (opcao != 0) {
        system("clear");
        printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
        printf("Digite a opcao desejada:\n\n");
        printf("\tClientes - 1\n");
        printf("\tReservas - 2\n");
        printf("\tConfigurações de salvamento - 9\n");
        printf("\tEncerrar - 0\n");

        printf("Opcão: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuCliente(binOUtxt);
                break;
            case 2:
                menuReserva(binOUtxt);
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
                dados = le_dados_cad(binOUtxt);
                if (binOUtxt == 0) {
                    salva_cadastro_pessoa_bin(dados);
                } else {
                    salva_cadastro_pessoa_txt(dados);
                }
                break;
            case 2:
                if (binOUtxt == 0) {
                    le_todos_cadastro_pessoa_bin();
                } else
                    le_todos_cadastro_pessoa_txt();
                break;
            case 3:
                if (binOUtxt == 0) {
                    le_cadastro_pessoa_bin();
                } else {
                    le_cadastro_pessoa_txt();
                }
                break;
            case 4:
                if (binOUtxt == 0) {
                    alteraBinario();
                } else {
                    altera_txt();
                }
                break;
            case 5:
                if (binOUtxt == 0) {
                    removeBinario();
                } else {
                    remover_txt();
                }
                break;
            case 6:
                menuPrincipal();
            default:
                printf("\nNúmero inválido, digite novamente!\n");
                break;
        }
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

//      Bin

void salva_cadastro_pessoa_bin(cad_clie saves) {

    FILE *salva;
    //      abrir arquivo
    salva = fopen("cadastro.bin", "ab");

    if (salva == NULL) {
        printf("\n\t!! Erro de salvamento de Cadastro !! \n");
        return;
    }

    //      Escrever no arquivo
    fwrite(&saves, sizeof (cad_clie), 1, salva);
    printf("\nCadastro realizado com sucesso!\n\n");
    fclose(salva);
}

void le_cadastro_pessoa_bin() {
    //      Variáveis
    FILE *arquivo;
    cad_clie cliente;
    float codigo;
    int encontrado = 0;
    printf("Digite o codigo do cliente que deseja ler: ");
    scanf("%f", &codigo);
    //      abrir arquivo
    arquivo = fopen("cadastro.bin", "rb");

    if (arquivo == NULL) {
        printf("\n\t!! Erro de leitura do Cadastro !! \n");
        exit(1);
    }

    while (fread(&cliente, sizeof (cad_clie), 1, arquivo)) {
        if (cliente.codigo == codigo) {
            encontrado = 1;
            printf("\nCod: %.0f\nNome: %s\n", cliente.codigo, cliente.nome);
            break;
        }
    }
    if (encontrado == 0) {
        printf("Cliente não encontrado!");
    }
    fclose(arquivo);
}

void le_todos_cadastro_pessoa_bin() {
    FILE *arquivo;
    cad_clie cliente;

    arquivo = fopen("cadastro.bin", "rb");

    while (fread(&cliente, sizeof (cad_clie), 1, arquivo)) {
        printf("\t Codigo: %.0f\tNome: %s\n", cliente.codigo, cliente.nome);
    }
    fclose(arquivo);

    getchar();
}

void alteraBinario() {
    //      Variáveis
    FILE *arquivo;
    cad_clie cliente, novo;
    int encontrado = 0;
    float codigo;

    //      abrir arquivo
    arquivo = fopen("cadastro.bin", "rb+wb");

    if (arquivo == NULL) {
        printf("\n\t!! Erro de leitura do Cadastro !! \n");
        exit(1);
    }

    printf("Digite o codigo do cliente que deseja alterar: ");
    scanf("%f", &codigo);

    while (fread(&cliente, sizeof (cad_clie), 1, arquivo)) {
        if (cliente.codigo == codigo) {
            encontrado = 1;
            printf("\nAntigos dados:\nCod: %.0f\nNome: %s\n", cliente.codigo, cliente.nome);

            printf("\nNovos dados:");

            novo.codigo = cliente.codigo;
            novo = le_dados_cad();

            //Volta para o inicio da linha de cadastro desse cliente, permitindo que se altere o cliente correto
            fseek(arquivo, -sizeof (cad_clie), SEEK_CUR);
            //Com o ponteiro no local correto, salva-se os novos dados, substituindo os antigos
            fwrite(&novo, sizeof (cad_clie), 1, arquivo);
            break;
        }

    }
    if (encontrado == 1) {
        printf("Dados alterados com sucesso!");
    } else {
        printf("Cliente não encontrado!");
    }
    fclose(arquivo);
}

void removeBinario() {
    FILE *arquivoAtual, *arquivoTemp;
    cad_clie cliente;
    float codigo;
    int encontrado = 0;

    //tentativa um(passar os dados, exeto o que foi excluido para o arquivo temp e renomea-lo com cadastro.bin):

    arquivoAtual = fopen("cadastro.bin", "rb");
    arquivoTemp = fopen("temporario.bin", "wb");

    printf("Digite o codigo do cliente que deseja excluir: ");
    scanf("%f", &codigo);

    while (fread(&cliente, sizeof (cad_clie), 1, arquivoAtual)) {
        //Le todos os cad clie e os escreve no arquivo temporario, exeto aquele que o código é igual ao que deve ser excluido
        if (cliente.codigo != codigo) {
            fwrite(&cliente, sizeof (cad_clie), 1, arquivoTemp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivoAtual);
    fclose(arquivoTemp);
    //Exclui o arquivo original e renomeia o temporário
    if (encontrado == 1) {
        if (remove("cadastro.bin") == 0 && rename("temporario.bin", "cadastro.bin")) {
            printf("Cliente excluido com sucesso!");
        }
    } else {
        printf("Cliente não encontrado!");
    }
}

int tamanhoArquivoBin() {
    cad_clie clie;
    int tam = 0;
    FILE *arquivo;

    arquivo = fopen("cadastro.bin", "rb");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo de cadastro!");
        return;
    }

    while (fread(&clie, sizeof (cad_clie), 1, arquivo)) {
        tam++;
    }
    return tam;
}

//      TXT

void salva_cadastro_pessoa_txt(cad_clie saves) {

    FILE *salva;

    int end, pessoa;

    //      abrir arquivo

    salva = fopen("cadastro.txt", "a");

    if (salva == NULL) {

        printf("\n\t!! Erro de salvamento de Cadasto !! \n");

        exit(1);
    }

    //      Escrever no arquivo

    pessoa = fprintf(salva, "%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", saves.codigo, saves.nome, saves.cpf, saves.telefone, saves.email, saves.sexo, saves.estado_civil, saves.nascimento);

    if (pessoa < 0) {

        printf("!! Erro em salvar os dados !!");

        exit(1);
    }

    //      Endereço

    end = fprintf(salva, "%0.0f;%s;%s;%s;%0.0f;\n", saves.local.cep, saves.local.cidade, saves.local.bairro, saves.local.rua, saves.local.numero);

    if (end < 0) {

        printf("!! Erro em salvar o endereço !!");

        exit(1);
    }

    //      Fechar arquivo
    fclose(salva);
}

void le_cadastro_pessoa_txt() {

    FILE *le;
    char linha[300], *token;
    char codigo[10];
   
    //      Coletar código
    printf("Digite o codigo do cliente que deseja ler: ");
    scanf("%s", codigo);
   
    //      abrir arquivo
    le = fopen("cadastro.txt", "r");
    if (le == NULL) {

        printf("\n\t!! Erro de leitura de Cadastro !! \n");

        exit(1);
    }
   
    while (fgets(linha, sizeof (linha), le) != NULL) {
        token = strtok(linha, ";");
       
        if (strcmp(codigo, token) == 0) {
            printf("Código: %s\n", token);
            token = strtok(NULL, ";");
            printf("Nome: %s\n", token);
            token = strtok(NULL, ";");
            printf("CPF: %s\n", token);
            token = strtok(NULL, ";");
            printf("Telefone: %s\n", token);
            token = strtok(NULL, ";");
            printf("Email: %s\n", token);
            token = strtok(NULL, ";");
            printf("Sexo: %s\n", token);
            token = strtok(NULL, ";");
            printf("Estado Civil: %s\n", token);
            token = strtok(NULL, ";");
            printf("Nascimento: %s\n", token);
            token = strtok(NULL, ";");
            printf("CEP: %s\n", token);
            token = strtok(NULL, ";");
            printf("Cidade: %s\n", token);
            token = strtok(NULL, ";");
            printf("Bairro: %s\n", token);
            token = strtok(NULL, ";");
            printf("Rua: %s\n", token);
            token = strtok(NULL, ";");
            printf("Número da casa: %s\n", token);
            token = strtok(NULL, ";");
        }
    }
    //      Fechar arquivo
    fclose(le);
   
    getchar();
}

void le_todos_cadastro_pessoa_txt() {
    FILE *ler;
    char linha[500], *token;
    int i = 0;

    ler = fopen("cadastro.txt", "r");
    if (ler == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    //verificar quantas linhas:
    while (fgets(linha, sizeof (linha), ler) != NULL) {
        printf("\n\tCliente %d:\n", i + 1);
        token = strtok(linha, ";");
        printf("Código: %s\n", token);
        token = strtok(NULL, ";");
        printf("Nome: %s\n", token);
        token = strtok(NULL, ";");
        printf("CPF: %s\n", token);
        token = strtok(NULL, ";");
        printf("Telefone: %s\n", token);
        token = strtok(NULL, ";");
        printf("Email: %s\n", token);
        token = strtok(NULL, ";");
        printf("Sexo: %s\n", token);
        token = strtok(NULL, ";");
        printf("Estado Civil: %s\n", token);
        token = strtok(NULL, ";");
        printf("Nascimento: %s\n", token);
        token = strtok(NULL, ";");
        printf("CEP: %s\n", token);
        token = strtok(NULL, ";");
        printf("Cidade: %s\n", token);
        token = strtok(NULL, ";");
        printf("Bairro: %s\n", token);
        token = strtok(NULL, ";");
        printf("Rua: %s\n", token);
        token = strtok(NULL, ";");
        printf("Número da casa: %s\n", token);
        token = strtok(NULL, ";");
        i++;
    }
    
    fclose(ler);
    
    getchar();
}

void altera_txt(){
    FILE *le, *altera;
    char linha[500], *token;
    int tam = 0, i = 0, encontrado = 0;
    float codigo;
    
    printf("Digite o código do cliente que deseja alterar:\n");
    scanf("%f", &codigo);
    
    le = fopen("cadastro.txt", "r");
    if (le == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    //verificar quantas linhas:
    while (fgets(linha, sizeof(cad_clie), le) != NULL) {
        tam++;
    }

    fclose(le);
    
    cad_clie txt[tam];
    
    le = fopen("cadastro.txt", "r");
    if (le == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    while (fgets(linha, sizeof(cad_clie), le) != NULL) {
        token = strtok(linha, ";");
        txt[i].codigo = atof(token);
        token = strtok(NULL, ";");
        strcpy(txt[i].nome, token);
        token = strtok(NULL, ";");
        txt[i].cpf = atof(token);
        token = strtok(NULL, ";");
        txt[i].telefone = atof(token);
        token = strtok(NULL, ";");
        strcpy(txt[i].email, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].sexo, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].estado_civil, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].nascimento, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].local.cidade, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].local.bairro, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].local.rua, token);
        token = strtok(NULL, ";");
        txt[i].local.numero = atof(token);
        
        i++;
    }
    
    fclose(le);
    
    i = 0;
    
    altera = fopen("temp.txt", "a");
    if (altera == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    for (i = 0; i < tam; i++) {
        if (txt[i].codigo == codigo) {
            txt[i] = le_dados_cad();
            fprintf(altera, "%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", txt[i].codigo, txt[i].nome, txt[i].cpf, txt[i].telefone, txt[i].email, txt[i].sexo, txt[i].estado_civil, txt[i].nascimento);
            fprintf(altera, "%0.0f;%s;%s;%s;%0.0f;\n", txt[i].local.cep, txt[i].local.cidade, txt[i].local.bairro, txt[i].local.rua, txt[i].local.numero);
            encontrado = 1;
        }
        
        else {
            fprintf(altera, "%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", txt[i].codigo, txt[i].nome, txt[i].cpf, txt[i].telefone, txt[i].email, txt[i].sexo, txt[i].estado_civil, txt[i].nascimento);
            fprintf(altera, "%0.0f;%s;%s;%s;%0.0f;\n", txt[i].local.cep, txt[i].local.cidade, txt[i].local.bairro, txt[i].local.rua, txt[i].local.numero);
        }
    }
    
    if (encontrado == 0) {
        printf("Cliente não encontrado!\n");
        return;
    }
    else {
        printf("Dados alterados com sucesso!\n");
    }
    
    fclose(altera);
    
    remove("cadastro.txt");
    rename("temp.txt", "cadastro.txt");
}

void remover_txt() {
    FILE *remover, *le;
    char linha[500], *token;
    int tam = 0, i = 0;
    float codigo;
    
    printf("Digite o código do cliente a ser excluido:\n");
    scanf("%f", &codigo);
    
    le = fopen("cadastro.txt", "r");
    if (le == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    //verificar quantas linhas:
    while (fgets(linha, sizeof(cad_clie), le) != NULL) {
        tam++;
    }

    fclose(le);
    
    cad_clie txt[tam];
    
    le = fopen("cadastro.txt", "r");
    if (le == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    while (fgets(linha, sizeof(cad_clie), le) != NULL) {
        token = strtok(linha, ";");
        txt[i].codigo = atof(token);
        token = strtok(NULL, ";");
        strcpy(txt[i].nome, token);
        token = strtok(NULL, ";");
        txt[i].cpf = atof(token);
        token = strtok(NULL, ";");
        txt[i].telefone = atof(token);
        token = strtok(NULL, ";");
        strcpy(txt[i].email, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].sexo, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].estado_civil, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].nascimento, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].local.cidade, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].local.bairro, token);
        token = strtok(NULL, ";");
        strcpy(txt[i].local.rua, token);
        token = strtok(NULL, ";");
        txt[i].local.numero = atof(token);
        
        i++;
    }
    
    fclose(le);
    
    i = 0;
    
    remover = fopen("temp.txt", "a");
    if (remover == NULL) {
        printf("Erro de abertura de arquivo!\n");
        exit(1);
    }
    
    for (i = 0; i < tam; i++) {
        if (txt[i].codigo != codigo) {
            fprintf(remover, "%0.0f;%s;%0.0f;%0.0f;%s;%s;%s;%s;", txt[i].codigo, txt[i].nome, txt[i].cpf, txt[i].telefone, txt[i].email, txt[i].sexo, txt[i].estado_civil, txt[i].nascimento);
            fprintf(remover, "%0.0f;%s;%s;%s;%0.0f;\n", txt[i].local.cep, txt[i].local.cidade, txt[i].local.bairro, txt[i].local.rua, txt[i].local.numero);
        }
    }
    
    fclose(remover);
    
    remove("cadastro.txt");
    rename("temp.txt", "cadastro.txt");
}

int tamanhoArquivoTXT() {
    int tam = 0;
    FILE *arquivo;
    arquivo = fopen("cadastro.txt", "r");
    char linha[500], *token;

    while (fgets(linha, sizeof (linha), arquivo) != NULL) {
        token = strtok(linha, ";");
        for (int i = 0; i < 13; i++) {
            token = strtok(NULL, ";");
        }
        tam++;
    }
    return tam;
}

//MAIN 

int main() {
    // setar linguagem pt-br
    setlocale(LC_ALL, "Portuguese");

    // cria o arquivo binario e txt caso não existam
    fopen("cadastro.bin", "ab");
    fopen("cadastro.txt", "a");

    //menuPrincipal();
    menuPrincipal();

    return 0;
}