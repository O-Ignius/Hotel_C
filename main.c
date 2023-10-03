/////////////////////////////   Bibliotecas  \\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

/////////////////////////////   Structs  \\\\\\\\\\\\\\\\\\\\\\\\\



typedef struct {
    char rua[150], bairro[100], cidade[100], estado[2];

    float numero, cep;

} endereco;

typedef struct {
    float codigo, cpf, telefone;
    char nome[100], email[150], sexo[50], estado_civil[50], nascimento[15];
    endereco local;

} cad_clie;

/////////////////////////////   Indicar subrotinas  \\\\\\\\\\\\\\\\\\\\\\\\\\\\

void menuPrincipal();

void menuCliente(int tipoArquivo);

void menuReserva(int tipoArquivo);

void salva_cadastro_pessoa_bin(cad_clie saves);

void le_cadastro_pessoa_bin();

void le_todos_cadastro_pessoa_bin();

void alteraBinario();

void removeBinario();

void salva_cadastro_pessoa_txt(cad_clie saves);

void le_cadastro_pessoa_txt();

void le_todos_cadastro_pessoa_txt();

void altera_txt();

void remover_txt();

cad_clie transforma_dados();

/////////////////////////////   subrotinas  \\\\\\\\\\\\\\\\\\\\\\\\\
\

//    Variadas

int selecionarTipoArquivo() {
    int tipoArquivo = 0;
    system("clear");
    printf("Digite 0 para salvar as informações em arquivos binários e 1 para arquivos txt: ");
    scanf("%d", &tipoArquivo);
    while (tipoArquivo != 0 && tipoArquivo != 1) {
        printf("Número inválido, digite novamente: ");
        scanf("%d", &tipoArquivo);
    }
    printf("Tipo de arquivo alterado com sucesso!");
    return tipoArquivo;
}

cad_clie le_dados_cad() {
    cad_clie dados;

    printf("Digite o código: \n");

    scanf("%f", &dados.codigo);

    setbuf(stdin, NULL);

    printf("Digite o seu nome completo: \n");

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

void menuPrincipal(){
    int opcao = -1, binOUtxt = 1;
    

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

        switch (opcao)
        {
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
            scanf("%d",&opcao);
            break;
        } 
    }
    
}

void menuCliente(int tipoArquivo){
    int opcao = 0, binOUtxt = tipoArquivo;
    cad_clie dados;   
        while (opcao != 5) {
            system("clear");
            setbuf(stdin, NULL);

            printf("\n\n///// HOTELARIA - MENU \\\\\n\n\n");
            printf("Digite a opcao desejada:\n\n");
            printf("\tCadastro de cliente - 1\n");
            printf("\tListar todos os cliente - 2\n");
            printf("\tLista dados de um cliente - 3\n");
            printf("\tAlterar dados cliente - 4\n");
            printf("\tExcluir dados de cliente - 5\n");
            printf("\tVoltar ao menu inicial - 6\n");

            printf("Opcão: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                dados = le_dados_cad();
                if (binOUtxt == 0) {
                    salva_cadastro_pessoa_bin(dados);
                } else {
                    salva_cadastro_pessoa_txt(dados);
                }
                break;
            case 2:
                if (binOUtxt == 0) {
                    le_todos_cadastro_pessoa_bin();
                } else {
                    le_todos_cadastro_pessoa_txt();
                }
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

void menuReserva(int tipoArquivo){
    int opcao, binOUtxt = tipoArquivo;
    cad_clie dados;
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

        while (opcao != 5) {

        }
        menuPrincipal();
}

//      Bin

//  Clientes
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
    scanf("%f",&codigo);
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
    if(encontrado == 0){
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
    scanf("%f",&codigo);

    while (fread(&cliente, sizeof (cad_clie), 1, arquivo)) {
        if (cliente.codigo == codigo) {
            encontrado = 1;
            printf("\nAntigos dados:\nCod: %.0f\nNome: %s\n", cliente.codigo, cliente.nome);

            printf("\nNovos dados:");

            novo.codigo = cliente.codigo;
            novo = le_dados_cad();

            //Volta para o inicio da linha de cadastro desse cliente, permitindo que se altere o cliente correto
            fseek(arquivo, -sizeof(cad_clie), SEEK_CUR);
            //Com o ponteiro no local correto, salva-se os novos dados, substituindo os antigos
            fwrite(&novo, sizeof (cad_clie), 1, arquivo);
            break;
        }
        
    } 
    if(encontrado == 1){
        printf("Dados alterados com sucesso!");
    } else{
        printf("Cliente não encontrado!");
    }
    fclose(arquivo);
}

int tamanhoArquivoBin(){
    cad_clie clie;
    int tam = 0;
    FILE *arquivo;

    arquivo = fopen("cadastro.bin","rb");

    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo de cadastro!");
        exit(1);
    }

    while(fread(&clie,sizeof(cad_clie),1,arquivo)){
        tam++;
    }
    return tam;
}

void removeBinario() {
    FILE *arquivoAtual, *arquivoTemp;
    cad_clie cliente;
    float codigo;
    int encontrado = 0;

    //tentativa um(passar os dados, exeto o que foi excluido para o arquivo temp e renomea-lo com cadastro.bin):
    arquivoAtual = fopen("C:\\Users\\ivan-\\Desktop\\Projetos\\NetBeans\\C\\Hotel\\cadastro.bin","rb");
    arquivoTemp = fopen("C:\\Users\\ivan-\\Desktop\\Projetos\\NetBeans\\C\\Hotel\\temporario.bin","wb");

    printf("Digite o codigo do cliente que deseja excluir: ");
    scanf("%f", &codigo);

    while(fread(&cliente,sizeof(cad_clie),1,arquivoAtual)){
        if(cliente.codigo != codigo){
            fwrite(&cliente,sizeof(cad_clie),1,arquivoTemp);
        } else {
            encontrado = 1;
        }
    }
    fclose(arquivoAtual);
    fclose(arquivoTemp);
    
    if(encontrado == 1){
        if(remove("C:\\Users\\ivan-\\Desktop\\Projetos\\NetBeans\\C\\Hotel\\cadastro.bin") == 0 && rename("C:\\Users\\ivan-\\Desktop\\Projetos\\NetBeans\\C\\Hotel\\temporario.bin", "C:\\Users\\ivan-\\Desktop\\Projetos\\NetBeans\\C\\Hotel\\cadastro.bin")){
            printf("Cliente excluido com sucesso!");
        }
    } else{ 
        printf("Cliente não encontrado!");
    }
    
    getchar();
    //tentativa dois(passar os dados para um vetor, depois sobreescrever o cadastro.bin com os dados do vetor):
    /*
        int tamanho = tamanhoArquivo();
        int i = 0;
        cad_clie vetorCliente[tamanho];
        
        float codigo;
        int encontrado = 0;

        arquivoAtual = fopen("cadastro.bin","rb");
        
        if(arquivoAtual == NULL || arquivoTemp == NULL){
            printf("\nErro ao abrir os arquivos de cadastros!");
            return;
        }

        printf("Digite o codigo do cliente que deseja excluir: ");
        scanf("%f", &codigo);
        //Passando os valores para um vetor e reescrevendo no arquivo
        
        while(fread(&cliente,sizeof(cad_clie),1,arquivoAtual)){
            if(cliente.codigo != codigo){
                vetorCliente[i].codigo = cliente.codigo;
                vetorCliente[i].cpf = cliente.cpf;
                
                    //vetorCliente[i].email = cliente.email;
                    //vetorCliente[i].estado_civil = cliente.estado_civil;
                
            } else {
                encontrado = 1;
            }
            i++;
        }

    fclose(arquivoAtual);
    arquivoAtual = fopen("cadastro.bin", "wb");
    
    for (i = 0; i < tamanho; i++)
    {
        fwrite(&vetorCliente[i], sizeof(cad_clie),1,arquivoAtual);
    }
    printf("\nExcluido com sucesso!");
    fclose(arquivoAtual);
    */
}

//  Reserva

//      TXT

//  Clientes
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

//  Reserva



int main() {
    // setar linguagem pt-br
    setlocale(LC_ALL, "Portuguese");

    // limpa arquivo
    // removeBinario();

    // cria o arquivo binario caso não tenha
    //FILE *arq = fopen("cadastro.bin", "ab");
    
    // cria o arquivo texto caso não tenha
    FILE *txt = fopen("cadastro.txt", "a");

    //menuPrincipal();
    menuPrincipal();
    return 0;
}